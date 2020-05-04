
/*
macros.h
hold all the various enums and const from the program
*/

//====================================consts================================

#pragma once


// Maximum Digger life
const int MAX_LIFE = 3;
const int MIN_LIFE = 1;

const int MAX_SCREEN_TIME = 60;

// Initialize point it is const in case there is need to 
// start with different number
const int POINTS_INIT = 0;

// maximum number of screen the game support
const int MAX_SCREENS = 20;

// the longest line in Board.txt is 256
const int MAX_LINE_SIZE = 256;

// the biggest screen to play has 80 lines and 80 columns
const int MAX_SCREEN_SIZE = 80;


// graphical const for size of screen and rectangles
const int DEFAULT_SCREEN_SIZE = 800;
const int MAX_REC_SIZE = 50;


const int LINES = 0;
const int COLUMNS = 1;
const int TIME = 2;
const int TOTAL = 3;
const float RECT_SIZE = 40;
const float SCREEN_MIN_X = 50;
const float SCREEN_MIN_Y = 60;
const unsigned int PREDATOR_RAND_FREQUENCY = 1;
const unsigned int PREDATOR_SPEED = 1;
const unsigned int CRAZY_DIGGER_SPEED = 1; 
const unsigned int WEIGHT_SPEED = 3;
const unsigned int BONUS_PREDATOR_KILLED = 5;
const unsigned int BONUS_DIAMOND = 10;
const float POS_PIXEL_MOVE = 20;
const float NEG_PIXEL_MOVE = -20;
const float PREDATOR_POS_PIXEL_MOVE = 5;
const float PREDATOR_NEG_PIXEL_MOVE = -5;
const unsigned int TEXTURE_SIZE = 25;




//==================================enums=================================

// screen can have different states depending on what happened 
enum screenState {
	CRAZY_DIGGER_KILLED_NO_TIME = 1,
	CRAZY_DIGGER_FOUND_LAST_DIAMOND = 2,
	GAME_OVER = 3,
	GAME_WON = 4,
	PREDATOR_KILLED_CRAZY_DIGGER = 5,
	CRAZY_DIGGER_KILLED_BY_GUARD = 6,
	NORMAL = 7,
	EXIT_GAME = 8,
	CRAZY_DIGGER_FOUND_DIAMOND = 9 ,
	CRAZY_DIGGER_FOUND_GRASS = 10,
	CRAZY_DIGGER_FOUND_WEIGHT =11,
	CRAZY_DIGGER_FOUND_WALL = 12
				 };

// these are all the shapes that can be presented
enum shape {
	WALL = '#',
	ERROR = 'E',
	PREDATOR = '!',
	CRAZY_DIGGER = '/',
	SPACE = ' ',
	DIAMOND = 'L',
	GRASS = 'S',
	WEIGHT = 'W'
			};

enum OpenClose { CLOSE = 0, OPEN = 1 };

// all the things a digger can do
enum robotMoves { 
				  UP = 1, 
				  DOWN = 2, 
				  LEFT = 3, 
				  RIGHT = 4, 
				  SKIP = 5,
				  HARDER = 6,
				  EASIER = 7,
				  STAY = 8
				};

enum locationType { 
					CURRENT_LOCATION = 1, 
					NEXT_LOCATION = 2, 
					ORIGINAL_LOCATION = 3 
				  };


enum bottonType {
	
	VSTART = 0, VEND = 1, VBACKROUND = 2, VWALL = 3, VPREDATOR = 4,
	VCLOSE = 5, VDIAMONDD = 6, VGRASS = 7, VWEIGHT = 8, VCRAZYDIGGER = 9,
	VCRAZYDIGGERO = 10, VCRAZYDIGGERU = 11, VCRAZYDIGGERUO = 12,
	VCRAZYDIGGERD = 13, VCRAZYDIGGERDO = 14, VCRAZYDIGGERL = 15,
	VCRAZYDIGGERLO = 16, VPREDATORU = 17, VPREDATORL = 18, VPREDATORD = 19,
	VDIAMONDL = 20, VDIAMONDLR = 21, VDIAMOND = 22, VCRAZYDIGGERC = 23
};
