*********************************************************************************************
Name: Kyong Ho Kim
*********************************************************************************************
This program is a simple single level rogue-like game.
The file name that is same with the second argument from terminal is opened and read.
This program then parses the input file information, determines shape and elements in the room.
Then, ncurses is used to draw the room on the terminal screen.
The user is then able to move around the rooms and pick up loots.
When the user presses q to quit, the ncurse is turned off, and inventory information of the hero is printed.
*********************************************************************************************
Compilation   
*********************************************************************************************


Type "make" on terminal while in the A2 folder


*********************************************************************************************
Running the Program
*********************************************************************************************


Type "bin/runMe assets/_____.txt" on terminal while in the A2 folder

The game screen will show up right away.

	Use w to move up.
	Use s to move down.
	Use a to move left.
	Use d to move right.
	Use q to quit
	Use k to throw a coin away.

When q is pressed, ncurse is stopped, and usual terminal screen can be seen.
Inventory information is printed on terminal screen.


*********************************************************************************************
Known Limitations
*********************************************************************************************


- the input text file needs 6 lines of data, and 1 line can't be over 150 characters long.
- You should open up the terminal to fullscreen. If not, the game might be cut off, and behave unexpectedly.
- Stairs don't have any function, just present on the gamescreen. Hero can walk on it though.
- When jumping from one to room to another, there is a set order. You can't go back to the previous room right away. need to cycle through.
- If the input file has same element information (i.e. ...g10,11...g10,11), the previous information is still stored, but the hero doesn't
  pick up 2 gold coins when he steps on 10,11.


*********************************************************************************************
