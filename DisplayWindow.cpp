#include "DisplayWindow.hpp"

DisplayWindow::DisplayWindow() : m_deltaTime(new double)
{
    *m_deltaTime = 0.f;

    configFile.loadFromFileGraphic("Config/Graphic.ini");
    getNewSettings();

	m_window = new sf::RenderWindow(m_sizeWindow, "PongSFML", sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(m_framerate);
    m_window->setVerticalSyncEnabled(m_vsync);
}

DisplayWindow::~DisplayWindow() {

	delete m_window;
    delete m_deltaTime;
    m_window = 0;
    m_deltaTime = 0;

    std::cout << "Window has been deleted in the displaywindow destructor" << std::endl;
}

void DisplayWindow::getNewSettings() {

    m_sizeWindow = configFile.getSizeWindow();
    m_framerate = configFile.getFramerate();
    m_fullscreen = configFile.getFullscreen();
    m_vsync = configFile.getVSync();

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

            if (m_event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, m_event.size.width, m_event.size.height);
                m_window->setView(sf::View(visibleArea));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
                m_window->setSize(sf::Vector2u(800, 450));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                m_window->setSize(sf::Vector2u(1920, 1080));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
                delete m_window;
                m_window = 0;
                m_window = new sf::RenderWindow(sf::VideoMode(800, 450), "PongSFML", sf::Style::Fullscreen);
                
            }

        }

        m_window->clear();

        switch (render.getStateGame())
        {
        case(STARTUP_MENU):
            //render.parametersMenu(m_window);
            render.startMenu(m_window);
            break;
        case(PLAYERS_MENU):
            render.playerMenu(m_window);
            break;
        case(PONG_WINDOW):
            render.pongWindow(m_window, m_deltaTime);
            break;
        case(PARAMETERS_MENU):
            render.parametersMenu(m_window);
            //Here call loadFromFileGraphic when menu parameters is quitted to load new window settings
            break;
        }

        m_window->display();

    }
}
