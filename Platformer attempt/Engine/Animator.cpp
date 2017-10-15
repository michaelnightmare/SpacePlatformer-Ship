#include "Animator.h"
#include <iostream>


Animator::Animator(GameObject* AnimatedObj) : owner(AnimatedObj),

m_column(0), m_row(0), m_timer(0.15f), m_timeElapsed(0.f)
{
	
}

void Animator::Update(sf::RenderWindow* window, float dt)
{
	//Starts idle (base row = 0, base column = 0)

	owner->body.setTextureRect(sf::IntRect(m_column * 128, m_row * 128, 110, 128));
	
	LoopAnimation(dt,framecount);
}

int Animator::ChooseRow(AnimationType type)
{
	switch (type)
	{
	
	case AnimationType::RUN:
	{
		
		framecount = 1;
		return m_row = 1;
		break;
	}

	case AnimationType::RUNL:
	{
		
		framecount = 1;
		return m_row = 3;
		break;
	}

	case AnimationType::JUMP:
	{

		framecount =  4;
		return m_row = 2;
		break;
	}
	case AnimationType::JUMPL:
	{

		framecount = 4;
		return m_row = 4;
		break;
	}
	
	case AnimationType::IDLE:
	{
		framecount = 0;
		return m_row = 0;
		break;
	}
	case AnimationType::IDLEL:
	{
		framecount = 0;
		return m_row = 5;
		break;
	}
	case AnimationType::COIN:
	{
		framecount = 5;
		return m_row = 0;
		break;
	}
	case AnimationType::FLYINGENEMY:
	{
		framecount = 4;
		return m_row = 0;
		break;
	}

	case AnimationType::SLIMEMOVE:
	{
		framecount = 1;
		return m_row = 1;
		break;
	}
	case AnimationType::SLIMEMOVER:
	{
		framecount = 1;
		return m_row = 5;
		break;
	}
	case AnimationType::SLIMEDEAD:
	{
		framecount = 0;
		return m_row = 3;
		break;
	}
	case AnimationType::SLIMEDEADR:
	{
		framecount = 0;
		return m_row = 7;
		break;
	}
	case AnimationType::SHIPIDLE:
	{
		framecount = 0;
		return m_row = 0;
		break;
	}
	case AnimationType::SHIPMOVE:
	{
		framecount = 4;
		return m_row = 1;
		break;
	}

	}
}

void Animator::LoopAnimation(float dt,int framecount)
{
	m_timeElapsed -= dt;

	if (m_timeElapsed <= 0)
	{
		m_timeElapsed = m_timer;
		m_column++;
	}

	if (m_column > framecount)

	{
		m_column = 0;

	}
}