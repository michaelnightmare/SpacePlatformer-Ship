#include "Game.h"
#include "GameObjects.h"
#include "NonInteractive.h"




NonInteractive::NonInteractive(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))


{
	




}



void NonInteractive::Update(sf::RenderWindow * window, float dt)
{
	GameObject::Update(window, dt);
}

void NonInteractive::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);
}
