#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
	static std::string ReadFile(std::string fileName);
private:
	Util(const Util& util);
	Util();
	~Util();
};

#endif