#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>

class LaserBeam : public GameObject
{
public:
	LaserBeam(std::string texturePath, sf::Vector2f pos, sf::Vector2f size);
	virtual void Update(sf::RenderWindow * window, float dt);

	virtual void CollidedWith(GameObject* other);
	float m_timeAlive;
	float bulletSpeed;
	sf::SoundBuffer enemyExplodeBuffer;
	sf::Sound enemyExplodeSound;
	

protected:
	

	

};