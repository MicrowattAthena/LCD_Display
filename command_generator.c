
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <time.h>   // time calls
#include "command_generator.h"
#include "command_constructs.h"

#include "character_constructor.h"

#define MAX_SCREENS 4

char first_header_final[7];
char second_header_final[64];


struct screen_main {
	char screen_contents[512];
};

struct screen_main screen_final[MAX_SCREENS];
 
char footer_final[2];

int generate_header(int screennumber, int effect_type, int screen_speed, int stay_time, int border_type, int length)
{
	int i; 
	int CRC_check = 0;
	
	// Copying Header Construct to Array
	
	for (i=0; i < 6; i++)
	{
		first_header_final[i] = first_header_construct[i];
	}
	
	for (i=0; i <=63; i++)
	{
		second_header_final[i] = second_header_construct[i];
	}
	
	// Taking User Defined Variables and Placing in Array
			
	first_header_final[6] = screennumber;
	
	//16 is character length on screen
	printf("Number of screens: %d\n", length);
	second_header_final[1] = length;
	second_header_final[7] = effect_type;
	second_header_final[9] = screen_speed;
	second_header_final[11] = stay_time;
	second_header_final[13] = border_type;
	
	// Calculating CRC and Placing in Array
	
	for (i=0; i <=61; i++)
	{
		CRC_check += second_header_final[i];
	}
	
	second_header_final[62] = CRC_check;
	return 0;
}

int generate_content(char *content, int length, int effect_type)
{
	int i,j,k,l, no_screens;
	int content_CRC_Check = 0;
	int character_position = 0;
	int printcount =0;
	int messagelength;
	
	messagelength = convert_char(content, length, effect_type);
			

	footer_final[0] = 0x77;
	footer_final[1] = 0x5A;
	
	//CRC Isn't actually used ?
	return messagelength;
}
int write_content()
{
	int usbdev; /* handle to FTDI device */
	system("stty raw -F /dev/ttyUSB0 115200 cs8 min 1 time 1");
	usbdev = open("/dev/ttyUSB0", O_RDWR);
	
	write_header(usbdev);
	write_main(usbdev);
	write_footer(usbdev);
}

int write_footer(int usbdev)
{
	int length;
	length = sizeof(footer_final);
	printf("\nWriting Footer\n");
	write(usbdev, footer_final,length);
	usleep(20000);
		
	close(usbdev); 	
}

int write_header(int usbdev)
{
	
	int no_screens, i, length;
		
	length = sizeof(first_header_final);
	printf("Writing Header\n");
	write(usbdev, first_header_final,length);
	usleep(250000);
		
	length = sizeof(second_header_final);
	
	write(usbdev, second_header_final, length); 
	usleep(250000);
		

	return 0;	
}
