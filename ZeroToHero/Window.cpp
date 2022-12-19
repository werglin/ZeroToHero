#include "Window.h"
#include <sstream>
#include "resource.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	: hInstance( GetModuleHandle(nullptr) )
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0; //extra bytes
	wc.cbWndExtra = 0;  // extra bytes
	wc.hInstance = hInstance;
	wc.hIcon = static_cast<HICON>(LoadImage( hInstance, MAKEINTRESOURCE( IDI_ICON1 ), IMAGE_ICON, 32,32,0 ));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr; // will not be used because its a game project
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const wchar_t* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}

// handles are explained here: https://www.youtube.com/watch?v=D-PC-huX-l8&t=5s
// WINAPI key used here to say compiler these func will linked to API :: Simply forces c++ to use our own WndProc
// this line masks the wndproc at WINAPI side
// SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// set WINAPI-managed user data to store ptr window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch ( msg )
	{
	case WM_CLOSE: 
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// to test our exception we need to delete noexcept
Window::Window(int width, int height, const wchar_t* name) noexcept 
{
	// we entered client width and height
	RECT wr;
	wr.left = 100;
	wr.right = wr.left + width;
	wr.top = 100;
	wr.bottom = wr.top + height;
	// this will make you get the window rect
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	
	this->width = wr.right - wr.left;
	this->height = wr.bottom - wr.top;

	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, this->width, this->height,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}