#ifndef DEF_BUTTON
#define DEF_BUTTON

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

enum states {BTN_INACTIVE = 0, BTN_HOVER = 1, BTN_PRESSED = 2, BTN_RELEASED = 3};

class Button {

public:

	Button(double x, double y, double width, double height,int id, int size, std::string textButton);
	~Button();

	bool isPressed() const;
	void update(sf::Vector2i& mousePosition);
	void update(sf::Vector2f& mousePosition); //To use with pixel to coord position
	void draw(sf::RenderTarget* window) const;

private:

	void setStyle();

	sf::RectangleShape m_shapeButton;
	sf::Text m_textButton;
	std::string m_textButtonString;
	sf::Font m_font;
	sf::FloatRect m_hitboxButton;
	sf::FloatRect m_hitboxText;
	states m_buttonState;
	int m_id;

};

#endif // !DEF_BUTTON
