#pragma once
#include <Windows.h>

class CMainTouchWindow
{
public:
	~CMainTouchWindow();

	static CMainTouchWindow* GetInstance();

	void RegisterWindowClass(HINSTANCE hInstance);
	bool InitWindow(HINSTANCE hInstance);

	static LRESULT StaticWndProc(HWND hWnd, UINT mMsg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd, UINT mMsg, WPARAM wParam, LPARAM lParam);

private:
	CMainTouchWindow();
	static CMainTouchWindow* instance;

	WNDCLASS baseWindClass;
	ATOM registeredCheck = NULL;

	HWND windowHandle = NULL;
};
