#include <Engine.h>
#include <Debug.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace KitKat;

Engine::Engine()
{

}

Engine::~Engine()
{
	delete shader;
}


// Public
void Engine::Update()
{
	static int velx = 5, vely = 5;

	static float r = 0;
	quad2->rotate(r += 5);

	quad2->resize(glm::abs(glm::sin(r/100)*100), glm::abs(glm::sin(r/100)*100));
	quad3->move(quad3->getX() + velx, quad3->getY() + vely);

	if(quad3->getX() < -screenWidth/2 || quad3->getX() > screenWidth/2)
		velx = -velx;

	if(quad3->getY() < -screenHeight/2 || quad3->getY() > screenHeight/2)
		vely = -vely;
}

void Engine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	quad1->draw(shader);
	quad2->draw(shader);
	quad3->draw(shader);
}	

bool Engine::Init(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	if(!setupGraphics(width, height))
		return false;

	quad1 = new Quad(0, 0, 300, 300);
	quad1->setTexture(Texture::loadFile("testi.tga"));

	quad2 = new Quad(500, 0, 100, 100);
	quad2->setTexture(Texture::loadFile("test1.tga"));

	quad3 = new Quad(0, 100, 100, 100);
	quad3->setTexture(Texture::loadFile("testi.tga"));

	checkGlError("Setup");
	GLfloat Projection[16] = 
	{
		1.0f/width, 0,	0, 0
		,0,	1.0f/height,0, 0
		,0,	0,	1,	0
		,0,	0,	0,	1
	};

	glm::mat4 projection = glm::ortho(-screenWidth/2.f, screenWidth/2.f,
		-screenHeight/2.f, screenHeight/2.f);

	Quad::setProjection(projection);

	return true;
}

// Private

bool Engine::setupGraphics(int width, int height)
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

	shader = new Shader("vertexshader.vert", "fragmentshader.frag");
	checkGlError("Shader");

    glViewport(0, 0, width, height);
    checkGlError("glViewport");

	shader->use();

	//glGenBuffers(1, &VBO); // Create the VBO
	//checkGlError("glGenBuffers");

#ifdef _WIN32
	glClearDepth(1);
#else
	glClearDepthf(1);
#endif

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	checkGlError("glClearColor");
    return true;
}