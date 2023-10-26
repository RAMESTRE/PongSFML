#include "DisplayWindow.hpp"


DisplayWindow::DisplayWindow() 
{
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "PongSFML");
    m_window->setFramerateLimit(60);
}

DisplayWindow::~DisplayWindow() {
	delete m_window;
    m_window = 0;
}

void DisplayWindow::runWindow() {

    sf::Clock clock;
    
    double deltaTime = 0.f;
    
    sf::Vector2u sizeWindow = m_window->getSize();

    Player player1(sizeWindow);
    player1.setPosition();

    while (m_window->isOpen())
    {
        deltaTime = clock.restart().asSeconds(); //func restart restart the clock AND the time elapsed since the clock was last started
        
        while (m_window->pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
                m_window->close();
        }

        player1.movePlayer(deltaTime);

        m_window->clear();
        m_window->draw(player1.display());
        m_window->display();
    }
}
