#include "Render.hpp"

Render::Render() {

	m_gameState = STARTUP_MENU;

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

}

Render::~Render() {}

void Render::startMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);

	sf::Text title;
	
	title.setFont(m_font);
	title.setString("PONG");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(xWindowSize/2, yWindowSize/10);

	Button startGame(xWindowSize / 2, yWindowSize/2, 100.f, 50.f, 0, "Start Game"), quitGame(xWindowSize / 2, yWindowSize / 3, 100.f, 50.f, 0, "Quit Game");

	startGame.update(mousePosition);
	if (startGame.isPressed()) {
		m_gameState = PONG_GAME;
	}

	quitGame.update(mousePosition);
	if (quitGame.isPressed()) {
		m_gameState = QUIT_GAME;
		window->close();
	}

	startGame.draw(window);
	quitGame.draw(window);

	window->draw(title);
}

void Render::pongGame() {

}

void Render::replayMenu() {

}

statesGame Render::getStateGame() const{
	return m_gameState;
}