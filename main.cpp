#include "DisplayWindow.hpp"
#include <Windows.h>

int main()
{

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    DisplayWindow window;

    window.runWindow();

    return 0;
}

//Go in project settings and put the app as window app and not console app to not have the console window displayed => Might want to try sfml-main instead for portability

/*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    DisplayWindow window;

    window.runWindow();

    return 0;
}*/