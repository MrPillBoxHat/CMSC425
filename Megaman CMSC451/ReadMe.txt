
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
	- Jump -> run needs frame timing fixes.  Doesn't look natural
	- combination of keys + jump causes flags to screw up
	- Jump fire animation is bugged, not working at all.  Causing X
	  to move wrong on the Y plane
	- Health bar needs to stop when reaching end of screen (right side)
	- Jump hit causes constant jumping
	- No charge shot
	- Dash jump implementation messed up

	(Zero)
	- Zero saber attack needs to dash in front of X, not past X
	- Saber needs to add sword sheath to animation
	- Zero goes invincible when performing slash missile

	(General)
	- Fix camera
	- Add in more implementations
	- Health bar too big

Camera:


Things need to implement:
______________________________________________________________

	(Characters)
	- Boss areana/stage entrance