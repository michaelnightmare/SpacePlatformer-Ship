#include "Game.h"
#include "GameObjects.h"
#include "Platform.h"




Platform::Platform(std::string texturePath, sf::Vector2f pos,sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))

{
	body.setSize(m_size/ 2.0f );
	m_collision.setSize(m_size / 2.0f);


}



void Platform::Update(sf::RenderWindow * window, float dt)
{
	GameObject::Update(window, dt);
}

void Platform::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);
}