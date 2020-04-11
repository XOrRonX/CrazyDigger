#include "Grass.h"
#include "macros.h"


Grass::Grass(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, unsigned int index) :
	StaticObject(size, pos, textures, index)
{
	m_objectType = VGRASS;
}


Grass::~Grass()
{
}