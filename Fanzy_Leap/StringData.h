#ifndef STRING_DATA_HPP
#define STRING_DATA_HPP

#include <clocale>
#include <string>
#include <vector>
#include "GNU/libintl.h"

class StringData
{
private:
	std::vector<std::string> data;
public:
	StringData(const std::string& message);
	std::string operator [](const unsigned int& n) const;
};

#endif

