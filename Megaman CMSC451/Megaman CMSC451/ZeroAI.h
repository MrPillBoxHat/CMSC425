#pragma once
#include "Zero.h"
#include "X.h"

// Zero AI class
class ZeroAI
{
	private:
		// hero's in the world
		Zero *zero;
		X *x;
		// thinking time
		int counter;
		// Actions
		void run();
		void jump();
		void saber();
		void fire();
		void dash();

	public:
		// Constructor
		ZeroAI(Zero *z, X *inX);
		// AI tells Zero what to do
		int getAction();
};