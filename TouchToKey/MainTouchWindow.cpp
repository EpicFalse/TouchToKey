#include "MainTouchWindow.h"

CMainTouchWindow* CMainTouchWindow::instance = nullptr;

CMainTouchWindow::CMainTouchWindow()
{

}

CMainTouchWindow::~CMainTouchWindow()
{
	if (windowHandle != NULL)
	{
		DestroyWindow(windowHandle);
		windowHandle = NULL;
	}
}

CMainTouchWindow* CMainTouchWindow::GetInstance()
{
	if (instance == nullptr)
		instance = new CMainTouchWindow();
	return instance;
}

void CMainTouchWindow::RegisterWindowClass(HINSTANCE hInstance)
{
	baseWindClass.cbClsExtra = 0;
	baseWindClass.cbWndExtra = 0;

	baseWindClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);	// 투명 브러시
	baseWindClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	baseWindClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	baseWindClass.hInstance = hInstance;
	baseWindClass.lpszClassName = "CustomTouchWindow";
	baseWindClass.lpszMenuName = NULL;

	baseWindClass.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
	baseWindClass.lpfnWndProc = StaticWndProc;

	registeredCheck = RegisterClass(&baseWindClass);
}

bool CMainTouchWindow::InitWindow(HINSTANCE hInstance)
{
	if (registeredCheck == NULL)
		this->RegisterWindowClass(hInstance);

	// 전체화면을 걸어주기 위하여 0번 디스플레이 장치에 대한 현재 디스플레이 정보를 얻어온다.
	DEVMODE fullscreenSettings;
	EnumDisplaySettings(NULL, 0, &fullscreenSettings);

	// 윈도우 생성
	// WS_EX_TOOLWINDOW로 작업 표시줄에 표시되지 않도록 하고, WS_EX_TOPMOST로 항상 상위에 위치하도록 한다.
	// WS_MAXIMIZE를 줘서 시작하자마자 최대화는 덤.
	windowHandle = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED, "CustomTouchWindow", "TouchWindow", WS_MAXIMIZE,
		0, 0, fullscreenSettings.dmPelsWidth, fullscreenSettings.dmPelsHeight,
		NULL, NULL, hInstance, NULL);

	// 윈도우 생성 실패 :(
	if (windowHandle == NULL)
		return false;

	// 투명 윈도우를 만들꺼기 때문에 윈도우의 alpha값을 0으로 만들자.
	SetLayeredWindowAttributes(windowHandle, 0, 0, LWA_ALPHA);

	// 윈도우를 만들었으면 띄우자.
	ShowWindow(windowHandle, SW_SHOWMAXIMIZED);
}

LRESULT CMainTouchWindow::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CMainTouchWindow::GetInstance()->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CMainTouchWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

