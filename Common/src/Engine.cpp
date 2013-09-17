#include <Engine.h>
#include <Debug.h>
#include <iostream>

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

// Static
void Engine::printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);

	char message[255];
	sprintf(message, "GL %s = %s\n", name, v);
	LOGI(message);

}

void Engine::checkGlError(const char* op)
{
    for (GLint error = glGetError(); error; error = glGetError())
	{
		char message[255];
		sprintf(message, "after %s() glError (0x%x)\n", op, error);
		LOGE(message);
    }
}