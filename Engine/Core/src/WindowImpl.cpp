#include "Window.h"

#include <sstream>

#include "WindowsMessageMap.h"

namespace RR
{
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
        const auto adjustWndRectRes = AdjustWindowRect(&wRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
        
        if (adjustWndRectRes == 0)
        {
            throw RR_WND_LAST_EXCEPT();
        }

        m_width = wRect.right - wRect.left;
        m_height = wRect.bottom - wRect.top;

        m_hWnd = CreateWindowEx(
            0, WindowClass::GetName(), name,
            WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
            nullptr, nullptr, WindowClass::GetInstance(), this);

        if (!m_hWnd)
        {
            throw RR_WND_LAST_EXCEPT();
        }

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

    Window::Exception::Exception(int line, const char* file, HRESULT hRes) noexcept
        : RRException(line, file), m_hRes(hRes) {}

    const char* Window::Exception::what() const noexcept
    {
        std::ostringstream oss;

        oss << GetType() << std::endl
            << "[Error Code] " << m_hRes << std::endl
            << "[Description] " << GetErrorString() << std::endl
            << GetOriginString();

        m_whatBuf = oss.str();
        return m_whatBuf.c_str();
    }

    const char* Window::Exception::GetType() const noexcept
    {
        return "RR Window Error";
    }

    std::string Window::Exception::TranslateErrorCode(HRESULT hRes) noexcept
    {
        char* pMsgBuf = nullptr;

        const DWORD nMsgLen = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, hRes, 0, reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);

        if (nMsgLen == 0)
        {
            return "Unidentified error code";
        }

        const std::string errStr = pMsgBuf;
        LocalFree(pMsgBuf);
        return errStr;
    }

    std::string Window::Exception::GetErrorString() const noexcept
    {
        return TranslateErrorCode(m_hRes);
    }
}