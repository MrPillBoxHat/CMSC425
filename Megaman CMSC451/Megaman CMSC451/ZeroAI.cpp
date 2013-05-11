#pragma once
#include "ZeroAI.h"
#include "Zero.h"
#include "X.h"	
#include "constants.h"

// Constructor
ZeroAI::ZeroAI(Zero *z, X *inX)
{
	zero = z;
	x = inX;
	counter = 0;
}

// Start AI
int ZeroAI::getAction()
{
	float *x_location = x->getHitBox();
	float *zero_location = zero->getPosition();
	// If zero is not in an action
	if(zero->getState() == STAND && counter % 30 == 0){
		// Make zero face X
		if(x_location[1] < zero_location[0]){
			zero->setDirection(LEFT);
		} else {
			zero->setDirection(RIGHT);
		}
		return FIRE;
	}
	counter++;
	if(counter % 60 == 0){
		counter = 0;
	}
	return STAND;
}

// run command
void ZeroAI::run()
{

}

// jump command
void ZeroAI::jump()
{

}

// saber attack command
void ZeroAI::saber()
{

}

// buster attack command
void ZeroAI::fire()
{

}

// dash command
void ZeroAI::dash()
{

}