#include "minic.h"

int main(int argc, char* argv[])
{
    CPU* c = new CPU();

    if(argc == 2)
    {
        std::ifstream asm_f(argv[1]);

        std::vector<char> inst = c->load(asm_f);

        std::cout << "Loaded." << std::endl;
        c->execute(inst);
        std::cout << "Executed." << std::endl;

        for(auto j:inst)
        {
            std::cout << "[" << static_cast<int>(j) << "]" << std::endl;
        }


        std::cout << "Done." << std::endl;

        delete c;
        asm_f.close();

        return 0;
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <filename> " << std::endl;
    }

}
