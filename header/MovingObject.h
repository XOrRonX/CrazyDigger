
/*
Class MovingObject

all the class functions are virtual 
the classes who inherit from MovingObject are Digger, Preditor
All the functions are implemented in those classes

*/


#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "ObjectCanFall.h"
#include "AbstructObject.h"

namespace sf {
	class Color;
	class RenderWindow;
}

class MovingObject : public AbstructObject
{
public:
	MovingObject() = default;
	virtual ~MovingObject() = default;
	
	virtual void draw(sf::RenderWindow& renderWindow) const = 0;
	virtual void move(const sf::Vector2f& vector2f,
					  const sf::Vector2f& screenBoundryMin,
					  const sf::Vector2f& screenBoundrymax,
					  sf::Vector2f rbotLocation) = 0;
	virtual void moveRevert() = 0;
	virtual void setToDefault() = 0;
	virtual unsigned int getState() const = 0;
	virtual bool isCollide(const sf::FloatRect& rect) const = 0;
	virtual bool collideHandler(MovingObject& baseObject) = 0;	
	virtual bool collideHandlerStatic(StaticObject& staticObject) = 0;
	virtual bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual unsigned int getType() const = 0;
	virtual void changeState() = 0;
	virtual void disable() = 0;
	virtual bool getIsAlive() const = 0;
	virtual void setSize(const sf::Vector2f& size) = 0;
	virtual void setPosition(const sf::Vector2f pos) = 0;
	virtual sf::RectangleShape getRectangleShape() = 0;
	virtual sf::Vector2f getCurrMove() = 0;
	virtual void setTexture(unsigned int index) = 0;

	bool m_predatorCollide;
	bool m_checkIfCanMove;
	sf::Vector2f m_currentMove;

};

