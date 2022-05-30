/*************************ass3.c****************************
Student Name: Kyong Ho Kim

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include "ass3.h"

FILE * openFile(char * filename)
{
    FILE * infile = fopen(filename,"r");
    if (infile == NULL)
    {
        printf("Error opening file named \"%s\"\nEither you forgot to write \".txt\" at end or file is corrupted.\n", filename);
        exit(1);
    }
    return infile;
}

int elementCount(char * buffer)
{
    int elementNumber = 1;
    int stringLength = strlen(buffer);
    int i;
    
    for (i=0;i<stringLength;i++)
    {
        if ((buffer[i] == ' ' && buffer[i+1] != ' ' ) && (buffer[i] == ' ' && buffer[i+1] != '\n') && (buffer[i] == ' ' && buffer[i+1] != '\0'))
        elementNumber++;
    }
    return elementNumber;
}

roomInfo * parseFunction(char * buffer, int elementNumber)
{
    char * token;
    roomInfo * room;
    int i;

    room = malloc(sizeof(roomInfo)); // malloc 1 room
    room->oneElement = malloc(sizeof(char *)*elementNumber); // malloc strings
    room->elementInfo = malloc(sizeof(element)*elementNumber); // malloc elements
    token = strtok(buffer," ");
    room->oneElement[0] = malloc(sizeof(char)*(strlen(token)+1)); // malloc a string
    strcpy(room->oneElement[0],token);
    
    for (i=1;i<elementNumber;i++)
    {
        token = strtok(NULL," ");
        room->oneElement[i] = malloc(sizeof(char)*(strlen(token)+1)); // malloc a string
        strcpy(room->oneElement[i],token);
    }
    room->elementNum = elementNumber;
    
    verifyDimension(room->oneElement[0], room);

    for (i=1;i<elementNumber;i++)
    {
        verifyFunction(room->oneElement[i], &(room->elementInfo[i]), room->length, room->width);
    }

    for (i=0;i< elementNumber; i++)
    {
        if (room->elementInfo[i].symbol == '@')
        {
            room->heroInitX = room->elementInfo[i].xPos; // find initial hero x position
            room->heroInitY = room->elementInfo[i].yPos; // find initial hero y position
        }
    }
    return room;
}

void verifyDimension(char * verify, roomInfo * room)
{
    int xtemp;
    int ytemp;

    sscanf(verify, "%dX%d",&xtemp,&ytemp);

    if (xtemp > 20 || ytemp > 25)
    {
        printf("One of the 6 rooms is too big. A room needs to be 20X25 or smaller\n");
        exit(0); // for error in room size
    }

    room->length = xtemp + 2;
    room->width = ytemp + 2;
}

void verifyFunction(char * verify, element * elementPtr, int length, int width)
{
    int xtemp;
    int ytemp;
    int difference;

    switch(verify[0])
    {
        case 'd' :
          elementPtr->symbol = '+';
          switch(verify[1])
          {
              case 'e' :
                sscanf(verify,"de%d",&xtemp);
                elementPtr->xPos = xtemp;
                if (xtemp > length-2)
                {
                    difference = xtemp - (length-2);
                    elementPtr->xPos = xtemp - difference;
                }       
                elementPtr->yPos = width - 1;
                break;
              case 'w' :
                sscanf(verify,"dw%d",&xtemp);
                elementPtr->xPos = xtemp;
                if (xtemp > length-2)
                {
                    difference = xtemp - (length-2);
                    elementPtr->xPos = xtemp - difference;
                }                    
                elementPtr->yPos = 0 ;
                break;
              case 's' :
                sscanf(verify,"ds%d",&ytemp);
                elementPtr->yPos = ytemp;
                if (ytemp > width-2)
                {
                    difference = ytemp - (width-2);
                    elementPtr->yPos = ytemp - difference;
                }                
                elementPtr->xPos = length - 1;
                break;
              case 'n' :
                sscanf(verify,"dn%d",&ytemp);
                elementPtr->yPos = ytemp;
                if (ytemp > width-2)
                {
                    difference = ytemp - (width-2);
                    elementPtr->yPos = ytemp - difference;
                }
                elementPtr->xPos = 0;
                break;
              default :
                printf("invalid file information: wrong door type\n");
                exit(0); // for error in door type
	      }    
          break;
        case 'h' : //hero
          elementPtr->symbol = '@'; 
          sscanf(verify,"h%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 'g' : //gold
          elementPtr->symbol = '*';
          sscanf(verify,"g%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 'M' : //monster
          elementPtr->symbol = 'M';
          sscanf(verify,"M%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 'p' : //potion
          elementPtr->symbol = '!';
          sscanf(verify,"p%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 'm' : //magic
          elementPtr->symbol = '$';
          sscanf(verify,"m%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 's' :  //stairs
          elementPtr->symbol = '%';
          sscanf(verify,"s%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        case 'w' : //weapon
          elementPtr->symbol = ')';
          sscanf(verify,"w%d,%d",&xtemp,&ytemp);
          elementPtr->xPos = xtemp;
          elementPtr->yPos = ytemp;
          adjustItem(width, length, xtemp, ytemp, elementPtr);
          break;
        default :
          printf("invalid file information: wrong element type\n");
          exit(0); // for error in element type
          
    }

}

void adjustItem (int width, int length, int xtemp, int ytemp, element * elementPtr)
{
    int difference;

    if (ytemp > width-2)
    {
        difference = ytemp - (width-2);
        elementPtr->yPos = ytemp - difference; // adjusting element y location in case of errorous information on file
    }
    if (xtemp > length-2)
    {
        difference = xtemp - (length-2);
        elementPtr->xPos = xtemp - difference; // adjusting element x location in case of errorous information on file
    }   
}

void initNcurse (void)
{
    initscr();
    cbreak();
    start_color();
    noecho();

    init_pair(1,1,0); // red
    init_pair(2,2,0); // green
    init_pair(3,3,0); // orange
    init_pair(4,4,0); // blue
    init_pair(5,5,0); // purple
    init_pair(6,6,0); // skyblue
    init_pair(7,7,0); // black

    mvprintw(54,0,"Use WSAD to move. Press Q to quit. Have fun!");
    mvprintw(59,0,"Level: 256   Class: Warrior    UserName: xX360_n0ObsT0mPXx");
    mvprintw(60,0,"Gold:  0  Weapon:  0  Potion:  0  Magic:  0  Room #1");
}

void drawScreen (roomInfo * lines, int lineNum)
{
	int i;
	int j;
	int tempx;
	int tempy;
    int roomLocationx = 0;
    int roomLocationy = 0;
    int colorNum;
    
    switch(lineNum)
    {
    case 0 :
        colorNum = 1;
        break;
    case 1 :
        roomLocationy = roomLocationy + 30;    
        colorNum = 2;
        break;
        
    case 2 :
        roomLocationy = roomLocationy + 60;    
        colorNum = 3;
        break;
        
    case 3 :
        roomLocationx = roomLocationx + 25;
        colorNum = 4;
        break;
        
    case 4 :
        roomLocationx = roomLocationx + 25;
        roomLocationy = roomLocationy + 30;    
        colorNum = 5;
        break;
        
    case 5 :
        roomLocationx = roomLocationx + 25;
        roomLocationy = roomLocationy + 60;    
        colorNum = 6;
        break;
        
    default : 
        mvprintw(55,0,"Error in line number");
    }
    
    tempx = lines->length + roomLocationx;
    tempy = lines->width + roomLocationy;
	
	attron(COLOR_PAIR(7));
	    
    for (i = roomLocationy; i < tempy; i++)
    {
        for (j = roomLocationx; j < tempx; j++)
        {
            mvaddch(j,i,'.'); // for floor
        }
    }
	attron(COLOR_PAIR(colorNum)); // coloring 6 rooms differently
		
    for (i = roomLocationy; i < tempy; i++)
    {
        mvaddch(roomLocationx, i, '-');
    }
    for(i = roomLocationx + 1; i < tempx-1; i++)
    {
        mvaddch(i, roomLocationy, '|');
        mvaddch(i, tempy-1, '|');
    }
    for (i=roomLocationy; i < tempy; i++)
    {
        mvaddch(tempx-1, i, '-');
    }
    
    attron(COLOR_PAIR(7));
    
    for (j=1; j < lines->elementNum ; j++)
    {
        mvaddch(lines->elementInfo[j].xPos + roomLocationx, lines->elementInfo[j].yPos + roomLocationy, lines->elementInfo[j].symbol);
    }
}

void rpgMove (char direction, roomInfo * * rooms, hero * heroStatus)
{
    int row;
    int col;
    int tempX;
    int tempY;
    int check;
	int i;
	int j;

    char tempChar;

    getyx(stdscr,row,col);
    
    heroStatus->heroX = row;
    heroStatus->heroY = col;
    
    if (heroStatus->roomNum == 1)
    {
		tempX = rooms[0]->length;
		tempY = rooms[0]->width; 
	} else if (heroStatus->roomNum == 2)
	{
		tempX = rooms[1]->length;
		tempY = rooms[1]->width; 
	} else if (heroStatus->roomNum == 3)
	{
		tempX = rooms[2]->length;
		tempY = rooms[2]->width; 
	} else if (heroStatus->roomNum == 4)
	{
		tempX = rooms[3]->length;
		tempY = rooms[3]->width; 
	} else if (heroStatus->roomNum == 5)
	{
		tempX = rooms[4]->length;
		tempY = rooms[4]->width;
	} else if (heroStatus->roomNum == 6)
	{
		tempX = rooms[5]->length;
		tempY = rooms[5]->width;
	}
    
    
    switch (direction)
    {
    case UP:
		check = evaluate(row-1,col, heroStatus);
		if (check == 1 || check == 2 || check == 3)
		{
			mvaddch(row, col, '.');
            if (heroStatus->wasStairs == 1)
            {
                mvaddch(row,col,'%');        
                heroStatus->wasStairs = 0;
            } 
			if (heroStatus->wasDoor == 1)
			{
				mvaddch(row,col,'+');
				heroStatus->wasDoor = 0;
			}
			row = row - 1;
        } else if (check == 0) 
        {
            row = row;
        }
        break;

    case DOWN:
        check = evaluate(row+1,col, heroStatus);
		if (check == 1 || check == 2 || check == 3)
		{
			mvaddch(row, col, '.');
            if (heroStatus->wasStairs == 1)
            {
                mvaddch(row,col,'%');        
                heroStatus->wasStairs = 0;
            } 
			if (heroStatus->wasDoor == 1)
			{
				mvaddch(row,col,'+');
				heroStatus->wasDoor = 0;
			}
			row = row + 1;
        } else if (check == 0)
        {
            row = row;
        }
        break;

    case RIGHT:
        check = evaluate(row,col+1, heroStatus);
		if (check == 1 || check == 2 || check == 3)
		{
			mvaddch(row, col, '.');
            if (heroStatus->wasStairs == 1)
            {
                mvaddch(row,col,'%');        
                heroStatus->wasStairs = 0;
            }
			if (heroStatus->wasDoor == 1)
			{
				mvaddch(row,col,'+');
				heroStatus->wasDoor = 0;
			} 
			col = col + 1;
        } else if (check == 0)
        {
            col = col;
        }
        break;

    case LEFT:
        check = evaluate(row,col-1, heroStatus);
		if (check == 1 || check == 2 || check == 3)
		{
			mvaddch(row, col, '.');
            if (heroStatus->wasStairs == 1)
            {
                mvaddch(row,col,'%');        
                heroStatus->wasStairs = 0;
            }
			if (heroStatus->wasDoor == 1)
			{
				mvaddch(row,col,'+');
				heroStatus->wasDoor = 0;
			} 
			col = col -1;
        } else if (check == 0)
        {
            col = col;
        }

        break;
	
	case THROW:
	    if (heroStatus->gold >= 1)
	    {
			mvprintw(56,0,"You threw away a gold coin. Feeling rich huh? ");
			heroStatus->gold--;
		} else if (heroStatus->gold == 0)
		{
			mvprintw(56,0,"No money to throw away");
		}
		break;
	
    default:
        mvprintw(56,0,"Use only WSAD, Q to quit or K for fun");
        mvprintw(56,0,"Use only WSAD, Q to quit or K for fun");
    }

    
    mvaddch(row,col,'@');


    if (check == 2)
    {
		heroStatus->wasDoor = 1;
		mvaddch(row,col,'+');
		
        if (heroStatus->roomNum == 1)
        {
			for (i=0;i < rooms[1]->length+1; i++)
			{
				for (j=0; j< rooms[1]->width+1; j++)
				{
					tempChar = mvinch(i,j+30);
					if (tempChar == '+')
					{
						row = i;
						col = j+30;
						heroStatus->roomNum = 2;
					}
				}
			}
        } else if (heroStatus->roomNum == 2)
        {
			for (i=0;i < rooms[2]->length+1; i++)
			{
				for (j=0; j< rooms[2]->width+1; j++)
				{
					tempChar = mvinch(i,j+60);
					if (tempChar == '+')
					{
						row = i;
						col = j+60;
						heroStatus->roomNum = 3;
					}
				}
			}
        } else if (heroStatus->roomNum == 3)
        {
			for (i=0;i < rooms[5]->length+1; i++)
			{
				for (j=0; j< rooms[5]->width+1; j++)
				{
					tempChar = mvinch(i+24,j+60);
					if (tempChar == '+')
					{
						row = i+25;
						col = j+60;
						heroStatus->roomNum = 6;
					}
				}
			}
        } else if (heroStatus->roomNum == 4)
        {
			for (i=0;i < rooms[0]->length+1; i++)
			{
				for (j=0; j< rooms[0]->width+1; j++)
				{
					tempChar = mvinch(i,j);
					if (tempChar == '+')
					{
						row = i;
						col = j;
						heroStatus->roomNum = 1;
					}
				}
			}
        } else if (heroStatus->roomNum == 5)
        {
			for (i=0;i < rooms[3]->length+1; i++)
			{
				for (j=0; j< rooms[3]->width+1; j++)
				{
					tempChar = mvinch(i+25,j);
					if (tempChar == '+')
					{
						row = i+25;
						col = j;
						heroStatus->roomNum = 4;
					}
				}
			}

        } else if (heroStatus->roomNum == 6)
        {
			for (i=0;i < rooms[4]->length+1; i++)
			{
				for (j=0; j< rooms[4]->width+1; j++)
				{
					tempChar = mvinch(i+25,j+30);
					if (tempChar == '+')
					{
						row = i+25;
						col = j+30;
						heroStatus->roomNum = 5;
					}
				}
			}
        }
        mvprintw(56,0,"Clipped! Now in room #%d", heroStatus->roomNum);
    }
    	
	if (check == 3)
    {
        heroStatus->wasStairs = 1;
    }	

    mvprintw(59,0,"Level: 256   Class: Warrior    UserName: xX360_n0ObsT0mPXx");
    mvprintw(60,0,"                                                             ");
    mvprintw(60,0,"Gold:  %d  Weapon:  %d  Potion:  %d  Magic:  %d  Room #%d", heroStatus->gold, heroStatus->weapon, heroStatus->potion, heroStatus->magic, heroStatus->roomNum);
    
    move(row,col);
    refresh();
}

int evaluate(int row, int col, hero * heroStatus)
{
    char tempChar;
    int check;
    
    tempChar = mvinch(row,col);
    
    switch (tempChar)
    {
    case '-':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"There is a wall there, and this ain't portal");
        check = 0; // check = 0 is for wall
        break;

    case '|':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"There is a wall there, and this ain't portal");
        check = 0; // check = 0 is for wall
        break;

    case '+':
        mvprintw(56,0,"                                                 ");
        check = 2; // check = 2 is for door
        break;

    case '*':
        mvprintw(56,0,"                                                 ");
        mvprintw(56,0,"Picked up a gold coin! Sorry beatcoin took over");
        heroStatus->gold++;
        check = 1; // check = 1 is for gold
        break;

    case 'M':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"AHK! A spooky scary skeleton blocking my way");
        check = 0; // check = 0 for monster too
        break;

    case '!':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"Picked up a mana potion as a warrior..");
        heroStatus->potion++;
        check = 1; // check = 1 for potion
        break;
        
    case '$':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"Picked up Fira..but not a magician");
		heroStatus->magic++;
        check = 1; // check = 1 for magic
        break;

    case '%':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"There are stairs! oh it's under construction.. ");
        check = 3; // check = 3 for stairs
        break;

    case ')':
        mvprintw(56,0,"                                                 ");
		mvprintw(56,0,"Picked up a deadly cotton candy");
		heroStatus->weapon++;
        check = 1; // check = 1 for weapon
        break;

    case '.':
        mvprintw(56,0,"                                                 ");
        check = 1; // check = 1 for floor
        break;
    
    default:
        mvprintw(56,0,"                                                 ");
        mvprintw(56,0,"You're out of boundary");
        check = 0; // check = 0 for area outside the room
    }
    return check;
}
