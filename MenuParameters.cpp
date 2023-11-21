#include "MenuParameters.hpp"

MenuParameters::MenuParameters() {

	m_menuPlan = new sf::RenderTexture;
	m_menuPlan->create(1920, 1080);
	m_menuSprite = new sf::Sprite;

	m_tabResolution = { "854x480", "960x540", "1024x576", "1280x720", "1366x768", 
		"1600x900", "1920x1080", "2048x1152", "2560x1440", "3200x1800", "3840x2160"};

	m_indexTabRes = 0;

	m_parametersState = INIT_GRAPHICS;

	m_staticPlan = new sf::RenderTexture;
	m_staticPlan->create(m_menuPlan->getSize().x / 2, 580);
	m_staticSprite = new sf::Sprite;

}

MenuParameters::~MenuParameters() {

	delete m_menuPlan;
	m_menuPlan = 0; 
	delete m_menuSprite;
	m_menuSprite = 0;
	std::cout << "MenuParameters pointer and content destroyed" << std::endl;

	std::map<std::string, std::vector<Button*>>::iterator itr;

	for (itr = m_tabButtons.begin(); itr != m_tabButtons.end(); ++itr){
		delete itr->second[0];
		itr->second[0] = 0;
		delete itr->second[1];
		itr->second[1] = 0;
	}
	m_tabButtons.clear();

	delete m_staticPlan;
	m_staticPlan = 0;
	delete m_staticSprite;
	m_staticSprite = 0;

}

void MenuParameters::displayMenu(sf::RenderWindow* window, sf::Font font) {

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);

	sf::Text resolution;
	sf::FloatRect titleBox = resolution.getGlobalBounds();

	std::map<std::string, std::vector<Button*>>::iterator it;

	switch (m_parametersState) {
	case(INIT_GRAPHICS): //Create own rendertexture that initialized only one time (static)
		m_staticPlan->clear();
		m_tabStringText = {"Size", "Framerate", "VSYNC", "Fullscreen"};
		for (int i(0); i < m_tabStringText.size(); i++) {
			m_tabTextSettings[m_tabStringText[i]].setFont(font);
			m_tabTextSettings[m_tabStringText[i]].setCharacterSize(50);
			m_tabTextSettings[m_tabStringText[i]].setFillColor(sf::Color::White);
			m_tabTextSettings[m_tabStringText[i]].setStyle(sf::Text::Bold);
			m_tabTextSettings[m_tabStringText[i]].setString(m_tabStringText[i]);

			m_tabTextSettingsBoxs[m_tabStringText[i]] = m_tabTextSettings[m_tabStringText[i]].getGlobalBounds();
			m_tabTextSettings[m_tabStringText[i]].setOrigin(m_tabTextSettingsBoxs[m_tabStringText[i]].left + m_tabTextSettingsBoxs[m_tabStringText[i]].width / 2, m_tabTextSettingsBoxs[m_tabStringText[i]].top + m_tabTextSettingsBoxs[m_tabStringText[i]].height / 2);
			m_tabTextSettings[m_tabStringText[i]].setPosition(40*i, 40*i);

			m_tabButtons[m_tabStringText[i]] = { new Button(50.f, 50.f * (1 + i), 10.f, 20.f, 0, "<"), new Button(100.f, 50.f * (1 + i), 10.f, 20.f, 0, ">") };

			m_staticPlan->draw(m_tabTextSettings[m_tabStringText[i]]);
		}
		m_staticPlan->display();

		*m_staticSprite = sf::Sprite(m_staticPlan->getTexture());
		m_staticSprite->setPosition(0, 300);

		m_parametersState = GRAPHICS;
		break;

	case(GRAPHICS):

		resolution.setFont(font);
		resolution.setCharacterSize(50);
		resolution.setFillColor(sf::Color::White);
		resolution.setStyle(sf::Text::Bold);
		resolution.setString(m_tabResolution[m_indexTabRes]);

		titleBox = resolution.getGlobalBounds();
		resolution.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
		resolution.setPosition(960, 40);

		m_menuPlan->clear();

		it = m_tabButtons.begin();
		while (it != m_tabButtons.end()) {
			it->second[0]->update(mousePosition);
			if (it->second[0]->isPressed()) {
				if (it->first == "Size" && m_indexTabRes > 0) {
					m_indexTabRes -= 1;
					resolution.setString(m_tabResolution[m_indexTabRes]);
				} //else if it first == "FRAMERATE",...
			}
			it->second[1]->update(mousePosition);
			if (it->second[1]->isPressed()) {
				if (it->first == "Size" && m_indexTabRes < m_tabResolution.size() - 1) {
					m_indexTabRes += 1;
					resolution.setString(m_tabResolution[m_indexTabRes]);
				} //else if it first == "FRAMERATE",...
			}
			it->second[0]->draw(m_menuPlan);
			it->second[1]->draw(m_menuPlan);
			it++;
		}
		m_menuPlan->draw(*m_staticSprite);
		m_menuPlan->draw(resolution);
		m_menuPlan->display();
		
		break;

	case(KEYBINDS):

		break;

	}

	const sf::Texture& parameterPlanUpdate = m_menuPlan->getTexture();
	*m_menuSprite = sf::Sprite(parameterPlanUpdate);
	m_menuSprite->setScale(sf::Vector2f(window->getSize().x / 1920.f, window->getSize().y / 1080.f)); //To put in display window directly + convert position for button
	window->draw(*m_menuSprite);

}

void MenuParameters::graphicSection() {

}

void MenuParameters::keybindSection() {

}