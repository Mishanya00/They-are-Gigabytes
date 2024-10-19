#pragma once

#include <string>


#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

namespace mishanya
{
	bool ReadFile(std::string const& pFileName, std::string& outFile);
}