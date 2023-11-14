#ifndef DEF_HITBOX
#define DEF_HITBOX

#include "Player.hpp"
#include "Ball.hpp"

class Hitbox {

public:
	Hitbox(Player& player);
	Hitbox(Ball& ball);
	~Hitbox();
	void hitboxUpdate(Player& player);
	void hitboxUpdate(Ball& ball);
	sf::RectangleShape futureMovement();

private:

	sf::FloatRect* m_boundingBox;
	sf::Vector2f m_movementEntity;

};

#endif // !DEF_HITBOX
