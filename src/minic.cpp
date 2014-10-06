#include "minic.h"

CPU::CPU()
{
    reset();
}

CPU::~CPU(){}

void CPU::reset()
{
    tmp = R0 = R1 = IR = PC = 0;

    status = true;
    overflow = underflow = false;
}

void CPU::execute(std::vector<char>& prog)
{
    reset();

    if ( prog.size() > 256)
    {
        std::cout << "More than 255 instructions, trying to run " << prog.size() << std::endl;
    }
    else
    {
        while (PC < prog.size())
        {
            IR = prog[PC];
            PC++;

        switch(IR)
        {
            case LOAD0:
                load0(prog);
	            break;
            case LOAD1:
	            load1(prog);
	            break;
            case ADD:
	            add();
            	break;
            case SUB:
            	sub();
            	break;
            case STORE0:
            	store0(prog);
            	break;
            case STORE1:
            	store1(prog);
            	break;
            default:
	            fault();
	            return;
        }
            if(overflow)
            {
	            std::cout << "Overflow, halting." << std::endl;
	            return;
            }

            if(underflow)
            {
	            std::cout << "Underflow, halting." << std::endl;
	            return;
            }
        }
    }
}

std::vector<char> CPU::load(std::ifstream &stream)
{
    std::vector<char> inst;
    if(stream.is_open()) {
        std::string op;
        int x;
        while (stream >> op) {
            if (op == "LOAD0") {
                stream.seekg(-5, std::ios::cur);
                stream >> op >> x;
                std::cout << "opcode: " << op << "\nvalue: " << x << std::endl;
                inst.push_back(LOAD0);
                inst.push_back(x);
            }
            else if (op == "LOAD1") {
                stream.seekg(-5, std::ios::cur);
                stream >> op >> x;
                std::cout << "opcode: " << op << "\nvalue: " << x << std::endl;
                inst.push_back(LOAD1);
                inst.push_back(x);
            }
            else if (op == "ADD") {
                std::cout << "opcode: " << op << std::endl;
                inst.push_back(ADD);
            }
            else if (op == "SUB") {
                std::cout << "opcode: " << op << std::endl;
                inst.push_back(SUB);
            }
            else if (op == "STORE0") {
                stream.seekg(-6, std::ios::cur);
                stream >> op >> x;
                std::cout << "opcode: " << op << "\nvalue: " << x << std::endl;
                inst.push_back(STORE0);
                inst.push_back(x);
            }
            else if (op == "STORE1") {
                stream.seekg(-6, std::ios::cur);
                stream >> op >> x;
                std::cout << "opcode: " << op << "\nvalue: " << x << std::endl;
                inst.push_back(STORE1);
                inst.push_back(x);
            }
            else
                std::cout << "Opcode [" << op << "] is not part of this instruction set." << std::endl;
        }
    }
    return inst;
}
void CPU::fault()
{
    status = false;
    std::cout << "Fault at: [" << PC << "]" << std::endl;
    dumpRegisters();
}

void CPU::dumpRegisters()
{
    printf("0: [%hhu]\n1: [%hhu]\nStatus: [%s]\nOverflow: [%s]\nUnderflow: [%s]\nPC: %hhu\nIR: [%hhu]\ntmp: [%d]\n", R0, R1, status?"true":"false", overflow?"true":"false", underflow?"true":"false", PC, IR, tmp);
}

void CPU::load0(std::vector<char>& prog)
{
    R0 = prog[PC];
    PC++;
}

void CPU::load1(std::vector<char>& prog)
{
    R1 = prog[PC];
    PC++;
}

void CPU::add()
{
    try
    {
        R0 += R1;
    }
    catch(char b)
    {
        std::cout << "Overflow caught" << std::endl;
    }
}

void CPU::sub()
{
    try
    {
        R0 -= R1;
    }
    catch(char b)
    {
        std::cout << "Underflow caught" << std::endl;
    }
}

void CPU::store0(std::vector<char>& prog)
{
    prog[PC] = R0;
    PC++;
}

void CPU::store1(std::vector<char>& prog)
{
    prog[PC] = R1;
    PC++;
}

