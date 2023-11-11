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

	Button startGame(xWindowSize / 2, yWindowSize/4, xWindowSize*100.f/1920, yWindowSize*50.f/1080, 0, "Start Game"),
		parametersMenu(xWindowSize / 2, yWindowSize / 3, xWindowSize * 100.f / 1920, yWindowSize * 50.f / 1080, 0, "Parameters") ,quitGame(xWindowSize / 2, yWindowSize / 2, xWindowSize * 100.f / 1920, yWindowSize * 50.f / 1080, 0, "Quit Game");

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

	Button pvp(xWindowSize / 2, yWindowSize / 2.5, 100.f, 50.f, 0, "Player vs Player"), pvcpu(xWindowSize / 2, yWindowSize / 1.5, 100.f, 50.f, 0, "Player vs Computer");

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

	sf::RenderTexture texture;
	if (!texture.create(1920, 1080))
	{
		// error...
	}

	sf::Sprite ssprite;
	const sf::Texture& ttexture = texture.getTexture();

	switch (m_pongState)
	{
	case(INIT_PVP):
		//m_ball = new Ball(sizeWindow);
		m_tabPlayers.push_back(new Player());
		m_tabPlayers.push_back(new Player());
		m_tabHitboxPlayers.push_back(new Hitbox(*m_tabPlayers[0]));
		m_tabHitboxPlayers.push_back(new Hitbox(*m_tabPlayers[1]));
		m_tabPlayers[0]->setPosition(sf::Vector2f(100.f,120.f));
		m_tabPlayers[1]->setPosition(sf::Vector2f(texture.getSize().x - 100.f, 120.f));
		//m_ball->setPosition(window);
		//m_ball->firstMove();
		m_pongState = CURRENT_GAME;
		break;

	case(INIT_PVCPU):
		break;

	case(CURRENT_GAME):

		//m_ballHitbox = m_ball->getBallShape().getGlobalBounds();

		m_tabPlayers[0]->movePlayer(*dt);
		m_tabPlayers[1]->movePlayer(*dt);

		m_tabHitboxPlayers[0]->hitboxUpdate(*m_tabPlayers[0]);
		m_tabHitboxPlayers[1]->hitboxUpdate(*m_tabPlayers[1]);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			m_pongState = END_GAME;
		}

		texture.clear();

		//m_ball->move(*dt);

		//m_ball->draw(window);

		texture.draw(m_tabHitboxPlayers[0]->futureCollision(*m_tabHitboxPlayers[1]));
		texture.draw(m_tabPlayers[0]->display());
		texture.draw(m_tabPlayers[1]->display());

		
		texture.display();

		//ttexture = texture.getTexture();
		ssprite = sf::Sprite(ttexture);
		ssprite.setScale(sf::Vector2f(sizeWindow.x / 1920.f, sizeWindow.y / 1080.f));

		window->draw(ssprite);
		break;


	case(END_GAME):

		for (int i(0); i < m_tabPlayers.size(); i++) {
			delete m_tabPlayers[i];
			m_tabPlayers[i] = 0;
		}
		for (int i(0); i < m_tabHitboxPlayers.size(); i++) {
			delete m_tabHitboxPlayers[i];
			m_tabHitboxPlayers[i] = 0;
		}
		m_tabPlayers.clear();
		m_tabHitboxPlayers.clear();

		m_gameState = STARTUP_MENU;
		break;

	}
}

void Render::parametersMenu() {

}

void Render::replayMenu() {

}

statesGame Render::getStateGame() const{
	return m_gameState;
}