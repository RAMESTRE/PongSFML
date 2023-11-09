#ifndef DEF_RENDER
#define DEF_RENDER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Button.hpp"
#include "Player.hpp"
#include "Hitbox.hpp"
#include "Ball.hpp"

enum statesGame { STARTUP_MENU = 0, PLAYERS_MENU = 1, PONG_WINDOW = 2, REPLAY_MENU = 3, PARAMETERS_MENU = 4, QUIT_GAME = 5 }; //Describe the current state of the whole game(menus, pong game,...)

enum statesPong {SLEEP = 0, INIT_PVP = 1, INIT_PVCPU = 2, CURRENT_GAME = 3, END_GAME = 4}; //Describe the current state of the PONG game

class Render {

public:

	Render();
	~Render();
	void startMenu(sf::RenderWindow* window);
	void playerMenu(sf::RenderWindow* window);
	void pongWindow(sf::RenderWindow* window, double* dt);
	void parametersMenu();
	void replayMenu();

	statesGame getStateGame() const;

private:

	sf::Font m_font;
	statesGame m_gameState;
	statesPong m_pongState;

	std::vector<Player*> m_tabPlayers;
	std::vector<Hitbox*> m_tabHitboxPlayers;

	Ball m_ball;
	sf::FloatRect m_ballHitbox; // For now will work with ball hitbox delared here and not using hitbox class (cause hitbox is only compatible with player class right now)

};

#endif // !DEF_RENDER
