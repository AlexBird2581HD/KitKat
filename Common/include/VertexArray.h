#pragma once
#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include <Shader.h>
namespace KitKat
{
	class VertexArray
	{
	public:
		VertexArray(const std::string& attribName, const int componentCount, const int vertexCount);
		VertexArray(const std::string& attribName, const std::vector<glm::vec2>& vertices);
		VertexArray(const std::string& attribName, const std::vector<glm::vec3>& vertices);
		~VertexArray();

		void addVertices(const std::vector<glm::vec2>& vertices, const int vertexOffset);
		void addVertices(const std::vector<glm::vec3>& vertices, const int vertexOffset);
		void setVertexData(const Shader* shader);
	private:
		VertexArray(const VertexArray& vertexArray);

		std::string _attributeName;

		int _componentCount; // How many components are inside one Vector

		std::vector<float> _vertices;
		GLuint _buffer;

		void initializeVertices(const std::vector<glm::vec2>& vertices);
		void initializeVertices(const std::vector<glm::vec3>& vertices);
		void initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage);
	};
}

#endif