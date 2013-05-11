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
	state = THINK;
	combo = 0;
	x_location = x->getHitBox();
	zero_location = zero->getHitBox();
}

// Start AI
int ZeroAI::getAction()
{
	// If zero is not in an action
	if(zero->getState() == STAND && counter % 169 == 0 && combo == 0){
		// Make zero face X
		if(x_location[1] < zero_location[0]){
			zero->setDirection(LEFT);
		} else {
			zero->setDirection(RIGHT);
		}
		combo++;
		return saber();
	}
	if(zero->getState() == STAND && combo != 0){
		return saber();
	}
	counter++;
	if(counter % 170 == 0){
		counter = 0;
	}
	return -1;
}

int ZeroAI::buster_saber_combo()
{
	// If first or 2nd attack
	if(combo == 1 || combo == 2){
		combo++;
		return buster();
	// If 3rd attack
	} else {
		return saber();
	}
}

int ZeroAI::saber()
{
	// flags to check conditions
	bool zeroIsRight = x_location[1] < zero_location[0];
	bool xInRange = false;
	// Check if X is within saber range
	if(zeroIsRight){
		// Turn zero to face right
		zero->setDirection(LEFT);
		if(65 > zero_location[0] - x_location[1]){
			xInRange = true;
		}
	} else {
		// Turn zero to face left
		zero->setDirection(RIGHT);
		if(65 > (x_location[1] - zero_location[0])){
			 xInRange = true;
		 }
	}
	// If not in saber range, dash to X
	if(xInRange){
		// reset combo
		combo = 0;
		return SABER;
	} else {
		return dash();
	}
}

int ZeroAI::tackle()
{
	// flags to check conditions
	bool zeroIsRight = x_location[1] < zero_location[0];
	bool passX;
	if(zeroIsRight){
		passX = x_location[0] > zero_location[1];
	} else {
		passX = x_location[1] < zero_location[0];
	}
	// If passed X, face X
	if(passX){
		if(zeroIsRight){
			zero->setDirection(LEFT);
		} else {
			zero->setDirection(RIGHT);
		}
		combo == 0;
	// dash until contact is made
	} else {
		return dash();
	}
}

int ZeroAI::dash(){
	return DASH;
}

int ZeroAI::buster()
{
	return FIRE;
}