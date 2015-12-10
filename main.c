/////////////////////////////////////////////////

// Serial port interface program   //

/////////////////////////////////////////////////

#include <stdio.h> // standard input / output functionsdd
#include "main.h"
#include "command_generator.h"

//DEFAULT VALUES - May need to overwrite these 

char screennumber = 0x01;
char effect_type = 0x01;
char screen_speed = 0x02;
char stay_time = 0x03;
char border_type = 0x00;

//END OF DEFAULT VALUES
int main ( int argc, char **argv )

{ 
	char inputtype= 0x00;
	
	generate_header(screennumber,effect_type,screen_speed,stay_time,border_type);
	generate_content(0xff);
	write_content();

	return 0;
};

