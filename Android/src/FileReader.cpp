#include <FileReader.h>
#include <Debug.h>

using namespace KitKat;

AAssetManager* FileReader::mgr = NULL;

FileReader::FileReader(const char* path)
{
	asset = AAssetManager_open(mgr,path,2);
}

FileReader::~FileReader()
{
	AAsset_close(asset);
}

int FileReader::GetFileSize()
{
	return AAsset_getLength(asset);
}

bool FileReader::FileSeek(int offset,int relation)
{
	if(AAsset_seek(asset,offset,relation)!=1)
		return true;
	return false;
}

bool FileReader::ReadBytes(unsigned int count,void*buffer)
{
	if(asset != NULL)
	{
		LOGI("Assetti on olemassa");
		if(AAsset_read(asset, buffer, count)>=0)
		{
			LOGI("Assetin luku onnistui");
			return true;
		}
	}
	return false;
}

std::string FileReader::ReadFile()
{
	int fileSize = GetFileSize();
	char* buffer = new char[fileSize];

	ReadBytes(fileSize, buffer);
	buffer[fileSize] = 0;

	std::string code(buffer);
	LOGI("%s", code.c_str());

	return std::string(buffer);
}