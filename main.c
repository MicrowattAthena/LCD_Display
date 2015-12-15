/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h> // standard input / output functionsdd
#include "main.h"
#include <string.h>
#include "command_generator.h"

//DEFAULT VALUES - May need to overwrite these 

char screennumber = SCREEN_TWO;
char effect_type = EFFECT_NONE;
char screen_speed = SPEED_SIX;
char stay_time = STAY_FIVE;
char border_type = BORDER_NONE;

//END OF DEFAULT VALUES
int main ( int argc, char **argv )

{ 
	if ( argc == 1 ) /* argc should be 2 for correct execution */
    {
        
        /* We print argv[0] assuming it is the program name */

        printf( "Usage: %s \"Text to display\"\n", argv[0] );
		return 1;
	
    }else{
		
		printf( "Displaying: %s\n", argv[1] );
		int length;
		length=strlen(argv[1]);
		if (length > 64) 
		{
		printf("Character Limit is 64, you have used %d\n", length);
		return 2;
		}
		generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, length);
		printf( "Generated Header\n");
		generate_content(argv[1], length);
		write_content();

		return 0;
		}
};

