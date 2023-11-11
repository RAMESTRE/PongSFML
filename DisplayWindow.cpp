#include "DisplayWindow.hpp"

DisplayWindow::DisplayWindow() : m_deltaTime(new double)
{
    *m_deltaTime = 0.f;
	m_window = new sf::RenderWindow(sf::VideoMode(800,450), "PongSFML");
    m_window->setFramerateLimit(60);
}

DisplayWindow::~DisplayWindow() {
	delete m_window;
    delete m_deltaTime;
    m_window = 0;
    m_deltaTime = 0;

    std::cout << "Window has been deleted in the displaywindow destructor" << std::endl;
}

double DisplayWindow::getDeltaTime() const {
    return *m_deltaTime;
}

void DisplayWindow::runWindow() {

    sf::Clock clock;

    Render render;

    /*sf::RenderTexture texture;
    sf::RectangleShape sprite(sf::Vector2f(1920.f,1080.f));
    if (!texture.create(1920, 1080))
    {
        // error...
    }
    texture.clear();
    texture.draw(sprite); // or any other drawable
    texture.display();

    const sf::Texture& ttexture = texture.getTexture();
    sf::Sprite ssprite(ttexture);
    ssprite.setScale(sf::Vector2f(800.f/ texture.getSize().x, 450.f/ texture.getSize().y));*/


    while (m_window->isOpen())
    {
        *m_deltaTime = clock.restart().asSeconds(); //func restart restart the clock AND the time elapsed since the clock was last started

        
        while (m_window->pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
                m_window->close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // left mouse button is pressed: shoot
                sf::Vector2i pixelPos = sf::Mouse::getPosition(*m_window);
                std::cout << sf::Mouse::getPosition(*m_window).x << " " << sf::Mouse::getPosition(*m_window).y << std::endl;
                sf::Vector2f worldPos = m_window->mapPixelToCoords(pixelPos);
                std::cout << worldPos.x << " " << worldPos.y << std::endl;
            }

            if (m_event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, m_event.size.width, m_event.size.height);
                m_window->setView(sf::View(visibleArea));
                std::cout << "Window Resized: x = " << m_window->getSize().x << " y = " << m_window->getSize().y << std::endl;
                std::cout << m_event.size.width << " " << m_event.size.height << std::endl;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
                delete m_window;
                m_window = 0;
                m_window = new sf::RenderWindow(sf::VideoMode(800, 450), "PongSFML");
                //m_window->setSize(sf::Vector2u(800, 600));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                delete m_window;
                m_window = 0;
                m_window = new sf::RenderWindow(sf::VideoMode(1920,1080), "PongSFML");
                //m_window->setSize(sf::Vector2u(1920, 1080));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
                delete m_window;
                m_window = 0;
                m_window = new sf::RenderWindow(sf::VideoMode(800, 450), "PongSFML", sf::Style::Fullscreen);
                
            }
        }

        m_window->clear();

        //m_window->draw(ssprite);

        switch (render.getStateGame())
        {
        case(STARTUP_MENU):
            render.startMenu(m_window);
            break;
        case(PLAYERS_MENU):
            render.playerMenu(m_window);
            break;
        case(PONG_WINDOW):
            render.pongWindow(m_window, m_deltaTime);
            break;
        case(PARAMETERS_MENU):
            break;
        }

        m_window->display();

    }
}
