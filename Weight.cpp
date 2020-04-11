#include "Weight.h"
#include "macros.h"
#include "StaticObject.h"
#include "MovingObject.h"


Weight::Weight(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	ObjectCanFall(size, pos, textures, index)
{
	m_objectType = VWEIGHT;
	m_rectangle.setPosition(pos);
}

Weight::~Weight()
{
}

void Weight::move(sf::Vector2f direction)
{
	m_rectangle.move(direction);
	m_prevMove = direction;
		
}


bool Weight::ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove)
{
	sf::RectangleShape temp;
	temp = m_rectangle;
	temp.move(nextMove);
	if (staticObject.isCollide(temp.getGlobalBounds()) )
		return false;
	else
		return true;


}