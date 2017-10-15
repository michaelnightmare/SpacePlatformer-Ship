#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects.h"

enum AnimationType
{
	IDLE,
	IDLEL,
	RUN,
	RUNL,
	JUMP,
	JUMPL,
	COIN,
	SLIMEMOVE,
	SLIMEMOVER,
	SLIMEDEAD,
	SLIMEDEADR,
	FLYINGENEMY,
	SHIPIDLE,
	SHIPMOVE,
};

class Animator
{
public:
	Animator(GameObject* AnimatedObj);
	virtual void Update(sf::RenderWindow* window, float dt);

	int GetRow() { return m_row; }

	int ChooseRow(AnimationType type);
	void LoopAnimation(float dt, int framecount);
	
protected:

	GameObject* owner;

	float m_timeElapsed;
	float m_timer;
	bool flip;
   
	int m_column;
	int m_row;
	int framecount;
};