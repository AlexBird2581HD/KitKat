#include <Graphics.h>
#include <Debug.h>
#include <stdlib.h> // malloc and free

using namespace KitKat;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

// Public
bool Graphics::Init(int width, int height)
{
	if(!setupGraphics(width, height))
		return false;
	bindVertices();
	return true;
}

void Graphics::Draw()
{
	clear();
	// Draw the stuff from the VBO(Position, Size, Type, Normal, Size of one point(x+y), pointer to array(comes from VBO)
	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), NULL);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}

// Private

bool Graphics::setupGraphics(int width, int height)
{
	printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

	LOGI("setupGraphics(%d, %d)", width, height);

	_shader = new Shader("vertexshader.vert", "fragmentshader.frag");

	gvPositionHandle = _shader->getAttribLocation("vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

	glViewport(0, 0, width, height);
    checkGlError("glViewport");

	_shader->use();

	glGenBuffers(1, &VBO); // Create the VBO
	checkGlError("glGenBuffers");

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	checkGlError("glClearColor");
    return true;
}

void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkGlError("glClear");
}

void Graphics::bindVertices()
{
	static const GLfloat gTriangleVertices[] =
						{ 0.0f, 0.5f,
						-0.5f, -0.5f,
						0.5f, -0.5f };

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Make VBO active
    checkGlError("glBindBuffer");
	glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_DYNAMIC_DRAW);
    checkGlError("glBufferData");
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Data has changed
    checkGlError("glBindBuffer");
}