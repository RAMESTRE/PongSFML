#ifndef DEF_MENUPARAMETERS
#define DEF_MENUPARAMETERS

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Configuration.hpp"
#include <vector>
#include <map>

enum stateParameters { INIT_GRAPHICS = 0, GRAPHICS = 1, APPLY = 2, DEFAULT = 3, SAVE = 4, BACK = 5 };

class MenuParameters {
	
public:

	MenuParameters();
	~MenuParameters();

	void displayMenu(sf::RenderWindow* window, sf::Font font);
	
	void getSettings();

private:

	void textOptions(sf::Text* text, sf::Font& font, int size, sf::Color color, std::string string);
	void createStaticTitlePlan(sf::Font font);
	void createStaticGraphicPlan(sf::Font font);
	void createStaticKeybindPlan(sf::Font font);


	stateParameters m_parametersState;


	//Main Texture in which everything drawn (dynamic and static)
	//
	//
	sf::RenderTexture* m_menuPlan;
	sf::Sprite* m_menuSprite;

	//Vectors for stocking differents options (resolution, framerates,...)
	//
	//
	std::vector<std::string> m_tabResolution;
	std::vector<std::string> m_tabFramerate;
	int m_indexTabRes;
	int m_indexTabFrame;

	//Local change that will be displayed if save button pressed
	//
	//
	int m_localWidthWindow, m_localHeightWindow, m_localFramerate;
	bool m_localVsync, m_localFullscreen;

	std::vector<std::string> m_tabStringText;
	std::map<std::string, sf::Text> m_tabTextSettings;
	std::map<std::string, sf::FloatRect> m_tabTextSettingsBoxs;
	std::map <std::string, std::vector<Button*>> m_tabButtons;

	//Static Texture (only drawn in init)
	sf::RenderTexture* m_staticGraphicPlan;
	sf::Sprite* m_staticGraphicSprite;

	sf::RenderTexture* m_staticTitlesPlan;
	sf::Sprite* m_staticTitlesSprite;

	sf::RenderTexture* m_staticKeybindsPlan;
	sf::Sprite* m_staticKeybindsSprite;

	//To save, load and put to default settings
	Configuration m_configFile;

};

#endif // !DEF_MENUPARAMETERS
