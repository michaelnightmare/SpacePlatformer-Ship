#include "Game.h"
#include <iostream>
#include "SFML\Graphics.hpp"
#include "GameObjects.h"
#include "Collider.h"
#include "Player.h"
#include <sstream>



Game::Game()
	: m_gameOver(false)
	, m_timeUntilRespawn(.01f)
	, m_livesRemaining(2)
	, coins(0)
	, lives(2)
	, points(0)
	, m_invulnerable(1.0f)
	, m_shipInvulnerable(1.0f)
	, m_healthRemaining(4)
	, m_shipHealthRemaining(4)
	, m_drawCollision(false)
	, playerInShip(false)
	, time(99)
	, m_bossHealthRemaining(10)
	, m_win(false)
	
{ 
	m_mainFont.loadFromFile("Fonts/kenpixel_high_square.ttf");

	m_ship = new Ship("Sprites/PNG/ShipSS.png", sf::Vector2f(3100, 150), sf::Vector2f(750, 850));
	AddObject(m_ship);

//Player
	m_player = new Player("Sprites/PNG/AlienSS.png", sf::Vector2f(75, 200), sf::Vector2f (100,150));
//Enemies	
	m_enemy = new Enemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(350, 325),sf::Vector2f(150,150));
	AddObject(m_enemy);

	m_enemy = new Enemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(1100, 325), sf::Vector2f(150, 150));
	AddObject(m_enemy);

	m_enemy = new Enemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(1800, 325), sf::Vector2f(150, 150));
	AddObject(m_enemy);

//Boss
	m_boss = new Boss("Sprites/PNG/Boss.png", sf::Vector2f(7500, 75), sf::Vector2f(500, 1400), m_ship);
	AddObject(m_boss);

	


//Flying Enemy
	
	m_FlyingEnemy = new FlyingEnemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(4500, -150), sf::Vector2f(200, 200));
	AddObject(m_FlyingEnemy);

	m_FlyingEnemy = new FlyingEnemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(5000, -50), sf::Vector2f(200, 200));
	AddObject(m_FlyingEnemy);

	m_FlyingEnemy = new FlyingEnemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(5500, 200), sf::Vector2f(200, 200));
	AddObject(m_FlyingEnemy);

	m_FlyingEnemy = new FlyingEnemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(6500, -75), sf::Vector2f(200, 200));
	AddObject(m_FlyingEnemy);

	m_FlyingEnemy = new FlyingEnemy("Sprites/PNG/SlimeSS.png", sf::Vector2f(7000, -100), sf::Vector2f(200, 200));
	AddObject(m_FlyingEnemy);

Level();
//Player View
	playerView = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(720.0f, 720.0f));

}

void Game::Update(sf::RenderWindow * window, float dt)
{
	if (!m_gameOver && !m_win)
	{
		time -= dt;
	}



	//ReSpawn Timer
	if (m_timeUntilRespawn > 0)
	{
		m_timeUntilRespawn -= dt;
		if (m_timeUntilRespawn <= 0)
		{
			if (!playerInShip)
			{
				m_player = new Player("Sprites/PNG/AlienSS.png", sf::Vector2f(3100, 200), sf::Vector2f(100, 150));
				AddObject(m_player);
			}
			else
			{
				m_player = new Player("Sprites/PNG/AlienSS.png", sf::Vector2f(3100, 200), sf::Vector2f(100, 150));
				AddObject(m_player);
			}

			//m_ship = new Ship("Sprites/PNG/ShipSS.png", sf::Vector2f(3100, 150), sf::Vector2f(750, 850));
			//AddObject(m_ship);
		}
	}

	//Destroy loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		if (current->IsDestroyed())
		{
			delete current;
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}

	//Update loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Update(window, dt);
	}

	//Collision Loop
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			GameObject* other = m_gameObjects[j];
			if (current->GetCollider().CheckCollision(other->GetCollider()))
			{
				current->CollidedWith(other);
			}
		}
	}

}

void Game::Draw(sf::RenderWindow * window)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		GameObject* current = m_gameObjects[i];
		current->Draw(window);
	}

	//HUD
	//-------------------------------------------------------------------------
	//Collectible coin for coin counter display
	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/PNG/coin.png"))
	{
		std::cout << "texture wont load";
	}
	sf::Sprite coin;
	coin.setTexture(texture);
	coin.setScale(.5, .5);
	coin.setOrigin(-25, -80);
	coin.setPosition(playerView->getCenter() + sf::Vector2f(215, -375));
	window->draw(coin);
	//----------------------------------------
	//X for coin counter display
	sf::Texture texture2;
	if (!texture2.loadFromFile("Sprites/PNG/X.png"))
	{
		std::cout << "texture wont load";
	}
	sf::Sprite times;
	times.setTexture(texture2);
	times.setScale(.4, .4);
	times.setOrigin(-25, -80);
	times.setPosition(sf::Vector2f(playerView->getCenter() + sf::Vector2f(255, -375)));
	window->draw(times);
	//----------------------------------------
	//Coin counter for display
	sf::Text Coins;
	Coins.setFont(m_mainFont);
	Coins.setString(std::to_string(coins));
	Coins.setCharacterSize(50);
	Coins.setPosition(playerView->getCenter() + sf::Vector2f(315, -350));
	window->draw(Coins);
	//---------------------------------------

	//Alien Lives X for display
	sf::Sprite times2;
	times2.setTexture(texture2);
	times2.setScale(.4, .4);
	times2.setOrigin(-25, -80);
	times2.setPosition(sf::Vector2f(playerView->getCenter() + sf::Vector2f(-315, -375)));
	window->draw(times2);
	//--------------------------------------

	//Alien Lives Face display
	sf::Texture texture3;
	if (!texture3.loadFromFile("Sprites/PNG/AlienLives.png"))
	{
		std::cout << "texture wont load";
	}
	sf::Sprite ALives;
	ALives.setTexture(texture3);
	ALives.setScale(.5, .5);
	ALives.setOrigin(-25, -80);
	ALives.setPosition(playerView->getCenter() + sf::Vector2f(-360, -385));
	window->draw(ALives);
	//---------------------------------------

	//Alien Lives No. for display
	sf::Text Lives;
	Lives.setFont(m_mainFont);
	Lives.setString(std::to_string(m_livesRemaining));
	Lives.setCharacterSize(50);
	Lives.setPosition(playerView->getCenter() + sf::Vector2f(-250 , -350));
	window->draw(Lives);


	
		//Alien Health Hearts
	for (int i = 0; i < m_healthRemaining; i++)
	{

		sf::Texture texture4;
		if (!texture4.loadFromFile("Sprites/PNG/Heart_full.png"))
		{
			std::cout << "texture wont load";
		}
		sf::Sprite Heart_full;
		Heart_full.setTexture(texture4);
		Heart_full.setScale(.25, .25);
		Heart_full.setPosition(playerView->getCenter() + sf::Vector2f(-335 + i * 25, -275));
		window->draw(Heart_full);

	}
	
	if (playerInShip)
	{
		//Ship Health Hearts
		for (int i = 0; i < m_shipHealthRemaining; i++)
		{

			sf::Texture texture4;
			if (!texture4.loadFromFile("Sprites/PNG/IronHeart_full.png"))
			{
				std::cout << "texture wont load";
			}
			sf::Sprite ShipHeart_full;
			ShipHeart_full.setTexture(texture4);
			ShipHeart_full.setScale(.25, .25);
			ShipHeart_full.setPosition(playerView->getCenter() + sf::Vector2f(-335 + i * 25, -275));
			window->draw(ShipHeart_full);

		}
	}
	//Timer Text
	sf::Text Timer;
	Timer.setFont(m_mainFont);
	Timer.setString("Time:");
	Timer.setCharacterSize(50);
	Timer.setPosition(playerView->getCenter() +  sf::Vector2f(-75, -350));
	window->draw(Timer);

	sf::Text TimerNo;
	TimerNo.setFont(m_mainFont);
	TimerNo.setString(std::to_string((int)time));
	TimerNo.setCharacterSize(50);
	TimerNo.setPosition(playerView->getCenter() + sf::Vector2f(-0, -350));
	window->draw(TimerNo);
	
	//Points Text
	sf::Text Points;
	Points.setFont(m_mainFont);
	Points.setString("Points:");
	Points.setCharacterSize(50);
	Points.setPosition(playerView->getCenter() + sf::Vector2f(175, -300));
	window->draw(Points);

	sf::Text PointsNo;
	PointsNo.setFont(m_mainFont);
	PointsNo.setString(std::to_string(points));
	PointsNo.setCharacterSize(50);
	PointsNo.setPosition(playerView->getCenter() + sf::Vector2f(300, -300));
	window->draw(PointsNo);

	score = coins * 100.f + points + time * 50.f;

	//GAME OVER TEXT
	if (m_gameOver)
	{
		sf::Text gameOverText;
		gameOverText.setFont(m_mainFont);
		gameOverText.setString("GAME OVER!");
		gameOverText.setCharacterSize(50);
		gameOverText.setPosition(900, 800);
		window->draw(gameOverText);
		m_healthRemaining = 0;
		m_livesRemaining = 0;

		sf::Text ScoreText;
		ScoreText.setFont(m_mainFont);
		ScoreText.setString("Score: ");
		ScoreText.setCharacterSize(50);
		ScoreText.setPosition(900, 900);
		window->draw(ScoreText);

		sf::Text ScoreNo;
		ScoreNo.setFont(m_mainFont);
		ScoreNo.setString(std::to_string(score));
		ScoreNo.setCharacterSize(50);
		ScoreNo.setPosition(1000, 900);
		window->draw(ScoreNo);
	}
	//Win Text (Currently no end)
	if (m_win)
	{
		sf::Text winText;
		winText.setFont(m_mainFont);
		winText.setString("You WIN!");
		winText.setCharacterSize(50);
		winText.setPosition(900,800);
		window->draw(winText);

		sf::Text ScoreText;
		ScoreText.setFont(m_mainFont);
		ScoreText.setString("Score: ");
		ScoreText.setCharacterSize(50);
		ScoreText.setPosition(900, 900);
		window->draw(ScoreText);

		sf::Text ScoreNo;
		ScoreNo.setFont(m_mainFont);
		ScoreNo.setString(std::to_string(score));
		ScoreNo.setCharacterSize(50);
		ScoreNo.setPosition(1000, 900);
		window->draw(ScoreNo);

	}
	

	// if player is out of the ship view follows him	
	if (!playerInShip)
	{
		playerView->setCenter(m_player->GetPosition().x + 300.f, 100);
		//If player is at edge, keep screen from showing black space
	if (m_player->GetPosition().x < 75.f)
	{
		playerView->setCenter( 375.f, 100);
	}
	
	}
	//if player is in the ship it follows the ship
	else 
	{
		playerView->setCenter(m_ship->GetPosition().x + 300.f, 100);
	}

	//if player wins the screen shifts to this location
	if (m_win || m_gameOver)
	{
		playerView->setCenter(1000, 1000);
	}

	window->setView(*playerView);
}

void Game::AddObject(GameObject * obj)
{
	m_gameObjects.push_back(obj);
	obj->SetOwner(this);
}

void Game::updateCoins(int c)
{
	coins += c;
}



void Game::updatePoints(int p)
{
	points += p;
}

void Game::updateTime(int t,float dt)
{
	time -= dt;
}

void Game::updateScore(int s)
{
	score += s;
}




void Game::RespawnPlayer()
{
	if (m_livesRemaining > 0)
	{
		m_livesRemaining--;
		m_timeUntilRespawn = 1.0f;
		m_healthRemaining = 4;
		m_shipHealthRemaining = 4;

	}

	else
	{
		m_gameOver = true;
		
	}

}
void Game::PlayerWin()
{
	
		m_win = true;
	

}
void Game::PlayerInShip()
{



	playerInShip = true;
	m_player->Destroy();
	m_ship->playerinside= true;
	

}
void Game::Level()
{
	//Backgroundpieces
	//-------------------------------

	//Rocks
	for (int i = 0; i < 2; i++)
	{
		m_noninteractive = new NonInteractive("Sprites/PNG/rock.png", sf::Vector2f(25 + i * 100, 250), sf::Vector2f(150, 150));
		AddObject(m_noninteractive);
	}

	for (int i = 0; i < 2; i++)
	{
		m_noninteractive = new NonInteractive("Sprites/PNG/rock.png", sf::Vector2f(415 + i * 100, 250), sf::Vector2f(150, 150));
		AddObject(m_noninteractive);
	}

	for (int i = 0; i < 3; i++)
	{
		m_noninteractive = new NonInteractive("Sprites/PNG/rock.png", sf::Vector2f(950 + i * 100, 250), sf::Vector2f(150, 150));
		AddObject(m_noninteractive);
	}
	//--------------------------------------------------

	//Sign
	m_noninteractive = new NonInteractive("Sprites/PNG/signRight.png", sf::Vector2f(290, 275), sf::Vector2f(125, 125));
	AddObject(m_noninteractive);
	//-----------------------------------------------------

	//Space Cactus
	m_noninteractive = new NonInteractive("Sprites/PNG/cactus2.png", sf::Vector2f(1525, 250), sf::Vector2f(150, 150));
	AddObject(m_noninteractive);
	//------------------------------------------------------

	//Fences
	for (int i = 0; i < 3; i++)
	{
		m_noninteractive = new NonInteractive("Sprites/PNG/fence.png", sf::Vector2f(1675 + i * 100, 275), sf::Vector2f(125, 125));
		AddObject(m_noninteractive);
	}

	m_noninteractive = new NonInteractive("Sprites/PNG/fenceBroken.png", sf::Vector2f(1975, 275), sf::Vector2f(125, 125));
	AddObject(m_noninteractive);

	m_noninteractive = new NonInteractive("Sprites/PNG/fence.png", sf::Vector2f(2075, 275), sf::Vector2f(125, 125));
	AddObject(m_noninteractive);
	//------------------------------------

	//Collectibles
	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(950 + i * 75, 175), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}
	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(950 + i * 75, 250), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}

	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(4500 + i * 75, -50), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}

	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(5000 + i * 75, -150), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}

	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(5750 + i * 75, -0), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}

	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(5500 + i * 75, 250), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}

	for (int i = 0; i < 5; i++) {
		m_collectible = new Collectible("Sprites/PNG/CoinSS.png", sf::Vector2f(6250 + i * 75, 150), sf::Vector2f(200, 200));
		AddObject(m_collectible);
	}
	//------------------------------------

	//Lava
	m_levelhazards = new LevelHazards("Sprites/PNG/lava.png", sf::Vector2f(675, 415), sf::Vector2f(900, 550));
	AddObject(m_levelhazards);

	m_levelhazards = new LevelHazards("Sprites/PNG/lava.png", sf::Vector2f(1300, 415), sf::Vector2f(800, 550));
	AddObject(m_levelhazards);

	m_levelhazards = new LevelHazards("Sprites/PNG/lava.png", sf::Vector2f(2575, 415), sf::Vector2f(900, 550));
	AddObject(m_levelhazards);

	m_levelhazards = new LevelHazards("Sprites/PNG/lava.png", sf::Vector2f(2800, 415), sf::Vector2f(900, 550));
	AddObject(m_levelhazards);

	for (int i = 0; i < 50; i++)
	{
		m_levelhazards = new LevelHazards("Sprites/PNG/lava.png", sf::Vector2f(3400 + i * 225, 415), sf::Vector2f(900, 550));
		AddObject(m_levelhazards);
	}

	//-----------------------------------------

	//Ground

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(0, 400), sf::Vector2f(1350, 150));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(900, 400), sf::Vector2f(900, 150));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(1500, 400), sf::Vector2f(1800, 150));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(2250, 310), sf::Vector2f(250, 310));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(2350, 210), sf::Vector2f(250, 510));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(2450, 110), sf::Vector2f(250, 710));
	AddObject(m_platform);

	m_platform = new Platform("Sprites/PNG/planet.png", sf::Vector2f(2900, 400), sf::Vector2f(1100, 150));
	AddObject(m_platform);

	//-----------------------------------------

	//Floating Platform
	m_platform = new Platform("Sprites/PNG/brick2.png", sf::Vector2f(305, 150), sf::Vector2f(150, 150));
	AddObject(m_platform);
}






