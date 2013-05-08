// Class for Main Menu screen
#include <GL\glut.h>

class Main_Menu
{
	private:
		int menu_state;
		int counter;
		GLuint textures[7];
		// Loads main menu textures
		void loadIntro();
		void loadNewGame();
		void loadContinue();
		void loadOption();
		void loadTraining();
	
	public:
		enum states {INTRO, INTRO_PRESS, NEWGAME, CONTINUE, OPTION, TRAINING, INGAME};
		// Constructor
		Main_Menu();
		// getter
		int getMenuState(){return menu_state;}
		// setter
		void setMenuState(int state){menu_state = state;}
		// Draw and load functions
		void loadTextures();
		void draw();
};