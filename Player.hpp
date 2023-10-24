#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player {

public:

	Player();
	virtual ~Player();

	void playerSetPosition(sf::Vector2f& playerPosition, sf::RectangleShape& rectangle) const;
	void movePlayer(sf::RectangleShape& rectangle, sf::Vector2u sizeWindow = sf::Vector2u(800,600), sf::Keyboard::Key keyUp = sf::Keyboard::Key::Z, sf::Keyboard::Key keyDown = sf::Keyboard::Key::S) const;
	sf::RectangleShape drawPlayer() const;

private:

};

#endif // !DEF_PLAYER
