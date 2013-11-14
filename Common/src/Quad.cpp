#include <Quad.h>
#include <Debug.h>
#include <glm/ext.hpp>
#include <cstdlib>

using namespace KitKat;

glm::mat4 Quad::_projection = glm::mat4(1.0f);

Quad::Quad(int x, int y, float w, float h)
	: _x(x),
	  _y(y),
	  _w(w),
	  _h(h)
{
	glGenBuffers(1, &_vbo);
	checkGlError("glGenBuffers");
	genBuffer();
	move(x, y);
	resize(w, h);
	rotate(0);
}

Quad::~Quad()
{
	delete _tex;
	free(Data);
}


// Public


void Quad::move(int x, int y)
{
	_x = x; _y = y;
	_translation = glm::translate(glm::vec3(x, y, 0.02f));
}

void Quad::resize(float width, float height)
{
	_w = width;
	_h = height;
	_scale = glm::scale(glm::vec3(width, height, 0));
}

void Quad::rotate(float angle)
{
	_angle = angle;
	_rotation = glm::rotate(angle, glm::vec3(0, 0, 1));
}

void Quad::setTexture(Texture* texture)
{
	_tex = texture;
}

void Quad::setProjection(glm::mat4 projection)
{
	Quad::_projection = projection;
}

void Quad::draw(Shader* shader)
{
	GLint pos, texCoord;
	pos = shader->getAttribLocation("vPosition");
	texCoord = shader->getAttribLocation("vTexCoord");	
	glEnableVertexAttribArray(pos);
	glEnableVertexAttribArray(texCoord);

	shader->use();

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	checkGlError("glEnable");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	checkGlError("glBlendFunc");

	_tex->bind(shader);	

	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), 0);
	checkGlError("glVertexAttribPointerPos");
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(sizeof(GL_FLOAT)*3)); 
	checkGlError("glVertexAttribPointerTex");
	
	checkGlError("glEnableVertexAttribArray");

	shader->setUniform("Projection", _projection);
	shader->setUniform("Translation", _translation);
	shader->setUniform("Rotation", _rotation);
	shader->setUniform("Scale", _scale);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	checkGlError("glBindBuffer");
	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkGlError("glDrawArrays");

	glDisableVertexAttribArray(pos);
	glDisableVertexAttribArray(texCoord);

	//move(_x + 1, _y);
	glDisable(GL_BLEND);
}


// Private


void Quad::genBuffer()
{
	Data = (float*)malloc(30 * sizeof(float));

	Data[0] = -0.5f;
	Data[1] = -0.5f;
	Data[2] = 0;

	Data[3] = 0;
	Data[4] = 0;


	Data[5] = -0.5f;
	Data[6] = 0.5f;
	Data[7] = 0;

	Data[8] = 0;
	Data[9] = 1;


	Data[10] = 0.5f;
	Data[11] = -0.5f;
	Data[12] = 0;

	Data[13] = 1;
	Data[14] = 0;


	Data[15] = -0.5f;
	Data[16] = 0.5f;
	Data[17] = 0;

	Data[18] = 0;
	Data[19] = 1;


	Data[20] = 0.5f;
	Data[21] = 0.5f;
	Data[22] = 0;

	Data[23] = 1;
	Data[24] = 1;


	Data[25] = 0.5f;
	Data[26] = -0.5f;
	Data[27] = 0;

	Data[28] = 1;
	Data[29] = 0;

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	checkGlError("glBindBuffer");

	glBufferData(GL_ARRAY_BUFFER, sizeof(Data)* 30, Data, GL_DYNAMIC_DRAW);
	checkGlError("glBufferData");
}