#include <Util.h>
#include <fstream>

// Public
// Static
std::string Util::ReadFile(std::string fileName)
{
	// Correct the path for windows
	fileName = "../" + fileName;


	std::string content, line;
	std::ifstream file;
	file.open(fileName, std::ios::in);

	if(file.is_open())
	{
		while(std::getline(file,line))
		{
			content.append(line);
		}
	}
	return content;
}