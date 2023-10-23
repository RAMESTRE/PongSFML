#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"
#include "RenderWindow.hpp"

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
    sf::Thread threadTestFunc(&testFunc); //Create a thread that will run in parallel of main
    
    threadTestFunc.launch(); //Run the thread;

    mutex.lock();

    for (int i = 0; i < 10; ++i) {
        std::cout << "I'm the main thread with i = " << i << std::endl;
    }

    mutex.unlock();

    RenderWindow window;

    window.displayWindow();

    return 0;
}