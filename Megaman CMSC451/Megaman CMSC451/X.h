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
		int state;
		int direction;
		GLuint textures[15];

	// Contains public functions
	public:
		// Contructor
		X();
		// Getters
		int getState(){return state;}
		int getDirection(){return direction;}
		// setters
		void setHealth(int number){health += number;}
		// Draw X
		void draw();
		// Actions
		void stand();
		void move();
		void jump();
		void fire();
		void charge();
		void dash();
		// Responses
		void damage();
		void die();
		// Loads textures
		void loadTextures();
		// Helper functions to load textures
		void loadStand();
		void loadMove();
		void loadJump();
		void loadFire();
		void loadCharge();
		void loadDash();
		void loadDamage();
		void loadDie();
};