#include <Windows.h>

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(69);
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hInstPrev,
    PSTR cmdline,
    int cmdshow)
{
    const auto clsName = L"HW3D";
    WNDCLASSEX wc{ 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = MyWndProc;
    wc.cbClsExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = clsName;
    wc.hIconSm = nullptr;

    auto cls = RegisterClassEx(&wc);

    if (!cls)
    {
        return -1;
    }

    auto hwnd = CreateWindowEx(
        0, clsName, L"My Window",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInst, nullptr);

    if (hwnd == nullptr)
    {
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);
    
    MSG msg{};
    BOOL res;

    do
    {
        res = GetMessage(&msg, nullptr, 0, 0);

        if (res <= 0)
        {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    } while (true);

    return res == -1 ? -1 : msg.wParam;
}