#include <VertexBuffer.h>

using namespace KitKat;

VertexBuffer::VertexBuffer() {}

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
	: _vertexArrays(vertexBuffer._vertexArrays)
{}

VertexBuffer::~VertexBuffer()
{
	destroyVertexArrays();
}


// Public
void VertexBuffer::addVertexArray(VertexArray* vertexArray)
{
	_vertexArrays.push_back(vertexArray);
}

void VertexBuffer::setVertexArrays(const Shader* shader)
{
	for(auto i = _vertexArrays.begin(); i != _vertexArrays.end(); ++i)
		(*i)->setVertexData(shader);
}

void VertexBuffer::clear()
{
	destroyVertexArrays();
}

// Private

void VertexBuffer::destroyVertexArrays()
{
	for(auto i = _vertexArrays.begin(); i != _vertexArrays.end(); ++i)
		delete (*i);

	_vertexArrays.clear();
}