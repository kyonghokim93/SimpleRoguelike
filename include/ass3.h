/*****************************ass3.h****************************/

/***************************************************************
Student Name: Kyong Ho Kim

This program is a simple single level rogue-like game.
The file name that is same with the second argument from terminal is opened and read.
This program then parses the input file information, determines shape and elements in the room.
Then, ncurses is used to draw the room on the terminal screen.
The user is then able to move around the rooms and pick up loots.
When the user presses q to quit, the ncurse is turned off, and inventory information of the hero is printed.
***************************************************************/

#ifndef _KKIM02_ASS3H
#define _KKIM02_ASS3H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define QUIT 'q'
#define THROW 'k'

typedef struct _element
{
    char symbol;
    int xPos;
    int yPos;
} element;

typedef struct _hero
{
    int gold;
    int magic;
    int potion;
    int weapon;
	int heroX;
	int heroY;
	int roomNum;
    int wasStairs;
    int wasDoor;
} hero;

typedef struct _roomInfo
{
    char * * oneElement;
    element * elementInfo;
    int length;
    int width;
    int elementNum;
    int heroInitX;
    int heroInitY;
} roomInfo;


/******************************************************************
openfile: Takes in the second argument on terminal as string. Then opens and reads the file of that string name.
Pre: The second argument on terminal
Post: Returns a file pointer
******************************************************************/
FILE * openFile(char * filename);


/******************************************************************
elementCount: In a single input line, elements are separated by a space (or spaces).
              This function reads a single input line, figures out how many elements there are by accessing 
              the line two characters at a time.
Pre: Takes in a single line in the file that was read previously
Post: Returns a number that tells you how many elements are there in that single line
******************************************************************/
int elementCount(char * buffer);


/******************************************************************
parseFunction: This function parses a single input line into usable elements.
               Also, It allocates memory to all the components of one room, and stores room information using parsed elements.
Pre: Takes in a single line in the file that was read previously
Post: Returns a roomInfo pointer to main, making the stored information accessible.
******************************************************************/
roomInfo * parseFunction(char * buffer, int elementNumber);


/******************************************************************
verifyDimension: This function takes in 1 element, specifically the information about room dimension.
           The element is further parsed to usable bits, and stored in memory.
Pre: Takes in 1 element, and a room pointer where the information can be stored
Post: None
******************************************************************/
void verifyDimension(char * verify, roomInfo * room);


/******************************************************************
verifyFunction: This function takes in 1 element, which isn't information about room dimension.
                Instead, It's either about door position, gold position, hero position, weapon position, monster position, and more.
                The element is further parsed to usable bits, and stored in memory.
Pre: Takes in 1 element, and a element pointer where the information can be stored. This function also takes in 
     length and width of room, so it can verify where in the room the element will be placed.
Post: None
******************************************************************/
void verifyFunction(char * verify, element * elementPtr, int length, int width);


/******************************************************************
adjustItem: This function takes in an element pointer, and adjusted the information on it, if needed.
            For example, if the door position is de10, but room dimnesion is only 7 by 7, then de10 is changed to de6. So that door can be accessed by the hero.
Pre: Takes in a element pointer, which is then possibly adjusted using room length and width, and temp x and y from parseFunction
Post: None
******************************************************************/
void adjustItem (int width, int length, int xtemp, int ytemp, element * elementPtr);


/******************************************************************
initNcurse: Initiates all components of ncurse that are necessary for this program.
Pre: None
Post: None
******************************************************************/
void initNcurse(void);


/******************************************************************
drawScreen: Draws the whole gamescreen. This includes all 6 rooms, and all of their elements.
Pre: roomInfo pointer, and number is taken in to draw the gameboard.
Post: None
******************************************************************/
void drawScreen(roomInfo * lines, int lineNum);


/******************************************************************
rpgMove: Moves the hero around in the room. Updates status of hero depending on where in the screen he is.
Pre: character input from the user is taken in for moving the hero.
     roomInfo is taken in to access the allocated information in it.
     heroStatus is taken in to keep track of inventory.
Post: None
******************************************************************/
void rpgMove(char direction, roomInfo * * rooms, hero * heroStatus);


/******************************************************************
initBoard: Evaluates the next character on the gameBoard that the user is trying to access
Pre: hero pointer, row number, and colume number
Post: int is returned to evaluate the next floor information.
******************************************************************/
int evaluate(int row, int col, hero * heroStatus);

#endif
