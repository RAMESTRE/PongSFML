#ifndef DEF_RENDER
#define DEF_RENDER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

#include "Button.hpp"
#include "Player.hpp"
#include "Hitbox.hpp"
#include "Ball.hpp"

#include"MenuParameters.hpp"

enum statesGame { STARTUP_MENU = 0, PLAYERS_MENU = 1, PONG_WINDOW = 2, REPLAY_MENU = 3, PARAMETERS_MENU = 4, QUIT_GAME = 5 }; //Describe the current state of the whole game(menus, pong game,...)

enum statesPong {SLEEP = 0, INIT_PVP = 1, INIT_PVCPU = 2, CURRENT_GAME = 3, END_GAME = 4}; //Describe the current state of the PONG game


class Render {

public:

	Render();
	~Render();

	void startMenu(sf::RenderWindow* window);
	void playerMenu(sf::RenderWindow* window);


	void pongWindow(sf::RenderWindow* window, double* dt);

	void parametersMenu(sf::RenderWindow* window);
	bool parametersSaved();

	void replayMenu();

	statesGame getStateGame() const;

private:


	sf::Font m_font;

	//startMenu Attributes
	//
	//
	std::vector<Button*> m_buttonsStartMenu;

	//PongWindows Attributes
	//
	// 
	//Create Plan in the game will be created (help with get a good resize of window)
	sf::RenderTexture* m_gamePlan;

	//Render
	sf::Sprite* m_gameSprites;

	statesGame m_gameState;
	statesPong m_pongState;

	std::vector<Player*> m_tabPlayers;
	std::vector<Hitbox*> m_tabHitboxPlayers;

	Ball* m_ball;
	Hitbox* m_ballHitbox; // For now will work with ball hitbox delared here and not using hitbox class (cause hitbox is only compatible with player class right now)

	int m_score[2];

	//MenuParameters
	MenuParameters parameters;


	//Add map with keybinds to move the players. Is modified with func parametersMenu
	std::map<std::string, sf::Keyboard> playerOneBinds;
	std::map<std::string, sf::Keyboard> playerTwoBinds;

};

#endif // !DEF_RENDER
