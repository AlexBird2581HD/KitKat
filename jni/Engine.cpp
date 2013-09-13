#include <Engine.h>

#include <iostream>

Engine::Engine()
{

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
	glClearColor(0, 0, 0, 1.0f); // Black
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
}

// Static
void Engine::checkGlError(const char* op)
{
    for (GLint error = glGetError(); error; error = glGetError())
	{
        printf("after %s() glError (0x%x)\n", op, error);
    }
}