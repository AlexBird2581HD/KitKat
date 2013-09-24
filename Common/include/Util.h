#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
	/*
	 * Returns the contents of a text file as a string
	 */
	static std::string ReadFile(std::string fileName);
private:
	Util(const Util& util);
	Util();
	~Util();
};

#endif