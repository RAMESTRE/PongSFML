#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

sf::Mutex mutex;

void testFunc() {

    mutex.lock();

    for (int i = 0; i < 10; ++i) {
        std::cout << "Thread number 1 with i = " << i << std::endl;
    }

    mutex.unlock();
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PongSFML");

    sf::CircleShape shape(500.f);
    shape.setFillColor(sf::Color::Blue);

    sf::Clock clock; //Set the clock
    sf::Thread threadTestFunc(&testFunc); //Create a thread that will run in parallel of main
    
    threadTestFunc.launch(); //Run the thread;

    mutex.lock();

    for (int i = 0; i < 10; ++i) {
        std::cout << "I'm the main thread with i = " << i << std::endl;
    }

    mutex.unlock();
        

    while (window.isOpen()) //Create window loop
    {
        sf::Time timeElapsed = clock.getElapsedTime(); //Get elapsed time since the clock got created
        std::cout << timeElapsed.asSeconds() << std::endl; //Display the time elapsed as seconds in the console

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    window.close();
                    break;

                default:
                    break;
            }
            }
            

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}