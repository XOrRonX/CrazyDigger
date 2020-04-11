
/*
Class Bomb 
inherit from class staticObject

this class takes care of all the stages of the bomb
it also takes care of the count down and the state change
*/

#pragma once


#include "StaticObject.h"
#include <SFML/Audio.hpp>

class Bomb : public StaticObject 
{
public:
	Bomb(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Bomb();

	// returns the state can be for example during explosion
	unsigned int getState();

	// handle all the momb states by the time that passed
	void bombHandle();

	// takes care of rock colliding with a bomb
	bool collideHandlerBomb(StaticObject& staticObject);

	// change state by the time that passed
	void setState(unsigned int state);

	virtual void move(const sf::Vector2f& vector2f,
		const sf::Vector2f& screenBoundryMin,
		const sf::Vector2f& screenBoundrymax,
		sf::Vector2f rbotLocation, int direction) override {}
	
private:
	float m_time;
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_state;
	sf::SoundBuffer soundBufferExplosion;
	sf::Sound soundExplosion;
	sf::SoundBuffer soundBufferBeep;
	sf::Sound soundBeep;
};


