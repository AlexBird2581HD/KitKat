#include <Windowsx.h>

#include <Window.h>
#include <Engine.h>
#include <string>
#include <OpenGL.h>
#include <Input.h>
#include <Debug.h>

#pragma comment(lib, "opengl32.lib")

HWND Window::handle;
HGLRC Window::OGLcontext;
HDC Window::hdc;

Window::Window(HINSTANCE instance,const char* windowName,int width,int height)
{
//Windowclass, defines template for windows
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wEventsProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = instance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"windowClass";
	wndClass.hIconSm = NULL;

	//register window class
	if(!RegisterClassEx(&wndClass))
	{
		//FAIL
	}

	//Creates window and return handle to it (a way to access the windows attributes)
	handle = CreateWindowA("windowClass", windowName, WS_OVERLAPPED, 0, 0, width, height, NULL, NULL, instance, NULL);

	if (handle == NULL)
	{
		//0.o
	}

	ShowWindow(handle, SW_SHOWNORMAL);
	UpdateWindow(handle);

	//pixel format description, only point worth of notice is if its 32 or 24 bit (alpha or no alpha)
			PIXELFORMATDESCRIPTOR pixelFormatDesc = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24, 0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
	//Device Contex handle
	hdc = GetDC(handle); // Gets the display context

	if(hdc == NULL) {

		//0.o
	}

	int pixelFormat = ChoosePixelFormat(hdc, &pixelFormatDesc); // Chooses the pixel format

	if(pixelFormat == 0) {

		//0.o
	}

	// Sets the pixel format
	if(SetPixelFormat(hdc, pixelFormat, &pixelFormatDesc) == 0) {

		//return 0;
	}

	HGLRC hglrc = wglCreateContext(hdc); // Creates the rendering context

	if(hglrc == NULL) {

		//0.o
	}

	// Attaches the rendering context
	if(wglMakeCurrent(hdc, hglrc) == 0) {

		//return 0;
	}
	
	LoadOpenGLFunctions(); // Loads OpenGL 2.1 functions
	//glViewport(0, 0, width, height); // Sets up the OpenGL viewport
	// Handled by engine->Init

	MSG msg ={};
	KitKat::Engine* engine = new KitKat::Engine();
	engine->Init(width, height);


	float deltaTime = 0.0f;
	long prevTime = GetTickCount(); // Return milliseconds

	// Main message loop:
	while(msg.message != WM_QUIT)
	{
		
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		//else // We've processed all pending Win32 messages, and can now do a rendering update.
		//{

			
		
		//}
		engine->Update(deltaTime);
		engine->Draw();
		long currTime = GetTickCount();
		deltaTime = (float)(currTime - prevTime) / 1000.f;
		prevTime = currTime;

		SwapBuffers(Window::hdc); // Swaps display buffers
	}
	delete engine;
}


LRESULT CALLBACK Window::wEventsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_MOUSEMOVE:
			{
			RECT desktop, window;
			GetWindowRect(GetDesktopWindow(), &desktop);
			GetWindowRect(hWnd, &window);

			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);

			KitKat::Input::processPosition(x, y);
			}
			break;
		case WM_LBUTTONDOWN:
			KitKat::Input::processClick(true);
			break;
		case WM_LBUTTONUP:
			KitKat::Input::processClick(false);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 1;
}


Window::~Window(void)
{
}
