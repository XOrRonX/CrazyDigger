
/*
Class Controller
this class is the main class of the project
it manages a game and it holds in it all the objects of one screen
it also manages all the moves in the game 

*/


#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "MovingObject.h"
#include "Board.h"
#include "StaticObject.h"
#include "macros.h"
#include "ObjectCanFall.h"
#include <vector>

using std::vector;
using std::unique_ptr;

class Controller
{
public:
	
	Controller(char *fileName,unsigned int stage);
	~Controller();

	// returns the state of the controller 
	unsigned int getState() const;

	// set the points from previos controller
	void setPoints(unsigned int m_totalPoints);

	// set the life from previous controller 
	void setLife(unsigned int m_lifeLeft);

	// the main function that execute the flow of the screen
	void run();

	void updateDiamondsTexture();

	// returns how many points the screen won
	unsigned int getPoints() const ;

	// returns how many life are left to the Digger
	unsigned int getLife() const ;

	void closeWindow();
	void display() const;

	// print the info on the right side of the screen
	void printInfo(char * string);

private:

	void moveDigger(unsigned int direction, unsigned int open);

	// handle the different key press
	void keyPressedHandler(const sf::Event& event);

	// main functions managing all the collisions 
	void collideHandler();

	bool checkIfNextMovePossible(sf::Vector2f nextMove);

	// poll for event if availbale check and act and if not continue
	void eventHandler();

	// hadles cases of state change like
	// all the life of the Digger are gone
	void handleStateChange();

	// calcaulate the boundries of the screen so no object
	// gets out of the screen 
	void updateScreenBoundry();

	// moves the object 
	void moveObjects();

	// takes care of the time count down of the screen 
	void hendelTime();

	// restart the whole screen to its initial state not including 
	// life or points which
	void restart();

	// return the Digger to its orginal location 
	void resetCrazyDigger();

	void movePredator();

	bool initSound();

	void initBoard();

	bool initTexture();

	std::unique_ptr<sf::RenderWindow> m_window;
	sf::Vector2f m_crazyDiggerMove = { 0,0 };  // track the next move of the Digger
	sf::Vector2f m_screenBoundryMax;
	sf::Vector2f m_screenBoundryMin;
	unsigned int m_state = NORMAL;
	sf::Font m_font;
	unsigned int m_points;
	unsigned int m_numOfFoundDiamond;
	unsigned int m_life ;
	unsigned int m_stage; //which screen is it
	float m_time; // time of the screen
	sf::Time m_t;
	sf::Clock m_clock;
	bool m_keyPress;
	void objectCanFallHendler();
	void checkIfItsWeight(sf::Vector2f move);
	unsigned int m_direction = STAY;
	Board m_board;

	std::vector<std::unique_ptr<ObjectCanFall>> m_objectCanFall;
	std::vector<std::unique_ptr<MovingObject>> m_MovingObjects; 
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	unsigned int m_crazyDiggerIndex;
	unsigned int m_numOfPredators;
	unsigned int m_numOfDiamonds;
	std::vector<sf::Texture> m_textures;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::SoundBuffer soundBufferDoor;
	sf::Sound soundDoor;
	sf::SoundBuffer soundBufferPresent;
	sf::Sound soundPresent;
	sf::SoundBuffer soundBufferBye;
	sf::Sound soundBye;
	sf::SoundBuffer soundBufferBite;
	sf::Sound soundBite;
	sf::SoundBuffer soundBufferNo;
	sf::Sound soundNo;


};

