#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <vector>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

namespace Utils
{
	std::string doubleToString(double val);
    double stringToDouble(std::string str);
    // splits with a delimiter, keep the delimiter or not -> keepChar
    unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch, bool keepChar);
    // splits with multiple delimiters, keep all the delimiter
    unsigned int split(const std::string &txt, std::vector<std::string> &strs, std::string chars);
}

#endif
