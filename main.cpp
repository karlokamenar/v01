#include <windows.h>
typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;

enum { id_button1 = 1, id_button2 };

void OnCreate(HWND hw) {
	HWND button1 = CreateWindow("BUTTON", "one", WS_CHILD | WS_VISIBLE,
		50, 50, 100, 40,
		hw, (HMENU) 1, NULL, NULL);
	HWND button2 = CreateWindow("BUTTON", "two", WS_CHILD | WS_VISIBLE,
		50, 150, 100, 40,
		hw, (HMENU) 2, NULL, NULL);
	
	// TODO: create two child windows of type button
}

void OnCommand(HWND hw, int id) {
	// TODO: show message box with text depending on which button was pressed
	switch (id) {
		case 1:
			MessageBox(NULL, "one", "NWP", MB_OK| MB_ICONWARNING);
			break;
		case 2:
			MessageBox(NULL, "two", "NWP", MB_OK| MB_ICONWARNING);
			break;
		default:
			return;

	}
}

void OnDestroy() {
	PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
			OnCreate(hw);
			return 0;
		case WM_COMMAND:
			OnCommand(hw, LOWORD(wp));
			return 0;
		case WM_DESTROY:
			OnDestroy();
			return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}


int RegisterMyClass(HINSTANCE hInstance, char* className)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255)); 

	return RegisterClass(&wc);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	char clsName[] = "NWPClass";

	if(!RegisterMyClass(hInstance, clsName))
		return 0;

	HWND hwnd = CreateWindow(clsName, "NWP 1",  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL); 
	
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}
