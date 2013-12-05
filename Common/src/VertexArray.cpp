#include <VertexArray.h>
#include <Debug.h>

using namespace KitKat;

VertexArray::VertexArray(const std::string& attribName, const int componentCount, const int vertexCount)
	: _componentCount(componentCount),
	  _buffer(0)
{
	initializeBuffer(NULL, vertexCount, GL_DYNAMIC_DRAW);
}

VertexArray::VertexArray(const std::string& attribName, const std::vector<glm::vec3>& vertices)
        : _attributeName(attribName),
          _componentCount(3),
          _buffer(0)
{
        initializeVertices(vertices);
        initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
}

VertexArray::VertexArray(const std::string& attribName, const std::vector<glm::vec2>& vertices)
        : _attributeName(attribName),
          _componentCount(2),
          _buffer(0)
{
        initializeVertices(vertices);
        initializeBuffer(&vertices.front(), vertices.size(), GL_STATIC_DRAW);
}


VertexArray::~VertexArray() { }


// Public

void VertexArray::addVertices(const std::vector<glm::vec2>& vertices, const int vertexOffset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGlError("glBindBuffer");

	const int componentSize = sizeof(float) * 2;
	const GLintptr offset = componentSize * vertexOffset;
	const GLsizeiptr size = componentSize * vertices.size();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
	checkGlError("glBufferSubData");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGlError("glBindBuffer");
}

void VertexArray::addVertices(const std::vector<glm::vec3>& vertices, const int vertexOffset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	checkGlError("glBindBuffer");

	const int componentSize = sizeof(float) * 3;
	const GLintptr offset = componentSize * vertexOffset;
	const GLsizeiptr size = componentSize * vertices.size();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertices.front());
	checkGlError("glBufferSubData");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGlError("glBindBuffer");
}

void VertexArray::setVertexData(const Shader* shader)
{
	GLint location = shader->getAttribLocation(_attributeName);

    glEnableVertexAttribArray(location);
    checkGlError("glEnableVertexAttribArray");

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    checkGlError("glBindBuffer");
    glVertexAttribPointer(location, _componentCount, GL_FLOAT, GL_FALSE, 0, 0);
    checkGlError("glVertexAttribPointer");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkGlError("glBindBuffer");
}

// Private

void VertexArray::initializeVertices(const std::vector<glm::vec2>& vertices)
{
	size_t vertexCount = vertices.size();
    _vertices.resize(_componentCount * vertexCount);

    size_t index;

    for(size_t i = 0; i < vertexCount; ++i)
    {
            index = _componentCount * i;

            _vertices[index]     = vertices[i].x;
            _vertices[index + 1] = vertices[i].y;
    }
}

void VertexArray::initializeVertices(const std::vector<glm::vec3>& vertices)
{
	size_t vertexCount = vertices.size();
    _vertices.resize(_componentCount * vertexCount);

    size_t index;

    for(size_t i = 0; i < vertexCount; ++i)
    {
            index = _componentCount * i;

            _vertices[index]     = vertices[i].x;
            _vertices[index + 1] = vertices[i].y;
            _vertices[index + 2] = vertices[i].z;
    }
}

void VertexArray::initializeBuffer(const GLvoid* data, const int vertexCount, const GLenum usage)
{
	glGenBuffers(1, &_buffer);
    checkGlError("glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    checkGlError("glBindBuffer");

    GLsizeiptr size = sizeof(float) * _componentCount * vertexCount;

    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    checkGlError("glBufferData");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkGlError("glBindBuffer");
}