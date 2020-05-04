#pragma once

// this class inherit from StaticObject
// this is an exit door in the game


#include "StaticObject.h"

class Door : public StaticObject
{
public:
	Door(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	virtual void move(const sf::Vector2f& vector2f,
		const sf::Vector2f& screenBoundryMin,
		const sf::Vector2f& screenBoundrymax,
		sf::Vector2f rbotLocation, int direction) override {}
	~Door();
};

