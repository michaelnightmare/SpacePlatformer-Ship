#pragma once

#include "GameObjects.h"
#include <SFML\Graphics.hpp>
#include "Animator.h"


class Collectible : public GameObject

{
public:
	Collectible(std::string texturePath, sf::Vector2f pos, sf::Vector2f size);
	virtual void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	virtual void CollidedWith(GameObject* other);
	virtual void Destroy();
	sf::SoundBuffer CoinBuffer;
	sf::Sound CoinSound;
	
protected:
	Animator* anim;



};