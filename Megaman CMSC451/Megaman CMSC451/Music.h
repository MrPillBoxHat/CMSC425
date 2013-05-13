/****************************************************************************************
* Music Class
*	This is the music player class.  It will play all music for the game depending on
*	state.
****************************************************************************************/

class Music{
	public:
		void endWithError(char* msg);

	private:
		Music();
		void play();
};