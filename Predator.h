
/*

Class Predator
This class is managing the Predators
it is inheriting from the abstruct class MovingObject

*/

//=============================include=======================================

#pragma once


#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Predator.h"
#include "macros.h"
#include "ObjectCanFall.h"

class CrazyDigger;

//==========================Class Robo==============================

class Predator : public MovingObject
{
public:
	 
	Predator(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures);
	
	void draw(sf::RenderWindow& renderWindow) const override;

	void setTexture(unsigned int index) override;

	// move the Predator, the Predator calculate in this function
	// where to move it is not using vector2f for that 
	void move(const sf::Vector2f& vector2f,
			  const sf::Vector2f& screenBoundryMin,
			  const sf::Vector2f& screenBoundrymax,
				sf::Vector2f crazyDiggerLocation) override;

	

	// if last move was not good - like collide with a wall
	// move back 
	void moveRevert() override;

	// returns the state of the Predator
	unsigned int getState() const override;

	// put the Predator in its defalt state and location 
	void setToDefault() override;

	// return true if the Predator and rect collide
	bool isCollide(const sf::FloatRect& rect) const override;

	// returns true of collide with MovingObject
	bool collideHandler(MovingObject& baseObject) override;

	// returns true of collide with staticObject
	bool collideHandlerStatic(StaticObject& staticObject) override;
	

	// disable a Predator
	void disable();

	

	// returns the position of the Predator
	sf::Vector2f getPosition() const { return m_rectangle.getPosition(); };

	// returns true of the Predator is a live
	bool getIsAlive() const ;

	
	unsigned int getType() const override;

	bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove) override { return false; }

	sf::RectangleShape getRectangleShape() { return m_rectangle; };

	// empty functions 
	void changeState() {};
	void setSize(const sf::Vector2f& size) {};
	void setPosition(sf::Vector2f pos) {};

	
	sf::Vector2f getCurrMove() override { return m_currentMove; }

private:
	
	// the frequency of Predator move by default is slower than Digger
	unsigned int m_speed = 2;
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	unsigned int m_randFrequency;
	unsigned int m_state = NORMAL;
	sf::Vector2f m_predatorRestart;
	bool m_alive;
	bool m_smart;  // is the Preditor smart or not
	bool m_moveRevert;
	bool m_hard;   
	
};

