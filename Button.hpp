#ifndef DEF_BUTTON
#define DEF_BUTTON

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

enum states {BTN_INACTIVE = 0, BTN_HOVER = 1, BTN_PRESSED = 2, BTN_RELEASED = 3};

enum styles {BTN_HOOK = 0, BTN_BASIC = 1};

class Button {

public:

	Button(double x, double y, double width, double height,int id, std::string textButton);
	~Button();

	bool isPressed() const;
	void update(sf::Vector2i& mousePosition);
	void update(sf::Vector2f& mousePosition);
	void draw(sf::RenderTarget* window) const;

private:

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
