#include "LaserBeam.h"
#include "Game.h"
#include "GameObjects.h"
#include <iostream> 

LaserBeam::LaserBeam(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject("Sprites/PNG/missle.png", pos, size, sf::RectangleShape(size))
	, m_timeAlive(0.0f)
	, bulletSpeed(50.0f)
{
	enemyExplodeSound.setBuffer(enemyExplodeBuffer);
	if (!enemyExplodeBuffer.loadFromFile("Audio/enemyExplode.wav"))
	{
		std::cout << "error";
	}
	
}

void LaserBeam::Update(sf::RenderWindow * window, float dt)
{
	
	m_pos.x += m_movement.x;
	m_movement += m_vel * dt;
	m_timeAlive += dt;

	if (m_timeAlive > .9f)
	{
		Destroy();
	}
	body.setPosition(m_pos);
	GameObject::Update(window, dt);
}

void LaserBeam::CollidedWith(GameObject * other)
{
	FlyingEnemy* flyingEnemy = dynamic_cast<FlyingEnemy*>(other);
	if (flyingEnemy != nullptr)
	{
		


		Destroy();
		enemyExplodeSound.play();
		other->Destroy();


	}

	Boss* boss = dynamic_cast<Boss*>(other);
	if (boss != nullptr)
	{
		if (m_owner->m_bossHealthRemaining >= 1)
		{
			m_owner->m_bossHealthRemaining--;
			std::cout << m_owner->m_bossHealthRemaining << std::endl;
			Destroy();
		}
		
		if (m_owner->m_bossHealthRemaining == 0)
		{
			Destroy();
			enemyExplodeSound.play();
			other->Destroy();
			m_owner->PlayerWin();
		}

	}
}

