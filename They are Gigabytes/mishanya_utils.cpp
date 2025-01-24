#include "mishanya_utils.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


namespace mishanya
{
    void RemoveFileExtension(std::string& file_name)
    {
        int k = file_name.size() - 1;
        while (file_name[k] != '.' && k >= 0) {
            file_name.resize(k);
            --k;
        }
        if (k >= 0 && file_name[k] == '.') {
            file_name.resize(k);
        }
    }

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

    std::string GetFileFromPath(const std::string& file_path)
    {
        std::string file_name;
        int k = file_path.size() - 1;
        while (file_path[k] != '/' && file_path[k] != '\\')
        {
            file_name += file_path[k];
            --k;
        }
        std::reverse(file_name.begin(), file_name.end());
        
        return file_name;
    }

    std::vector<std::string> GetFileList(std::string directory)
    {
        namespace fs = std::filesystem;
        std::vector<std::string> file_list;

        try {
            for (const auto& entry : fs::directory_iterator(directory)) {

                if (entry.is_regular_file()) {
                    file_list.push_back(entry.path().string());
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        return file_list;
    }
}