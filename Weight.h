#pragma once

#include "ObjectCanFall.h"
#include "StaticObject.h"


class Weight : public ObjectCanFall
{
public:
	Weight(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);

	void move(sf::Vector2f direction);

	bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove);

	sf::RectangleShape getRectangleShape() { return m_rectangle; };

	~Weight();


};
