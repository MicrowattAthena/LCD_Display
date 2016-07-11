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

		readconfig();


        // Function removes trailing whitespace after punctuation
                int punctuationfound;
                char *i = argv[1];
/*                char *j = argv[1];
		printf("i char: %s\n", i);
                while(*j != 0)
                {
                        *i = *j++;
//                      printf("Char: %s, punctuation state: %d\n", i, punctuationfound);
                        if( (*i != ' ') || (punctuationfound != 1 ))
                        i++;

                if(*j == '.' || *j == '!' || *j == '?')
                        {
 //                               printf("Punctuation: %s\n", j);
                                punctuationfound = 1;
                        }
                        else if (*j != ' ')
                                punctuationfound = 0;
                }
                *(i+1) = 0;
		printf("I Char: %s\n", i);
*/
		// We generate the body before the header as the header needs to specify the message length

  // Trim leading space

char *end;
while(isspace(*i)) i++;

  // Trim trailing space
  end = i + strlen(i) - 1;
  while(end > i && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;
  printf("Formatted char: \'%s\'\n", i);
		length=strlen(i);
		messagelength = generate_body(i, length, effect_type);
		if (messagelength > 0)
		{
			generate_header(screennumber,effect_type,screen_speed,stay_time,border_type, messagelength);

			write_content();
			add_message_log(i);
			add_last_message(i);
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
