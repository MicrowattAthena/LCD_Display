/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include "message_generator.h"
#include "logging.h"
#include <fcntl.h>
#include <errno.h>

//DEFAULT VALUES - May need to overwrite these

int screennumber = SCREEN_TWO;
int effect_type = EFFECT_NONE;
int screen_speed = SPEED_THREE;
int stay_time = STAY_SIX;
int border_type = BORDER_NONE;

// END OF DEFAULT VALUES

const char CONFIG_LOCATION[]="./config/led_display_config";


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

		readconfig();
		// We generate the body before the header as the header needs to specify the message length

		messagelength = generate_body(argv[1], length, effect_type);
		if (messagelength > 0)
		{
			generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, messagelength);

			write_content();
			add_message_log(argv[1]);
			add_last_message(argv[1]);
			return 0;
		}else{
			add_last_message("Error: Last Message Failed to Write");
			return 1;
		}
	}
};


int readconfig()
{
	// Using stat to see if file exists and is readable
	struct stat fileStat;
	if (stat(CONFIG_LOCATION, &fileStat) < 0)
	{
		add_error_log("Config File could not be found: Creating default config!");
		return 1;
	}else{
		add_debug_log("Config File found, loading...");
		return 0;
	}
};


int newconfig()
{


};
