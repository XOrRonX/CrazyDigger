#include "Game.h"
#include <memory>
#include "Controller.h"
#include <time.h>
#include <Windows.h>
#include <SFML/Audio.hpp>



Game::Game() :
	m_window(sf::VideoMode(600, 300), "Crazy Digger"), // menu screen
	m_textures(25)
{
	m_totalPoints = 0;
	m_numOfScreens = 0;
	m_activeScreen = 0;
	m_lifeLeft = 0;
	m_endgame.setSize({ 110 , 80 }); // endgame button
	m_start.setSize({ 340 , 100 });   // start a game button
	m_backround.setSize( {600,310 });
	sf::Vector2f endPos;
	sf::Vector2f startPos;
	sf::Vector2f backroundPos;
	m_window.setVisible(false);   
	m_font.loadFromFile("Gabriola.TTF");
	if (!m_textures[VEND].loadFromFile("quit.png")
		|| !m_textures[VSTART].loadFromFile("start.png")
		|| !m_textures[VBACKROUND ].loadFromFile("backround.png")
		)
	{
		m_window.close();
		return;
	}

	endPos = { 565,65 }; // position of the two buttons
	startPos = { 300,250 };
	backroundPos = { 300,145 };


	//----------------endgame-------------------------------

	m_endgame.setPosition(endPos);
	m_endgame.setTexture(&m_textures[VEND]);
	m_endgame.setOrigin(m_endgame.getLocalBounds().width / 2,
		m_endgame.getLocalBounds().height / 2);
	
	//----------------startgame------------------------------

	m_start.setPosition(startPos);
	m_start.setTexture(&m_textures[VSTART]);
	m_start.setOrigin(m_start.getLocalBounds().width / 2,
		m_start.getLocalBounds().height / 2);

	//----------------backround------------------------------

	m_backround.setPosition(backroundPos);
	m_backround.setTexture(&m_textures[VBACKROUND]);
	m_backround.setOrigin(m_backround.getLocalBounds().width / 2,
		m_backround.getLocalBounds().height / 2);


	//--------------------sound-----------------------------

	if (!soundBufferSelect.loadFromFile("select.wav"))
		printf("cannot open file\n");
	soundSelect.setBuffer(soundBufferSelect);

	if (!music.openFromFile("Friends.ogg"))
		printf("cannot open file\n");

}


Game::~Game()
{
}

// Add a new controller to the vector
void Game::addController(char *fileName)
{
	m_controllers.push_back(std::make_unique<Controller,
		char * & , unsigned int & >(fileName, m_numOfScreens));
	m_numOfScreens++;
}


bool Game::run(unsigned int firstTime)
{
	if (firstTime) // show the buttons if first time 
		           // second time is shown by the options below
	{
		switch (hendelEndStartGame()) {
		case VEND:
		case VCLOSE:
			soundSelect.play();
			return false;
		case VSTART:
			soundSelect.play();
			break;
		};
	}
	
	music.setLoop(true);
	music.play();
	music.setVolume(20.0f);
	
	while (m_activeScreen < m_numOfScreens)
	{
		m_controllers[m_activeScreen]->run(); // run a screen
		// check what is the state at the return from the screen
		unsigned int state = m_controllers[m_activeScreen]->getState();
		if (state == CRAZY_DIGGER_FOUND_LAST_DIAMOND)
		{
			if (moveToNextScreen() == GAME_OVER) //no more screens
			{
				m_controllers[m_activeScreen - 1]->printInfo(" GAME WON \n  ;-)");
				m_controllers[m_activeScreen - 1]->display();
				Sleep(3000);
				m_controllers[m_activeScreen - 1]->closeWindow();
				break;
			}
			else // there are more screens so close the prev window 
				m_controllers[m_activeScreen-1]->closeWindow();
		}
		if ((state == GAME_OVER) || (state == EXIT_GAME))
			break;
	}
	switch (hendelEndStartGame()) {
	case VEND:
	case VCLOSE:
		soundSelect.play();
		return false;
	case VSTART:
		soundSelect.play();
		return true;
	};
	return false;
}

// handle the screen of exit or start a game
int Game::hendelEndStartGame()
{
	sf::Event event{};
	m_window.setVisible(true);
	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_start);
		m_window.draw(m_backround);
		m_window.draw(m_endgame);
		m_window.display();
		m_window.waitEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			return VCLOSE;
			break;
		case sf::Event::MouseButtonPressed:
			if (MousePressedHandler(event) == VSTART)
			{
				
				m_window.setVisible(false);
				return VSTART;
			}
			if (MousePressedHandler(event) == VEND)
			{
				m_window.close();
				return VEND;
			}
			break;
		default:
			break;
		}
		
	}
	return -1;
}


// checks where the mouse cursor was the click was pressed 
// this is to decide if start, end or nothing 
int Game::MousePressedHandler(sf::Event event)
{
	const auto coords = m_window.mapPixelToCoords
	({ event.mouseButton.x, event.mouseButton.y });

	if (m_endgame.getGlobalBounds().contains(coords) == true)
		return VEND;

	if (m_start.getGlobalBounds().contains(coords) == true)
		return VSTART;
	
	return -1; // the click was outside the two boxes
}



// one screen is done now move to the next screen - each screen is a controller
unsigned int Game::moveToNextScreen()
{
	saveDataToNextScrean();

	// active screen is the next one
	m_activeScreen++;
	if (m_activeScreen >= m_numOfScreens)
		return GAME_OVER;

	// copy the data to the next screen
	m_controllers[m_activeScreen]->setPoints(m_totalPoints);
	m_controllers[m_activeScreen]->setLife(m_lifeLeft);
	return NORMAL;
}

// reading the data from the current screen so can move it to the next screen
void Game::saveDataToNextScrean()
{
	m_totalPoints = m_controllers[m_activeScreen]->getPoints();
	m_lifeLeft = m_controllers[m_activeScreen]->getLife();
}

