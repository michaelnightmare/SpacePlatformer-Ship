#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>


class Platform : public GameObject

{ 
public:
	Platform(std::string texturePath, sf::Vector2f pos, sf::Vector2f size);
	virtual void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	
	
};