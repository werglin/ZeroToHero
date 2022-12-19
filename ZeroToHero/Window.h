#pragma once

//target win 7 or later
#define _WIN32_WININT 0x0601
#include<sdkddkver.h>

#define WIN32_LEAN_AND_MEAN
// we wont use GDI, its directx project
#define NOGDICAPMASKS
#define NOMENUS
#define NOATOM
#define NOCOLOR
#define NOKANJI
#define NOIMAGE
#define NOMINMAX
#define NORPC
#define NOMCX
#define NOTAPE
#define NODEFERWINDOWPOS
#define NOSOUND 
#define NOWH
#define NOCOMM
#define NOTEXTMETRIC
#define NOHELP
#define NOPROFILER
#define NODRAWTEXT
#define NOKERNEL
#define NOCLIPBOARD
#define NOMETAFILE
#define NOCTLMGR
#define NOSERVICE
#define NONLS
#define NORASTEROPS
#define OEMRESOURCE
#define NOSYSMETRICS

#define STRICT


#include<Windows.h>




class Window
{
private: //variable

	HWND hWnd;
	int width;
	int height;

private: //func

	static LRESULT WINAPI HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) noexcept;
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private: // private class

	//there will be only 1 window class because we will make game for now
	class WindowClass
	{
	private: //private vals
		
		HINSTANCE hInstance;
		static constexpr const wchar_t* wndClassName = TEXT("Directx3D Engine");
		static WindowClass wndClass;

	private: //private func
		
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete; //removes copy constructer
		WindowClass& operator=(const WindowClass&) = delete;

	public: //public func
		
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	
	};

	
public:

	Window(int width, int height, const wchar_t* name) noexcept; 
	~Window();
	Window(const Window&) = delete; //removes copy constructer
	Window& operator=(const Window&) = delete;

};
// helper macro from chilli
#define COWND_EXCEPT( hr ) Window::Exception( __LINE__, __FILE__, hr)