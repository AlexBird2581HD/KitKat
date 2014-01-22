#include <Engine.h>
#include <Debug.h>

#include <Input.h>

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

	glm::mat4 projection = glm::ortho(0.f, (float)screenWidth, 0.f, (float)screenHeight);
	Quad::setProjection(projection);

	enemyText = Texture::loadFile("enemy.tga");
	bulletText = Texture::loadFile("bullet.tga");

	player = new GameObject(100, screenHeight/2, 64, 64);
	player->setTexture(Texture::loadFile("player.tga"));
	//player->move(100, screenWidth/2);

	return true;
}

void Engine::Update(float dt)
{
	//LOGI("deltaTime: %f\n", dt);

	static float bulletCooldown = 0.1;
	static float enemyCooldown = 0.3;


	//player->Update(dt);

	player->move(Input::getPosition().x, Input::getPosition().y); 


	for(int i = 0; i < enemies.size(); ++i)
	{
		enemies.at(i)->Update(dt);
	}
	for(int i = 0; i < bullets.size(); ++i)
	{
		bullets.at(i)->Update(dt);
	}

	collisionCheck();
}

void Engine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	for(int i = 0; i < bullets.size(); ++i)
	{
		bullets.at(i)->draw(shader);
	}
	for(int i = 0; i < enemies.size(); ++i)
	{
		enemies.at(i)->draw(shader);
	}

	player->draw(shader);
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

void Engine::collisionCheck()
{
	for(int i = 0; i < bullets.size(); ++i)
	{
		for(int j = 0; j < enemies.size(); ++j)
		{
			//auto bullet = bullets.at(i);
			//auto enemy = enemies.at(j);

			//if(bullet->getX() > enemy->getX() && bullet->getY() <= enemy->getX())
		}
	}
}