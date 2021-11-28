#include "Application.h"

#include "Window.h"
#include "Debug.h"

RR::Application::Application(int width, int height, const char* name)
	: m_pWindow(new Window(width, height, name))
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
