
#include "Predator.h"
#include "macros.h"
#include <cmath>

Predator::Predator(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures)
	: m_rectangle(size), m_index(VPREDATOR), m_textures(textures)
{
	m_hard = false;
	m_predatorCollide = false;
	m_checkIfCanMove = true;
	int rndom = rand() % 4;
	rndom <= 2 ? m_smart = true : m_smart = false; 
	m_alive = true;
	m_randFrequency = PREDATOR_RAND_FREQUENCY;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}

void Predator::draw(sf::RenderWindow& renderWindow) const
{
	if (m_alive == true)
		renderWindow.draw(m_rectangle);
}

void Predator::setTexture(unsigned int index)
{
	m_index = index;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}


void Predator::move(const sf::Vector2f& direction,
				 const sf::Vector2f& screenBoundryMin,
				 const sf::Vector2f& screenBoundrymax,
					sf::Vector2f currDirection)
{
	sf::Vector2f up = { 0 , -5 };
	sf::Vector2f down = { 0 , 5 };
	sf::Vector2f left = { -5 ,0 };
	sf::Vector2f right = { 5,0 };

	if (m_alive)
	{
		
		
		m_currentMove = direction;
		m_prevMove = m_rectangle.getPosition();
		m_rectangle.move(direction);
		

		sf::Vector2f location;
		location = m_rectangle.getPosition();
		if (!(location.x <= screenBoundrymax.x && location.x >= screenBoundryMin.x) ||
			!(location.y <= screenBoundrymax.y && location.y >= screenBoundryMin.y))
				moveRevert();
	}

}




// go back on the last move
void Predator::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

unsigned int Predator::getState() const
{
	return m_state;
}



void Predator::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
	m_alive = true;
}


bool Predator::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}


bool Predator::collideHandler(MovingObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}


bool Predator::collideHandlerStatic(StaticObject& staticObject)
{
	if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
	{
		switch (staticObject.getType())
		{
		
		case VDIAMOND:
			return false;
			break;
		}
		return true;
	}
	return false;
}

// returns the type of object 
unsigned int Predator::getType() const
{
	return m_index;
}

void Predator::disable()
{
	m_alive = false;
}
	

bool Predator::getIsAlive() const
{
	return m_alive;
}

