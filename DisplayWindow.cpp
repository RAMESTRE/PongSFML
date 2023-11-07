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
    m_deltaTime = 0;

    std::cout << "Window has been deleted in the displaywindow destructor" << std::endl;
}

double DisplayWindow::getDeltaTime() const {
    return *m_deltaTime;
}

void DisplayWindow::runWindow() {

    sf::Clock clock;

    Render render;

    while (m_window->isOpen())
    {
        *m_deltaTime = clock.restart().asSeconds(); //func restart restart the clock AND the time elapsed since the clock was last started

        while (m_window->pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
                m_window->close();
        }

        m_window->clear();

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
