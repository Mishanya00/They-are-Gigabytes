#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>


namespace mishanya
{
    bool ReadFile(std::string& pFileName, std::string& outFile)
    {
        std::ifstream f(pFileName);

        bool ret = false;

        if (f.is_open()) {
            std::string line;
            while (getline(f, line)) {
                outFile.append(line);
                outFile.append("\n");
            }

            f.close();

            ret = true;
        }

        return ret;
    }
}