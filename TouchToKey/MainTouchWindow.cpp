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

	baseWindClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);	// ���� �귯��
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

	// ��üȭ���� �ɾ��ֱ� ���Ͽ� 0�� ���÷��� ��ġ�� ���� ���� ���÷��� ������ ���´�.
	DEVMODE fullscreenSettings;
	EnumDisplaySettings(NULL, 0, &fullscreenSettings);

	// ������ ����
	// WS_EX_TOOLWINDOW�� �۾� ǥ���ٿ� ǥ�õ��� �ʵ��� �ϰ�, WS_EX_TOPMOST�� �׻� ������ ��ġ�ϵ��� �Ѵ�.
	// WS_MAXIMIZE�� �༭ �������ڸ��� �ִ�ȭ�� ��.
	windowHandle = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED, "CustomTouchWindow", "TouchWindow", WS_MAXIMIZE,
		0, 0, fullscreenSettings.dmPelsWidth, fullscreenSettings.dmPelsHeight,
		NULL, NULL, hInstance, NULL);

	// ������ ���� ���� :(
	if (windowHandle == NULL)
		return false;

	// ���� �����츦 ���鲨�� ������ �������� alpha���� 0���� ������.
	SetLayeredWindowAttributes(windowHandle, 0, 0, LWA_ALPHA);

	// �����츦 ��������� �����.
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

