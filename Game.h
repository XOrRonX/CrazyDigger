
/*
Class Game 
This class holds all the screens and also 
have a menu for start a game or exit
This class calls run() of each screen (class Controller)
and wait until the screen finsinhed running and then 
it can move to the next screen

*/


#pragma once

#include "Controller.h"
#include <memory>
#include <vector>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game::Game();
	~Game();

	// add creation add a controller for every input file
	// that the main() function find
	void addController(char *fileName);

	// do the menu screen and call run of each controller (screen)
	bool run(unsigned int firstTime);
	

private:

	// runs the menu for start or end a game
	int hendelEndStartGame();

	// takes care of mouse clicking on start or end game
	int MousePressedHandler(sf::Event event);

	// when moving between screens read the data from previous screen
	void saveDataToNextScrean();

	// after one screen is done move to next screen if exist
	unsigned int moveToNextScreen();

	// hold all the contollers - each one of them is a screen
	std::vector<std::unique_ptr<Controller>> m_controllers;
	
	unsigned int m_numOfScreens;
	unsigned int m_activeScreen; // which controller is active now
	unsigned int m_totalPoints; // acumulate all points 
	unsigned int m_lifeLeft;   
	sf::RenderWindow m_window;
	std::vector<sf::Texture> m_textures;
	sf::Font m_font;
	Board m_board;
	sf::RectangleShape m_endgame;
	sf::RectangleShape m_start;
	sf::RectangleShape m_backround;
	sf::Music music;
	sf::SoundBuffer soundBufferSelect;
	sf::Sound soundSelect;

};

