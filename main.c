/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include "message_generator.h"

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
		int length;
		int messagelength;
		length=strlen(argv[1]);
		
		//Might remove the character limit as the value is abritrary: the font is not monospaced
		if (length > 90) 
		{
		printf("\nCharacter Limit is 90, you have used %d\n", length);
		return 2;
		}

		 /* switch (testvalue)
	 
		{
				case 'D':
				effect_type=EFFECT_NONE;
				printf("Case D");
				break;
				case 1:
				effect_type=EFFECT_MOVE_LEFT_FULL;
						printf("Case 1");
				break;
				default:
				effect_type=EFFECT_NONE;
						printf("Case Default");
				break;
		} 
		*/
		
		// We generate the body before the header as the header needs to specify the message length
		
		messagelength = generate_body(argv[1], length, effect_type);
		generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, messagelength);
		
		write_content();
		printf(" \nComplete!\n");
		return 0;
		} 
};

