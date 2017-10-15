#include "Boss.h"
#include <iostream>
#include "Animator.h"


#include "GameObjects.h"
#include "Game.h"
#include "Ship.h"

Boss::Boss(std::string texturePath, sf::Vector2f pos, sf::Vector2f size, Ship* player)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))
	, bossAlive(true)
	, bossPStart(0, m_pos.y)
	, bossPEnd(0, m_pos.y - 125)
	, patrolTimer(2.f)
	, bossDead(false)
	, m_Ship(player)


{
	body.setSize(m_size/2.f);
	//m_collision.setSize(m_size / 2.f);

	anim = new Animator(this);

	
	movementFrame = bossPEnd - bossPStart;
	//m_stateMachine->SetCurrentState(StandingState::Instance());

	PlayerHurtSound.setBuffer(PlayerHurtBuffer);
	if (!PlayerHurtBuffer.loadFromFile("Audio/PlayerHurt.wav"))
	{
		std::cout << "error";
	}
	
}



void Boss::Update(sf::RenderWindow * window, float dt)
{
	

	Patrol(dt);



	//Update animator
	//anim->Update(window, dt);

	body.setPosition(m_pos);

	//Set the body to the new position
	if (m_Ship->body.getPosition().x > 7000.f)
	{
		body.setPosition(m_Ship->body.getPosition().x + 400, body.getPosition().y);
	}

	

	GameObject::Update(window, dt);

}

void Boss::CollidedWith(GameObject * other)
{



}

void Boss::Patrol(float dt)
{
	if (bossAlive)
	{
		patrolTimer -= dt;

		if (patrolTimer <= 0.f)
		{
			movementFrame.y *= -1;
			patrolTimer = 2.f;

		
		}

		m_pos.y += movementFrame.y *dt;
	}
	else
	{

	}
}


void Boss::Destroy()
{
	GameObject::Destroy();

}

void Boss::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);

}

