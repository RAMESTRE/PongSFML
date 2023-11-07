#include "Render.hpp"

Render::Render() {

	m_gameState = STARTUP_MENU;
	m_pongState = SLEEP;

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

	Button startGame(xWindowSize / 2, yWindowSize/4, 100.f, 50.f, 0, "Start Game"), parametersMenu(xWindowSize / 2, yWindowSize / 3, 100.f, 50.f, 0, "Parameters") ,quitGame(xWindowSize / 2, yWindowSize / 2, 100.f, 50.f, 0, "Quit Game");

	startGame.update(mousePosition);
	if (startGame.isPressed()) {
		m_gameState = PLAYERS_MENU;
	}

	parametersMenu.update(mousePosition);
	if (parametersMenu.isPressed()) {
		m_gameState = PARAMETERS_MENU;
	}

	quitGame.update(mousePosition);
	if (quitGame.isPressed()) {
		m_gameState = QUIT_GAME;
		window->close();
	}

	startGame.draw(window);
	parametersMenu.draw(window);
	quitGame.draw(window);

	window->draw(title);
}

void Render::playerMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);

	Button pvp(xWindowSize / 2, yWindowSize / 2.5, 100.f, 50.f, 0, "Player vs Player"), pvcpu(xWindowSize / 2, yWindowSize / 3.5, 100.f, 50.f, 0, "Player vs Computer");

	pvp.update(mousePosition);
	if (pvp.isPressed()) {
		m_gameState = PONG_WINDOW;
		m_pongState = INIT_PVP;
	}

	pvcpu.update(mousePosition);
	if (pvcpu.isPressed()) {
		m_gameState = PONG_WINDOW;
		m_pongState = INIT_PVCPU;
	}

	pvp.draw(window);
	pvcpu.draw(window);
}

void Render::pongWindow(sf::RenderWindow* window, double* dt) {

	sf::Vector2u sizeWindow = window->getSize();

	Player player1(sizeWindow);
	Player player2(sizeWindow);

	Hitbox hitboxPlayer1(player1);
	Hitbox hitboxPlayer2(player2);

	player1.setPosition();
	player2.setPosition(sf::Vector2f(sizeWindow.x - 100.f, 120.f));

	hitboxPlayer1.hitboxUpdate(player1);

	player1.movePlayer(*dt);
	player2.movePlayer(*dt);

}

void Render::parametersMenu() {

}

void Render::replayMenu() {

}

statesGame Render::getStateGame() const{
	return m_gameState;
}