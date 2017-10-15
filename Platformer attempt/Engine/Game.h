#pragma once
#include "GameObjects.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Collectible.h"
#include "NonInteractive.h"
#include "Levelhazards.h"
#include "Ship.h"
#include "FlyingEnemy.h"
#include "Boss.h"




class Game
{
public:
	Game();

	void Update(sf::RenderWindow* window, float dt);
	void Draw(sf::RenderWindow* window);
	void AddObject(GameObject* obj);
	void updateCoins(int c);
	void updateScore(int s);
	void updatePoints(int p);
	void updateTime(int t, float dt);
	std::vector<GameObject*> m_gameObjects;
	void RespawnPlayer();
	void PlayerWin();
	void PlayerInShip();
	void ToggleDrawCollision() {m_drawCollision = !m_drawCollision;}
	bool DrawCollision() { return m_drawCollision;  }
	int m_healthRemaining;
	int m_bossHealthRemaining;
	int m_shipHealthRemaining;
	float m_invulnerable;
	float m_shipInvulnerable;
	void Level();



private:
	Player* m_player;
	Platform* m_platform;
	sf::View* playerView;
	Enemy* m_enemy;
	Collectible* m_collectible;
	NonInteractive* m_noninteractive;
	LevelHazards* m_levelhazards;
	Ship* m_ship;
	FlyingEnemy* m_FlyingEnemy;
	Boss* m_boss;

	int coins;
	int lives;
	int points;
	int score;
	float time;

	
	sf::Font m_mainFont;
	bool m_gameOver;
	
	int m_livesRemaining;
	float m_timeUntilRespawn;
	bool m_win;
	bool playerInShip;
	bool m_drawCollision;

	
};

