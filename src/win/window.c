#include "win/window.h"
#include <stdbool.h>
#include "logging.h"

bool NewWindow(Window* window) {
    LogInfo("Creating new window\n");

    const LPCSTR className = "Traveller";

    WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = NULL;

    if (!RegisterClassEx(&wcex)) {
        LogError("Failed to register window class\n");
        return false;
    }

    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    window->hWnd = CreateWindow(className, className, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (!window->hWnd) {
        LogError("Failed to create window\n");
        return false;
    }

    ShowWindow(window->hWnd, SW_SHOWDEFAULT);

	LogInfo("Created new window\n");

    return true;
}