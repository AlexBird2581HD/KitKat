#ifdef _WIN32
#include <Debug.h>
#include <Windows.h>

// Log function
void printDebug(bool error, const char* message)
{
	if(error == true)
		OutputDebugStringA("Error: ");

	else
		OutputDebugStringA("Info: ");

	OutputDebugStringA(message);
	OutputDebugStringA("\n");
}

#endif