#pragma once
#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>


class Animator;
class StateMachine;
class Ship;

class Boss : public GameObject
{
public:

	Boss(std::string texturePath, sf::Vector2f pos, sf::Vector2f size, Ship* player);
	void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);

	virtual void CollidedWith(GameObject* other);
	void Patrol(float dt);

	

	sf::SoundBuffer PlayerHurtBuffer;
	sf::Sound PlayerHurtSound;

	virtual void Destroy();

protected:

	Animator* anim;
	StateMachine* m_stateMachine;
	float bossSpeed = 250.f;
	float patrolTimer;
	Ship* m_Ship;
	sf::Vector2f bossPEnd;
	sf::Vector2f bossPStart;
	sf::Vector2f movementFrame;
	bool bossAlive;
	bool bossDead;
	float m_timeAlive;



};

