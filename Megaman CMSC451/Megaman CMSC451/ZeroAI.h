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
		// Actions performed in sequence
		int combo;
		int state;
		// Keeps track of X and Zero location
		float *x_location;
		float *zero_location;
		bool zeroIsRight;
		int distance;
		int buster_saber_combo();
		int buster();
		int saber();
		int tackle();
		int dash();
		void update();
		
		// action states
		enum action {THINK, SABERBUSTER, Z_SABER, BUSTER, TACKLE};

	public:
		// Constructor
		ZeroAI(Zero *z, X *inX);
		// Setter
		void setState(int inState){state = inState;}
		// AI tells Zero what to do
		int getAction();
};