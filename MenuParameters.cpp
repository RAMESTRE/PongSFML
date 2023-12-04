#include "MenuParameters.hpp"

MenuParameters::MenuParameters() {

	m_menuPlan = new sf::RenderTexture;
	m_menuPlan->create(1920, 1080);
	m_menuSprite = new sf::Sprite;

	m_tabStringText = { "Size", "Framerate", "V-Sync", "Fullscreen" };

	m_tabPossibleResolution = { "854x480", "960x540", "1024x576", "1280x720", "1366x768",
		"1600x900", "1920x1080", "2048x1152", "2560x1440", "3200x1800", "3840x2160"};

	m_tabPossibleFramerate = { "30", "60", "120", "Illimited" };

	m_indexTabRes = 0;

	m_indexTabFrame = 0;

	m_parametersState = INIT_GRAPHICS;

	//Create Function for creating rendertextures
	//
	//
	m_staticGraphicPlan = new sf::RenderTexture;
	m_staticGraphicPlan->create(1920/4, 580);
	m_staticGraphicSprite = new sf::Sprite;

	m_staticKeybindsPlan = new sf::RenderTexture;
	m_staticKeybindsPlan->create(1920 / 4, 580);
	m_staticKeybindsSprite = new sf::Sprite;

	m_staticTitlesPlan = new sf::RenderTexture;
	m_staticTitlesPlan->create(1920, 300);
	m_staticTitlesSprite = new sf::Sprite;
	//
	//
	//

	m_configFile.loadFromFileGraphic("Config/Graphic.ini");

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

	delete m_staticGraphicPlan;
	m_staticGraphicPlan = 0;
	delete m_staticGraphicSprite;
	m_staticGraphicSprite = 0;

	delete m_staticTitlesPlan;
	m_staticTitlesPlan = 0;
	delete m_staticTitlesSprite;
	m_staticTitlesSprite = 0;

	delete m_staticKeybindsPlan;
	m_staticKeybindsPlan = 0;
	delete m_staticKeybindsSprite;
	m_staticKeybindsSprite = 0;

}

void MenuParameters::displayMenu(sf::RenderWindow* window, sf::Font font) {
	
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);

	

	std::map<std::string, std::vector<Button*>>::iterator it;

	switch (m_parametersState) {

	case(INIT_GRAPHICS): //Create own rendertexture that initialized only one time (static)

		createStaticTitlePlan(font);
		createStaticGraphicPlan(font);
		createStaticKeybindPlan(font);

		for (int i(0); i < m_tabStringText.size(); i++) {
			if (m_tabStringText[i] == "Size") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabPossibleResolution[m_indexTabRes]);
			else if (m_tabStringText[i] == "Framerate") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabPossibleFramerate[m_indexTabFrame]);
			else if (m_tabStringText[i] == "V-Sync") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Enabled");
			else if (m_tabStringText[i] == "Fullscreen") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Enabled");

			m_tabTextSettingsBoxs[m_tabStringText[i]] = m_tabChosenSettings[m_tabStringText[i]].getGlobalBounds();
			
			m_tabChosenSettings[m_tabStringText[i]].setOrigin(m_tabTextSettingsBoxs[m_tabStringText[i]].width / 2, m_tabTextSettingsBoxs[m_tabStringText[i]].top + m_tabTextSettingsBoxs[m_tabStringText[i]].height / 2);
			m_tabChosenSettings[m_tabStringText[i]].setPosition(1920 / 2 / 4 * 3, 300 + (116 * (1 + i)));
		}

		m_parametersState = GRAPHICS;

		break;

	case(GRAPHICS):

		

		m_menuPlan->clear();

		it = m_tabButtons.begin();
		while (it != m_tabButtons.end()) {
			it->second[0]->update(mousePosition);
			if (it->second[0]->isPressed()) {
				if (it->first == "Size" && m_indexTabRes > 0) {
					m_indexTabRes -= 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleResolution[m_indexTabRes]);
					m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
					m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabTextSettingsBoxs[it->first].top + m_tabTextSettingsBoxs[it->first].height / 2);
				}
				else if (it->first == "Framerate" && m_indexTabFrame > 0) {
					m_indexTabFrame -= 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleFramerate[m_indexTabFrame]);
					m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
					m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabTextSettingsBoxs[it->first].top + m_tabTextSettingsBoxs[it->first].height / 2);
					
				} 
				else if (it->first == "V-Sync") {
					m_localVsync = !(m_localVsync);
				}
				else if (it->first == "Fullscreen") {
					m_localFullscreen = !(m_localFullscreen);
				}
			}
			it->second[1]->update(mousePosition);
			if (it->second[1]->isPressed()) {
				if (it->first == "Size" && m_indexTabRes < m_tabPossibleResolution.size() - 1) {
					m_indexTabRes += 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleResolution[m_indexTabRes]);
					m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
					m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabTextSettingsBoxs[it->first].top + m_tabTextSettingsBoxs[it->first].height / 2);
				}
				else if (it->first == "Framerate" && m_indexTabFrame < m_tabPossibleFramerate.size() - 1) {
					m_indexTabFrame += 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleFramerate[m_indexTabFrame]);
					m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
					m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabTextSettingsBoxs[it->first].top + m_tabTextSettingsBoxs[it->first].height / 2);
					
					std::cout << m_tabChosenSettings[it->first].getPosition().x << std::endl;
				}
				else if (it->first == "V-Sync") {
					m_localVsync = !(m_localVsync);
				}
				else if (it->first == "Fullscreen") {
					m_localFullscreen = !(m_localFullscreen);
				}
			}

			


			m_menuPlan->draw(m_tabChosenSettings[it->first]);
			it->second[0]->draw(m_menuPlan);
			it->second[1]->draw(m_menuPlan);
			it++;
		}
		m_menuPlan->draw(*m_staticTitlesSprite);
		m_menuPlan->draw(*m_staticGraphicSprite);
		m_menuPlan->draw(*m_staticKeybindsSprite);
		m_menuPlan->display();
		
		break;

	case(SAVE):
		m_configFile.saveChange(m_localWidthWindow, m_localHeightWindow, m_localFramerate, m_localVsync, m_localFullscreen);
		break;
	}

	const sf::Texture& parameterPlanUpdate = m_menuPlan->getTexture();
	*m_menuSprite = sf::Sprite(parameterPlanUpdate);
	m_menuSprite->setScale(sf::Vector2f(window->getSize().x / 1920.f, window->getSize().y / 1080.f)); //To put in display window directly + convert position for button
	window->draw(*m_menuSprite);

}

void MenuParameters::textOptions(sf::Text* text, sf::Font& font, int size, sf::Color color, std::string string) {
	text->setFont(font);
	text->setCharacterSize(size);
	text->setFillColor(color);
	text->setStyle(sf::Text::Bold);
	text->setString(string);
}

void MenuParameters::createStaticTitlePlan(sf::Font font) {
	////////////////////////
	sf::RectangleShape outlineTitles;
	outlineTitles = sf::RectangleShape(sf::Vector2f(1920 - 20, 300 - 20));
	outlineTitles.setPosition(10, 10);
	outlineTitles.setFillColor(sf::Color::Transparent);
	outlineTitles.setOutlineThickness(10.f);
	outlineTitles.setOutlineColor(sf::Color::Green);
	/////////////////////////

	sf::Text title;
	textOptions(&title, font, 50, sf::Color::White, "Graphics");

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(m_staticTitlesPlan->getSize().x / 4, 150);

	m_staticTitlesPlan->clear();

	m_staticTitlesPlan->draw(title);

	title.setString("Keybinds");
	title.setPosition((m_staticTitlesPlan->getSize().x / 4) * 3, 150);
	m_staticTitlesPlan->draw(title);

	m_staticTitlesPlan->draw(outlineTitles);////////////////////////

	m_staticTitlesPlan->display();

	*m_staticTitlesSprite = sf::Sprite(m_staticTitlesPlan->getTexture());

}

void MenuParameters::createStaticGraphicPlan(sf::Font font) {
	////////////
	sf::RectangleShape outline;
	outline = sf::RectangleShape(sf::Vector2f(480 - 20, 580 - 20));
	outline.setPosition(10, 10);
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(10.f);
	outline.setOutlineColor(sf::Color::Blue);
	///////////

	sf::FloatRect titleBox;

	m_staticGraphicPlan->clear();

	for (int i(0); i < m_tabStringText.size(); i++) {

		textOptions(&m_tabTextSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabStringText[i]);

		titleBox = m_tabTextSettings[m_tabStringText[i]].getGlobalBounds();
		m_tabTextSettings[m_tabStringText[i]].setOrigin(titleBox.width / 2, titleBox.top + titleBox.height / 2);
		m_tabTextSettings[m_tabStringText[i]].setPosition(240, 116 * (1 + i));

		m_tabButtons[m_tabStringText[i]] = { new Button(1920 / 2 / 4 * 3 - 150, 300 + (116 * (1 + i)), 10.f, 40.f, 0, "<"), new Button(1920 / 2 / 4 * 3 + 150, 300 + (116 * (1 + i)), 10.f, 40.f, 0, ">") };

		m_staticGraphicPlan->draw(m_tabTextSettings[m_tabStringText[i]]);

		m_staticGraphicPlan->draw(outline);/////////////////////////////////////////////

	}
	m_staticGraphicPlan->display();

	*m_staticGraphicSprite = sf::Sprite(m_staticGraphicPlan->getTexture());
	m_staticGraphicSprite->setPosition(0, 300);
}

void MenuParameters::createStaticKeybindPlan(sf::Font font) {
	///////////////////
	sf::RectangleShape outlineKey;
	outlineKey = sf::RectangleShape(sf::Vector2f(480 - 20, 580 - 20));
	outlineKey.setPosition(10, 10);
	outlineKey.setFillColor(sf::Color::Transparent);
	outlineKey.setOutlineThickness(10.f);
	outlineKey.setOutlineColor(sf::Color::Red);
	//////////////////

	m_staticKeybindsPlan->clear();
	m_staticKeybindsPlan->draw(outlineKey);
	m_staticKeybindsPlan->display();

	*m_staticKeybindsSprite = sf::Sprite(m_staticKeybindsPlan->getTexture());
	m_staticKeybindsSprite->setPosition(1920 / 2, 300);

}

void MenuParameters::getSettings() {

	m_localWidthWindow = m_configFile.getSizeWindow().width;
	m_localHeightWindow = m_configFile.getSizeWindow().height;
	m_localFramerate = m_configFile.getFramerate();
	m_localFullscreen = m_configFile.getFullscreen();
	m_localVsync = m_configFile.getVSync();

}