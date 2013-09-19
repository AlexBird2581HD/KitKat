#include <Debug.h>
#ifdef _WIN32 // Windows specific stuff
#include <Windows.h>
#include <iostream>

// Log function
void printDebug(bool error, const char* format, ...)
{
#ifndef NDEBUG // Do not define function if debug is "off"
	va_list args;
	char message[10240]; // Apparently there are a lot of OpenGL Extensions

	va_start(args, format);
	vsprintf(message, format, args); 
	va_end(args);

	if(error == true)
		OutputDebugStringA("Error: ");

	else
		OutputDebugStringA("Info: ");

	OutputDebugStringA(message);
#endif
}
#endif // End of windows nonsense

// Debug functions
void printGLString(const char *name, GLenum s)
{
#ifndef NDEBUG
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
#endif

}

void checkGlError(const char* op)
{
#ifndef NDEBUG
	for (GLint error = glGetError(); error; error = glGetError())
	{
		LOGI("after %s() glError (0x%x)\n", op, error);
	}
#endif
}