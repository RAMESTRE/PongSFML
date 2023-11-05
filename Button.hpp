#ifndef DEF_BUTTON
#define DEF_BUTTON

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

enum states {BTN_INACTIVE = 0, BTN_HOVER = 1, BTN_PRESSED = 2};

class Button {

public:

	Button(double x, double y, double width, double height,int id, std::string textButton);
	~Button();

	bool isPressed() const;
	void update();
	void draw(sf::RenderWindow* window) const;

private:

	sf::RectangleShape m_shapeButton;
	sf::Text m_textButton;
	sf::Font m_font;
	int m_id;
	states m_buttonState;

};

#endif // !DEF_BUTTON
