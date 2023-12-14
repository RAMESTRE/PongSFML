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
	m_gamePlan->create(1920, 1080);
		

	m_gameSprites = new sf::Sprite;

	//CREATE BUTTON STARTMENU HERE, WILL NEED A FUNCTION FOR IT LATER ON
	std::vector<std::string> tabOpt{ "Start Game", "Parameters", "Quit Game" };
	for (int i(0); i < tabOpt.size(); i++) {
		if (i == 2) m_buttonsStartMenu.push_back(new Button(1920 / 2, 780, 100.f, 50.f, 0, 30, tabOpt[i]));
		else m_buttonsStartMenu.push_back(new Button(1920 / 2, 380 + (100 * i), 100.f, 50.f, 0, 30, tabOpt[i]));
	}

	m_buttonsPlayersMenu.push_back(new Button(1920 / 2, 480, 100.f, 50.f, 0, 30, "Player vs Player"));
	m_buttonsPlayersMenu.push_back(new Button(1920 / 2, 680, 100.f, 50.f, 0, 30, "Player vs Computer"));


	/////////////////////CREATE FUNCTION STATIC/////////////////////////////////////////////
	m_line = new sf::RenderTexture;
	m_line->create(10, 1080);
	m_lineSprite = new sf::Sprite;

	sf::RectangleShape cutLine(sf::Vector2f(10.f, 50.f));
	
	m_line->clear();

	for (int i(0); i < 15; i++) {
		cutLine.setPosition(0, 72*(i));
		m_line->draw(cutLine);
	}

	m_line->display();

	*m_lineSprite = sf::Sprite(m_line->getTexture());
	m_lineSprite->setPosition(1920/2-5, 10);
	///////////////////////////////////////////////////////////////////////////////////////

	m_buttonsReplayMenu.push_back(new Button(1920 / 2, 480, 100.f, 50.f, 0, 30, "Yes"));
	m_buttonsReplayMenu.push_back(new Button(1920 / 2, 580, 100.f, 50.f, 0, 30, "No"));
	m_buttonsReplayMenu.push_back(new Button(1920 / 2, 780, 100.f, 50.f, 0, 30, "Quit"));

}

Render::~Render() {
	delete m_gamePlan;
	m_gamePlan = 0;
	delete m_gameSprites;
	m_gameSprites = 0;
	delete m_line;
	m_line = 0;
	delete m_lineSprite;
	m_lineSprite = 0;
}

void Render::startMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition, m_gamePlan->getView()); //Put in hpp


	//Put a switch and case to be called only once////////////////
	sf::Text title;
	
	title.setFont(m_font);
	title.setString("PONG");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(m_gamePlan->getSize().x/2, m_gamePlan->getSize().x / 10);

	/////////////////////////////////////////////////////////////////
	m_gamePlan->clear();

	for (int i(0); i < m_buttonsStartMenu.size(); i++) {
		m_buttonsStartMenu[i]->update(worldPos);
		
		if (m_buttonsStartMenu[i]->isPressed()) {
			switch (i) {
			case(0):
				m_gameState = PLAYERS_MENU;
				break;
			case(1):
				m_gameState = PARAMETERS_MENU;
				break;
			case(2):
				m_gameState = QUIT_GAME;
				break;
			}
		}	
		
		m_buttonsStartMenu[i]->draw(m_gamePlan);

	}
	m_gamePlan->draw(title);
	m_gamePlan->display();

	*m_gameSprites = sf::Sprite(m_gamePlan->getTexture());
	m_gameSprites->setScale(sf::Vector2f(xWindowSize / 1920.f, yWindowSize / 1080.f));

	window->draw(*m_gameSprites);
} //CREATE BUTTON TAB IN CLASS TO INITIALIZE BUTTONS ONLY ONCE

void Render::playerMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition, m_gamePlan->getView()); //Put in hpp

	/////////////////////////////////////////////////////////////////
	sf::Text title;

	title.setFont(m_font);
	title.setString("Choose a mode");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(m_gamePlan->getSize().x / 2, m_gamePlan->getSize().x / 10);
	/////////////////////////////////////////////////////////////////

	m_gamePlan->clear();

	m_buttonsPlayersMenu[0]->update(worldPos);
	if (m_buttonsPlayersMenu[0]->isPressed()) {
		m_gameState = PONG_WINDOW;
		m_pongState = INIT_GAME;
		m_vsState = PVP;
	}

	m_buttonsPlayersMenu[1]->update(worldPos);
	if (m_buttonsPlayersMenu[1]->isPressed()) {
		m_gameState = PONG_WINDOW;
		m_pongState = INIT_GAME;
		m_vsState = PVCPU;
	}

	m_buttonsPlayersMenu[0]->draw(m_gamePlan);
	m_buttonsPlayersMenu[1]->draw(m_gamePlan);

	m_gamePlan->draw(title);
	m_gamePlan->display();

	*m_gameSprites = sf::Sprite(m_gamePlan->getTexture());
	m_gameSprites->setScale(sf::Vector2f(xWindowSize / 1920.f, yWindowSize / 1080.f));

	window->draw(*m_gameSprites);
}

void Render::pongWindow(sf::RenderWindow* window, double* dt, std::map<std::string, sf::Keyboard::Scancode>& pOneControls, std::map<std::string, sf::Keyboard::Scancode>& pTwoControls) {

	//Get window size to actualize scale gamePlan
	//
	//
	sf::Vector2u sizeWindow = window->getSize();


	//Initialize scoreText to display score of 2 players////////////////////////////////////////////////////////////
	//
	//
	sf::Text scoreText;
	scoreText.setFont(m_font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setString(std::to_string(m_score[0]) + "          " + std::to_string(m_score[1]));

	sf::FloatRect titleBox = scoreText.getGlobalBounds();
	scoreText.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	scoreText.setPosition(960, 40);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	case(INIT_GAME):

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
		m_ball->firstMove(0,141);

		//Score init
		m_score[0] = m_score[1] = 0;
		scoreText.setString( m_score[0]+" : "+ m_score[1]);

		//State Game init
		m_pongState = CURRENT_GAME;
		break;

	case(CURRENT_GAME):

		//Create a separate function for the "gameplay/pong"
		//
		//


		//Update players/ball/hitbox positions
		//
		//

		m_tabPlayers[0]->movePlayer(*dt, pOneControls);

		switch (m_vsState) {

		
		case(PVP):

			m_tabPlayers[1]->movePlayer(*dt, pTwoControls);
			break;
			
		case(PVCPU):

			if (m_ball->getBallShape().getPosition().x >= m_gamePlan->getSize().x / 5 * 4) { //Pretty good difficulty (if not delimited ai is impossible to win except by touching corners)
				if (m_tabPlayers[1]->display().getPosition().y > m_ball->getBallShape().getPosition().y) m_tabPlayers[1]->moveAI(*dt, "UP");
				else if (m_tabPlayers[1]->display().getPosition().y < m_ball->getBallShape().getPosition().y) m_tabPlayers[1]->moveAI(*dt, "DOWN");
				else m_tabPlayers[1]->moveAI(*dt, "NONE");
			}
			break;
		}

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
			m_ball->firstMove(325, 395);

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
			m_ball->firstMove(145, 215);
		}


		if (m_ballHitbox->futureCollision().y < 0 || m_ballHitbox->futureCollision().y > m_gamePlan->getSize().y - m_ball->getBallShape().getSize().y) {
			m_ball->changeDirection(1, -1);
		}



		topP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[0]->display().getSize().x - 2, 1.f));
		topP1.setPosition(m_tabPlayers[0]->display().getPosition());

		botP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[0]->display().getSize().x - 2, 1.f));
		botP1.setPosition(sf::Vector2f(m_tabPlayers[0]->display().getPosition().x + 1, m_tabPlayers[0]->display().getPosition().y + 100));

		if (m_ballHitbox->getHitbox()->intersects(*m_tabHitboxPlayers[0]->getHitbox())) {

			if (m_tabPlayers[0]->getMovement().y < 0 && m_ball->getMovement().y > 0) {
				m_ball->setPositionBall(sf::Vector2f(100.f + 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_tabPlayers[0]->getMovement().y > 0 && m_ball->getMovement().y < 0) {
				m_ball->setPositionBall(sf::Vector2f(100.f + 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_ballHitbox->getHitbox()->intersects(topP1.getGlobalBounds()) || m_ballHitbox->getHitbox()->intersects(botP1.getGlobalBounds())) {
				if (m_tabPlayers[0]->getMovement().y == 0) {
					m_ball->setPositionBall(sf::Vector2f(100.f - 20.f, m_ball->getBallShape().getPosition().y));
					m_ball->changeDirection(1, -1);
				}
				else if (m_tabPlayers[0]->getMovement().y > 0 && m_ball->getMovement().y > 0 || m_tabPlayers[0]->getMovement().y < 0 && m_ball->getMovement().y < 0) {
					m_ball->setPositionBall(sf::Vector2f(100.f + 20.f, m_ball->getBallShape().getPosition().y));
				}
			}
			else {
				m_ball->setPositionBall(sf::Vector2f(100.f + 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, 1);
			}
		}

		topP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[1]->display().getSize().x - 2, 1.f));
		topP1.setPosition(m_tabPlayers[1]->display().getPosition());

		botP1 = sf::RectangleShape(sf::Vector2f(m_tabPlayers[1]->display().getSize().x - 2, 1.f));
		botP1.setPosition(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x + 1, m_tabPlayers[0]->display().getPosition().y + 100));

		if (m_ballHitbox->getHitbox()->intersects(*m_tabHitboxPlayers[1]->getHitbox())) {

			if (m_tabPlayers[1]->getMovement().y < 0 && m_ball->getMovement().y > 0) {
				m_ball->setPositionBall(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x - 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_tabPlayers[1]->getMovement().y > 0 && m_ball->getMovement().y < 0) {
				m_ball->setPositionBall(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x - 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, -1);
			}
			else if (m_ballHitbox->getHitbox()->intersects(topP1.getGlobalBounds()) || m_ballHitbox->getHitbox()->intersects(botP1.getGlobalBounds())) {
				if (m_tabPlayers[1]->getMovement().y == 0) {
					m_ball->setPositionBall(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x + 20.f, m_ball->getBallShape().getPosition().y));
					m_ball->changeDirection(1, -1);
				}
				else if (m_tabPlayers[1]->getMovement().y > 0 && m_ball->getMovement().y > 0 || m_tabPlayers[1]->getMovement().y < 0 && m_ball->getMovement().y < 0) {
					m_ball->setPositionBall(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x - 20.f, m_ball->getBallShape().getPosition().y));
				}
			}
			else {
				m_ball->setPositionBall(sf::Vector2f(m_tabPlayers[1]->display().getPosition().x - 20.f, m_ball->getBallShape().getPosition().y));
				m_ball->changeDirection(-1, 1);
			}
		}

		//For me to quit game before ending an actual game (will be replaced with a quit button)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

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
			m_pongState = END_GAME;
			m_gameState = STARTUP_MENU;
			break;
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

		m_gamePlan->draw(*m_lineSprite);
		m_gamePlan->draw(scoreText);
		m_ball->draw(&*m_gamePlan);
		m_gamePlan->draw(m_tabPlayers[0]->display());
		m_gamePlan->draw(m_tabPlayers[1]->display());

		m_gamePlan->display();

		//Scale the sprite that got the actual texture and position in it to fit the window
		*m_gameSprites = sf::Sprite(m_gamePlan->getTexture());
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

		m_pongState = SLEEP;

		//Add Buttons for replay/main menu

		m_gameState = REPLAY_MENU;
		break;

	}
}

//DELETE PARAMETERS IN RENDER AND DECLARES IT IN DISPLAY WINDOW INSTEAD

void Render::parametersMenu(sf::RenderWindow* window, sf::Event* evenmt) {
	
	parameters.displayMenu(window, m_font, evenmt);
	if (parameters.getStateParametersMenu()) {
		m_gameState = STARTUP_MENU;
		parameters.setStateParametersMenu();
	}
}

bool Render::parametersSaved(){
	if (parameters.getSaved()) {
		m_gameState = STARTUP_MENU;
		parameters.setStateParametersMenu();
		return true;
	}
	return false;
}

void Render::replayMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition, m_gamePlan->getView()); //Put in hpp

	m_gamePlan->clear();

	/////////////////////////////////////////////////////////////////
	sf::Text title;

	title.setFont(m_font);
	if (m_score[0] == 11) title.setString("Player 1 won");
	else title.setString("Player 2 won");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(m_gamePlan->getSize().x / 2, m_gamePlan->getSize().x / 10);
	/////////////////////////////////////////////////////////////////

	m_gamePlan->draw(title);

	title.setString("Do you want to replay ?");
	titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.width / 2, titleBox.height / 2);
	title.setPosition(m_gamePlan->getSize().x / 2, m_gamePlan->getSize().x / 10 * 1.5);

	m_gamePlan->draw(title);

	for (int i(0); i < m_buttonsReplayMenu.size(); i++) {
		m_buttonsReplayMenu[i]->update(worldPos);

		if (m_buttonsReplayMenu[i]->isPressed()) {
			switch (i) {
			case(0):
				m_gameState = PLAYERS_MENU;
				break;
			case(1):
				m_gameState = STARTUP_MENU;
				break;
			case(2):
				m_gameState = QUIT_GAME;
				break;
			}
		}

		m_buttonsReplayMenu[i]->draw(m_gamePlan);
	}

	m_gamePlan->display();

	*m_gameSprites = sf::Sprite(m_gamePlan->getTexture());
	m_gameSprites->setScale(sf::Vector2f(xWindowSize / 1920.f, yWindowSize / 1080.f));

	window->draw(*m_gameSprites);
}

statesGame Render::getStateGame() const{
	return m_gameState;
}