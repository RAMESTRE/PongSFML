#ifndef DEF_HITBOX
#define DEF_HITBOX

#include "Player.hpp"

class Hitbox {

public:
	Hitbox(Player& player);
	~Hitbox();
	void hitboxUpdate(Player& player);
	sf::RectangleShape futureCollision(Hitbox& otherEntityHitbox);

private:

	sf::FloatRect* m_boundingBox;
	double m_movementEntity;

};

#endif // !DEF_HITBOX
