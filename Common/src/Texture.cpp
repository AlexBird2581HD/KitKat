#include <Texture.h>

#include <Debug.h>
#include <cassert>

using namespace KitKat;

Texture::Texture(const Header& header, BYTE* data)
	: _id(0),
	  _width(header.width),
	  _height(header.height),
	  _depth(header.depth),
	  _data(data)
{
	createObject();
	initializeObject();
}


Texture::~Texture()
{
	glDeleteTextures(1, &_id);
	checkGlError("glDeleteTextures");
	delete[] _data;
}

// Public

int Texture::width()
{
	return _width;
}

int Texture::height()
{
	return _height;
}

void Texture::bind(Shader* shader)
{
	glActiveTexture(GL_TEXTURE0);
	checkGlError("glActiveTexture");

	bindObject(this);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	checkGlError("glTexParameteri");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	checkGlError("glTexParameteri");

	GLint location = shader->getUniformLocation("texSampler");
	glUniform1i(location, 0);
	checkGlError("glUniform1i");
}

// Static

// Load TGA File
Texture* Texture::loadFile(const std::string &name)
{
	FileReader fr(name.c_str());

	Header header = readHeader(fr);

	assert(header.type == 2);
	assert(header.depth == 24 || header.depth == 32);

	BYTE* data = readData(fr, header);

	return new Texture(header, data);
}


// Private

void Texture::createObject()
{
	glGenTextures(1, &_id);
	checkGlError("glGenTextures");
}

void Texture::initializeObject()
{
	bindObject(this);

    GLint format = GL_RGB;

    if(_depth == 32)
            format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _data);
    checkGlError("glTexImage2D");

    bindObject(NULL);
}

// Static
void Texture::bindObject(const Texture* texture)
{
	GLuint id = 0;

	if(texture != NULL)
		id = texture->_id;

	glBindTexture(GL_TEXTURE_2D, id);
	checkGlError("glBindTexture");
}

Texture::Header Texture::readHeader(FileReader& fileReader)
{
	Header header;

	fileReader.FileSeek(2, SEEK_CUR);
	fileReader.ReadBytes(sizeof(header.type), (int*)&header.type);

	fileReader.FileSeek(9, SEEK_CUR);
	fileReader.ReadBytes(sizeof(header.width), &header.width);
	fileReader.ReadBytes(sizeof(header.height), &header.height);
	fileReader.ReadBytes(sizeof(header.depth), &header.depth);
	fileReader.ReadBytes(sizeof(header.descriptor), &header.descriptor);

	return header;
}

Texture::BYTE* Texture::readData(FileReader& fileReader, const Header& header)
{
	const int componentCount = header.depth / 8;
	const int dataSize = componentCount * header.width * header.height;

	BYTE* buffer = new BYTE[dataSize];
	fileReader.ReadBytes(dataSize, buffer);

	BYTE* data = formatData(buffer, dataSize, componentCount, header);
	delete[] buffer;

	return data;
}

Texture::BYTE* Texture::formatData(const BYTE* buffer, const int dataSize, const int componentCount, const Header& header)
{
	BYTE* data = new BYTE[dataSize];
    bool isOriginAtBottom = (header.descriptor & (1 << 5)) == 0;

    const int width = componentCount * header.width;

    int dataIndex;
    int bufferIndex;

    for(int y = 0; y < header.height; ++y)
    {
        for(int x = 0; x < width; x += componentCount)
        {
            dataIndex = (header.height - 1- y) * width + x;

            if(isOriginAtBottom)
                 bufferIndex = dataIndex;
            else
                bufferIndex = y * width + x;

            data[dataIndex]     = buffer[bufferIndex + 2];
            data[dataIndex + 1] = buffer[bufferIndex + 1];
            data[dataIndex + 2] = buffer[bufferIndex];

            if(header.depth == 32)
                data[dataIndex + 3] = buffer[bufferIndex + 3];
        }
    }

    return data;
}
