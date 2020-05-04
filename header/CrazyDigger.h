
/*

Class CrazySigger
This class is managing the CrazyDigger
it inherits from the virtual class MovingObject 

*/

//=============================include=======================================

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MovingObject.h"
#include "Predator.h"
#include "ObjectCanFall.h"

//==========================Class Robo==============================

class CrazyDigger : public MovingObject
{
public:
	
	//constractor with location 
    CrazyDigger(const sf::Vector2f& size, const sf::Vector2f& pos, 
			std::vector<sf::Texture>& textures);
	

	void setTexture(unsigned int index) override;

	// draws the Digger
	void draw(sf::RenderWindow& renderWindow) const override;

	// move the robot gets the vector to move and boundries of the 
	// screen to make sure it is not going outside the screen
	void move(const sf::Vector2f& vector2f, 
			  const sf::Vector2f& screenBoundryMin,
		      const sf::Vector2f& screenBoundrymax,
				sf::Vector2f rbotLocation) override;

	
	// used if the last move was wrong then move back to before the
	// last move
	void moveRevert() override;

	// returns the state of the Digger - e.g. killed by a preditor
	// and so on
	unsigned int getState() const override;

	// Return the Digger to its original location and state
	void setToDefault() override;

	// return true if the Digger and rect collide
	bool isCollide(const sf::FloatRect& rect) const override;

	// handle a collision between a digger and preditor
	bool collideHandler(MovingObject& baseObject) override;

	// handle a collision between a digger and a wall or grass
	bool collideHandlerStatic(StaticObject& staticObject) override;

	// chnage the size of the digger
	void setSize(const sf::Vector2f& size) override;
	
	// always return true that the digger is alive
	bool getIsAlive() const { return true; };

	// set digger state to Normal 
	void changeState() override;

	// set the digger to be in position pos
	void setPosition(sf::Vector2f pos) override;
	
	// returns the current digger position 
	sf::Vector2f getPosition() const override;

	unsigned int getType() const override;

	sf::Vector2f getCurrMove() override { return m_currentMove; }
	
	// empty functions in robot
	void disable() {};
	void changePredatorSpeed() {};
	
	bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove);

	sf::RectangleShape getRectangleShape() { return m_rectangle; };

private:
	
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	unsigned int m_state = NORMAL;
	unsigned int m_speed = 1;
};

