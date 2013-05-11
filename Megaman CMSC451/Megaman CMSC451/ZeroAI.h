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
		void buster_saber_combo();
		void buster();
		void saber();
		void dash();

	public:
		// Constructor
		ZeroAI(Zero *z, X *inX);
		// AI tells Zero what to do
		int getAction();
};