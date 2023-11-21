#ifndef DEF_MENUPARAMETERS
#define DEF_MENUPARAMETERS

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <vector>
#include <map>

enum stateParameters {INIT_GRAPHICS = 0, INIT_KEYBINDS = 1, GRAPHICS = 2, KEYBINDS = 3, SAVE = 4};

class MenuParameters {
	
public:

	MenuParameters();
	~MenuParameters();
	void displayMenu(sf::RenderWindow* window, sf::Font font);
	void graphicSection();
	void keybindSection();

private:

	//Main Texture in which everything drawn (dynamic and static)
	sf::RenderTexture* m_menuPlan;
	sf::Sprite* m_menuSprite;

	std::vector<std::string> m_tabResolution;
	int m_indexTabRes;
	
	stateParameters m_parametersState;
	int m_localWidthWindow, m_localHeightWindow, m_localFramerate;
	bool m_localVsync, m_localFullscreen;

	std::vector<std::string> m_tabStringText;
	std::map<std::string, sf::Text> m_tabTextSettings;
	std::map<std::string, sf::FloatRect> m_tabTextSettingsBoxs;
	//std::vector<std::string> m_tabTextTitle;
	std::map <std::string, std::vector<Button*>> m_tabButtons;

	//Static Texture (only drawn in init)
	sf::RenderTexture* m_staticPlan;
	sf::Sprite* m_staticSprite;

};

#endif // !DEF_MENUPARAMETERS
