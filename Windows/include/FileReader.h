#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <stdio.h>

namespace KitKat
{
	class FileReader
	{
	public:
		FileReader(const char* path);
		 ~FileReader();

		 int GetFileSize();
		 // Still probably might want to use file headers if possible

		 bool FileSeek(int offset,int relation);
		 bool ReadBytes(unsigned int count,void*buffer);
		 std::string ReadFile(); // Reads the whole file and returns as string
		
	private:
		std::string filePath;
		FILE* file;
	};
}

#endif