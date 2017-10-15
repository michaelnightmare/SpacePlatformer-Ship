#include "Game.h"
#include "GameObjects.h"
#include "Ship.h"
#include <iostream>
#include "Animator.h"
#include "LaserBeam.h"
#include "Player.h"




Ship::Ship(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(sf::Vector2f(50, 150)))
	, shipSpeed(0.f)
	, shipCollide(false)
	
	

{
	body.setSize(m_size / 4.0f);
	m_collision.setSize(sf::Vector2f(195.f, 150.f));

	anim = new Animator(this);
	anim->ChooseRow(AnimationType::SHIPIDLE);
	maxSpeed = 500.f;
	currentAcceleration = 0.f;
	defaultAcceleration = 600.f;
	defaultDeceleration = 3000.f;
	BeamSound.setBuffer(BeamBuffer);
	if (!BeamBuffer.loadFromFile("Audio/beam.wav"))
	{
		std::cout << "error";
	}
	BeamSound.setVolume(20);


}



void Ship::Update(sf::RenderWindow * window, float dt)
{
	m_fireCooldown -= dt;
	//setting the x and y movements to 0
	m_movement.x = 0.f;
	m_movement.y = 0.f;

	////Handle ship movements
	if (playerinside)
	{

		HandleInput(dt);
	
	}
	m_pos.y += m_movement.y;
	m_pos.x += m_movement.x;
	//add vel to movement
	m_movement += m_vel * dt;

	//Set the body to the new position
	body.setPosition(m_pos);

	anim->Update(window, dt);
	GameObject::Update(window, dt);
}

void Ship::UpdateCollision()
{
	body.setPosition(m_pos);
	GameObject::Update(NULL, 0.0f);
	m_collision.setPosition(body.getSize().x * .5f + body.getPosition().x , body.getPosition().y);
}

void Ship::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);	
	
}

void Ship::Destroy()
{
	GameObject::Destroy();

}

void Ship::CollidedWith(GameObject* other)
{
	Player* m_player = dynamic_cast<Player*>(other);

	if (m_player != nullptr)
	{
		shipCollide = true;
	}

}


void Ship::HandleInput(float dt)
{

	currentAcceleration = 0.f;
		//KEY PRESSED
		//---------------------------------------------
		//Movement to the right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_movement.x = shipSpeed * dt;
			currentAcceleration = defaultAcceleration;
			anim->ChooseRow(AnimationType::SHIPMOVE);
			
		}
		else
		{
			currentAcceleration = defaultAcceleration * .5;
			anim->ChooseRow(AnimationType::SHIPMOVE);
		
			
		}

		//Movement to the left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//m_movement.x = -shipSpeed * dt;
			//travel left original way
			//currentAcceleration = -defaultAcceleration;
			//traveling up left movement
			//currentAcceleration = defaultAcceleration;
			
		}
	

		//Movement up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//for flying up
			//m_movement.y = shipSpeed * dt;

			//for flying up
			//currentAcceleration = -defaultAcceleration;

			//for flying right
			m_movement.y = -shipSpeed * dt;
			//for flying right
			currentAcceleration = defaultAcceleration;
			
		}

		//Movement down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_movement.y = shipSpeed * dt;
			//currentAcceleration = defaultAcceleration;
		
		}
	
		shipSpeed += currentAcceleration * dt;

		if (shipSpeed > maxSpeed)
		{
			shipSpeed = maxSpeed;
		}

		if (shipSpeed < -maxSpeed)
		{
			shipSpeed = -maxSpeed;
		}

		if (currentAcceleration == 0 && shipSpeed != 0)
		{
			shipSpeed -= shipSpeed * 20 * dt;
		}
		//Space Travel to the Right
		m_movement.x = shipSpeed * dt;
		
		//Space Travel Up
		//m_movement.y = -shipSpeed * dt;

	    //Space Travel Down
		//m_movement.y = shipSpeed * dt;

		//Shoot Laser Beams
		if (m_fireCooldown <= 0.0f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_fireCooldown = .7f;
				LaserBeam* laserBeam = new LaserBeam("Sprites/PNG/Laser.png", sf::Vector2f(this->GetPosition().x + 215, this->GetPosition().y + 100), sf::Vector2f(65, 25));
				laserBeam->m_vel.x += laserBeam->bulletSpeed;
				BeamSound.play();

				m_owner->AddObject(laserBeam);

			}
		}
}

 bool Ship::ShipPlayerCollide() 
{
	return shipCollide;
}
