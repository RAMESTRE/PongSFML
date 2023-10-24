#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player {

public:

	Player();
	virtual ~Player();

	void movePlayer(sf::RectangleShape& rectangle, sf::Vector2u sizeWindow = sf::Vector2u(800,600)) const;
	sf::RectangleShape drawPlayer() const;

private:

};

#endif // !DEF_PLAYER
