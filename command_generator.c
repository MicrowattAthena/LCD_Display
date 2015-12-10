
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <time.h>   // time calls
#include "command_generator.h"
#include "command_constructs.h"
#include "character_arrays.h"

char first_header_final[7];
char second_header_final[64];
char first_screen_final[512];
char second_screen_final[512];
char third_screen_final[512];
char fourth_screen_final[512];
char footer_final[2];

int generate_header(char screennumber, char effect_type, char screen_speed, char stay_time, char border_type, int length)
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
	second_header_final[1] = ((((length -1)/ 16) + 1 ) * 2);
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
	printf("Calculated Header CRC: %x	\n", CRC_check);
	return 0;
}

int generate_content(char *content, int length)
{
	int i,j,k,l, no_screens;
	int content_CRC_Check = 0;
	int character_position = 0;
	int printcount =0;
	/* TO DO:
		Recieve Input from User
		Determine Number of Screens needed
		Set number of screens
		Write Data to correct screens
		*/
	printf( "Displaying: %s\n", content );
	no_screens = (((length -1)/ 16) + 1 );
	
	if (no_screens >= 1)
	{
		for (k= 0; k < 8; k++)
		{
			for (j = 0; j < 2; j++)
			{
				for (i=0; i <16; i++)
					{
						first_screen_final[(2 * (i * 2 + j + (k * 32)))] = full[i];
						first_screen_final[(2 * (i * 2 + j + (k * 32))) + 1] = 0x00;
					}
			}
		
		}
	}
	
	if (no_screens >=2)
	
	{
		for (k= 0; k < 8; k++)
		{
			for (j = 0; j < 2; j++)
			{
				for (i=0; i <16; i++)
					{
						second_screen_final[(2 * (i * 2 + j + (k * 32)))] = a_capital[i];
						second_screen_final[(2 * (i * 2 + j + (k * 32))) + 1] = 0x00;
					}
			}
		
		}
		
	}
	
	if (no_screens >=3)
	
	{
		for (k= 0; k < 8; k++)
		{
			for (j = 0; j < 2; j++)
			{
				for (i=0; i <16; i++)
					{
						third_screen_final[(2 * (i * 2 + j + (k * 32)))] = 0x00;
						third_screen_final[(2 * (i * 2 + j + (k * 32))) + 1] = 0x00;
					}
			}
		
		}
		
	}
	
	if (no_screens >=4)
	
	{
		for (k= 0; k < 8; k++)
		{
			for (j = 0; j < 2; j++)
			{
				for (i=0; i <16; i++)
					{
						fourth_screen_final[(2 * (i * 2 + j + (k * 32)))] = 0xFF;
						fourth_screen_final[(2 * (i * 2 + j + (k * 32))) + 1] = 0x00;
					}
			}
		
		}
		
	}
	footer_final[0] = 0x77;
	footer_final[1] = 0x5A;
	
	//CRC Isn't actually used ?
	return 0;
}

int write_content()
{
	int usbdev; /* handle to FTDI device */
	int no_screens, i, length;
		
	system("stty -F /dev/ttyUSB0 115200 cs8 min 1 time 1");
	usbdev = open("/dev/ttyUSB0", O_RDWR);
		
	length = sizeof(first_header_final);
	printf("\nLength of First Header: %d", length);
	write(usbdev, first_header_final,length);
	usleep(250000);
		
	length = sizeof(second_header_final);
	printf("\nLength of Second Header: %d", length);
	write(usbdev, second_header_final, length); 
	usleep(250000);
		
		
	length = 256;
		
	char *firstHalf = malloc(length * sizeof(char));
		if (!firstHalf) 
		{
			/* handle error */
		}
		char *secondHalf = malloc(length * sizeof(char));
		if (!secondHalf)
		{
			/* handle error */
		}	
	
		memcpy(firstHalf, first_screen_final, length * sizeof(char));
		memcpy(secondHalf, first_screen_final, length * sizeof(char));
	
		printf("\nLength of First half of First Screen: %d", length);
		write(usbdev, firstHalf,length);
		usleep(250000);
		
		printf("\nLength of Second Half of First Screen: %d", length);
		write(usbdev, secondHalf,length);
		usleep(250000);
	
	
		memcpy(firstHalf, second_screen_final, length * sizeof(char));
		memcpy(secondHalf, second_screen_final, length * sizeof(char));
	
		printf("\nLength of First half of First Screen: %d", length);
		write(usbdev, firstHalf,length);
		usleep(250000);
		
		printf("\nLength of Second Half of First Screen: %d", length);
		write(usbdev, secondHalf,length);
		usleep(250000);
		
		
		memcpy(firstHalf, third_screen_final, length * sizeof(char));
		memcpy(secondHalf, third_screen_final, length * sizeof(char));
	
		printf("\nLength of First half of First Screen: %d", length);
		write(usbdev, firstHalf,length);
		usleep(250000);
		
		printf("\nLength of Second Half of First Screen: %d", length);
		write(usbdev, secondHalf,length);
		usleep(250000);
		
		
		memcpy(firstHalf, fourth_screen_final, length * sizeof(char));
		memcpy(secondHalf, fourth_screen_final, length * sizeof(char));
	
		printf("\nLength of First half of First Screen: %d", length);
		write(usbdev, firstHalf,length);
		usleep(250000);
		
		printf("\nLength of Second Half of First Screen: %d", length);
		write(usbdev, secondHalf,length);
		usleep(250000);
		
	
	length = sizeof(footer_final);
	printf("\nLength of Footer: %d\n", length);
	write(usbdev, footer_final,length);
	usleep(20000);
		
	close(usbdev); 
	
	return 0;	
}
