/*************************main.c****************************
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

int main (int argc, char * argv[])
{
    FILE * infile;
    char inputString[6][150];
    int i = 0;
    int j;
    int elementNumber;
    roomInfo * * rooms;
    char input;
    hero * heroInformation;

    if (argc != 2)
    {
        printf("Need correct argument style, such as...\nbin/runMe assets/_______.txt\n");
        exit(1);
    }
    
    infile = openFile(argv[1]);
    
    while (fgets(inputString[i], 150, infile) != NULL)
    {
        i++;
    }
    
    rooms = malloc(sizeof(roomInfo *)* 6);
    
    for (i=0;i<6;i++)
    {
        inputString[i][strlen(inputString[i])-1] = '\0';
        elementNumber = elementCount(inputString[i]);
        rooms[i] = parseFunction(inputString[i], elementNumber);
    }
    
    
    /**************************************************/ //ncurse start
    
    initNcurse();
    
    heroInformation = malloc(sizeof(hero));
    
    for (i=0;i<6;i++)
    {
        drawScreen(rooms[i],i);
        for (j=0; j<rooms[i]->elementNum; j++)
        {
			if (rooms[i]->elementInfo[j].symbol == '@')
			{
                heroInformation->heroX = rooms[i]->heroInitX;
                heroInformation->heroY = rooms[i]->heroInitY;
            }
        }
    }
    
    heroInformation->gold = 0;
    heroInformation->magic = 0;    
    heroInformation->weapon = 0;    
    heroInformation->potion = 0;
    heroInformation->roomNum = 1;
    
    move(heroInformation->heroX,heroInformation->heroY);

    input = getch();
    
    
    while (input != 'q')
    {
		
        rpgMove(input,rooms, heroInformation);
        input = getch();
    }

    endwin();    
    
    /**************************************************/ //ncurse finish
    
    fclose(infile);
	
    printf("\nGame Over. Bye for now :)\n\nInventory\nGold:  %d  Weapon:  %d  Potion:  %d  Magic:  %d\n\n", heroInformation->gold, heroInformation->weapon, heroInformation->potion, heroInformation->magic);
	
	if (heroInformation->gold == 0)
	{
		printf("wow.. you couldn't even collect one gold coin. tsk tsk\n\n");
	}
	
	for (i=0;i<6;i++)
	{
		for (j=0; j < rooms[i]->elementNum; j++)
		{
            free(rooms[i]->oneElement[j]);
        }
		free(rooms[i]->elementInfo);
		free(rooms[i]->oneElement);
        free(rooms[i]);
    }
    free(heroInformation);
	free(rooms);
	
    return 0;
}
