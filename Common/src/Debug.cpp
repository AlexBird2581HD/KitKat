#include <Debug.h>
#ifdef _WIN32 // Windows specific stuff
#include <Windows.h>
#include <iostream>

// Log function
void printDebug(bool error, const char* message)
{
#ifndef NDEBUG // Do not define function if debug is "off"
	if(error == true)
		OutputDebugStringA("Error: ");

	else
		OutputDebugStringA("Info: ");

	OutputDebugStringA(message);
	OutputDebugStringA("\n");
#endif
}
#endif // End of windows nonsense

// Debug functions
void printGLString(const char *name, GLenum s)
{
#ifndef NDEBUG
		const char *v = (const char *) glGetString(s);
	#ifdef _WIN32 // Windows implementation
		char message[255];
		sprintf(message, "GL %s = %s\n", name, v);
		LOGI(message);
	#else // Android implementation
		LOGI("GL %s = %s\n", name, v);
	#endif
#endif

}

void checkGlError(const char* op)
{
#ifndef NDEBUG
		for (GLint error = glGetError(); error; error = glGetError())
		{
	#ifdef _WIN32 // Windows implementation
			char message[255];
			sprintf(message, "after %s() glError (0x%x)\n", op, error);
			LOGE(message);
	#else // Android implementation
			LOGI("after %s() glError (0x%x)\n", op, error);
	#endif
		}
#endif
}