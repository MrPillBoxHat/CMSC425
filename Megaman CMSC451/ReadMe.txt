
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
	- You take damage if enemy fire hits you
	- You take damage if you make contact with an enemy
3) Main Weapon: X buster.
	- You fire a plasma blast from your arm
	- Hold the fire button to charge






Bugs:
______________________________________________________________
Animation:

	(X)
	- Jump -> run needs frame timing fixes.  Doesn't look natural
	- combination of keys + jump causes flags to screw up
	- Jump fire animation is bugged, not working at all.  Causing X
	  to move wrong on the Y plane
	- bullet splat is messed up
	- Dash animation not scaled properly
	- Health bar goes upside down randomly for some reason
	- jump and turn and fire screws up cannon location
	- perfrom mid-air jumps when pressing left, right, jump and fire
	  jump, right, and fire key cause x to "fly"
	- dash to wall jump is messed up
	- can shoot through walls
	- sometimes dash abruptly ends
	- X character data gets messed up on boss entrance (pressing random buttons)
	- doesn't charge unless in STAND state
	- teleports up the wall when trying to wall jump sometimes
	- glitchy when trying to run/dash while up against the wall
	- when doing a run dash, if no buttons are held, X should just drop
	- doesn't die when getting hit in the air
	- fix charge blast when not max, shoots max shot.

	- Possible future bugs
		- slide hit, need to resize hitbox and texture box

	(Zero)
	- saber attack needs to dash in front of X, not past X
	- Saber needs to add sword sheath to animation
	- first bullet(attack?) doesn't hurt
	- needs collision detection
	- z_bullet hit box too tall
	- flickers on entry
	- hit box too large
	- needs scaling work on entrance ANimation
	- saber hit box may be created too late

	(General)
	- Fix camera	
	- Add in more implementations


Things need to implement:
______________________________________________________________
	
	(X)
	- dash wall jump

	(Misc)
	- Talking/text
	- Boss areana/stage entrance
	- More stages/abilities/items
	- Fade out screen when finished
	- Add more enemies