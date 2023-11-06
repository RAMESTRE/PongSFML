#include "DisplayWindow.hpp"

DisplayWindow::DisplayWindow() : m_deltaTime(new double)
{
    *m_deltaTime = 0.f;
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "PongSFML");
    m_window->setFramerateLimit(60);
}

DisplayWindow::~DisplayWindow() {
	delete m_window;
    delete m_deltaTime;
    m_window = 0;
}

double DisplayWindow::getDeltaTime() const {
    return *m_deltaTime;
}

void DisplayWindow::runWindow() {

    sf::Clock clock;
    
    sf::Vector2u sizeWindow = m_window->getSize();
    sf::Vector2i mousePosition;

    Player player1(sizeWindow);
    Player player2(sizeWindow);

    Hitbox hitboxPlayer1(player1);
    Hitbox hitboxPlayer2(player2);

    player1.setPosition();
    player2.setPosition(sf::Vector2f(sizeWindow.x - 100.f, 120.f));

   
    Button but(200.0,200.0,100.0,50.0,0,"Options");

    Render render;

    while (m_window->isOpen())
    {
        *m_deltaTime = clock.restart().asSeconds(); //func restart restart the clock AND the time elapsed since the clock was last started
        
        mousePosition = sf::Mouse::getPosition(*m_window);

        while (m_window->pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
                m_window->close();
        }


        /*hitboxPlayer1.hitboxUpdate(player1);
        
        player1.movePlayer(*m_deltaTime);
        player2.movePlayer(*m_deltaTime);*/

        m_window->clear();

        render.startMenu(m_window);
        /*m_window->draw(hitboxPlayer1.futureCollision(hitboxPlayer2));
        m_window->draw(player1.display());
        m_window->draw(player2.display());
        but.update(mousePosition);
        but.draw(m_window);*/
        m_window->display();
    }
}
