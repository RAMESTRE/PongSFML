#include <iostream>
#include <SFML/Graphics.hpp>

//#include "DisplayWindow.hpp"
#include "Configuration.hpp"

int main()
{
    //DisplayWindow window;
    //window.runWindow();

    Configuration config;
    config.loadFromFileGraphic("Config/Graphic.ini");

    

    return 0;
}