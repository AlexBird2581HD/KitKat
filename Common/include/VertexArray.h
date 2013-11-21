#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

class VertexArray
{
public:
	VertexArray(const int componentCount, const int vertexCount);
	VertexArray(const std::vector<glm::vec3>& vertices);
	~VertexArray();

private:
	VertexArray(const VertexArray& vertexArray);

	int _componentCount;
};

#endif