#include "RenderWindow.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "Player.hpp"
#include "Ball.hpp"

RenderWindow::RenderWindow() {}

RenderWindow::~RenderWindow() {}

void RenderWindow::displayWindow() const{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "PongSFML");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    sf::Clock clock; //Set the clock

    sf::Vector2u sizeWindow = window.getSize();


    //Create Players

    Player player1, player2; //Instantiate 2 player objects

    sf::RectangleShape player1Sprite = player1.drawPlayer(); //Create Sprite p1
    sf::RectangleShape player2Sprite = player2.drawPlayer(); //Create Sprite p2

    sf::Vector2f positionPlayer2 ((sizeWindow.x - player2Sprite.getSize().x), 0);

    player2.playerSetPosition(positionPlayer2, player2Sprite);

    //Create Ball

    Ball ball;

    sf::CircleShape ballSprite = ball.drawBall();

    //ball.firstBallMovement();


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

                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    window.close();
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << event.key.scancode << std::endl;
                    std::cout << "code: " << event.key.code << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;
                    std::cout << "alt: " << event.key.alt << std::endl;
                    std::cout << "shift: " << event.key.shift << std::endl;
                    std::cout << "system: " << event.key.system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
                    std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
                    std::cout << "Window has been closed with a button pushed" << std::endl << "Program has been running for " << timeElapsed.asSeconds() << " seconds" << std::endl;
                } 
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
                {
                    // right key is pressed: move our character
                    shape.move(1.f, 0.f);
                }
                std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                break;

            case sf::Event::MouseWheelScrolled:
                
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    std::cout << "wheel type: vertical" << std::endl;
                }
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                    std::cout << "wheel type: horizontal" << std::endl;
                }
                else {
                    std::cout << "wheel type: unknown" << std::endl;
                    std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                    std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                    std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                }   
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                break;

            case sf::Event::MouseMoved:
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                break;

            case sf::Event::JoystickButtonPressed:
                std::cout << "joystick button pressed!" << std::endl;
                std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
                std::cout << "button: " << event.joystickButton.button << std::endl;
                break;

            case sf::Event::JoystickMoved:
                if (event.joystickMove.axis == sf::Joystick::X)
                {
                    std::cout << "X axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
                }
                break;

            default:
                break;
            }
        }


        sf::FloatRect boundingBoxP1 = player1Sprite.getGlobalBounds();
        sf::FloatRect boundingBoxBall = ballSprite.getGlobalBounds();

        if (boundingBoxP1.intersects(boundingBoxBall))
        {
            std::cout << "COLLISION" << std::endl;
        }
        
        player1.movePlayer(player1Sprite, sizeWindow);
        player2.movePlayer(player2Sprite, sizeWindow, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);
        ball.ballMove(ballSprite);

        window.clear();
        window.draw(ballSprite);
        window.draw(player1Sprite);
        window.draw(player2Sprite);
        window.draw(shape);
        window.display();

        //std::cout << "Player 1:" << "x = " << player1Sprite.getPosition().x << ". y = " << player1Sprite.getPosition().y << std::endl;
        //std::cout << "Player 2:" << "x = " << player2Sprite.getPosition().x << ". y = " << player2Sprite.getPosition().y << std::endl;
    }
}