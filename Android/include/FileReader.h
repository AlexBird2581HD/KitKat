#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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
		 
		 static AAssetManager* mgr;
	private:
		std::string filePath;

		AAsset* asset;
	};
}

#endif