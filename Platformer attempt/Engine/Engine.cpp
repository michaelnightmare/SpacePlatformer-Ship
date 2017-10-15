// Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include "GameObjects.h"

int main()
{
	Game game;
	srand(static_cast<unsigned int>(time(0)));

	sf::RenderWindow window(sf::VideoMode(1000, 700), "Platformer!");

	//Background Texture
	//-----------------------------------------------------
	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/PNG/space1.jpg"))
	{
		std::cout << "texture wont load";
	}
	
	sf::Music Music;
	Music.openFromFile("Audio/Music.wav");
	//Music.play();
	Music.setLoop(true);
	Music.setVolume(20);
	
	sf::Sprite background;
	background.setTexture(texture);
	background.setScale(1, .7f);
	background.setPosition(0, -310.f);
	
	sf::Sprite background2;
	background2.setTexture(texture);
	background2.setScale(1, .7f);
	background2.setPosition(2700, -310.f);

	sf::Sprite background3;
	background3.setTexture(texture);
	background3.setScale(1, .7f);
	background3.setPosition(5000, -310.f);

	sf::Sprite background4;
	background4.setTexture(texture);
	background4.setScale(1, .7f);
	background4.setPosition(7000, -310.f);

	sf::Sprite background5;
	background5.setTexture(texture);
	background5.setScale(1, .7f);
	background5.setPosition(9000, -310.f);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::C)
				{
					game.ToggleDrawCollision();
				}
			}
		}

		window.clear();
        window.draw(background);
		window.draw(background2);
		window.draw(background3);
		window.draw(background4); 
		window.draw(background5);
		game.Update(&window, dt.asSeconds());
		game.Draw(&window);
		window.display();
	}

	return 0;
}
