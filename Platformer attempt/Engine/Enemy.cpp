#include "Enemy.h"
#include <iostream>
#include "Animator.h"

#include "GameObjects.h"
#include "Game.h"

Enemy::Enemy(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))
	, enemyAlive(true)
	, enemyPStart(m_pos.x, 0)
	, enemyPEnd(m_pos.x - 50, 0)
	, patrolTimer(3.f)
	, enemyDead(false)
	
	

{
	body.setSize(m_size/2.f);
	m_collision.setSize(m_size/2.f );
	
	


	anim = new Animator(this);
	anim->ChooseRow(AnimationType::SLIMEMOVE);



	movementFrame = enemyPEnd - enemyPStart;

	SquishSound.setBuffer(SquishBuffer);
	if (!SquishBuffer.loadFromFile("Audio/Squish.wav"))
	{
		std::cout << "error";
	}
	PlayerHurtSound.setBuffer(PlayerHurtBuffer);
	if (!PlayerHurtBuffer.loadFromFile("Audio/PlayerHurt.wav"))
	{
		std::cout << "error";
	}
	SquishSound.setVolume(100);
}



void Enemy::Update(sf::RenderWindow * window, float dt)
{ 

	
	Patrol(dt);



	//Update animator
	anim->Update(window, dt);
	
	//Set the body to the new position
	body.setPosition(m_pos);

	GameObject::Update(window, dt);

}

void Enemy::CollidedWith(GameObject * other)
{
	
	//--------------------------------------------------------
	Player* m_player = dynamic_cast<Player*>(other);

	if (m_player != nullptr)
	{
				
		sf::RectangleShape lastPlayerPosition = m_player->GetLastFrameCollision();

		// player squished enemy
		if (lastPlayerPosition.getPosition().x + lastPlayerPosition.getSize().x  > m_collision.getPosition().x  &&
			(lastPlayerPosition.getPosition().x < (m_lastCollision.getPosition().x + m_lastCollision.getSize().x)) &&
			lastPlayerPosition.getPosition().y < m_collision.getPosition().y)
		{
			if (enemyAlive)
			{
				// Add a vector to players y position to make him jump...
				if (m_player->IsGrounded())
				{

				}
				else
				{
				SquishSound.play();
				m_player->m_vel.y += -1000.f;
				enemyAlive = false;
				anim->ChooseRow(AnimationType::SLIMEDEAD);
				m_owner->updatePoints(100);
				}
				
			}
			else
			{

			}
			
		}
	
		// enemy hits player
		else
		{

			if (enemyAlive)
			{
				if (m_owner->m_invulnerable < 0.0f &&m_owner->m_healthRemaining >= 1)
				{

					if (m_player->IsGrounded() && enemyAlive)
					{
						m_owner->m_healthRemaining--;
						m_owner->m_invulnerable = 1.0f;
						PlayerHurtSound.play();
					}
					else
					{

					}
				}

			}
			else
			{
				enemyAlive = false;

			}
		}
		if (enemyAlive)
		{
			if (m_owner->m_invulnerable < 0.0f && m_owner->m_healthRemaining == 0)
			{
				m_player->Destroy();
			
				m_owner->RespawnPlayer();
			}
		}
			
	}


}

void Enemy::Patrol(float dt)
{
	if (enemyAlive)
	{
		patrolTimer -= dt;

		if (patrolTimer <= 0.f)
		{
			movementFrame.x *= -1;
			patrolTimer = 3.f;

			if (movementFrame.x > 0)
				anim->ChooseRow(AnimationType::SLIMEMOVER);

			else
				anim->ChooseRow(AnimationType::SLIMEMOVE);
		}

		m_pos.x += movementFrame.x *dt;
	}
	else
	{

	}
}


void Enemy::Destroy()
{
	GameObject::Destroy();
	
}

void Enemy::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	
}

