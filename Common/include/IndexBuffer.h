#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <vector>

namespace KitKat
{
	typedef unsigned int INDEX;

	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(const IndexBuffer& indexBuffer);
		~IndexBuffer();

		const std::vector<INDEX>& indices();

		void addIndex(const INDEX index);

		void addIndices(const std::vector<INDEX>& indices);

		void clear();

		bool isEmpty();

	private:
		std::vector<INDEX> _indices;
	};
}

#endif