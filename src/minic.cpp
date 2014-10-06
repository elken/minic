#include "minic.h"

m::CPU::CPU()
{
  reset();
}

m::CPU::~CPU(){}

void m::CPU::reset()
{
  tmp = R0 = R1 = PC = IR = 0;
  status = true;
  overflow = underflow = false;
}

void m::CPU::execute(std::vector<byte>& prog)
{
  reset();

  if ( prog.size() > 256)
  {
    std::cout << "More than 255 instructions" << std::endl;
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
      case SUBTRACT:
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

void m::CPU::fault()
{
  status = false;
  std::cout << "Fault at: [" << PC << "]" << std::endl;
  dumpRegisters();
}

void m::CPU::dumpRegisters()
{
  printf("0: [%hhu]\n1: [%hhu]\nStatus: [%s]\nOverflow: [%s]\nUnderflow: [%s]\nPC: %hhu\nIR: [%hhu]\ntmp: [%d]\n", R0, R1, status?"true":"false", overflow?"true":"false", underflow?"true":"false", PC, IR, tmp);
}

void m::CPU::load0(std::vector<byte>& prog)
{
  R0 = prog[PC];
  PC++;
}

void m::CPU::load1(std::vector<byte>& prog)
{
  R1 = prog[PC];
  PC++;
}

void m::CPU::add()
{
  try
  {
    R0 += R1;
  }
  catch(byte b)
  {
    std::cout << "Overflow caught" << std::endl;
  }
}

void m::CPU::sub()
{
  try
  {
    R0 -= R1;
  }
  catch(byte b)
  {
    std::cout << "Underflow caught" << std::endl;
  }
}

void m::CPU::store0(std::vector<byte>& prog)
{
  prog[PC] = R0;
  PC++;
}

void m::CPU::store1(std::vector<byte>& prog)
{
  prog[PC] = R1;
  PC++;
}
