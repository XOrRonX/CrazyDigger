#include "Diamond.h"
#include "macros.h"


Diamond::Diamond(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, unsigned int index) :
	ObjectCanFall(size, pos, textures, index)
{
	m_objectType = VDIAMOND;
	m_rectangle.setPosition(pos);
}


Diamond::~Diamond()
{
}

void Diamond::move(sf::Vector2f direction)
{
	m_rectangle.move(direction);
	m_prevMove = direction;

}


bool Diamond::ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove)
{
	sf::RectangleShape temp;
	temp = m_rectangle;
	temp.move(nextMove);
	if (staticObject.isCollide(temp.getGlobalBounds()))
		return false;
	else
		return true;


}