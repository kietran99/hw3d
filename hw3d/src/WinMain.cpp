#include "Window.h"
#include "Input.h"
#include "Debug.h"

using namespace RR;

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hInstPrev,
    PSTR cmdline,
    int cmdshow)
{
    try
    {
        RR::Window wnd{ 800, 450, "My Window" };

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
    catch (const RR::Window::Exception& e)
    {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION); 
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }

    return -1;
}