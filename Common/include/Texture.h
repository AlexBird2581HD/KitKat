#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <string>

namespace KitKat
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		int width();
		int height();

		void bind(const Shader* shader);

		// Load TGA File
		static Texture* loadFile(std::string &name);
	private:
		Texture(const Texture& texture);

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

	};
}
#endif