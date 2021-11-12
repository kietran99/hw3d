#include "Application.h"

using namespace RR;

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hInstPrev,
    PSTR cmdline,
    int cmdshow)
{
    Application app{};
    return (int)app.Start();
}