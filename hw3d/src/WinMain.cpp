#include <Windows.h>
#include "Window.h"

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hInstPrev,
    PSTR cmdline,
    int cmdshow)
{
    Window wnd{ 640, 480, "My Window" };

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

    return res == -1 ? -1 : (int) msg.wParam;
}