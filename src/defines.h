//  SuperTux
//  Copyright (C) 2000 Bill Kendrick <bill@newbreedsoftware.com>
//  Copyright (C) 2004 Tobias Glaesser <tobi.web@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#if !defined( SUPERTUX_DEFINES_H )

#define SUPERTUX_DEFINES_H
/* Version: */

#ifndef VERSION
#define VERSION "0.1.1"
#endif

/* Frames per second: */

#define FPS (1000 / 25)

enum Direction { LEFT = 0, RIGHT = 1 };

/* Direction (keyboard/joystick) states: */

#define UP 0
#define DOWN 1

/* Dying types: */

/* ---- NO 0 */
enum DyingType {
	DYING_NOT = 0,
	DYING_SQUISHED = 1,
	DYING_FALLING = 2
};

/* Sizes: */

#define SMALL 0
#define BIG 1

/* Speed constraints: */

#define MAX_WALK_XM 2.3
#define MAX_RUN_XM 3.2
#define MAX_YM 20.0
#define MAX_JUMP_TIME 375
#define MAX_LIVES 99

#define WALK_SPEED 1.0
#define RUN_SPEED 1.5
#define JUMP_SPEED 1.2

/* gameplay related defines */

#define START_LIVES 4

#define MAX_BULLETS 2

#define YM_FOR_JUMP 6.0
#define WALK_ACCELERATION_X 0.03
#define RUN_ACCELERATION_X 0.04
#define KILL_BOUNCE_YM 8.0

#define SKID_XM 2.0
#define SKID_TIME 200

/* Size constraints: */

#define OFFSCREEN_DISTANCE 256

#define LEVEL_WIDTH 375

/* Timing constants (in ms): */

#define KICKING_TIME 200

/* Scrolling text speed */

#define SCROLL_SPEED_CREDITS 1.2
#define SCROLL_SPEED_MESSAGE 1.0

/* Debugging */

#ifdef DEBUG

// Print a single message in the console
#define DEBUG_MSG( msg ) { \
	printf("[INFO]  %s \n", msg); \
}

#define DEBUG_MSG2( msg , arg ) { \
	printf( "[INFO] " ); fprintf(stdout, msg , arg ); printf("\n"); \
}

/* Print a loading message like :  "[INFO] Loading image ...    OK"
 * Usage :
 * 	DEBUG_START("Loading image")
 * 	DEBUG_DONE()
 */
#define DEBUG_START(msg,arg) {\
	printf( "[INFO] " ); fprintf( stdout , msg , arg ); printf(" ... "); fflush(stdout); \
}
#define DEBUG_DONE() {\
	printf("   OK\n"); \
}

// Display warning messages
#define DEBUG_WAR( msg ) {\
	printf("[WARN] %s\n", msg); \
}

#define DEBUG_WAR2( msg, arg) {\
	printf("[WARN] "); printf(msg, arg); printf("\n")

// Dipslay error messages
#define DEBUG_ERR( msg ) {\
	fprintf(stderr, "[ERR] %s\n", msg);	\
}
#define DEBUG_ERR2(msg, arg) {\
	fprintf(stderr, "[ERR] "); fprintf(stderr, msg, arg); fprintf(stderr, "\n"); \
}
#define DEBUG_ERR3(msg, arg1, arg2) {\
	fprintf(stderr, "[ERR] "); fprintf(stderr, msg, arg1, arg2); fprintf(stderr, "\n"); \
}

#else
#define DEBUG_MSG( msg ) {}
#define DEBUG_MSG2( msg, arg) {}
#define DEBUG_START( msg, arg) {}
#define DEBUG_DONE() {}
#define DEBUG_WAR( msg ) {}
#define DEBUG_WAR2( msg, arg) {}
#define DEBUG_ERR( msg ) {}
#define DEBUG_ERR2( msg, arg) {}
#define DEBUG_ERR3( msg, arg1, arg2) {}
#endif

#endif

