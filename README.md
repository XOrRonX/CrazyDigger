# CrazyDigger
A clone of the game "CrazyDigger" 


Prerequisites
In order to run the project you need:
Visual Studio with Windows 10 SDK version 10.0.17763.0
SFML
Installing
Download Visual Studio from here. In installation process choose "Windows 10 SDK (10.0.17763.0)" at the Individual components tab. If you have Visual Studio installed already you can download SDK from "Visual Studio Installer".
Download sfml 2.5.0 from here. just extract it and run "SFMLInstall.bat" as administrator (extraction path must contain english letters only).

1. Crazy Digger 

2. Name :
   Or Ron 
   
  
   
   
3. Prorgam explanation: 

	this program implement the CrazyDigger game 
	In this game there are a few screens defines in files, a player win the game when 
	he is able to complete all the screens eating all the diamonds in each screen of the 
        game without getting killed more than 2 time and w/o taking more time than was defined 
        in the file of the screens (if time is defined in the file, if not defined then the place of the time will be -1).

	The game is runing on time and so the user controlling the digger can decide
	to which direction the digger will go, the user needs to press once with one of the arrow keys 
	for a single move the digger cannot go through a wall however it can eat grass, it can eat
	diamonds and it can get crushed by a diamond falling on it or by a round weihgt falling on him.
	The Digger can also get eaten by a preditor in case it get to it.

4. Design:




Main.cpp takes care of two things:
1. checking if there are more files of screens to read  
2. runs in endless loop each loop is a full game it calls run()
   function Game class which execute the game, when the game is over 
   controller return to main with or restart the game or exit , if it is start the game 
   main will delete and reallocation the game which is class Game
   with all the screens


Objects of the game:

Starting with the basic objects.

There are three inherits in the game
1. Regular - Class StaticObject is the parent and it implement all the functions
	     From Static objects inherit: Wall and Grass. both objects cannot move
	     Grass can be eaten by digger and Wall cannot change in the game
2. Regular - Class ObjectCanFall is the partent and implement the functions.
	     From ObjectCanFall inherit - Weight and Diamond - both objects will fall
	     if they do not have any Wall or Grass below them - Diamond can be eaten by the digger
	     both falling object will kill a digger and a predator if the hit them while falling.
2. Polimorphism  - Class MovingObject is the parent with all its function virtual
		  From MovingObject inherits: CrazyDigger and Predator
	

Class Board is another base object which is taking care of reading one input file 
and storing all its information in data members.
it stores the how the screen looks in matrix of chars and it also stores
the time of the screen and the lines and columns


Class Game - this is not a base class
	The top object it holds array of Class Controller (explained below), 
	each controller is like a screen it holds all the object of the screen 
	and manage the game. The controllers array is created when main call 
	Game to add a screen and this happens as long 
	as main see there are more files with screen available to read.  
	Game also hold a menu screen where the user can decide if to start a game
	or to exit, when one game end the user can decide to start the game from the 
	begining or to exit the game.
	Main calls run() function of Game, run() function starts the menu 
	and based on the user if he chose exit then the game ends and if start 
	then Game call run() of the active Controller and then wait until the 
	controller ends executing the screen and all its moves.
	then Game based on the state decide what to do if game over then open the 
	menue for the user to decide what to do next and if not game over then 
	it means the CarzyDigger found all diamonds in the screen so move to next controller if exist 
	and copy it the points and the life of the previous controller.
	If this was the last controller then the game is won.	

Class Controller is actually a screen 
	the is the main object of the game and it has all the objects of the game
	This class manages all the moves and knows all the rules of the game 
	for one screen It has these main obejcts:
		1. m_board of class Board - hold all the info read on one screen from a file 
		2. m_objectCanFall- vector of objectCanFall of Diamonds and Weights 
		3. m_MovingObjects - vector of all the moving objects - digger and predators
		4. m_staticObjects - vector of Walls and of Grass 
		5. all the graphical objects like Window
	

5. File Format

	Each file is only one screen
	Main() is looking for the following name format "boardX.txt"
	where X is a numebr starting from 1 and next file will be 2 next 3 and so on
	when main() does not find the next file it assumes no more files or screens.

6. List of files:

main.cpp  - holds the game of class Bomberman, in endless loop call the game until
			the user chose in the menu to exit
Macros.h - Holds all the enums and consts for the program
Controller.cpp and Controller.h - holds class Controller described abot 
BaseObject.cpp and BaseObject.h - virtual base class BaseObject
Board.cpp and Board.h - class Board
Game.cpp and Game.h - class Bomberman
CrazyDigger.cpp and .h - class CrazyDigger
Diamond.cpp and .h - class Diamond
Grass.cpp and Grass.h - class Grass
Weight.cpp and Weight.h - Class Weight
Wall.cpp and Wall.h - class Wall
Predator.cpp and Predator.h - class Predator
MovingObject.cpp and MovingObject.h - base class MovingObject
ObjectCanFall.cpp and ObjectCanFall.h - base class of ObjectCanFall
StaticObject.cpp and StaticOpject.h - base class of StaticObject 



There are 10 ready screens :

board1.txt...board10.txt

List of graphical used files sound and pictures


7. Main data structures:
		1. m_board of class Board - hold all the info read on one screen from a file 
		2. m_objectCanFall- vector of objectCanFall of Diamonds and Weights 
		3. m_MovingObjects - vector of all the moving objects - digger and predators
		4. m_staticObjects - vector of Walls and of Grass 
		5. all the graphical objects like Window

		Class Game which holds Vector of controller one for every screen


8. Algorithms:
			Falloing Object:

			The algorithm to decide how to drop all the falling objects 
			 

9. known bugs - no known bugs

10. comment -




