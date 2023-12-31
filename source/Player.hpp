#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

class Player {

public:

	Player();
	Player(sf::Vector2u& sizeWindow);
	~Player();
	void setPosition(sf::Vector2f positionPlayer) const;
	sf::RectangleShape& display();
	void movePlayer(double& deltaTime, std::map<std::string, sf::Keyboard::Scancode>& controls); //To modify later for player 1 and 2 to have differents controls
	sf::Vector2f getMovement() const;

	void moveAI(double& deltaTime, std::string direction);

private:

	sf::RectangleShape *m_playerShape;
	sf::Vector2u m_sizeWindow;
	double m_speed;
	sf::Vector2f m_movement;

};

#endif // !DEF_PLAYER
