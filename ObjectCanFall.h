#pragma once

#include <SFML/Graphics.hpp>
#include "ObjectCanFall.h"
#include "StaticObject.h"
#include "MovingObject.h"

	class ObjectCanFall
{
public:
	ObjectCanFall(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~ObjectCanFall();
	ObjectCanFall(std::vector<sf::Texture>& textures);

	

	// returns true if the object is active 
	bool isActive() const;

	// returns the object to its original state and position 
	void backToDefault();

	// disable the object so it is not effecting the game 
	void disable();

	// draw the object on the renderWindow
	void draw(sf::RenderWindow& renderWindow);

	// returns true if this and rect have a collision 
	bool isCollide(const sf::FloatRect& rect) const;

	// Switch state if active make not and the other way around
	void changeActive();

	// change the picture for example for the bomb states
	void updatePicture(unsigned int index);

	// update the size of the rectangle 
	void changeSize(const sf::Vector2f& size);

	// return the position of an object
	sf::Vector2f getPos() const;

	// returns the object type 
	unsigned int getType() const;

	void changeKillMode() { m_killMode = true; }

	void resetKillMode() { m_killMode = false; }

	bool getKillMode() { return m_killMode; }

	void setTexture(unsigned int index);

	virtual bool ifNextMovePossible(StaticObject& staticObject, sf::Vector2f nextMove) = 0;

	virtual void move(sf::Vector2f direction) = 0;

	sf::RectangleShape getRectangleShape() { return m_rectangle; };

protected: // accessed by children
	sf::RectangleShape m_rectangle;
	unsigned int m_objectType;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;

private:
	bool m_killMode;
	bool m_active;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	unsigned int m_type;
};


