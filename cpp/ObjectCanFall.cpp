#include "ObjectCanFall.h"
#include "macros.h"


ObjectCanFall::ObjectCanFall(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	m_textures(textures), m_index(index), m_rectangle(size)
{
	m_killMode = false;
	m_objectType = index;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
	m_active = true;
}

void ObjectCanFall::updatePicture(unsigned int index)
{
	m_rectangle.setTexture(&m_textures[index]);
}

void ObjectCanFall::changeSize(const sf::Vector2f& size)
{
	m_rectangle.setSize(size);
}

void ObjectCanFall::draw(sf::RenderWindow& renderWindow)
{
	if (m_active)
		renderWindow.draw(m_rectangle);
}


ObjectCanFall::~ObjectCanFall()
{
}

ObjectCanFall::ObjectCanFall(std::vector<sf::Texture>& textures) :
	m_textures(textures)
{

}

bool ObjectCanFall::isActive() const
{
	return m_active;
}

void ObjectCanFall::backToDefault()
{

	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setTexture(&m_textures[m_index]);
	m_active = true;
}

void ObjectCanFall::disable()
{
	m_active = false;
}


bool ObjectCanFall::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}


void ObjectCanFall::changeActive()
{
	m_rectangle.setPosition({ 0,0 });
}


sf::Vector2f ObjectCanFall::getPos() const
{
	return m_rectangle.getPosition();
}

unsigned int ObjectCanFall::getType() const
{
	return m_objectType;
}

void ObjectCanFall::setTexture(unsigned int index)
{
	m_rectangle.setTexture(&m_textures[index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}
