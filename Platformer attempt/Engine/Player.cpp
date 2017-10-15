#include "Player.h"
#include "Game.h"
#include "GameObjects.h"

#include <iostream>
#include "Animator.h"
#include "Approach.h"
#include "Collider.h"
#include "Ship.h"

Player::Player(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(sf::Vector2f(50, 150)))
	, isjumping(false)
	, jumpCooldown(0.0f)
	, isgrounded(false)
	, playerSpeed(0.f)
	, facingRight(true)
	, playerInShip(false)
	, enemyIsDead(false)
	, getInShip(false)
	
{   

	anim = new Animator(this);


	m_collision.setSize(sf::Vector2f(30.f,150.f));
	
	JumpSound.setBuffer(JumpBuffer);
	if (!JumpBuffer.loadFromFile("Audio/Jump.wav"))
	{
		std::cout << "error";
	}
	BumpSound.setBuffer(BumpBuffer);
	if (!BumpBuffer.loadFromFile("Audio/Bump.wav"))
	{
		std::cout << "error";
	}

	
	JumpSound.setVolume(20);

	maxSpeed = 300.f;

	currentAcceleration = 0.f;
	defaultAcceleration = 600.f;
	defaultDeceleration = 3000.f;
	
}

void Player::Update(sf::RenderWindow * window, float dt)
{
	
	m_owner->m_invulnerable -= dt;

	
	//}

	//Kinda unnessary, stop player from moving off the edge of the map
	Restrain();

	//Lower the jump cooldown
	jumpCooldown -= dt;
	
	//Add gravity into acceleration
	m_accel.y = gravity;

	//Check for movement commands
	//Start by zeroing out m_movement
	m_movement.x = 0.f;
	m_movement.y = 0.f;

	//Check for input and apply movement etc..
	HandleInput(dt);
	
	//Add acceleration to velocity, then add the velocity to movement
	m_movement += m_vel * dt; 
	

	//Add any movement to the player

    m_pos.y += m_movement.y;
	m_pos.x += m_movement.x;
	m_vel.y += gravity * dt ;


	//Update the animator
	anim->Update(window, dt);

	//Set the body to the new position	
	UpdateCollision();	
}

void Player::UpdateCollision()
{
	body.setPosition(m_pos);
	GameObject::Update(NULL, 0.0f);
	m_collision.setPosition(body.getSize().x * 0.5f + body.getPosition().x, body.getPosition().y);
}

void Player::CollidedWith(GameObject * other)
{
	
	//Platform Collision
	//------------------------------------------------------------
	Platform* m_platform = dynamic_cast<Platform*>(other);

	bool collidedVertically = false;
	bool collidedHorizontally = false;
	if (m_platform != nullptr )
	{				
		if (GetCollider().CheckCollision(other->GetCollider()))
		{				
			m_pos.y -= m_movement.y;
			m_vel.y = 0;
			isgrounded = true;
			UpdateCollision();
			collidedVertically = true;
		}
		if (GetCollider().CheckCollision(other->GetCollider()))
		{	
			m_pos.x -= m_movement.x;
			UpdateCollision();
			collidedHorizontally = true;
		}
	}

	Ship* ship = dynamic_cast<Ship*>(other);
		
		if (ship)
		{
			if (ship->ShipPlayerCollide())
			{
				getInShip = true;
			}
		}



}

void Player::HandleInput(float dt)
{

	if (facingRight && isgrounded)
	{
		anim->ChooseRow(AnimationType::IDLE);

	}
	else if (!facingRight && isgrounded)
	{
		anim->ChooseRow(AnimationType::IDLEL);
	}

	currentAcceleration = 0.f;
	//KEY PRESSED
	//---------------------------------------------
	//Movement to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		
		facingRight = true;
		if (isgrounded)
		{
			currentAcceleration = defaultAcceleration;
			anim->ChooseRow(AnimationType::RUN);
		}
		else
		{
			currentAcceleration = defaultAcceleration * .5;
		}

	}

	//Movement to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		facingRight = false; 
		
		if (isgrounded)
		{
			currentAcceleration = -defaultAcceleration;
			anim->ChooseRow(AnimationType::RUNL) ;
		}
		else 
		{
			currentAcceleration = -defaultAcceleration * .5;
		}
	}
	
	playerSpeed += currentAcceleration * dt;

	if (playerSpeed > maxSpeed)
	{
		playerSpeed = maxSpeed;
	}

	if (playerSpeed < -maxSpeed)
	{
		playerSpeed = -maxSpeed;
	}

	if (currentAcceleration == 0 && playerSpeed != 0)
	{
		playerSpeed -= playerSpeed * 20 * dt;
	}

	m_movement.x = playerSpeed * dt;
	//Movement ATTACK
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
	}
	//Enter Ship
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{	
		if(getInShip)
		{
		m_owner->PlayerInShip();
		anim->ChooseRow(AnimationType::SHIPMOVE);
		}
		
	}

	//Jumping  
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)  && jumpCooldown <= 0.0f && isgrounded)
	{
	
		//Player isn't on the ground anymore
		isgrounded = false;
		isjumping = true; 
		m_vel.y = -700.f;
		if (!isgrounded && facingRight)
		{
			anim->ChooseRow(AnimationType::JUMP);
		}
		if(!isgrounded && !facingRight)
		{
			anim->ChooseRow(AnimationType::JUMPL);
		}

		JumpSound.play();
		std::cout << "Jumped";

		//Set cooldown for jump
		jumpCooldown = 1.5f;
	}



}

void Player::Restrain()
{
	//character cant leave the screen to the left
	if (body.getPosition().x < -35)
	{
		m_pos.x = -35;
	}
}




void Player::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
}

