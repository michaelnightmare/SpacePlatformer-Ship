#include "FlyingEnemy.h"
#include "Animator.h"


#include "Game.h"
#include <iostream>
#include "EnemyProjectiles.h"

FlyingEnemy::FlyingEnemy(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
            :Enemy(texturePath, pos, size)
			, enemyPStart(m_pos.x, 0)
			, enemyPEnd(m_pos.x - 50, 0)
			, patrolTimer(3.f)
			, enemyAlive(true)
			, enemyDead(false)
{
	body.setSize(m_size / 2.f);
	m_collision.setSize(m_size / 2.f);
	anim = new Animator(this);
	anim->ChooseRow(AnimationType::FLYINGENEMY);

	movementFrame = enemyPEnd - enemyPStart;

	PlayerHurtSound.setBuffer(PlayerHurtBuffer);
	if (!PlayerHurtBuffer.loadFromFile("Audio/PlayerHurt.wav"))
	{
		std::cout << "error";
	}
}

void FlyingEnemy::Draw(sf::RenderWindow * window)
{
	GameObject::Draw(window);
}

void FlyingEnemy::Update(sf::RenderWindow * window, float dt)
{
	m_owner->m_shipInvulnerable -= dt;
	m_fireCooldown -= dt;
	Patrol(dt);



	//EnemyFire
	if (m_fireCooldown < 0.0f)
	{
		Fire();
	}


	//Update animator
	anim->Update(window, dt);

	//Set the body to the new position
	body.setPosition(m_pos);

	GameObject::Update(window, dt);
}

void FlyingEnemy::CollidedWith(GameObject * other)
{
	
	Ship* ship = dynamic_cast<Ship*>(other);
	if (ship != nullptr)
	{

			if (m_owner->m_shipInvulnerable < 0.0f && m_owner->m_shipHealthRemaining >= 1)
			{
				m_owner->m_shipHealthRemaining--;
				m_owner->m_shipInvulnerable = 4.0f;
				PlayerHurtSound.play();
				std::cout << "hit" << std::endl;
			}
			else
			{
				
			}

			if (m_owner->m_shipInvulnerable < 0.0f && m_owner->m_shipHealthRemaining == 0)
			{
				other->Destroy();
				m_owner->RespawnPlayer();
			}


	}
}

void FlyingEnemy::Patrol(float dt)
{
	if (enemyAlive)
	{
		patrolTimer -= dt;

		if (patrolTimer <= 0.f)
		{
			movementFrame.x *= -1;
			patrolTimer = 3.f;

			if (movementFrame.x > 0)
				anim->ChooseRow(AnimationType::FLYINGENEMY);

			else
				anim->ChooseRow(AnimationType::FLYINGENEMY);
		}

		m_pos.x += movementFrame.x *dt;
	}
	else
	{

	}
}

void FlyingEnemy::Destroy()
{
	GameObject::Destroy();
	m_owner->updatePoints(100);

}

void FlyingEnemy::Fire()
{
	m_fireCooldown = 3.f;
	EnemyProjectiles* enemyprojectiles = new EnemyProjectiles("Sprites/PNG/Laser2.png", sf::Vector2f(this->GetPosition().x, this->GetPosition().y+50), sf::Vector2f(45, 7));
	enemyprojectiles->m_vel.x -= enemyprojectiles->bulletSpeed;
	//BeamSound.play();
	m_owner->AddObject(enemyprojectiles);
}
