#include "RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

RenderWindow::RenderWindow() {}

RenderWindow::~RenderWindow() {}

void RenderWindow::displayWindow() const{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "PongSFML");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    sf::Clock clock; //Set the clock


    while (window.isOpen()) //Create window loop
    {

        sf::Time timeElapsed = clock.getElapsedTime(); //Get elapsed time since the clock got created
        //std::cout << timeElapsed.asSeconds() << std::endl; //Display the time elapsed as seconds in the console

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                std::cout << "Window has been closed with red cross" << std::endl << "Program has been running for " << timeElapsed.asSeconds() << " seconds" << std::endl;
                break;

            case sf::Event::KeyPressed:
                window.close();
                std::cout << "Window has been closed with a button pushed" << std::endl << "Program has been running for " << timeElapsed.asSeconds() << " seconds" << std::endl;
                break;

            default:
                break;
            }
        }


        window.clear();
        window.draw(shape);
        window.display();
    }
}