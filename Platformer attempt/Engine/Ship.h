#pragma once
#include "GameObjects.h"
#include <SFML\Graphics.hpp>
#include "Animator.h"



class Ship : public GameObject

{
public:
	Ship(std::string texturePath, sf::Vector2f pos, sf::Vector2f size);
	virtual void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	virtual void CollidedWith(GameObject* other);
	virtual void Destroy();
	void HandleInput(float dt);
	bool playerinside;
	sf::SoundBuffer BeamBuffer;
	sf::Sound BeamSound;
	bool ShipPlayerCollide();
	void UpdateCollision();
	

protected:
	Animator* anim;
	float shipSpeed;
	float currentAcceleration;
	float defaultAcceleration;
	float defaultDeceleration;
	float maxSpeed;
	bool shipCollide; 

};