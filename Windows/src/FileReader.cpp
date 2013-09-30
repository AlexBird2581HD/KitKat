#include <FileReader.h>
#include <fstream>

using namespace KitKat;

FileReader::FileReader(const char* path)
{
	filePath = std::string("..\\Assets\\");
	filePath += path;
	file = fopen(filePath.c_str(),"rb");
}

FileReader::~FileReader()
{
	fclose(file);
}

bool FileReader::FileSeek(int offset,int relation)
{
	if(fseek(file,offset,relation) == 0)
		return true;
	return false;
}

bool FileReader::ReadBytes(unsigned int count,void*buffer)
{
	if(file != NULL)
		if(fread(buffer, 1,count,file)==count)
			return true;
	return false;
}