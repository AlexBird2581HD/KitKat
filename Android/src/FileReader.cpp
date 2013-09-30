#include <FileReader.h>

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

bool FileReader::FileSeek(int offset,int relation)
{
	if(AAsset_seek(asset,offset,relation)!=1)
		return true;
	return false;
}

bool FileReader::ReadBytes(unsigned int count,void*buffer)
{
	if(asset != NULL)
		if(AAsset_read(asset, buffer, count)>=0)
			return true;
	return false;
}