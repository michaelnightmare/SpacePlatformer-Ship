#include "EnemyProjectiles.h"
#include "Game.h"
#include "GameObjects.h"
#include <iostream> 

EnemyProjectiles::EnemyProjectiles(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject("Sprites/PNG/Laser.png", pos, size, sf::RectangleShape(size))
	, m_timeAlive(0.0f)
	, bulletSpeed(50.0f)
{
	enemyExplodeSound.setBuffer(enemyExplodeBuffer);
	if (!enemyExplodeBuffer.loadFromFile("Audio/enemyExplode.wav"))
	{
		std::cout << "error";
	}

}

void EnemyProjectiles::Update(sf::RenderWindow * window, float dt)
{

	m_pos.x += m_movement.x;
	m_movement += m_vel * dt;
	m_timeAlive += dt;

	if (m_timeAlive > .7f)
	{
		Destroy();
	}
	body.setPosition(m_pos);
	GameObject::Update(window, dt);
}

void EnemyProjectiles::CollidedWith(GameObject * other)
{
	Ship* ship = dynamic_cast<Ship*>(other);
	if (ship != nullptr)
	{



		Destroy();
		//enemyExplodeSound.play();
		m_owner->m_shipHealthRemaining--;


	}
}

