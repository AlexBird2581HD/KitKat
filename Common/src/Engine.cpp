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

bool Engine::Init(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	if(!setupGraphics(width, height))
		return false;

	quad1 = new Quad(screenWidth/2, screenHeight/2, 300, 300);
	quad1->setTexture(Texture::loadFile("testi.tga"));
	quad2 = new Quad(screenWidth/1.2f, screenHeight/2, 100, 100);
	quad2->setTexture(Texture::loadFile("test1.tga"));
	quad3 = new Quad(200, 200, 100, 100);
	quad3->setTexture(Texture::loadFile("testi.tga"));

	glm::mat4 projection = glm::ortho(0.f, (float)screenWidth, 0.f, (float)screenHeight);
	Quad::setProjection(projection);

	return true;
}

void Engine::Update(float dt)
{
	LOGI("deltaTime: %f\n", dt);

	static float r = 0;
	quad2->rotate(r += 5);
	quad2->resize(glm::abs(glm::sin(r/100)*100), glm::abs(glm::sin(r/100)*100));

	static int velx = 5, vely = 5;
	quad3->move(quad3->getX() + velx, quad3->getY() + vely);

	if(quad3->getX() < 0 || quad3->getX() > screenWidth)
		velx = -velx;

	if(quad3->getY() < 0 || quad3->getY() > screenHeight)
		vely = -vely;
}

void Engine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	quad1->draw(shader);
	quad2->draw(shader);
	quad3->draw(shader);
}	


// Private

bool Engine::setupGraphics(int width, int height)
{
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

#ifdef _WIN32
	glClearDepth(1);
#else
	glClearDepthf(1);
#endif

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	checkGlError("glClearColor");
    return true;
}