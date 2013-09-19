#include <Engine.h>
#include <vector>

Engine::Engine()
	: graphics(0)
{
	// Empty constructor is empty
}

Engine::~Engine()
{
	delete graphics;
}


// Public
void Engine::Update()
{
	// Add update code here
}

void Engine::Draw()
{
	graphics->Draw();
}	

bool Engine::Init(int width, int height)
{
	graphics = new Graphics();
	if(!graphics->Init(width, height))
		return false;
	return true;
}