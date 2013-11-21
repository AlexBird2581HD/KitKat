#include <IndexBuffer.h>

using namespace KitKat;

IndexBuffer::IndexBuffer() { }

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
	: _indices(indexBuffer._indices)
{ }

IndexBuffer::~IndexBuffer() { }


// Public

const std::vector<INDEX>& IndexBuffer::indices()
{
	return _indices;
}

void IndexBuffer::addIndex(const INDEX index)
{
	_indices.push_back(index);
}

void IndexBuffer::addIndices(const std::vector<INDEX>& indices)
{
	_indices.insert(_indices.end(), indices.begin(), indices.end());
}

void IndexBuffer::clear()
{
	_indices.clear();
}

bool IndexBuffer::isEmpty()
{
	return _indices.size() == 0;
}

