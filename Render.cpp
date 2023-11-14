#include "Render.hpp"

Render::Render() {

	m_gameState = STARTUP_MENU;
	m_pongState = SLEEP;

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	m_gamePlan = new sf::RenderTexture;
	if (m_gamePlan->create(1920, 1080)) {
		std::cout << "Error creating gamePlan" << std::endl;
	}

	m_gameSprites = new sf::Sprite;

}

Render::~Render() {
	delete m_gamePlan;
	m_gamePlan = 0;
	delete m_gameSprites;
	m_gameSprites = 0;
}

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

	const sf::Texture& gamePlanUpdate = m_gamePlan->getTexture();

	switch (m_pongState)
	{
	case(INIT_PVP):

		//Players Init
		m_tabPlayers.push_back(new Player());
		m_tabPlayers.push_back(new Player());
		m_tabHitboxPlayers.push_back(new Hitbox(*m_tabPlayers[0]));
		m_tabHitboxPlayers.push_back(new Hitbox(*m_tabPlayers[1]));
		m_tabPlayers[0]->setPosition(sf::Vector2f(100.f,120.f));
		m_tabPlayers[1]->setPosition(sf::Vector2f(m_gamePlan->getSize().x - 100.f, 120.f));

		//Ball Init
		m_ball = new Ball();
		m_ballHitbox = new Hitbox(*m_ball);
		m_ball->setPosition(&*m_gamePlan);
		m_ball->firstMove();

		//State Game init
		m_pongState = CURRENT_GAME;
		break;

	case(INIT_PVCPU):
		break;

	case(CURRENT_GAME):

		m_tabPlayers[0]->movePlayer(*dt);
		m_tabPlayers[1]->movePlayer(*dt);
		m_ball->move(*dt);

		m_tabHitboxPlayers[0]->hitboxUpdate(*m_tabPlayers[0]);
		m_tabHitboxPlayers[1]->hitboxUpdate(*m_tabPlayers[1]);
		m_ballHitbox->hitboxUpdate(*m_ball);

		if (m_ballHitbox->futureCollision().x < 0 || m_ballHitbox->futureCollision().x > m_gamePlan->getSize().x- m_ball->getBallShape().getSize().x) {
			m_ball->changeDirection(-1,1);
		}
		if (m_ballHitbox->futureCollision().y < 0 || m_ballHitbox->futureCollision().y > m_gamePlan->getSize().y-m_ball->getBallShape().getSize().y) {
			m_ball->changeDirection(1, -1);
		}


		//For me to quit game before ending an actual game (will be replaced with a quit button)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			m_pongState = END_GAME;
		}

		//Draw all sprite in gamePlan texture;
		m_gamePlan->clear();

		m_gamePlan->draw(m_tabHitboxPlayers[0]->futureMovement());
		m_gamePlan->draw(m_ballHitbox->futureMovement());

		m_ball->draw(&*m_gamePlan);
		m_gamePlan->draw(m_tabPlayers[0]->display());
		m_gamePlan->draw(m_tabPlayers[1]->display());
		

		

		m_gamePlan->display();

		//Scale the sprite that got the actual texture and position in it to fit the window
		*m_gameSprites = sf::Sprite(gamePlanUpdate);
		m_gameSprites->setScale(sf::Vector2f(sizeWindow.x / 1920.f, sizeWindow.y / 1080.f));

		//Draw to window(to delete to be called in class DisplayWindow
		window->draw(*m_gameSprites);

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