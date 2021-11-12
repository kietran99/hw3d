#include "Application.h"

#include "Window.h"
#include "Debug.h"

RR::Application::Application()
	: m_pWindow(new Window(800, 450, "My Window"))
{}

RR::Application::~Application()
{
    delete m_pWindow;
    Debug::Free();
}

WPARAM RR::Application::Start()
{
    try
    {
        while (true)
        {
            const auto exitCode = Window::ProcessMessagePump();

            if (exitCode)
            {
                return *exitCode;
            }

            Update();
        }
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
    m_pWindow->UpdateGraphics();
}
