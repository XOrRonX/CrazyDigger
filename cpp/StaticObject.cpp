#include "StaticObject.h"
#include "macros.h"


StaticObject::StaticObject(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	m_textures(textures) , m_index(index) , m_rectangle(size)
{
	m_objectType = index;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
	m_active = true;
}

void StaticObject::updatePicture(unsigned int index)
{
	m_rectangle.setTexture(&m_textures[index]);
}

void StaticObject::changeSize(const sf::Vector2f& size)
{
	m_rectangle.setSize(size);
}

void StaticObject::draw(sf::RenderWindow& renderWindow)
{
	if (m_active)
		renderWindow.draw(m_rectangle);
}


StaticObject::~StaticObject()
{
}

StaticObject::StaticObject(std::vector<sf::Texture>& textures):
						m_textures(textures)
{

}

bool StaticObject::isActive() const
{
	return m_active;
}

void StaticObject::backToDefault()
{

	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setTexture(&m_textures[m_index]);
	m_active = true;
}

void StaticObject::disable()
{
	m_active = false;
}


bool StaticObject::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}


void StaticObject::changeActive()
{
	m_rectangle.setPosition({ 0,0 });
}


sf::Vector2f StaticObject::getPos() const 
{
	return m_rectangle.getPosition();
}

unsigned int StaticObject::getType() const 
{
	return m_objectType;
}