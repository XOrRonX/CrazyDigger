

#include "CrazyDigger.h"
#include "macros.h"
#include "StaticObject.h"
#include "Wall.h"
#include <SFML/Audio.hpp>
#include "ObjectCanFall.h"


CrazyDigger::CrazyDigger(const sf::Vector2f& size,const sf::Vector2f& pos, 
	         std::vector<sf::Texture>& textures)
	         : m_rectangle(size), m_index(VCRAZYDIGGER), m_textures(textures)
{
	m_checkIfCanMove = true;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
	m_speed = CRAZY_DIGGER_SPEED;
}

void CrazyDigger::draw(sf::RenderWindow& renderWindow) const 
{
	renderWindow.draw(m_rectangle);
}

void CrazyDigger::setTexture(unsigned int index)
{
	m_rectangle.setTexture(&m_textures[index]);
	//m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}


// The main Digger move function
// this function gets the move 
void CrazyDigger::move(const sf::Vector2f& vector2f, 
				 const sf::Vector2f& screenBoundryMin,
				 const sf::Vector2f& screenBoundrymax,
					sf::Vector2f crazyDiggerLocation)
{
	
	sf::Vector2f location;
	m_prevMove.x = vector2f.x  * -1;
	m_prevMove.y = vector2f.y  * -1;
	m_rectangle.move(vector2f);
	location = m_rectangle.getPosition();


	if (!(location.x <= screenBoundrymax.x && location.x >= screenBoundryMin.x) ||
		!(location.y <= screenBoundrymax.y && location.y >= screenBoundryMin.y))
		moveRevert();
}


// go back on the last move 
void CrazyDigger::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

// the state is the way for the crazy digger to communicate
// with the game that something happened it can be
// found a last diamond,  got killed and so on
unsigned int CrazyDigger::getState() const 
{
	return m_state;
}


void CrazyDigger::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
}


bool CrazyDigger::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}

bool CrazyDigger::collideHandler(MovingObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}



bool CrazyDigger::ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove)
{
	sf::RectangleShape temp;
	temp = m_rectangle;
	temp.move(nextMove);
	if (staticObject.isCollide(temp.getGlobalBounds()))
		return true;
	else
		return false;
	

}

// each time this function called it checks if 
// there is a collision with the staticObject it got
// if there is a collision it handles
bool CrazyDigger::collideHandlerStatic(StaticObject& staticObject)
{
	// check if there is a collision with staticObject
	// if there is then depends on the type of the object
	// do different things 
	if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
	{
		switch (staticObject.getType())
		{
		case VDIAMOND:
			m_state = CRAZY_DIGGER_FOUND_DIAMOND;
			return true;
			break;
		case VGRASS:
			m_state = CRAZY_DIGGER_FOUND_GRASS;
			return true;
			break;
		case VWEIGHT:
			m_state = CRAZY_DIGGER_FOUND_WEIGHT;
			return true;
			break;
		
		}
		return true;
	}
	return false;
}




void CrazyDigger::setSize(const sf::Vector2f& size)
{
	m_rectangle.setSize(size);
}

void CrazyDigger::changeState()
{
	m_state = NORMAL;
}

sf::Vector2f CrazyDigger::getPosition() const
{
	sf::Vector2f location;
	location = m_rectangle.getPosition();
	return location;
}

void CrazyDigger::setPosition(sf::Vector2f pos)
{
	sf::Vector2f location;
	location = m_rectangle.getPosition();
	location.x += pos.x;
	location.y += pos.y;
	m_rectangle.setPosition(location);
}

// returns the type of object 
unsigned int CrazyDigger::getType() const
{
	return m_index;
}