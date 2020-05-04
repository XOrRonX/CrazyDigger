
#define _CRT_SECURE_NO_WARNINGS

#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include "macros.h"
#include "Predator.h"
#include "CrazyDigger.h"
#include "Wall.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Grass.h"
#include "Diamond.h"
#include "Weight.h"


// takes care of all event we care only about a few
void Controller::eventHandler()
{
	sf::Event event{};
	bool result = false;


	objectCanFallHendler();
	if (m_state == GAME_OVER)
		return;
	//poll means not block on event 
	//becasue all the images need to move
	result = m_window->pollEvent(event);
	// in case no event still need to take care of collision 
	// on the screen
	if (result == false || m_direction != STAY)
	{
		if (m_direction != STAY)
		{
			m_keyPress = true;
			moveDigger(m_direction, CLOSE);
			m_direction = STAY;
		}
		collideHandler();
		return;
	}
	
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window->close();
		m_state = EXIT_GAME;
		return;
	case sf::Event::KeyPressed:
		keyPressedHandler(event);
		break;
	default:
		break;
	}
	if (m_state == GAME_OVER)
		return;
	collideHandler();
}

// The constructire that build all the screen
Controller::Controller(char *fileName,unsigned int stage) : 
							m_board(fileName) // reads the file into matrix
											
{
	    m_textures.resize(TEXTURE_SIZE);

		m_points = 0;
		m_numOfFoundDiamond = 0;
		m_life = MAX_LIFE;
		m_stage = stage; // which screen index is this 
		m_time = m_board.getTime(); // get the time

		updateScreenBoundry(); //set he size of the screen will be used to check
						   // no image is getting out of the screen

		if (!initSound() || !initTexture())
			return;
		initBoard();

}



bool Controller::initTexture()
{
	if (!m_textures[VCRAZYDIGGER].loadFromFile("cd.png")
		|| !m_textures[VPREDATOR].loadFromFile("Predator.jpg")
		|| !m_textures[VWALL].loadFromFile("wall.png")
		|| !m_textures[VDIAMONDD].loadFromFile("Diamond.png")
		|| !m_textures[VGRASS].loadFromFile("Grass.png")
		|| !m_textures[VWEIGHT].loadFromFile("Wight.jpg")
		|| !m_textures[VCRAZYDIGGERO].loadFromFile("cd-o.png")
		|| !m_textures[VCRAZYDIGGERU].loadFromFile("cd-u.png")
		|| !m_textures[VCRAZYDIGGERUO].loadFromFile("cd-uo.png")
		|| !m_textures[VCRAZYDIGGERD].loadFromFile("cd-d.png")
		|| !m_textures[VCRAZYDIGGERDO].loadFromFile("cd-do.png")
		|| !m_textures[VCRAZYDIGGERL].loadFromFile("cd-l.png")
		|| !m_textures[VCRAZYDIGGERLO].loadFromFile("cd-lo.png")
		|| !m_textures[VPREDATORU].loadFromFile("Predator-u.jpg")
		|| !m_textures[VPREDATORL].loadFromFile("Predator-l.jpg")
		|| !m_textures[VPREDATORD].loadFromFile("Predator-d.jpg")
		|| !m_textures[VDIAMONDL].loadFromFile("Diamond-l.png")
		|| !m_textures[VDIAMONDLR].loadFromFile("Diamond-lr.png")
		|| !m_textures[VDIAMOND].loadFromFile("Diamond.png")
		|| !m_textures[VCRAZYDIGGERC].loadFromFile("cd-c.png")
		)
		return false;
	return true;

}

void Controller::initBoard()
{
	sf::Vector2f pos;
	// this section go over the matrix that was read from the file
	// and call the relevant constructor of the rlevant image
	for (int i = 0; i < m_board.boardInfo(LINES); i++)
	{
		for (int j = 0; j < m_board.boardInfo(COLUMNS); j++)
		{
			// calcualte from the location in the matrix
			// the location on the screen
			pos = { (float)j * RECT_SIZE + SCREEN_MIN_X ,
				(float)i * RECT_SIZE + SCREEN_MIN_Y };
			switch (m_board.getChar(i, j))
			{
			case CRAZY_DIGGER:
				m_crazyDiggerIndex = (unsigned int)m_MovingObjects.size();
				m_MovingObjects.push_back(std::make_unique<CrazyDigger,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>& >
					({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				break;
			case PREDATOR:
				m_MovingObjects.push_back(std::make_unique<Predator,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>& >
					({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				m_numOfPredators++;
				break;
			case WALL:
				m_staticObjects.push_back(std::make_unique<Wall,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int&>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VWALL));
				break;
			case WEIGHT:
				m_objectCanFall.push_back(std::make_unique<Weight,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VWEIGHT));
				break;
			case DIAMOND:
				m_numOfDiamonds++;
				m_objectCanFall.push_back(std::make_unique<Diamond,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VDIAMOND));
				break;
			case GRASS:
				m_staticObjects.push_back(std::make_unique<Grass,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VGRASS));
				break;
			}
		}
	}
}


bool Controller::initSound()
{

	//-------------sound section------------------

	if (!soundBuffer.loadFromFile("BOM_ST5.wav")
		|| !soundBufferDoor.loadFromFile("open_door_3.wav")
		|| !soundBufferPresent.loadFromFile("coin_1.wav")
		|| !soundBufferBye.loadFromFile("bye.wav")
		|| !soundBufferBite.loadFromFile("bite.wav")
		|| !soundBufferNo.loadFromFile("no.wav"))
	{
		return false;
	}
	sound.setBuffer(soundBuffer);
	soundDoor.setBuffer(soundBufferDoor);
	soundPresent.setBuffer(soundBufferPresent);
	soundBye.setBuffer(soundBufferBye);
	soundBite.setBuffer(soundBufferBite);
	soundNo.setBuffer(soundBufferNo);
	return true;
}






// calcualte the screen boundries to check impages not getting our of the screen
void Controller::updateScreenBoundry()
{
	m_screenBoundryMin.x = SCREEN_MIN_X ;
	m_screenBoundryMin.y = SCREEN_MIN_Y ;
	m_screenBoundryMax.x = (m_board.boardInfo(COLUMNS)-1) * RECT_SIZE + SCREEN_MIN_X ;
	m_screenBoundryMax.y = (m_board.boardInfo(LINES)-1) * RECT_SIZE + SCREEN_MIN_Y ;
}

Controller::~Controller() = default;

// the main function that execute the game on one screen
void Controller::run()
{
	// doing the allocation here and not in the constructure to avoid
	// all the screen windows appearing for a second when the game start
	m_window = std::make_unique<sf::RenderWindow>
	(sf::VideoMode(DEFAULT_SCREEN_SIZE, DEFAULT_SCREEN_SIZE), "Crazy Digger");
	
	bool delay = false;

	if (m_board.getTime()!= -1)
		m_clock.restart();
	
	m_window->setVisible(true);
	unsigned int x = (unsigned int)m_screenBoundryMax.x + 600;
	unsigned int y = (unsigned int) m_screenBoundryMax.y;

	// need to keep a screen size at least at default size 
	// else when low number of lines or columns the view is very bad
	y < DEFAULT_SCREEN_SIZE ? y = DEFAULT_SCREEN_SIZE : y = y ;
	x < DEFAULT_SCREEN_SIZE ? x = DEFAULT_SCREEN_SIZE : x = x;

	m_window->setSize({ x,y });
	while (m_window->isOpen())
	{
		if (m_board.getTime() != -1)
			hendelTime();
		if (m_state == GAME_OVER)
			break;
		m_window->clear();
		updateDiamondsTexture();
		for (auto& shape : m_staticObjects)
			shape->draw(*m_window);
		for (auto& shape : m_objectCanFall )
			shape->draw(*m_window);
		for (auto& shape : m_MovingObjects)
			if (shape->getIsAlive())
				shape->draw(*m_window);
		m_MovingObjects[m_crazyDiggerIndex]->draw(*m_window);
		eventHandler(); // look for event 
		if (m_state != NORMAL)
			break;
		  // move all objects on the screen
		moveObjects();
		printInfo(" ");
		m_window->display();
		if (delay == true)
		{
			Sleep(75);
			delay = false;
		}
		if (m_direction != STAY)
			delay = true;
		m_keyPress = false;
	}
	handleStateChange();
}


void Controller::updateDiamondsTexture()
{
	unsigned int index = rand() % m_objectCanFall.size();

	for (vector<unique_ptr<ObjectCanFall>>::iterator it1 
		= m_objectCanFall.begin(); it1 != m_objectCanFall.end(); ++it1)
		if ((*it1)->getType() == VDIAMOND)
		{
			if (rand() % 5 == 0)
				(*it1)->setTexture((rand() % 3) + VDIAMONDL);
		}
}


// takes care of the information printed on the left side of the screen
void Controller::printInfo(char * add_string)
{
	sf::Font font;
	char string[150];
	
	sprintf(string, "Points: %d \nLife: %d \nStage: %d\n time: %.1f\n%s",
		m_points, m_life, m_stage, m_time, add_string);
	font.loadFromFile("Gabriola.TTF");
	std::string str(string);
	sf::Text txt(str, font, 10);
	txt.setFillColor(sf::Color::Red);
	txt.setOutlineThickness(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setStyle(sf::Text::Bold);
	txt.setCharacterSize(20);
	txt.setPosition((float)m_screenBoundryMax.x + 50, (float)100);
	m_window->draw(txt);
}


void Controller::moveObjects()
{
	
	sf::Vector2f crazyDiggerLocation;
	crazyDiggerLocation = m_MovingObjects[m_crazyDiggerIndex]->getPosition();

	if ( m_keyPress == true  )
		m_MovingObjects[m_crazyDiggerIndex]->move(m_crazyDiggerMove,
			m_screenBoundryMin, m_screenBoundryMax, crazyDiggerLocation);
	movePredator();

}

void Controller::movePredator()
{
	sf::Vector2f crazyDiggerLocation, currDirection = {0,0};
	crazyDiggerLocation = m_MovingObjects[m_crazyDiggerIndex]->getPosition();
	bool moveUpStatic = true, moveDownStatic = true, moveLeftStatic = true, moveRightStatic = true;
	bool moveUpDynamic = true, moveDownDynamic = true, moveLeftDynamic = true, moveRightDynamic = true;
	bool currDirectionFlagStatic = true, currDirectionFlagDynamic = true ;
	sf::Vector2f frize = { 0 , 0 };
	sf::Vector2f up = { 0 , -5 };
	sf::Vector2f down = { 0 , 5 };
	sf::Vector2f left = { -5 ,0 };
	sf::Vector2f right = { 5,0 };
	sf::RectangleShape tempUp, tempDown, tempLeft, tempRight , currPos;
	for (vector<unique_ptr<MovingObject>>::iterator it1
		= m_MovingObjects.begin(); it1 != m_MovingObjects.end(); ++it1)
	{
		if ((m_state = (*it1)->getState()) != NORMAL)
			return;
		if ((*it1)->getType() == VCRAZYDIGGER)
			continue;
		currPos = (*it1)->getRectangleShape();
		currDirection = (*it1)->getCurrMove();
		currPos.move(currDirection);
		tempUp = (*it1)->getRectangleShape();
		tempUp.move(up);
		tempDown = (*it1)->getRectangleShape();
		tempDown.move(down);
		tempLeft = (*it1)->getRectangleShape();
		tempLeft.move(left);
		tempRight = (*it1)->getRectangleShape();
		tempRight.move(right);

		

		for (vector<unique_ptr<StaticObject>>::iterator it2
			= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
		{
			if ((*it2)->isCollide(tempUp.getGlobalBounds()))
				moveUpStatic = false;
			if ((*it2)->isCollide(tempDown.getGlobalBounds()))
				moveDownStatic = false;
			if ((*it2)->isCollide(tempLeft.getGlobalBounds()))
				moveLeftStatic = false;
			if ((*it2)->isCollide(tempRight.getGlobalBounds()))
				moveRightStatic = false;
			if ((*it2)->isCollide(currPos.getGlobalBounds()))
				currDirectionFlagStatic = false;

		}

		for (vector<unique_ptr<ObjectCanFall>>::iterator it2
			= m_objectCanFall.begin(); it2 != m_objectCanFall.end(); ++it2)
		{
			if ((*it2)->isCollide(tempUp.getGlobalBounds()))
				moveUpDynamic = false;
			if ((*it2)->isCollide(tempDown.getGlobalBounds()))
				moveDownDynamic = false;
			if ((*it2)->isCollide(tempLeft.getGlobalBounds()))
				moveLeftDynamic = false;
			if ((*it2)->isCollide(tempRight.getGlobalBounds()))
				moveRightDynamic = false;
			if ((*it2)->isCollide(currPos.getGlobalBounds()))
				currDirectionFlagDynamic = false;
		}

		if (currDirection != frize && currDirectionFlagStatic && currDirectionFlagDynamic)
		{
			(*it1)->move(currDirection, m_screenBoundryMin, m_screenBoundryMax, currDirection);
			moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
			moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
			currDirectionFlagStatic = true; currDirectionFlagDynamic = true;
			if (currDirection == up)
				(*it1)->setTexture(VPREDATORU);
			if (currDirection == down)
				(*it1)->setTexture(VPREDATORD);
			if (currDirection == left)
				(*it1)->setTexture(VPREDATORL);
			if (currDirection == right)
				(*it1)->setTexture(VPREDATOR);
			continue;
		}

		switch (rand()%4 + 1 )
		{
		case 1:
			if (moveUpStatic && moveUpDynamic)
			{
				(*it1)->setTexture(VPREDATORU);
				(*it1)->move(up, m_screenBoundryMin, m_screenBoundryMax, currDirection);
				moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
				moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
				continue;
			}
		case 2:
			if (moveDownStatic && moveDownDynamic)
			{
				(*it1)->setTexture(VPREDATORD);
				(*it1)->move(down, m_screenBoundryMin, m_screenBoundryMax, currDirection);
				moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
				moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
				continue;
			}
		case 3:
			if (moveLeftStatic && moveLeftDynamic)
			{
				(*it1)->setTexture(VPREDATORL);
				(*it1)->move(left, m_screenBoundryMin, m_screenBoundryMax, currDirection);
				moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
				moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
				continue;
			}
		case 4:
			if (moveRightStatic && moveRightDynamic)
			{
				(*it1)->setTexture(VPREDATOR);
				(*it1)->move(right, m_screenBoundryMin, m_screenBoundryMax, currDirection);
				moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
				moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
				continue;
			}
		default:
			break;
		}
		

		moveUpStatic = true; moveDownStatic = true; moveLeftStatic = true; moveRightStatic = true;
		moveUpDynamic = true; moveDownDynamic = true; moveLeftDynamic = true; moveRightDynamic = true;
		currDirectionFlagStatic = true; currDirectionFlagDynamic = true;
	}
}

bool Controller::checkIfNextMovePossible(sf::Vector2f nextMove)
{
	sf::Vector2f up = { 0, NEG_PIXEL_MOVE };
	sf::RectangleShape OneStepAhead , twoStepAhead;
	OneStepAhead = m_MovingObjects[m_crazyDiggerIndex]->getRectangleShape();
	OneStepAhead.move(nextMove);
	twoStepAhead = OneStepAhead;
	twoStepAhead.move(nextMove);
	twoStepAhead.move(nextMove);

	for (vector<unique_ptr<StaticObject>>::iterator it2
		= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
	{
		if ( (*it2)->getType() == VWALL &&
			m_MovingObjects[m_crazyDiggerIndex]->ifNextMovePossible((**it2),nextMove))
			return true;
	}
	for (vector<unique_ptr<ObjectCanFall>>::iterator it1
		= m_objectCanFall.begin(); it1 != m_objectCanFall.end(); ++it1)
	{
		if ((*it1)->getType() == VDIAMOND)
			continue;
		
		if ((*it1)->isCollide(OneStepAhead.getGlobalBounds()))
		{
			if (nextMove == up)
				return true;
			for (vector<unique_ptr<ObjectCanFall>>::iterator it2
				= m_objectCanFall.begin(); it2 != m_objectCanFall.end(); ++it2)
			{
				if (it1 != it2 && (*it2)->isCollide(twoStepAhead.getGlobalBounds()))
					return true;
			}
			for (vector<unique_ptr<StaticObject>>::iterator it2
				= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
			{
				if ((*it2)->isCollide(twoStepAhead.getGlobalBounds()))
					return true;
			}
		}
	}
	return false;
}

void Controller::objectCanFallHendler()
{
	
	sf::Vector2f newDown = { 0 , 8 };
	sf::Vector2f down = { 0 , (POS_PIXEL_MOVE *2) };
	sf::Vector2f left = { (NEG_PIXEL_MOVE*2) ,0 };
	sf::Vector2f right = { (POS_PIXEL_MOVE*2),0 };
	sf::RectangleShape  temp, tempRight, tempLeft, tempDown, tempDownRight, tempDownLeft;
	
	bool cantFallStatic = false;
	bool cantFallDynamic = false;

	// --------- flags of the static object all around the current falling object -----------

	bool tempLeftEmptyStatic = true;
	bool tempRightEmptyStatic = true;
	bool tempDownLeftEmptyStatic = true;
	bool tempDownRightEmptyStatic = true;

	// --------- flags of the falling object all around the current falling object -----------

	bool tempLeftEmptyDynamic = true;
	bool tempRightEmptyDynamic = true;
	bool tempDownLeftEmptyDynamic = true;
	bool tempDownRightEmptyDynamic = true;
	
	for (vector<unique_ptr<ObjectCanFall>>::iterator it1
		= m_objectCanFall.begin(); it1 != m_objectCanFall.end(); ++it1)
	{
		temp = (*it1)->getRectangleShape();
		tempRight = temp;
		tempRight.move(right);
		tempLeft = temp;
		tempLeft.move(left);
		tempDown = temp;
		tempDown.move(newDown);
		tempDownRight = tempDown;
		tempDownRight.move(right);
		tempDownLeft = tempDown;
		tempDownLeft.move(left);

		for (vector<unique_ptr<StaticObject>>::iterator it2
			= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
		{
			if ((*it2)->isCollide(tempDown.getGlobalBounds()))
				cantFallStatic = true;
			if ((*it2)->isCollide(tempLeft.getGlobalBounds()))
				tempLeftEmptyStatic = false;
			if ((*it2)->isCollide(tempRight.getGlobalBounds()))
				tempRightEmptyStatic = false;
			if ((*it2)->isCollide(tempDownLeft.getGlobalBounds()))
				tempDownLeftEmptyStatic = false;
			if ((*it2)->isCollide(tempDownRight.getGlobalBounds()))
				tempDownRightEmptyStatic = false;

		}

		if (cantFallStatic)
		{
			(*it1)->resetKillMode();
			cantFallStatic = false;
			tempLeftEmptyStatic = true;
			tempRightEmptyStatic = true;
			tempDownLeftEmptyStatic = true;
			tempDownRightEmptyStatic = true;
			continue;
		}
		
		for (vector<unique_ptr<ObjectCanFall>>::iterator it3
			= m_objectCanFall.begin(); it3 != m_objectCanFall.end(); ++it3)
		{
			if (it1 != it3 && (*it3)->isCollide(tempDown.getGlobalBounds()))
				cantFallDynamic = true;
			if (it1 != it3 && (*it3)->isCollide(tempLeft.getGlobalBounds()))
				tempLeftEmptyDynamic = false;
			if (it1 != it3 && (*it3)->isCollide(tempRight.getGlobalBounds()))
				tempRightEmptyDynamic = false;
			if (it1 != it3 && (*it3)->isCollide(tempDownLeft.getGlobalBounds()))
				tempDownLeftEmptyDynamic = false;
			if (it1 != it3 && (*it3)->isCollide(tempDownRight.getGlobalBounds()))
				tempDownRightEmptyDynamic = false;

		}

		
		if (cantFallDynamic)
		{
			cantFallDynamic = false;

			if ( m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempLeft.getGlobalBounds())==false &&
				m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempDownLeft.getGlobalBounds()) == false &&
				tempLeftEmptyDynamic && tempDownLeftEmptyDynamic &&
				tempLeftEmptyStatic && tempDownLeftEmptyStatic)
			{
				(*it1)->move(left);
				(*it1)->resetKillMode();
				continue;
			}
			if (m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempRight.getGlobalBounds()) == false &&
				m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempDownRight.getGlobalBounds()) == false &&
				tempRightEmptyDynamic && tempDownRightEmptyDynamic &&
				tempRightEmptyStatic && tempDownRightEmptyStatic)
			{
				(*it1)->move(right);
				(*it1)->resetKillMode();
				continue;
			}
			else
			{
				(*it1)->resetKillMode();
				tempLeftEmptyStatic = true;
				tempRightEmptyStatic = true;
				tempDownLeftEmptyStatic = true;
				tempDownRightEmptyStatic = true;
				tempLeftEmptyDynamic = true;
				tempRightEmptyDynamic = true;
				tempDownLeftEmptyDynamic = true;
				tempDownRightEmptyDynamic = true;
				continue;
			}
		}

		if (cantFallStatic == false && cantFallDynamic == false &&
			m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempDown.getGlobalBounds()) == false)
		{
			(*it1)->move(newDown);
			(*it1)->changeKillMode();
		}

		if ( m_MovingObjects[m_crazyDiggerIndex]->isCollide(tempDown.getGlobalBounds()) && (*it1)->getKillMode()
			 && m_MovingObjects[m_crazyDiggerIndex]->getPosition().y > (*it1)->getPos().y)
		{
			soundNo.play();
			for (auto& shape : m_objectCanFall)
				shape->draw(*m_window);
			for (auto& shape : m_objectCanFall)
				shape->resetKillMode();
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERC);
			m_MovingObjects[m_crazyDiggerIndex]->draw(*m_window);
			m_window->display();
			Sleep(1500);
			m_window->display();
			resetCrazyDigger();
			if (m_state == GAME_OVER)
				return;
			restart();
		}

		for (int x = 0; x < m_MovingObjects.size(); x++)
		{
			if (x != m_crazyDiggerIndex && m_MovingObjects[x]->isCollide(tempDown.getGlobalBounds())
				&& (*it1)->getKillMode())
			{
				m_MovingObjects[x]->disable();
			}

		}
		
		
		cantFallStatic = false;
		cantFallDynamic = false;
		tempLeftEmptyStatic = true;
		tempRightEmptyStatic = true;
		tempDownLeftEmptyStatic = true;
		tempDownRightEmptyStatic = true;
		tempLeftEmptyDynamic = true;
		tempRightEmptyDynamic = true;
		tempDownLeftEmptyDynamic = true;
		tempDownRightEmptyDynamic = true;
	}
	

}


void Controller::handleStateChange()
{
	if (m_state == CRAZY_DIGGER_FOUND_LAST_DIAMOND)
	{
		soundDoor.play();
		//m_points += BONUS_DIAMOND * m_stage * m_numOfDiamonds;
	}
	if (m_state == GAME_OVER)
		m_window->close();
}

unsigned int Controller::getState() const
{
	return m_state;
}

void Controller::setPoints(unsigned int totalPoints)
{
	m_points = totalPoints;
}

void Controller::setLife(unsigned int lifeLeft)
{
	m_life = lifeLeft;
}


void Controller::moveDigger(unsigned int direction, unsigned int open)
{
	sf::Vector2f crazyDiggerLocation;
	crazyDiggerLocation = m_MovingObjects[m_crazyDiggerIndex]->getPosition();

	if (open == OPEN)
		m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERO);
	else 
		m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGER);
	//m_keyPress = true;
	sf::Vector2f v{ 0,0 };
	switch (direction)
	{
	case RIGHT:
		if (open == OPEN)
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERO);
		else
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGER);
		m_crazyDiggerMove = { POS_PIXEL_MOVE,0 };
		checkIfItsWeight(m_crazyDiggerMove);
		if (checkIfNextMovePossible(m_crazyDiggerMove))
			m_crazyDiggerMove = { 0 , 0 };
		break;
	case LEFT:
		if (open == OPEN)
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERLO);
		else
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERL);
		m_crazyDiggerMove = { NEG_PIXEL_MOVE ,0 };
		checkIfItsWeight(m_crazyDiggerMove);
		if (checkIfNextMovePossible(m_crazyDiggerMove))
			m_crazyDiggerMove = { 0 , 0 };
		break;
	case UP:
		if (open == OPEN)
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERUO);
		else
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERU);
		m_crazyDiggerMove = { 0 , NEG_PIXEL_MOVE };
		if (checkIfNextMovePossible(m_crazyDiggerMove))
			m_crazyDiggerMove = { 0 , 0 };
		break;
	case DOWN:
		if (open == OPEN)
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERDO);
		else
			m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGERD);
		m_crazyDiggerMove = { 0 , POS_PIXEL_MOVE };
		if (checkIfNextMovePossible(m_crazyDiggerMove))
			m_crazyDiggerMove = { 0 , 0 };
		break;
	default:
		break;
	}
}


void Controller::keyPressedHandler(const sf::Event& event)
{
	sf::Vector2f crazyDiggerLocation;
	crazyDiggerLocation = m_MovingObjects[m_crazyDiggerIndex]->getPosition();

	m_keyPress = true;
	sf::Vector2f v{ 0,0 };
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		m_direction = RIGHT;
		moveDigger(RIGHT, OPEN);
		break;
	case sf::Keyboard::Left:
		m_direction = LEFT;
		moveDigger(LEFT, OPEN);
		break;
	case sf::Keyboard::Up:
		m_direction = UP;
		moveDigger(UP, OPEN);
		break;
	case sf::Keyboard::Down:
		m_direction = DOWN;
		moveDigger(DOWN, OPEN);
		break;
	case sf::Keyboard::Space: //halt robot
		m_crazyDiggerMove = { 0 , 0 };
		break;
	case sf::Keyboard::D:  // this is the key to leave a screen and restrat it
		resetCrazyDigger();
		if (m_state == GAME_OVER)
			return;
		restart();
		printInfo("You abandon\nthe Screen\nStarts over");
		m_window->display();
		soundBye.play();
		Sleep(3000);
		break;
	default:
		break;
	}
}

void Controller::checkIfItsWeight(sf::Vector2f move)
{
	bool flagStatic = true;
	bool flagCanFall = true;
	sf::RectangleShape temp;
	temp = m_MovingObjects[m_crazyDiggerIndex]->getRectangleShape();
	temp.move(move);

	for (vector<unique_ptr<ObjectCanFall>>::iterator it1
		= m_objectCanFall.begin(); it1 != m_objectCanFall.end(); ++it1)
	{
		if ((*it1)->getType() != VWEIGHT)
			continue;

		sf::RectangleShape temp1 = (*it1)->getRectangleShape();
		temp1.move(move);

		for (vector<unique_ptr<StaticObject>>::iterator it2
			= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
		{
			if ((*it2)->isCollide(temp1.getGlobalBounds()))
				flagStatic = false;
		}
		for (vector<unique_ptr<ObjectCanFall>>::iterator it3
			= m_objectCanFall.begin(); it3 != m_objectCanFall.end(); ++it3)
		{
			if ( it1 != it3 && (*it3)->isCollide(temp1.getGlobalBounds()) && (*it3)->isActive())
				flagCanFall = false;
		}
		if ( flagCanFall && flagStatic && (*it1)->isCollide(temp.getGlobalBounds()))
			(*it1)->move(move);
		flagStatic = true;
		flagCanFall = true;
	}
	
}

// The big functions that takes of all collisions in the game
void Controller::collideHandler()
{
	sf::Vector2f crazyDiggerLocation;
	sf::RectangleShape oneStepDown, twoStepDown;
	sf::Vector2f down = { 0 , POS_PIXEL_MOVE };
	bool movingCollide = false, staticCollide = false, fallCollide = false;

	for (vector<unique_ptr<MovingObject>>::iterator it1
		= m_MovingObjects.begin(); it1 != m_MovingObjects.end(); ++it1)
	{
		movingCollide = false; staticCollide = false; fallCollide = false;

		//-------------------predator killed crazzy digger--------------------------

		if (m_MovingObjects[m_crazyDiggerIndex]->collideHandler((**it1)) &&
			(*it1)->getIsAlive() == true && (*it1)->getType() != VCRAZYDIGGER)
		{
			
			resetCrazyDigger();
			restart();
			Sleep(1500);
			return;
		}

		//-----------------check collision with static objects----------------------

		for (vector<unique_ptr<StaticObject>>::iterator it2
			= m_staticObjects.begin(); it2 != m_staticObjects.end(); ++it2)
		{
			
			if ((*it1)->collideHandlerStatic((**it2)))
			{
				if ((*it1)->getType() != VCRAZYDIGGER)
					(*it1)->m_predatorCollide = true;
				(*it1)->moveRevert();
			}
			if (m_state != GAME_OVER)
				m_state = (*it1)->getState();

			if (m_state == CRAZY_DIGGER_FOUND_GRASS)
			{
				m_MovingObjects[m_crazyDiggerIndex]->move(m_crazyDiggerMove,
					m_screenBoundryMin, m_screenBoundryMax, crazyDiggerLocation);
				
					soundBite.play();
					(*it2)->disable();
					(*it2)->changeActive();
				if (m_state != GAME_OVER)
					m_state = NORMAL;
				(*it1)->changeState();
				return;
			}

		}

		for (vector<unique_ptr<MovingObject>>::iterator it4
			= m_MovingObjects.begin(); it4 != m_MovingObjects.end(); ++it4)
		{
			if ((*it1)->collideHandler((**it4)) && (it4!=it1) &&
				(*it1)->getType() != VCRAZYDIGGER )
			{
				(*it1)->m_predatorCollide = true;
				//(*it1)->moveRevert();
			}
		}

	}

	for (vector<unique_ptr<ObjectCanFall>>::iterator it1
		= m_objectCanFall.begin(); it1 != m_objectCanFall.end(); ++it1)
	{
		
		if ( (*it1)->getType() == VDIAMOND 
			&& (*it1)->isCollide(m_MovingObjects[m_crazyDiggerIndex]->getRectangleShape().getGlobalBounds()))
		{
			(*it1)->disable();
			(*it1)->changeActive();
			soundPresent.play();
			m_numOfFoundDiamond++;
			m_points += BONUS_DIAMOND * (m_stage+1) ;
			if (m_numOfDiamonds == m_numOfFoundDiamond)
			{
				m_state = CRAZY_DIGGER_FOUND_LAST_DIAMOND;
				return;
			}
		}
	}
}


// called after Digger is killed 
void Controller::resetCrazyDigger()
{
	printInfo("CrazyDigger Killed \n  ;-(");
	m_window->display();
	m_life--;
	if (m_life == 0)
	{
		m_state = GAME_OVER;
		printInfo("GAME LOST \n  ;-(");
		m_window->display();
		Sleep(3000);
		return;
	}

 
	m_crazyDiggerMove = { 0, 0 };
	m_MovingObjects[m_crazyDiggerIndex]->setSize({ 150,150 }); 
	m_MovingObjects[m_crazyDiggerIndex]->setToDefault();
	m_MovingObjects[m_crazyDiggerIndex]->setTexture(VCRAZYDIGGER);
	m_MovingObjects[m_crazyDiggerIndex]->setSize({ RECT_SIZE,RECT_SIZE });
	m_MovingObjects[m_crazyDiggerIndex]->setToDefault();
	for (int k = 0; k < m_MovingObjects.size(); k++)
	{
		if ((k != m_crazyDiggerIndex) && (m_MovingObjects[k]->getIsAlive())) 
			m_MovingObjects[k]->setToDefault();
	}
}

void Controller::closeWindow()
{
	m_window->close();
}

void Controller::display() const 
{
	m_window->display();
}

void Controller::hendelTime()
{
	if (m_time == -1)
		return;
	m_t = m_clock.getElapsedTime();
	m_time = m_t.asSeconds();
	m_time = m_time * -1 + m_board.getTime();
	if (m_time <= 0)
	{
		resetCrazyDigger();
		if (m_state == GAME_OVER)
			return;
		restart();
		printInfo("Time Ended \nRestarting\n");
		m_window->display();
		Sleep(3000);
		m_clock.restart();
	}

}

// this is called after time ended or after user decided 
// to get out of a screen and restart it.
// it gets all objects to their orginal place and status
void Controller::restart()
{
	for (auto& shape : m_MovingObjects)
		shape->setToDefault();
	for (auto& shape : m_staticObjects)
		shape->backToDefault();
	for (auto& shape : m_objectCanFall)
		shape->backToDefault();
	m_numOfFoundDiamond = 0;
	if (m_board.getTime() != -1)
		m_clock.restart();
	m_time = m_board.getTime();
	m_crazyDiggerMove = { 0 , 0 };
}


unsigned int Controller::getPoints() const
{
	return m_points;
}

unsigned int Controller::getLife() const
{
	return m_life;
}


