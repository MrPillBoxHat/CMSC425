#pragma once
#include <ctime>
#include <cstdlib>
#include "ZeroAI.h"
#include "Zero.h"
#include "X.h"	
#include "constants.h"

// Constructor
ZeroAI::ZeroAI(Zero *z, X *inX)
{
	zero = z;
	x = inX;
	counter = -1;
	state = THINK;
	last_action = THINK;
	combo = 0;
	x_location = x->getHitBox();
	zero_location = zero->getHitBox();
	zeroIsRight = x_location[1] < zero_location[0];
	srand(time(0));
}

// Start AI
int ZeroAI::getAction(){
	counter++;
	if(counter % 101 == 0){
		counter = 0;
	}
	// If not in an action, perform new action
	if(zero->getState() == STAND){
		update();
		if(combo == 0 && counter % 100 == 0){
			// new action
			return runAI();
		// If in the middle of an action, keep going
		} else {
			switch(state)
			{
				case Z_SABER:
					return saber();
					
				case SABERBUSTER:
					return buster_saber_combo();
					
				case TACKLE:
					return tackle();
					
			}
		}
	}
	// Do nothing
	return -1;
}

int ZeroAI::runAI()
{
	random = rand() % 3;
	if(last_action == Z_SABER || last_action == TACKLE){
		last_action = MOVE_AWAY;
		return dashAway();
	} else if (distance <= 50) {
		last_action = Z_SABER;
		return saber();
	} else if (distance > 50 && distance <= 330){
		// Randomly perform either saber, tackle, or buster attack
		if(random == 0){
			last_action = state = Z_SABER;
			return saber();
		} else if(random == 1) {
			state = last_action = BUSTER;
			return buster();
		} else {
			state = last_action = TACKLE;
			return tackle();
		}
	// Perform saber buster combo
	} else {
		state = last_action = SABERBUSTER;
		return buster_saber_combo();
	}
}

// Update instance variables
void ZeroAI::update()
{
	// Check if zero passed X
	if(zeroIsRight){
		passX = x_location[0] > zero_location[1];
	} else {
		passX = x_location[1] < zero_location[0];
	}
	// update Zero's position
	zeroIsRight = x_location[1] < zero_location[0];
	// Check if X is within saber range
	if(zeroIsRight){
		// Turn zero to face right
		zero->setDirection(LEFT);
		distance = zero_location[0] - x_location[1];
	} else {
		// Turn zero to face left
		zero->setDirection(RIGHT);
		distance = x_location[0] - zero_location[1];
	}
}

int ZeroAI::buster_saber_combo()
{
	// If first or 2nd attack
	if(combo == 0 || combo == 1){
		combo++;
		state = SABERBUSTER;
		return buster();
	// If 3rd attack
	} else {
		combo = 0;
		state = THINK;
		return SABER_MISSILE;
	}
}

int ZeroAI::saber()
{
	// flags to check conditions
	bool xInRange = false;
	// Check if X is within saber range
	if(zeroIsRight){
		// Turn zero to face right
		zero->setDirection(LEFT);
		if(50 > distance){
			xInRange = true;
		}
	} else {
		// Turn zero to face left
		zero->setDirection(RIGHT);
		if(50 > distance){
			 xInRange = true;
		 }
	}
	// If not in saber range, dash to X
	if(xInRange){
		// reset combo
		combo = 0;
		state = THINK;
		counter = 50;
		return SABER;
	} else {
		combo++;
		return dashFoward();
	}
}

int ZeroAI::tackle()
{
	// If passed X, face X
	if(passX){
		if(zeroIsRight){
			zero->setDirection(LEFT);
		} else {
			zero->setDirection(RIGHT);
		}
		combo = 0;
		state = THINK;
		counter = 100;
		return STAND;
	// dash until contact is made
	} else {
		combo++;
		return dashFoward();
	}
}

int ZeroAI::dashFoward(){
	return DASH;
}

int ZeroAI::dashAway()
{
	if(zeroIsRight){
		zero->setDirection(RIGHT);
	} else {
		zero->setDirection(LEFT);
	}
	return DASH;
}

int ZeroAI::buster()
{
	return FIRE;
}