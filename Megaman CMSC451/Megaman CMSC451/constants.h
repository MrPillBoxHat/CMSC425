//Constants used by the game

/*********************************************************************************************
* Enumerations
*	Keeps track of the state of X/Zero and also creates symbols to make code easier to read 
*	and program.
*
*********************************************************************************************/
static const enum directions {LEFT, RIGHT};
static const enum states {STAND, RUN, JUMP, FIRE, CHARGE, DASH, DAMAGE, DIE, ENTRY};
static const enum texture_states{STAND_RIGHT, STAND_LEFT, RUN_LEFT, RUN_RIGHT, JUMP_LEFT, JUMP_RIGHT,
								FIRE_LEFT, FIRE_RIGHT, DASH_LEFT, DASH_RIGHT, DAMAGE_LEFT, DAMAGE_RIGHT,
								DIE_LEFT, DIE_RIGHT, CHARGE_TEXTURE, ENTRY_TEXUTRE, JUMP_FIRE_RIGHT, JUMP_FIRE_LEFT};