#include "Configuration.hpp"

Configuration::Configuration() {
	defaultGraphicParameters();
}

Configuration::~Configuration() {
	std::cout << "Config deleted" << std::endl;
}

void Configuration::saveToFileGraphic(std::string path) {

	std::ofstream file(path);

	if (file.is_open()) {
		file << "SIZE=" << m_widthWindow << "x" << m_heightWindow;
		file << "FRAMERATE=" << m_framerate;
		file << "VSYNC=" << m_vsync;
		file << "FULLSCREEN=" << m_fullscreen;
	}
	else {
		std::cout << "Cannot open config file" << std::endl;
	}
}

void Configuration::loadFromFileGraphic(std::string path) {

	std::ifstream flux(path);
	std::string line;
	std::string settings;

	if (flux.is_open()) {
		int i = 0;
		while (std::getline(flux, line)) {

			settings = line.substr(line.find('=')+1);
			
			if (line.substr(0, line.find('=')) == "SIZE") {

				m_widthWindow = std::stoi(settings.substr(0, settings.find('x')));
				m_heightWindow = std::stoi(settings.substr(settings.find('x') + 1));

			}
			else if (line.substr(0, line.find('=')) == "FRAMERATE") {
				m_framerate = std::stoi(settings);
			}
			else if (line.substr(0, line.find('=')) == "VSYNC") {
				m_vsync = (settings=="true");
			}
			else if (line.substr(0, line.find('=')) == "FULLSCREEN"){
				m_fullscreen == (settings == "true");
			}
		}
	}
	else {
		std::cout << "Cannot open config file" << std::endl;
	}
}

sf::VideoMode Configuration::getSizeWindow() const {
	return sf::VideoMode(m_widthWindow, m_heightWindow);
}

int Configuration::getFramerate() const {
	return m_framerate;
}

bool Configuration::getFullscreen() const {
	return m_framerate;
}

bool Configuration::getVSync() const {
	return m_vsync;
}

void Configuration::defaultGraphicParameters() {

	m_widthWindow = sf::VideoMode::getDesktopMode().width;
	m_heightWindow = sf::VideoMode::getDesktopMode().height;
	m_framerate = 60;
	m_fullscreen = false;
	m_vsync = false;

}