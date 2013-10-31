#include <Quad.h>
#include <Debug.h>
#include <stdlib.h>

using namespace KitKat;

float* Quad::Projection = NULL;

Quad::Quad(int x, int y, int w, int h)
	: _x(x),
	  _y(y),
	  _w(w),
	  _h(h)
{
	Translation = (float*)calloc(16,sizeof(float));
	Rotation = (float*)calloc(16,sizeof(float));

	glGenBuffers(1, &_vbo);
	checkGlError("glGenBuffers");
	genBuffer();
	move(x,y);
}

Quad::~Quad()
{
	delete _tex;
}


// Public


void Quad::move(int x, int y)
{
	_x = x; _y = y;

	Translation[0] = 1;
	Translation[3] = _x;
	Translation[5] = 1;
	Translation[7] = _y;
	Translation[10] = 1;
	Translation[15] = 1;
}

void Quad::resize(int width, int height)
{
	_w = width;
	_h = height;
	genBuffer();
}

void Quad::setTexture(Texture* texture)
{
	_tex = texture;
}

void Quad::setProjection(float* matrixArray)
{
	Quad::Projection = (float*)malloc(sizeof(float)*16);
}

void Quad::draw(Shader* shader)
{
	//Translation[11] = z;

	shader->use();

	glEnable(GL_BLEND);
	checkGlError("glEnable");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	checkGlError("glBlendFunc");


	_tex->bind(shader);

	GLint pos, texCoord;

	pos = shader->getAttribLocation("vPosition");
	texCoord = shader->getAttribLocation("vTexCoord");

	glVertexAttribPointer(pos,3,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),0);
	checkGlError("glVertexAttribPointerPos");
	glVertexAttribPointer(texCoord,2,GL_FLOAT,GL_FALSE,5*sizeof(GL_FLOAT),(void*)(sizeof(GL_FLOAT)*3)); 
	checkGlError("glVertexAttribPointerTex");

	shader->setUniform("Projetion", Projection);
	checkGlError("Projection");
	shader->setUniform("Translation", Translation);
	checkGlError("Translation");

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	checkGlError("glBindBuffer");
	glDrawArrays(GL_TRIANGLES, 0, 30);
	checkGlError("glDrawArrays");
}


// Private


void Quad::genBuffer()
{
	float* Data = (float*)malloc(sizeof(float)*30);

    Data[0] = -_w/2; 
	Data[1] = -_h/2; 
    Data[2] = 0;

    Data[3] = 0; 
    Data[4] = 0; 


    Data[5] = -_w/2; 
	Data[6] = _h/2; 
    Data[7] = 0;

    Data[8] = 0; 
    Data[9] = 1; 


	Data[10] = _w/2; 
	Data[11] = -_h/2; 
	Data[12] = 0; 

    Data[13] = 1; 
    Data[14] = 0; 
    

	Data[15] = -_w/2; 
	Data[16] = _h/2; 
    Data[17] = 0; 

	Data[18] = 0; 
    Data[19] = 1; 


	Data[20] = _w/2; 
	Data[21] = _h/2; 
	Data[22] = 0; 

    Data[23] = 1; 
    Data[24] = 1; 


	Data[25] = _w/2; 
	Data[26] = -_h/2; 
    Data[27] = 0; 

	Data[28] = 1; 
    Data[29] = 0;
	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	checkGlError("glBindBuffer");

	glBufferData(GL_ARRAY_BUFFER, sizeof(Data)*30, Data, GL_DYNAMIC_DRAW);
	checkGlError("glBufferData");
}