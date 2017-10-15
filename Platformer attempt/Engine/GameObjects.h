#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Collider.h"

class Game;

class GameObject
{
public:

	GameObject(std::string texturePath, sf::Vector2f pos, sf::Vector2f size, const sf::RectangleShape& Collision );
	virtual void Draw(sf::RenderWindow* window);
	virtual void Update(sf::RenderWindow* window, float dt);
	const sf::Vector2f& GetSize() { return body.getSize(); }
	void SetPosition(sf::Vector2f newPosition) { body.setPosition(newPosition); }
	void SetOwner(Game* game) { m_owner = game; }
	virtual void CollidedWith(GameObject* other);
	virtual void Destroy();
	
	bool IsDestroyed();
	sf::RectangleShape GetLastFrameCollision() { return m_lastCollision; }
	Collider GetCollider() { return Collider(m_collision); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::RectangleShape body;
	//sf::Vector2f knockback;
	float gravity; 
	sf::Vector2f m_vel;
protected:

	Game* m_owner;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Vector2f m_movement;
	bool m_destroyed;
	float m_fireCooldown;


	
	sf::Vector2f m_accel;
    sf::RectangleShape m_collision;
	sf::RectangleShape m_lastCollision;

	
	sf::Texture m_texture;

};
