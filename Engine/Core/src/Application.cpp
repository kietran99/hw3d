#include "Application.h"

#include "Window.h"

RR::Application::Application()
	: m_window(new Window(800, 450, "My Window"))
{}

RR::Application::~Application()
{
    delete m_window;
}

int RR::Application::Start()
{
    try
    {
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
            Update();

        } while (true);

        return res == -1 ? -1 : (int)msg.wParam;
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

void RR::Application::Update()
{
}
