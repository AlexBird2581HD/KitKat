#include <Engine.h>
#include <Debug.h>

Engine::Engine()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	checkGlError("glClearColor");
	printGLString("Version", GL_VERSION);
}

Engine::~Engine()
{
}


// Public
void Engine::Update()
{
	// Add update code here
}
void Engine::Draw()
{
	clear(); // Clears the screen for next draw
}


// Private

void Engine::clear()
{    
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
}