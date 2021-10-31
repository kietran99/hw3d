#include "Debug.h"

#include <Windows.h>
#include <stdio.h>

#include "Window.h"

RR::Debug* RR::Debug::s_instance = new Debug();

RR::Debug::Debug()
{
    if (!AllocConsole())
    {
        throw RR_WND_LAST_EXCEPT();
    }

    FILE* pDummy;
    freopen_s(&pDummy, "CONOUT$", "w", stdout);
}

void RR::Debug::Log(const char* msg)
{
    printf("%s", msg);
}
