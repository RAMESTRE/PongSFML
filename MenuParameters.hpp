#ifndef DEF_MENUPARAMETERS
#define DEF_MENUPARAMETERS

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Configuration.hpp"
#include <vector>
#include <map>

///////////////////////////////PUT FONT AS AN ATTRIBUTE OF CONSTRUCTOR INSTEAD OF ALL THE METHODS

enum stateParameters { INIT_GRAPHICS = 0, GRAPHICS = 1, APPLY = 2, DEFAULT = 3, SAVE = 4, BACK = 5, CHOOSING_KEY = 6};

class MenuParameters {
	
public:

	MenuParameters();
	~MenuParameters();

	void displayMenu(sf::RenderWindow* window, sf::Font font, sf::Event* evenmt);
	
	void getSettings();

	bool getStateParametersMenu() const;
	void setStateParametersMenu();

	bool getSaved() const;

private:

	void textOptions(sf::Text* text, sf::Font& font, int size, sf::Color color, std::string string);
	void createStaticTitlePlan(sf::Font font);
	void createStaticGraphicPlan(sf::Font font);
	void createStaticKeybindPlan(sf::Font font);
	void createStaticChoosePlan(sf::Font font);

	void createButtons();

	void displayActualSettings();


	stateParameters m_parametersState;


	//Main Texture in which everything drawn (dynamic and static)
	//
	//
	sf::RenderTexture* m_menuPlan;
	sf::Sprite* m_menuSprite;

	//Vectors for stocking differents options (resolution, framerates,...)
	//
	//
	std::vector<std::string> m_tabPossibleResolution;
	std::vector<std::string> m_tabPossibleFramerate;
	int m_indexTabRes;
	int m_indexTabFrame;

	//Local change that will be displayed if save button pressed
	//
	//
	int m_localWidthWindow, m_localHeightWindow, m_localFramerate;
	bool m_localVsync, m_localFullscreen;

	std::vector<std::string> m_tabStringText; //Differents Graphics Options
	std::map<std::string, sf::Text> m_tabChosenSettings; //To stock graphics settings to display on screen in text (ex:800x400, enabled,...) => Dynamic
	std::map<std::string, sf::Text> m_tabTextSettings; //To stock Settings options to display on screen (size, framerate,...) => Static
	std::map<std::string, sf::FloatRect> m_tabTextSettingsBoxs; //Stock FloatRect tabChosenSettings Text
	std::map<std::string, std::vector<Button*>> m_tabButtons; //To stock button that will change the chosen option => Dynamic 

	std::map<std::string, Button*> m_bottomLineButtons; 

	//Keybinds

	std::map<std::string, Button*> m_keybindsButtonsPlayerOne;
	std::map<std::string, Button*> m_keybindsButtonsPlayerTwo;

	Button* m_choosingKey; //Put in tuple string button* (to know which action will be modified)
	sf::Keyboard::Scancode* m_newKey;

	std::map<std::string, sf::Keyboard::Scancode>* m_localPlayerOneControl; //Stock keybinds players
	std::map<std::string, sf::Keyboard::Scancode>* m_localPlayerTwoControl;


	//Static Texture (only drawn in init)
	sf::Sprite* m_staticGraphicSprite;

	sf::Sprite* m_staticTitlesSprite;


	////For Controls part

	sf::Sprite* m_staticKeybindsSprite;

	sf::Sprite* m_staticActionSprite;

	////Texture to display choose key pop up

	sf::Sprite* m_staticChooseSprite;

	std::map<std::string, sf::RenderTexture*> m_tabTextures;

	//To save, load and put to default settings
	Configuration m_configFile;

};

#endif // !DEF_MENUPARAMETERS
