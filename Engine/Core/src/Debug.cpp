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

void RR::Debug::Log(const char* fmt, ...)
{ 
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}


