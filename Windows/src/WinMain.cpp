#include <Win32toAndroid.h>
#include <Window.h>
#include <Engine.h>

#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	Window * window = new Window(hInstance,"KitKat Testi",1280,752);
	return 0;
}