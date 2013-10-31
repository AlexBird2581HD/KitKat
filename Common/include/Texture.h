#ifndef TEXTURE_H
#define TEXTURE_H

#include <Shader.h>
#include <FileReader.h>

#include <string>

namespace KitKat
{
	class Texture
	{
	public:
		typedef unsigned char BYTE;
		typedef unsigned short USHORT;

		struct Header
		{
			BYTE type;
			USHORT width;
			USHORT height;
			BYTE depth;
			BYTE descriptor;
		};

	public:
		Texture(const Header& header, BYTE* data);
		~Texture();

		int width();
		int height();

		void bind(Shader* shader);

		// Load TGA File
		static Texture* loadFile(const std::string &name);

	private:
		GLuint _id;
		int _width, _height, _depth;

		BYTE* _data;

		Texture(const Texture& texture);

		void createObject();
		void initializeObject();

		static void bindObject(const Texture* texture);
        static Header readHeader(FileReader& fileReader);
        static BYTE* readData(FileReader& fileReader, const Header& header);
        static BYTE* formatData(const BYTE* buffer, const int dataSize, const int componentCount, const Header& header);
	};
}
#endif
