#include "Application.h"

using namespace RR;

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hInstPrev,
    PSTR cmdline,
    int cmdshow)
{
    Application app{ 800, 600, "My Window" };
    return (int)app.Start();
}