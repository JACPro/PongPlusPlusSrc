#include "utils.cpp"
#include <windows.h>
#include <thread>
#include "platform_common.cpp"
#include <time.h>
#include <array>

global_variable bool running = true;

struct Render_State
{
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "renderer.cpp"
#include "game.cpp"

std::array<int, 7> c_maj { 
	131, //C3 
	//139, //C#3
	147, //D3
	//156, //D#3
	165, //E3
	175, //F3
	//185, //F#3
	196, //G3
	//208, //G#3
	220, //A3
	//233, //A#3
	247 //B3
};

int GetRandomNote()
{
	srand(time(NULL));
	return c_maj[rand() % 7];
}

void PlayBeep(int duration)
{
	std::thread t1 (Beep, GetRandomNote(), duration);
	t1.detach();
}

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

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ShowCursor(false);

	//1. Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = TEXT("GameWindow");
	window_class.lpfnWndProc = window_callback;

	//2. Register Window Class
	RegisterClass(&window_class);

	//3. Create Window
	HWND window = CreateWindow(window_class.lpszClassName, TEXT("Pong++"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	//Manage framerate 
	float delta_time = 0.01666f;
	LARGE_INTEGER frame_start_time;
	QueryPerformanceCounter(&frame_start_time);
	LARGE_INTEGER frame_end_time;
	LARGE_INTEGER tick_frequency;
	QueryPerformanceFrequency(&tick_frequency);

	while (running)
	{
		

		//Gather Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
				case WM_KEYUP:
				case WM_KEYDOWN:
				{
					u32 vk_code = (u32)message.wParam;
					bool is_down = (message.message == WM_KEYDOWN);

					switch (vk_code)
					{
#define process_button(b, vk)\
case vk: {\
input.buttons[b].is_down = is_down;\
input.buttons[b].changed = is_down == input.buttons[b].is_down;\
} break;
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_W, 'W');
						process_button(BUTTON_S, 'S');
						process_button(BUTTON_ENTER, VK_RETURN);
						process_button(BUTTON_ESCAPE, VK_ESCAPE);
					}
				} break;
				default:
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				} break;
			}
			
		}

		//Process Input and Simulate Game State
		SimulateGame(&input, delta_time, &PlayBeep);

		//Render Output
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		//Update delta_time
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_start_time.QuadPart) / tick_frequency.QuadPart;
		frame_start_time = frame_end_time;
	}
}