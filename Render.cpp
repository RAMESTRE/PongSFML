#include "Render.hpp"

Render::Render() {

	m_gameState = STARTUP_MENU;
	m_pongState = SLEEP;

	m_score[0] = m_score[1] = 0;

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
} //CREATE BUTTON TAB IN CLASS TO INITIALIZE BUTTONS ONLY ONCE

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

	//Get window size to actualize scale gamePlan
	//
	//
	sf::Vector2u sizeWindow = window->getSize();


	//Initialize scoreText to display score of 2 players
	//
	//
	sf::Text scoreText;
	scoreText.setFont(m_font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setString(std::to_string(m_score[0]) + " : " + std::to_string(m_score[1]));

	sf::FloatRect titleBox = scoreText.getGlobalBounds();
	scoreText.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	scoreText.setPosition(960, 40);

	//Get move that have been done last frame
	//
	//
	const sf::Texture& gamePlanUpdate = m_gamePlan->getTexture();

	//Hitbox for top and bottom player 1 (need to add player 2)
	//
	//
	sf::RectangleShape topP1;
	sf::RectangleShape botP1;


	//Switch to display differents states on scrren 
	//(see if not better to create a function for each states ?)
	//
	//
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
		m_ball->firstMove(361);

		//Score init
		std::cout << m_score[0] << std::endl;
		m_score[0] = m_score[1] = 0;
		scoreText.setString( m_score[0]+" : "+ m_score[1]);

		//State Game init
		m_pongState = CURRENT_GAME;
		break;

	case(INIT_PVCPU):
		break;

	case(CURRENT_GAME):

		//Create a separate function for the "gameplay/pong"
		//
		//


		//Update players/ball/hitbox positions
		//
		//

		m_tabPlayers[0]->movePlayer(*dt); //Use func deltaTime of displayWindow class ?
		m_tabPlayers[1]->movePlayer(*dt);
		m_ball->move(*dt);

		m_tabHitboxPlayers[0]->hitboxUpdate(*m_tabPlayers[0]);
		m_tabHitboxPlayers[1]->hitboxUpdate(*m_tabPlayers[1]);
		m_ballHitbox->hitboxUpdate(*m_ball);

		//Collision detection
		//
		//

		if (m_ballHitbox->futureCollision().x < 0) {
			//Increment Score
			//
			//
			m_score[1] += 1;

			//Delete ball and her collision and creates new ones (with deleting content pointer and pointing to new ones)
			//
			//
			delete m_ball;
			m_ball = 0;
			m_ball = new Ball();
			delete m_ballHitbox;
			m_ballHitbox = 0;
			m_ballHitbox = new Hitbox(*m_ball);

			m_ball->setPosition(&*m_gamePlan);

			//Ball goes to the direction of the one who marked the point
			// 
			// 
			m_ball->firstMove(-180);
			
		}
		else if (m_ballHitbox->futureCollision().x > m_gamePlan->getSize().x - m_ball->getBallShape().getSize().x) {
			//Increment Score
			//
			//
			m_score[0] += 1;

			//Delete ball and her collision and creates new ones (with deleting content pointer and pointing to new ones)
			//
			//
			delete m_ball;
			m_ball = 0;
			m_ball = new Ball();
			delete m_ballHitbox;
			m_ballHitbox = 0;
			m_ballHitbox = new Hitbox(*m_ball);

			m_ball->setPosition(&*m_gamePlan);

			//Ball goes to the direction of the one who marked the point
			// 
			// 
			m_ball->firstMove(180);
		}
		if (m_ballHitbox->futureCollision().y < 0 || m_ballHitbox->futureCollision().y > m_gamePlan->getSize().y-m_ball->getBallShape().getSize().y) {
			m_ball->changeDirection(1, -1);
		}

		topP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[0]->display().getSize().x - 2, 1.f));
		topP1.setPosition(m_tabPlayers[0]->display().getPosition());

		botP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[0]->display().getSize().x - 2, 1.f));
		botP1.setPosition(sf::Vector2f(m_tabPlayers[0]->display().getPosition().x, m_tabPlayers[0]->display().getSize().y+1));
		

		if (m_ballHitbox->getHitbox()->intersects(*m_tabHitboxPlayers[0]->getHitbox())) {

			if (m_tabPlayers[0]->getMovement().y < 0 && m_ball->getMovement().y > 0) {
				m_ball->setPositionBall(sf::Vector2f(100.f+20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_tabPlayers[0]->getMovement().y > 0 && m_ball->getMovement().y < 0) {
				m_ball->setPositionBall(sf::Vector2f(100.f + 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_ballHitbox->getHitbox()->intersects(topP1.getGlobalBounds()) || m_ballHitbox->getHitbox()->intersects(botP1.getGlobalBounds())){
				m_ball->setPositionBall(sf::Vector2f(100.f - 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(1, -1);
			}
			else {
				m_ball->changeDirection(-1, 1);
			}
		}
		
		//For me to quit game before ending an actual game (will be replaced with a quit button)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			m_pongState = END_GAME;
		}

		//Ending game condition
		//
		//

		if (m_score[0] == 11 || m_score[1] == 11) {
			m_pongState = END_GAME;
		}

		//Draw all sprite in gamePlan texture;
		//
		//

		m_gamePlan->clear();

		//m_gamePlan->draw(m_tabHitboxPlayers[0]->futureMovement());
		//m_gamePlan->draw(m_ballHitbox->futureMovement());

		m_gamePlan->draw(scoreText);
		m_ball->draw(&*m_gamePlan);
		m_gamePlan->draw(m_tabPlayers[0]->display());
		m_gamePlan->draw(m_tabPlayers[1]->display());

		m_gamePlan->display();

		//Scale the sprite that got the actual texture and position in it to fit the window
		*m_gameSprites = sf::Sprite(gamePlanUpdate);
		m_gameSprites->setScale(sf::Vector2f(sizeWindow.x / 1920.f, sizeWindow.y / 1080.f));

		//Draw to window(to delete to be called in class DisplayWindow (return instead of window draw ?)
		window->draw(*m_gameSprites);

		break;


	case(END_GAME):

		//Delete all pointers and their content
		//
		//
		for (int i(0); i < m_tabPlayers.size(); i++) {
			delete m_tabPlayers[i];
			m_tabPlayers[i] = 0;
		}
		for (int i(0); i < m_tabHitboxPlayers.size(); i++) {
			delete m_tabHitboxPlayers[i];
			m_tabHitboxPlayers[i] = 0;
		}
		delete m_ball;
		delete m_ballHitbox;
		m_ballHitbox = 0;
		m_ball = 0;

		m_tabPlayers.clear();
		m_tabHitboxPlayers.clear();

		//Add Buttons for replay/main menu

		m_gameState = STARTUP_MENU;
		break;

	}
}

void Render::parametersMenu(sf::RenderWindow* window) {
	parameters.displayMenu(window, m_font);
	if (parameters.getStateParametersMenu()) m_gameState = STARTUP_MENU;
}

void Render::replayMenu() {

}

statesGame Render::getStateGame() const{
	return m_gameState;
}