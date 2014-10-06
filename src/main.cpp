#include "minic.cpp"
#include <fstream>
#include <string>
#include <cstdio>

int main()
{
  m::CPU* c = new m::CPU();
  
  std::vector<byte> inst;
  std::ifstream asm_f("test.asm");

  if(asm_f.is_open())
  {
    std::string line;
    while(getline(asm_f, line))
    {
      byte l = *line.c_str();
      std::cout << l << std::endl;
      inst.push_back(line.c_str());
    }
    std::cout << "Loaded." << std::endl;
    c->execute(inst);
    std::cout << "Executed." << std::endl;

    for(auto i:inst)
    {
      std::cout << "[" << static_cast<int>((i)) << "]" << std::endl;
    }
  }

  std::cout << "Done." << std::endl;
  
  delete c;
  asm_f.close();

  return 0;
}
