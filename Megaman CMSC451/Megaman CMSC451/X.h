/******************************************************
* Header file for Megaman X
*	Contains all function definitions
*   and state of the character
*******************************************************/

class X {
	// Contains X's health and location
	private:
		float x_coordinate;
		float y_coordinate;
		int health;

	// Contains public functions
	public:
		// Contructor
		X();
		// Draw X
		void draw();
		// Actions
		void move(int direction);
		void jump(int direction);
		void fire(int direction);
		void charge(int direction);
		void dash(int direction);
		// Responses
		void damage(int damage);
		void die();
};