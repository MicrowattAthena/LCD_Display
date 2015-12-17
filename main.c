/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include "command_generator.h"

//DEFAULT VALUES - May need to overwrite these 

int screennumber = SCREEN_TWO;
int effect_type = EFFECT_NONE;
int screen_speed = SPEED_ONE;
int stay_time = STAY_FOUR;
int border_type = BORDER_NONE;

//END OF DEFAULT VALUES

int main ( int argc, char **argv )

{ 
	if ( argc == 1 ) /* argc should be 2 for correct execution */
    {
        
        /* We print argv[0] assuming it is the program name */

        printf( "Usage: %s \"Text to display\"\n", argv[0] );
		return 1;
	
    }else{
		printf("Number of Arguments: %d\n", argc);
		int length;
		int messagelength;
		length=strlen(argv[1]);
		if (length > 90) 
		{
		printf("\nCharacter Limit is 90, you have used %d\n", length);
		return 2;
		}
   //while(argc--)
     //           printf("%s\n", *argv++);
     //   exit(EXIT_SUCCESS);
		
		int testvalue;
	/*	testvalue = strtol(argv[2], NULL, 10);
			printf("Argument 3: %d\n", testvalue);
		switch (testvalue)
	 
		{
				case 0:
				effect_type=EFFECT_NONE;
				printf("Case 0");
				break;
				case 1:
				effect_type=EFFECT_MOVE_LEFT_FULL;
						printf("Case 1");
				break;
				default:
				effect_type=EFFECT_NONE;
						printf("Case Default");
				break;
		} */ 
		messagelength = generate_content(argv[1], length, effect_type);
		generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, messagelength);
		printf( "Generated Header\n");
		write_content();
		printf(" \nComplete!\n");
		return 0;
		} 
};

