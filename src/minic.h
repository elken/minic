#ifndef MINIC_H
#define MINIC_H
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstddef>

class CPU
{

public:
    CPU();
    ~CPU();

    char R0;
    char R1;

    bool status;
    bool overflow;
    bool underflow;

    char PC;
    char IR;

    int tmp;

    std::vector<std::string> LUT = {"LOAD0", "LOAD1", "ADD", "SUB", "STORE0", "STORE1"};

    void reset();
    void execute(std::vector<char *>& prog);
    std::vector<char *> load(std::ifstream &stream);
    void fault();
    void dumpRegisters();
    void load0(std::vector<char *>& prog);
    void load1(std::vector<char *>& prog);
    void add();
    void sub();
    void store0(std::vector<char *>& prog);
    void store1(std::vector<char *>& prog);
};

enum InstructionSet
{
    LOAD0 = 0,
    LOAD1,
    ADD,
    SUB,
    STORE0,
    STORE1
};

#endif //MINIC_H
