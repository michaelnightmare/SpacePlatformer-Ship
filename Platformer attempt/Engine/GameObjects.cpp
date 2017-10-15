#include "stdafx.h"
#include "GameObjects.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"

GameObject::GameObject(std::string texturePath, sf::Vector2f pos, sf::Vector2f size, const sf::RectangleShape & Collision)
	: m_pos(pos), m_size(size)
	, gravity(800.0f)
	, m_destroyed(false)
	, m_fireCooldown(0.0f)
{
	//m_sprite.setPosition(m_pos);

	if (texturePath != "")
	{
		m_texture.loadFromFile(texturePath);
	}

	body.setPosition(m_pos);
	body.setSize(m_size);
	m_collision = body;
	m_collision.setSize(Collision.getSize());
	
	body.setTexture(&m_texture);

	/*knockback.x = GetPosition().x - 50;
	knockback.y = GetPosition().y - 200;*/

	m_vel.x = 0;
	m_vel.y = 0;
	m_accel.x = 0;
	m_accel.y = 0;


}

void GameObject::Update(sf::RenderWindow * window, float dt)
{
	m_lastCollision = m_collision;
	m_collision.setPosition(body.getPosition());
}

void GameObject::Draw(sf::RenderWindow * window)
{
	window->draw(body);
	
	if (m_owner->DrawCollision())
	{
		m_collision.setFillColor(sf::Color::Red);
		window->draw(m_collision);
	}
}


void GameObject::Destroy()
{
	m_destroyed = true;
}


	
bool GameObject::IsDestroyed()
{
	return m_destroyed;
}



void GameObject::CollidedWith(GameObject * other)
{


}




 