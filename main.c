/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include "message_generator.h"
#include "logging.h"

//DEFAULT VALUES - May need to overwrite these

int screennumber = SCREEN_TWO;
int effect_type = EFFECT_NONE;
int screen_speed = SPEED_THREE;
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
		if (length > 60)
		{
		add_error_log("Character Limit is 60: Your message is too long!\n");
		return 2;
		}
		// We generate the body before the header as the header needs to specify the message length

		messagelength = generate_body(argv[1], length, effect_type);
		generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, messagelength);

		write_content();
		add_message_log(argv[1]);
		return 0;
		}
};

