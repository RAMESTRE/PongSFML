#ifndef DEF_RENDER
#define DEF_RENDER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.hpp"

enum statesGame { STARTUP_MENU = 0, PONG_GAME = 1, REPLAY_MENU = 2, PARAMETERS_MENU = 3, QUIT_GAME = 4 };

class Render {

public:
	Render();
	~Render();
	void startMenu(sf::RenderWindow* window);
	void pongGame();
	void replayMenu();

	statesGame getStateGame() const;

private:

	sf::Font m_font;
	statesGame m_gameState;

};

#endif // !DEF_RENDER
