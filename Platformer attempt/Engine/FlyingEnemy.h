#pragma once
#include <SFML\Graphics.hpp>
#include "Enemy.h"
#include "Animator.h"

class Animator;
class StateMachine;

class FlyingEnemy : public Enemy
{
public:

	FlyingEnemy(std::string texturePath, sf::Vector2f pos, sf::Vector2f size);
	void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	virtual void CollidedWith(GameObject* other);
	void Patrol(float dt);
	void Fire();
	sf::SoundBuffer PlayerHurtBuffer;
	sf::Sound PlayerHurtSound;

	void Destroy();

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
