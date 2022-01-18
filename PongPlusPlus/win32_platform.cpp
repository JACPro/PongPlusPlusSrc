#include "utils.cpp"
#include <windows.h>

global_variable bool running = true;

struct Render_State
{
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "renderer.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_DESTROY:
		case WM_CLOSE:
		{
			running = false;
		} break;

		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int size = render_state.width * render_state.height * sizeof(unsigned int);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_info.bmiHeader.biPlanes = 1;
			render_state.bitmap_info.bmiHeader.biBitCount = 32;
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
		} break;

		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	return result;
}

int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//1. Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = TEXT("GameWindow");
	window_class.lpfnWndProc = window_callback;

	//2. Register Window Class
	RegisterClass(&window_class);

	//3. Create Window
	HWND window = CreateWindow(window_class.lpszClassName, TEXT("PongPlusPlus"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running)
	{
		//Gather Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//Process Input and Simulate Game State
		ClearScreen(0x7de1ff);
		DrawRect(0, 0, 10, 10, 0xfc6358);
		//Bottom left
		DrawRect(-40, -40, 5, 5, 0xfc6358);
		//Top left
		DrawRect(-40, 40, 7, 7, 0xfc6358);
		//Top right
		DrawRect(40, 40, 5, 5, 0xfc6358);
		//Bottom right
		DrawRect(40, -40, 7, 7, 0xfc6358);

		//Render Output
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}