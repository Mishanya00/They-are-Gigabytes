#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>


namespace mishanya
{
    bool ReadFile(std::string const & pFileName, std::string & outFile)
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
    std::string GetDirFromFilename(const std::string& Filename)
    {
        // Extract the directory part from the file name
        std::string::size_type SlashIndex;

    #ifdef _WIN64
        SlashIndex = Filename.find_last_of("\\");

        if (SlashIndex == -1) {
            SlashIndex = Filename.find_last_of("/");
        }
    #else
        SlashIndex = Filename.find_last_of("/");
    #endif

        std::string Dir;

        if (SlashIndex == std::string::npos) {
            Dir = ".";
        }
        else if (SlashIndex == 0) {
            Dir = "/";
        }
        else {
            Dir = Filename.substr(0, SlashIndex);
        }

        return Dir;
    }
}