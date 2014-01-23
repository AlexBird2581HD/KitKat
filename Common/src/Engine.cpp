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
	srand(time(NULL));
	screenWidth = width;
	screenHeight = height;

	if(!setupGraphics(width, height))
		return false;

	glm::mat4 projection = glm::ortho(0.f, (float)screenWidth, (float)screenHeight, 0.f);
	Quad::setProjection(projection);

	enemyText = Texture::loadFile("evilonionminion.tga");
	bulletText = Texture::loadFile("candycaneboom1.tga");

	player = new GameObject(100, screenHeight/2, 64, 64);
	player->setTexture(Texture::loadFile("mufficupcake.tga"));
	//player->move(100, screenWidth/2);

	return true;
}

void Engine::Update(float dt)
{
	//LOGI("deltaTime: %f\n", dt);

	static float bulletCooldown = 0.1f;
	static float enemyCooldown = 2.0f;


	//player->Update(dt);

	player->move(150, Input::getPosition().y+32);

	if(Input::isClick())
	{
		bulletCooldown -= dt;
		if(bulletCooldown <= 0)
		{
			bulletCooldown = 0.1f;
			auto bullet = new GameObject(player->getX(), player->getY(), 16, 16);
			bullet->setTexture(bulletText);
			bullet->SetVelocity(glm::vec2(250, 0));
			bullets.push_back(bullet);
		}
	}

	if(enemies.size() < 30)
	{
		enemyCooldown -= dt;
		if (enemyCooldown <= 0)
		{
			enemyCooldown = 0.3f;
			float height = rand()/(float)RAND_MAX * screenHeight;
			auto enemy = new GameObject(screenWidth, height, 64, 64);
			enemy->setTexture(enemyText);
			enemy->SetVelocity(glm::vec2(-100, 0));
			enemies.push_back(enemy);
		}
	}

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
		auto bullet = bullets.at(i);
		for(int j = 0; j < enemies.size(); ++j)
		{			
			auto enemy = enemies.at(j);

			if(bullet->getX() > enemy->getX() - 32 && 
				bullet->getY() <= enemy->getY() + 32&&
				bullet->getY() >= enemy->getY() - 32)
			{
				delete enemy;
				delete bullet;
				enemies.erase(enemies.begin() + j);
				bullets.erase(bullets.begin() + i);
				--i; --j;
			}
		}
		if(bullet->getX() > screenWidth)
		{
			delete bullet;
			bullets.erase(bullets.begin() + i);
			--i;
		}		
	}
}