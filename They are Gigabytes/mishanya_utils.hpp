#pragma once

#include <string>
#include <vector>


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

namespace mishanya
{
	void RemoveFileExtension(std::string& file_name);
	bool ReadFile(std::string const& pFileName, std::string& outFile);
	std::string GetDirFromFilename(const std::string& Filename);
	std::vector<std::string> GetFileList(std::string directory);
	std::string GetFileFromPath(const std::string& file_path);
}