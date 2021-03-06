#pragma once

//Constants used by the game

/*********************************************************************************************
* Enumerations
*	Keeps track of the state of X/Zero and also creates symbols to make code easier to read 
*	and program.
*
*********************************************************************************************/
static const enum directions {LEFT, RIGHT};
static const enum states {STAND, RUN, JUMP, JUMP_OUT, FIRE, CHARGE, DASH, DAMAGE, DIE_STATE, ENTRY, SABER, SABER_MISSILE, SLIDE, CHARGE_FIRE};
static const enum texture_states{STAND_RIGHT, STAND_LEFT, RUN_LEFT, RUN_RIGHT, JUMP_LEFT, JUMP_RIGHT,
								FIRE_LEFT, FIRE_RIGHT, DASH_LEFT, DASH_RIGHT, DAMAGE_LEFT, DAMAGE_RIGHT,
								DIE, ENTRY_TEXUTRE, JUMP_FIRE_RIGHT, JUMP_FIRE_LEFT, HEALTH_BAR, HEALTH_BLOCK, SLIDE_LEFT, SLIDE_RIGHT, 
								SABER_RIGHT, SABER_LEFT, CHARGE_TEXTURE, MAX_CHARGE, CHARGE_LEFT, CHARGE_RIGHT};
static const enum menu_states {INTRO, INTRO_PRESS, NEWGAME, CONTINUE, OPTION, TRAINING, INGAME};
enum bullet {XBULLET, XBULLETDIE, XCHARGE_RIGHT, XCHARGE_LEFT, Z_BULLET_LEFT, Z_BULLET_RIGHT, Z_SABER_RIGHT, Z_SABER_LEFT};
//movement of camera TODO sync this up with X
const float CM_WALK = 4.0;
const float CM_DASH = 10.0;