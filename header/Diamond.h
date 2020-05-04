
#pragma once

// this class inherit from StaticObject
// this is a diamond in the game whihc the digger eats and 
// get points for the digger needs to eat all the diamonds in the
// screen to move to the next screen


#include "ObjectCanFall.h"

class Diamond : public ObjectCanFall
{
public:

	Diamond(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, unsigned int index);
	~Diamond();

	void move(sf::Vector2f direction);

	bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove);

	sf::RectangleShape getRectangleShape() { return m_rectangle; };
};