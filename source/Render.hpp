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

enum statesPong {SLEEP = 0, INIT_GAME = 1, CURRENT_GAME = 3, END_GAME = 4}; //Describe the current state of the PONG game

enum statesVs { PVP = 0, PVCPU = 1 };


class Render {

public:

	Render();
	~Render();

	void startMenu(sf::RenderWindow* window);
	void playerMenu(sf::RenderWindow* window);

	//Content actual game method

	void pongWindow(sf::RenderWindow* window, double* dt, std::map<std::string, sf::Keyboard::Scancode>& pOneControls, std::map<std::string, sf::Keyboard::Scancode>& pTwoControls);


	void parametersMenu(sf::RenderWindow* window, sf::Event* evenmt);
	bool parametersSaved();

	void replayMenu(sf::RenderWindow* window);

	void ai();

	statesGame getStateGame() const;

private:

	//Create Plan in the game will be created (help with get a good resize of window)
	sf::RenderTexture* m_gamePlan;

	//Render
	sf::Sprite* m_gameSprites;

	sf::Font m_font;

	//startMenu Attributes
	//
	//
	std::vector<Button*> m_buttonsStartMenu;

	//PlayerMenu Attributes

	std::vector<Button*> m_buttonsPlayersMenu;

	//PongWindows Attributes
	//
	// 
	sf::RenderTexture* m_line;
	sf::Sprite* m_lineSprite;

	statesGame m_gameState;
	statesPong m_pongState;
	statesVs m_vsState;

	std::vector<Player*> m_tabPlayers;
	std::vector<Hitbox*> m_tabHitboxPlayers;

	Ball* m_ball;
	Hitbox* m_ballHitbox; // For now will work with ball hitbox delared here and not using hitbox class (cause hitbox is only compatible with player class right now)

	int m_score[2];

	//ReplayMenu Attributes
	//
	//
	std::vector<Button*> m_buttonsReplayMenu;

	//MenuParameters
	MenuParameters parameters;


	//Add map with keybinds to move the players. Is modified with func parametersMenu
	std::map<std::string, sf::Keyboard> playerOneBinds;
	std::map<std::string, sf::Keyboard> playerTwoBinds;

};

#endif // !DEF_RENDER
