#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <VertexArray.h>
#include <list>

namespace KitKat
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
        VertexBuffer(const VertexBuffer& vertexBuffer);                
        ~VertexBuffer();

		void addVertexArray(VertexArray* vertexArray);
		void setVertexArrays(const Shader* shader);

		void clear();

	private:
		 std::list<VertexArray*> _vertexArrays;

		 void destroyVertexArrays();
	};
}

#endif