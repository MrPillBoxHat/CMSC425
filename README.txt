
Controls:
______________________________________________________________
w: jump
a: move left
d: move right
h: fire
j: dash



How to play:
______________________________________________________________
1) Navigate through the level and find the boss room
2) You have a health bar on the left of the screen.
	- If it completely depletes, you die.
	- You have 3 lives.
	- You take damage if enemy fire hits you
	- You take damage if you make contact with an enemy
3) Main Weapon: X buster.
	- You fire a plasma blast from your arm



Implementations:
______________________________________________________________
Animation/Sprites: 
	- Downloaded a full sprite sheet online
	- Modified (cut out) each sprite and made a file
	  containing all the appropriate sprites to simulate
	  a movement.
	- Added transparency.
	- Had to position each sprite in the correct position
	  in the frame
	- Animated using openGL texture mapping on GL_POLYGON



Bugs:
______________________________________________________________
Animation:

	(X)
	- Need to fix animation timings (some frames should
	  be displayed longer than other frames).
	- Fire needs to continue until finished firing
	- Jump -> run needs frame timing fixes.  Doesn't look natural
	- combination of keys + jump causes flags to screw up
	- Bullet animation needs to be fixed according to hitting wall
	- Jump fire animation is bugged, not working at all.  Causing X
	  to move wrong on the Y plane
	- Can change direction while in dash animation
	- character still slides when doing fire and dash animation
	- jump 

	(Zero)
	- No Known Bugs

	(general)
	- Fix dash.  Only move when in dash animation (not when stoppin/starting)
	- need to detec where contact is made in order to play proper damage animation
	  and move in the correct location

Camera:
	- Doesn't follow X when jumping
	- Moves at end of dash
