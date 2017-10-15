#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>


class Animator;
class StateMachine;

class Player : public GameObject
{
public:

	Player(std::string texturePath,  sf::Vector2f pos, sf::Vector2f size);
	void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	virtual void CollidedWith(GameObject* other);
	bool IsGrounded() { return isgrounded; }
	Collider GetCollider() { return Collider(body); }
	void HandleInput(float dt);
	void Restrain();
	void UpdateCollision();
	
	sf::SoundBuffer JumpBuffer;
	sf::Sound JumpSound;
	sf::SoundBuffer BumpBuffer;
	sf::Sound BumpSound;
	
	bool playerHit;
	bool getInShip;
	
protected:

	Animator* anim;
	StateMachine* m_stateMachine;

	float currentAcceleration;
	float defaultAcceleration;
	float defaultDeceleration;


	float playerSpeed;
	float maxSpeed;
	float jumpHeight = 0.f; 
	float jumpCooldown;
	bool isjumping;
	bool isgrounded;
	bool facingRight;
	bool playerInShip;
	bool enemyIsDead;
	

	
	
	
};

