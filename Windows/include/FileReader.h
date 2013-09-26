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

		 void LoadFile(const char* name);

		 bool ReadBytes(unsigned int count,void*buffer);
		 bool FileSeek(int offset,int relation);
	private:
		std::string filePath;
		FILE* file;
	};
}

#endif