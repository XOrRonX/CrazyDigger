#pragma once

#include "StaticObject.h"

class Grass : public StaticObject
{
public:

	Grass(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, unsigned int index);
	~Grass();
	virtual void move(const sf::Vector2f& vector2f,
		const sf::Vector2f& screenBoundryMin,
		const sf::Vector2f& screenBoundrymax,
		sf::Vector2f crazyDiggerLocation, int direction) override {}

};

