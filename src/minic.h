#ifndef MINIC_H
#define MINIC_H
#include <iostream>
#include <cstdio>
#include <vector>

typedef unsigned char byte;

namespace m
{
    class CPU
    {
     public:
      CPU();
      ~CPU();

      byte R0;
      byte R1;

      bool status;
      bool overflow;
      bool underflow;

      byte PC;
      byte IR;

      int tmp;

      void reset();
      void execute(std::vector<byte>& prog);
      void fault();
      void dumpRegisters();
      void load0(std::vector<byte>& prog);
      void load1(std::vector<byte>& prog);
      void add();
      void sub();
      void store0(std::vector<byte>& prog);
      void store1(std::vector<byte>& prog);
    };

    enum InstructionSet
    {  
      LOAD0 = 0,
      LOAD1,
      ADD,
      SUBTRACT,
      STORE0,
      STORE1
    };
}

#endif //MINIC_H
