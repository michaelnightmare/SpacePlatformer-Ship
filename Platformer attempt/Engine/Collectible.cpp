#include "Game.h"
#include "GameObjects.h"
#include "Collectible.h"
#include <iostream>




Collectible::Collectible(std::string texturePath, sf::Vector2f pos, sf::Vector2f size)
	: GameObject(texturePath, pos, size, sf::RectangleShape(size))
	

{
	body.setSize(m_size / 4.0f);
	m_collision.setSize(m_size / 4.0f);
	CoinSound.setBuffer(CoinBuffer);
	if (!CoinBuffer.loadFromFile("Audio/Coin.wav"))
	{
		std::cout << "error";
	}
	CoinSound.setVolume(15);
	anim = new Animator(this);
	anim->ChooseRow(AnimationType::COIN);
}



void Collectible::Update(sf::RenderWindow * window, float dt)
{
	GameObject::Update(window, dt);
	anim->Update(window,dt);
}

void Collectible::Draw(sf::RenderWindow* window)
{
	GameObject::Draw(window);
	window->draw(body);
}

void Collectible::Destroy()
{
	GameObject::Destroy();
	CoinSound.play();
}

void Collectible::CollidedWith(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);

	if (player)
	{
		this->Destroy();
		m_owner->updateCoins(1);
	}

	Ship* ship = dynamic_cast<Ship*>(other);

	if (ship)
	{
		this->Destroy();
		m_owner->updateCoins(1);
	}
}
