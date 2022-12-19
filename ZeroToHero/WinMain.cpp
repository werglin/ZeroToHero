#include"Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	lpCmdLine,
	int nCmdShow
)
{

	Window win(800, 300, TEXT("NICE ASSY WIN"));

	// get message
	MSG msg;
	BOOL gRes;
	while ((gRes = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	if (gRes == -1)
	{
		return -1;
	}
	// PostQuitMessage( 69//wParam );
	return msg.wParam;

	return -1;
}