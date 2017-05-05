#!/usr/bin/env python3
import sys
import re
import subprocess
from decimal import *

def header():
    print("MATRUSHKA VIRTUAL MACHINE\n")

def usage():
    print("Usage: ./mvm.py file.mka")

header()

if (len(sys.argv)!=2):
    usage()
    exit()

ircode = sys.argv[1]

#Crea
## This Virtual Machine es Multipass
# We first do one pass to build some structures
# Then we interpret the code line by line

#Global Vars
debug = False
lineno = 0
eip = 0
esp = []
function_address = {}
function_era = {}
stack = []    # For reference, Linux allow stacks up to 2 megabytes of size
globalstack = [0 for x in range(100)] # For reference, Linux allow stacks up to 2 megabytes of size
callstack = []
esptmp = 0
array_offset = 0
marray = []

#Auxiliary Functions
# Esta funcion recibe un operando que puede ser
# una constante o una direccion a una variable o vector o matriz
# El que quiero utilizar el valor no le interesa donde esta almacenado
# Le manda la chamba a esta funcion
def getValue(operand):
    currentstack_base = sum(esp[:-1])   
       
    if operand.startswith("("):
        index = re.search('([\d]+)',operand).group(1)
        offset = int(index) - 1
        if operand.startswith("(%STACK"):
            operand = stack[currentstack_base+offset]
        else:
            operand = globalstack[offset]
    elif operand.startswith("["):
        if(len(marray)>0):
            multi_metadata = marray.pop()
            dim = int(multi_metadata.split()[3])
            filas = int(multi_metadata.split()[1])
            columnas = int(multi_metadata.split()[2])
            ary_offset = (dim*filas)+columnas
        else:
            ary_offset = array_offset
        index = re.search('([\d]+)',operand).group(1)
        offset = int(index) - 1
        if operand.startswith("[%STACK"):
            operand = stack[currentstack_base+offset+ary_offset]
        else:
            operand = globalstack[offset+ary_offset]
    
    if (str(operand)=="true"):
        operand = str(1)
    elif (str(operand)=="false"):
        operand = str(0)
    
    return operand


def save_in(address,value):
    if address.startswith("["):
        if(len(marray)>0):
            multi_metadata = marray.pop()
            dim = int(multi_metadata.split()[3])
            filas = int(multi_metadata.split()[1])
            columnas = int(multi_metadata.split()[2])
            ary_offset = dim*filas+columnas
        else:
            ary_offset = array_offset
    
    currentstack_base = sum(esp[:-1])
    index = re.search('([\d]+)',address).group(1)
    offset = int(index) - 1
    if address.startswith("(%STACK"):
        stack[currentstack_base+offset] = str(value)
    elif address.startswith("(%GLOBAL"):
        globalstack[offset] = str(value)
    elif address.startswith("[%STACK"):
        stack[currentstack_base+offset+ary_offset] = str(value)
    else:
        globalstack[offset+ary_offset] = str(value)
    
if(debug):
    print("\nFirst pass\n-----------------------------\n")

#First decrypt in case it is encrypted 
ceropass = open(ircode,'r').readlines()
while("ASKP" in ceropass[0]):
    regs =re.findall(r'(\S+)', ceropass[0])
    cipher = regs[1]
    print("This software is encrypted with %s" % cipher)
    if(cipher=="DES"):
        cipher = "-des-cbc"
    elif(cipher=="AES"):
        cipher = "-aes-256-cbc"
    elif(cipher=="BLOWFISH"):
        cipher = "-bf-cbc"
    else:
        sys.exit();

    password = input('Enter the passphrase: ')
    proc = subprocess.Popen(["openssl","enc","-a",cipher,"-d","-k",password], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    ciphertext = "\n".join(ceropass[1:])    
    try:
        proc.stdin.write(str.encode(ciphertext))
        proc.stdin.close()
        result = proc.stdout.read()
        ceropass = result.decode().splitlines(1)
    except:
        print("Couldn't decrypt software")
        sys.exit()  
  
# In the first pass we build the function_adress and function_era structures
firstpass = ceropass
for line in iter(firstpass):
    lineno = lineno + 1
    if line.startswith(".data"):
        function_address["!QUIT"] = lineno-1
    if line.startswith("_"):
        function_name = re.search('_(.*):', line).group(1)
        function_address[function_name] = lineno-1
        if(debug):
            print("A function %s at location %s" % (function_name,lineno-1))
    if line.startswith("era_size_"):
        regs = re.search('era_size_(.*):\s*(\d+)',line)
        function_name = regs.group(1)
        era_size = regs.group(2)
        function_era[function_name] = int(era_size)
        if(debug):
            print("A function %s with %s variables" % (function_name,era_size))

if(debug):
    print("\nSecond pass\n-----------------------------\n")

# In the second pass we actually execute the code
# We keep advacing the EIP until we reach the .data section
secondpass = ceropass

while(".data:" not in (secondpass[eip])):
    instruction = secondpass[eip]
    
    #Python no maneja SWITCH/CASE structures. Tendra que ser un good old fashion if/elseif
    
    if instruction == '\n':
        # THIS WORKS BASICALLY LIKE A NOP INSTRUCTION
        # WE JUST INCREMENT THE EIP
        print("%3s: NOP" % (eip))
        eip += 1
    elif instruction.startswith("_"):
        # Ignore, labels are just for human consumers
        nextstack_base = sum(esp)
        currentstack_base = sum(esp[:-1])
        
        if(debug):
            print("%3s: Starting the function %s" % (eip, instruction[1:-2]))
            print("%3s: CURRENT_STACK_FRAME: %s NEXT_STACK_FRAME %s" % (eip, currentstack_base, nextstack_base))

        eip += 1
    elif instruction.startswith("ERAS"):
        regs = re.search('era_size_(.*)', instruction)
        function_name = regs.group(1)[:-1]
        era_size = function_era[function_name]
        esptmp = era_size
        if(debug):
            print("%3s: Allocating %s spaces for %s" % (eip, era_size,function_name))
        eip += 1
    elif instruction.startswith("CALL"):
        regs = re.search('CALL _(.*)', instruction)
        function_name = regs.group(1)
        jmp = function_address[function_name]
        esp.append(esptmp)
        # When a function starts we allocate the space needed for it
        while(len(stack) < sum(esp)):
            stack.append(0)
            
        if(debug):
            print("%3s: Jumping to function %s at address %s" % (eip, function_name, jmp))
        if function_name != "main":
            callstack.append(eip+1)
        else:
            callstack.append(function_address["!QUIT"])
        eip = jmp
    elif instruction.startswith("PUSH"):
        regs = re.search('PUSH (.*)', instruction)
        argument = regs.group(1)
        nextstack_base = sum(esp)
        currentstack_base = sum(esp[:-1])
        
        argument = getValue(argument)
        stack.append(argument)
    
        if(debug):
            print("%3s: Pushing %s" % (eip, argument))
        eip = eip + 1
    elif instruction.startswith("AVER"):
        regs =re.findall(r'(\S+)', instruction)
        operand = regs[1]
        
        if(debug):
            print("%3s: %s"  % (eip, instruction.strip()))
        
        array_offset = getValue(operand)
        array_offset = int(array_offset)
        if(debug):
            print("%3s: AVER %s"  % (eip, array_offset))
        eip = eip + 1
    elif instruction.startswith("MVER"):
        marray.append(instruction.strip())
        if(debug):
            print("%3s: %s"  % (eip, instruction.strip()))
        eip = eip + 1
    elif instruction.startswith("SADD"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
                
        operation = (operandB[0:-1] + operandA[1:])
        
        save_in(result,operation)
        eip = eip + 1;
    elif instruction.startswith("IADD"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB + operandA
        
        save_in(result,operation)
        eip = eip + 1
    elif instruction.startswith("ISUB"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
                
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB - operandA
        
        if(debug):
            print("%3s: ISUB %s = %s - %s" % (eip, operation, operandB, operandA))
        
        save_in(result,operation)
        eip = eip + 1;    
    elif instruction.startswith("IMUL"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB * operandA
        
        save_in(result,operation)
        eip = eip + 1;
    elif instruction.startswith("IDIV"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB // operandA
        
        save_in(result,operation)
        eip = eip + 1;
    elif instruction.startswith("DADD"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB + operandA
        
        save_in(result,operation)
        eip = eip + 1;    
    elif instruction.startswith("DSUB"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB - operandA
        
        save_in(result,operation)
        eip = eip + 1;     
    elif instruction.startswith("DMUL"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB * operandA
        
        save_in(result,operation)
        eip = eip + 1;
    elif instruction.startswith("DDIV"):
        # ISUB OPERANDA OPERANDB
        # a -1; ISUB 1 (%GLOBALS+1) (%STACK+4)
        # B - A
            
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = operandB / operandA
        
        save_in(result,operation)
        eip = eip + 1;
    elif instruction.startswith("ORVL"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = bool(Decimal(operandA))
        operandB = getValue(operandB)
        operandB = bool(Decimal(operandB))
        
        operation = (operandA|operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("ANDV"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = bool(Decimal(operandA))
        operandB = getValue(operandB)
        operandB = bool(Decimal(operandB))
        
        operation = (operandA&operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("EQLV"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = (operandA==operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("NEQL"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandA = Decimal(operandA)
        operandB = getValue(operandB)
        operandB = Decimal(operandB)
        
        operation = (operandA!=operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("EQST"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = (operandA==operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("NEQS"):
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = (operandA!=operandB)
        
        save_in(result,Decimal(operation))
        eip = eip + 1
    elif instruction.startswith("ENDF"):
        # This opcode is for when we hit the end of a fuction without a return value
        # Clean the stack
        while(len(stack) > sum(esp[:-1])):
            stack.pop()
        esp.pop()
        
        if(debug):
            print("%3s: GLOBALSTACK: %s" % (eip, globalstack))
            print("%3s: STACK: %s" % (eip, stack))
            print("%3s: CALLSTACK %s" % (eip, callstack))
        
        stack.append(0)
        
        eip = callstack.pop()
    elif instruction.startswith("RETV"):
        returnvalue = re.search('RETV\s(.*)',instruction).group(1)
        
        #Case 1 we get a reference to somewhere in the stack
        if returnvalue.startswith("("):
            index = re.search('([\d]+)',returnvalue).group(1)
            offset = int(index) - 1
            if returnvalue.startswith("(%STACK"):
                returnvalue = stack[currentstack_base+offset]
            else:
                returnvalue = globalstack[offset]
        if(debug):
            print("%3s: GLOBALSTACK: %s" % (eip, globalstack))
            print("%3s: STACK: %s" % (eip, stack))
            print("%3s: CALLSTACK %s" % (eip, callstack))
        
        # Clean the stack
        while(len(stack) > sum(esp[:-1])):
            stack.pop()
        esp.pop()

        # Do one last push before returning to instruction
        stack.append(returnvalue)
        if(debug):
            print("%3s: RETV %s" % (eip, returnvalue))
            print("%3s: GLOBALSTACK: %s" % (eip, globalstack))
            print("%3s: STACK: %s" % (eip, stack))
            print("%3s: CALLSTACK %s" % (eip, callstack))
        
        
        eip = callstack.pop()
    elif instruction.startswith("POPV"):
        variable_address = re.search('POPV\s(.*)',instruction).group(1)
        currentstack_base = sum(esp[:-1])
        returnvalue = stack.pop()
        
        #El argumento de POP siempre es una direccion del stack local
        #no hay necesidad de checar por gloabl
        index = re.search('([\d]+)',variable_address).group(1)
        offset = int(index) - 1
        stack[currentstack_base+offset] = returnvalue
        if(debug):
            print("%3s: POPV %s, STACK: %s" % (eip, returnvalue, stack))
            nextstack_base = sum(esp)
            currentstack_base = sum(esp[:-1])
            print("%3s: CURRENT_STACK_FRAME: %s NEXT_STACK_FRAME %s" % (eip, currentstack_base, nextstack_base))
        eip = eip + 1
    elif instruction.startswith("MOVE"):
        # Move es la operacion de asignacion
        # Tiene dos operandos. A y B. 
        # B = A
        # B puede ser referencia local o global
        # A puede ser constante, referencia local o global
        
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        
        operandA = getValue(operandA)
        
        save_in(operandB, operandA)
            
        if(debug):
            print("%3s: MOVE %s %s" % (eip, operandA, operandB))
        eip = eip + 1        
    elif instruction.startswith("LTVL"):
        # a<9999 = LTVL 9999 (%GLOBALS+1) (%STACK+2)
        #B<A
        
        regs =re.findall(r'(\S+)', instruction)
        operandA = str(regs[1])
        operandB = str(regs[2])
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = Decimal(operandB) < Decimal(operandA)
        
        save_in(result,Decimal(operation))
        eip = eip +1
    elif instruction.startswith("LTEV"):
        # a<9999 = LTVL 9999 (%GLOBALS+1) (%STACK+2)
        #B<A
        
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = Decimal(operandB) <= Decimal(operandA)
        
        save_in(result,Decimal(operation))
        eip = eip +1
    elif instruction.startswith("GTVL"):
        # num>5000 = GTL 5000 (%GLOBALS+1) (%STACK+3)
        # B>A
        
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = Decimal(operandB) > Decimal(operandA)
                
        save_in(result,Decimal(operation))
        eip = eip +1
    elif instruction.startswith("GTEV"):
        # num>5000 = GTL 5000 (%GLOBALS+1) (%STACK+3)
        # B>A
        
        regs =re.findall(r'(\S+)', instruction)
        operandA = regs[1]
        operandB = regs[2]
        result = regs[3]
        
        operandA = getValue(operandA)
        operandB = getValue(operandB)
        
        operation = Decimal(operandB) >= Decimal(operandA)
                
        save_in(result,Decimal(operation))
        eip = eip +1
    elif instruction.startswith("GTOF"):
        regs =re.findall(r'(\S+)', instruction)
        test = regs[1]
        jmp = int(regs[2]) - 1
        
        test = getValue(test)
        test = int(test)
        test = bool(test)
                
        if(test):
            eip = eip+1
        else:
            eip = jmp
    elif instruction.startswith("GOTO"):
        regs =re.findall(r'(\S+)', instruction)
        jmp = int(regs[1]) - 1
        
        #unconditional jump bro
        eip = jmp       
    elif instruction.startswith("IGET"):
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('IGET (.*)', instruction)
        
        operandA = regs.group(1)
        s = input('--> ')
        s = int(s)

        save_in(operandA,s)
        eip = eip + 1;
    elif instruction.startswith("DGET"):
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('DGET (.*)', instruction)
        
        operandA = regs.group(1)
        s = input('--> ')
        s = Decimal(s)

        save_in(operandA,s)
        eip = eip + 1;
    elif instruction.startswith("SGET"):
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('SGET (.*)', instruction)
        
        operandA = regs.group(1)
        s = input('--> ')
        s = str(s)

        save_in(operandA,s)
        eip = eip + 1;
    elif instruction.startswith("BGET"):
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('BGET (.*)', instruction)
        
        operandA = regs.group(1)
        s = input('--> ')
        if (str(s)=="true"):
            s = str(1)
        elif (str(s)=="false"):
            s = str(0)
        save_in(operandA,s)
        eip = eip + 1;
    elif instruction.startswith("IPUT"):
        # IPUT operandA
        # A can be either a constant or a reference
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('IPUT (.*)', instruction)
        
        operandA = regs.group(1)
        operandA = getValue(operandA)

        print(int(Decimal(operandA)))
        eip = eip + 1;
    elif instruction.startswith("DPUT"):
        # IPUT operandA
        # A can be either a constant or a reference
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('DPUT (.*)', instruction)
        
        operandA = regs.group(1)
        operandA = getValue(operandA)
        operandA = Decimal(operandA)

        print(operandA)
        eip = eip + 1;
    elif instruction.startswith("BPUT"):
        # IPUT operandA
        # A can be either a constant or a reference
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))
        
        regs = re.search('BPUT (.*)', instruction)
        
        operandA = regs.group(1)
        operandA = getValue(operandA)
        operandA = bool(int(operandA))

        print(operandA)
        eip = eip + 1;
    elif instruction.startswith("SPUT"):
        # IPUT operandA
        # A can be either a constant or a reference
        if(debug):
            print("%3s: %s" % (eip, instruction.strip()))

        regs = re.search('SPUT (.*)', instruction)

        operandA = regs.group(1)
        operandA = getValue(operandA)
        operandA = str(operandA)
            
        print(operandA[1:-1])
        eip = eip + 1;    
    else:
        print("%3s: ERROR NO ENTIENDO INSTRUCCION\n\n%s" % (eip,instruction.strip()))
        exit()

exit_status = stack.pop()

print("\nExited program with status: %s" % exit_status)