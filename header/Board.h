
/*
class Board
the class takes care of reading a file of a screen
and storing the screen in matrix of chars and also
all the other information like 
lines/columns and time 
*/


#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "MovingObject.h"
#include "StaticObject.h"
#include "macros.h"
#include "CrazyDigger.h"
#include "ObjectCanFall.h"
#include <vector>
#include <fstream>
#include "Diamond.h"
#include "Weight.h"
#include "Grass.h"
#include "Wall.h"

class Board
{
public:
	Board();
	~Board();

	// get a file as an input and then call the rest of the 
	// functions to read the file and store its data in the 
	// relevant members
	Board(char * fileName);

	// read from the file everything the main function of 
	// the file reading
	void fileToMatrix();

	// skip empty lines in the file
	bool notEmptyLine(char *numString);

	// readd only the matrix of chars from the file 
	void readMatrix();

	// return the char from the matrix in location i,j
	char getChar(unsigned int i, unsigned int j) const;

	// returns the requests info that can be num of lines
	// num of columns, num of bombs
	int boardInfo(int type) const;

	// return the time since it is float it is separate from the rest
	float getTime() const;


private:
	std::ifstream m_file;
	std::vector<std::vector<char>> m_boardMatrix;  //char matrix
	int m_boardInfo[4];	 // lines/columns and bombs
	float m_time; // the time from the file 
	
};

