#include <FileReader.h>
#include <fstream>

using namespace KitKat;

FileReader::FileReader(const char* path)
{
	filePath = std::string("..\\Assets\\");
	filePath += path;
	file = fopen(filePath.c_str(), "rb");
}

FileReader::~FileReader()
{
	fclose(file);
}

int FileReader::GetFileSize()
{
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	return size;
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

std::string FileReader::ReadFile()
{
	int fileSize = GetFileSize();
	char* buffer = new char[fileSize];

	ReadBytes(fileSize, buffer);
	buffer[fileSize] = 0;

	return std::string(buffer);
}