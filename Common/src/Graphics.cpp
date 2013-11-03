#include <Graphics.h>
#include <Debug.h>
#include <cstdlib> // malloc and free

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
	//bindVertices();
	
	//quads.push_back(new Quad(100, 100, 100 ,100));
	//quads.at(0)->setTexture(Texture::loadFile("testi.tga"));

	quad = new Quad(100, -100, 100, 100);
	quad->setTexture(Texture::loadFile("test1.tga"));

	checkGlError("Setup");
	GLfloat Projection[16] = 
	{
		1.0f/width, 0,	0,	-1
		,0,	1.0f/height,0,1
		,0,	0,	1,	0
		,0,	0,	0,	1
	};
	//Quad::setProjection(Projection);
	Quad::Projection = (float*)calloc(16,sizeof(float));
	Quad::Projection[0] = Projection[0];
	Quad::Projection[1] = Projection[1];
	Quad::Projection[2] = Projection[2];
	Quad::Projection[3] = Projection[3];
	Quad::Projection[4] = Projection[4];
	Quad::Projection[5] = Projection[5];
	Quad::Projection[6] = Projection[6];
	Quad::Projection[7] = Projection[7];
	Quad::Projection[8] = Projection[8];
	Quad::Projection[9] = Projection[9];
	Quad::Projection[10] = Projection[10];
	Quad::Projection[11] = Projection[11];
	Quad::Projection[12] = Projection[12];
	Quad::Projection[13] = Projection[13];
	Quad::Projection[14] = Projection[14];
	Quad::Projection[15] = Projection[15];

	return true;
}

void Graphics::Draw()
{
	clear();
	// Draw the stuff from the VBO(Position, Size, Type, Normal, Size of one point(x+y), pointer to array(comes from VBO)
	//glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), NULL);
 //   checkGlError("glVertexAttribPointer");
 //   glEnableVertexAttribArray(gvPositionHandle);
 //   checkGlError("glEnableVertexAttribArray");
 //   glDrawArrays(GL_TRIANGLES, 0, 3);
 //   checkGlError("glDrawArrays");

	quad->draw(_shader);
}

// Private

bool Graphics::setupGraphics(int width, int height)
{
	glEnable(GL_TEXTURE_2D);
	checkGlError("glEnable");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	checkGlError("glPixelStorei");
	printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

	LOGI("setupGraphics(%d, %d)", width, height);

	_shader = new Shader("vertexshader.vert", "fragmentshader.frag");
	checkGlError("Shader");

    glViewport(0, 0, width, height);
    checkGlError("glViewport");

	_shader->use();

	//glGenBuffers(1, &VBO); // Create the VBO
	//checkGlError("glGenBuffers");

#ifdef _WIN32
	glClearDepth(1);
#else
	glClearDepthf(1);
#endif

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
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