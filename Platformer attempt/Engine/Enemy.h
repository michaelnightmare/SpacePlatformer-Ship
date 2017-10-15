#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>

class Animator;
class StateMachine;

class Enemy : public GameObject
{
public:

	Enemy(std::string texturePath, sf::Vector2f pos,sf::Vector2f size);
	void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	
	virtual void CollidedWith(GameObject* other);
	void Patrol(float dt);
	
	sf::SoundBuffer SquishBuffer;
	sf::Sound SquishSound;

	sf::SoundBuffer PlayerHurtBuffer;
	sf::Sound PlayerHurtSound;

	virtual void Destroy();

protected:

	Animator* anim;
	StateMachine* m_stateMachine;
	float enemySpeed = 100.f;
	float patrolTimer;
	
	sf::Vector2f enemyPEnd;
	sf::Vector2f enemyPStart;
	sf::Vector2f movementFrame;
	bool enemyAlive;
	bool enemyDead;
	float m_timeAlive;



};

