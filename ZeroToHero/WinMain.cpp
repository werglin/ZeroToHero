#include"Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	lpCmdLine,
	int nCmdShow
)
{
	try
	{

		Window win(800, 300, TEXT("NICE ASSY WIN"));
		Window win2(1024, 720, TEXT("NICE ASSY WIN 2"));

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
	}
	catch (const MyException& e)
	{
		MessageBox( nullptr, reinterpret_cast<LPCWSTR>(e.what()), reinterpret_cast<LPCWSTR>(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e )
	{
		MessageBox( nullptr, reinterpret_cast<LPCWSTR>(e.what()), TEXT("Standart Exception"), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, TEXT("No details available"), TEXT("Unknown Exception"), MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}