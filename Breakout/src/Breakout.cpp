#include <Windows.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Keyboard.h"
#include "Message.h"

#define LOG(x) std::cout << x << std::endl;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
	case WM_KEYDOWN:
		Keyboard::OnKeyPressed((int)wParam);
		break;
	case WM_SYSKEYDOWN:
		Keyboard::OnKeyPressed((int)wParam);
		break;
	case WM_KEYUP:
		Keyboard::OnKeyReleased((int)wParam);
		break;
	case WM_SYSKEYUP:
		Keyboard::OnKeyReleased((int)wParam);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int main() {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"Breakout", NULL };
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName, L"Breakout", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	Message msg;
	while (!msg.ShouldClose()) {
		if (msg.Peek())
		{
			msg.Dispatch();
			continue;
		}

	}
}