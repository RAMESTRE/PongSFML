#ifndef DEF_MENUPARAMETERS
#define DEF_MENUPARAMETERS

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <vector>

class MenuParameters {
	
public:

	MenuParameters();
	~MenuParameters();
	void displayMenu(sf::RenderWindow* window, sf::Font font);

private:

	sf::RenderTexture* m_menuPlan;
	sf::Sprite* m_menuSprite;

	std::vector<std::string> m_tabResolution;
	int m_indexTabRes;
	

};

#endif // !DEF_MENUPARAMETERS
