#include "Window.h"

#include "WindowsMessageMap.h"

Window::WindowClass Window::WindowClass::m_instance;

Window::WindowClass::WindowClass() noexcept
	: m_hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc{ 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMessageSetup;
    wc.cbClsExtra = 0;
    wc.hInstance = m_hInst;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = nullptr;

    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(GetName(), m_hInst);
}

const char* Window::WindowClass::GetName() noexcept
{
	return WND_CLS_NAME;
}

const HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return m_instance.m_hInst;
}

Window::Window(int width, int height, const char* name) noexcept
{
    RECT wRect{};
    wRect.left = 100;
    wRect.right = width + wRect.left;
    wRect.top = 100;
    wRect.bottom = height + wRect.top;
    AdjustWindowRect(&wRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    
    m_width = wRect.right - wRect.left;
    m_height = wRect.bottom - wRect.top;

    m_hWnd = CreateWindowEx(
        0, WindowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
        nullptr, nullptr, WindowClass::GetInstance(), this);

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
    DestroyWindow(m_hWnd);
}

LRESULT WINAPI Window::HandleMessageSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg != WM_NCCREATE)
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
    Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
    SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageThunk));
    return pWnd->HandleMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMessageThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static WindowsMessageMap mm{};
    OutputDebugString(mm(uMsg, lParam, wParam).c_str());
    
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}