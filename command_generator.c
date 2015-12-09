
#include <stdio.h>
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <time.h>   // time calls
#include "command_generator.h"
#include "command_constructs.h"

char first_header_final[7];
char second_header_final[64];

char first_content_final[192];
char second_content_final[256];
char third_content_final[68];


int generate_header(char screennumber, char effect_type, char screen_speed, char stay_time, char border_type)
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

int generate_content(int content)
{
	int i;
	int content_CRC_Check = 0;
	
	for (i=0; i < 192; i++)
	{
		if (i%2)
		{
			first_content_final[i]= 0x00;
		}
		else
		{
			first_content_final[i]= content;
			content_CRC_Check+= content;
		}
	}
	
	for (i=0; i <256; i++)
	{
		if (i%2)
		{
			second_content_final[i] = 0x00;
		}
		else
		{
			second_content_final[i]= content;
			content_CRC_Check+= content;
	
		}
	}	
	for (i=0; i<64; i++)
	{
		if (i%2)
		{
			third_content_final[i] = 0x00;
		}
		else
		{
			third_content_final[i] = content;
			content_CRC_Check+= content;
		}
	}
	
	third_content_final[64] = 0x77;
	third_content_final[65] = 0x5A;
	
	//CRC Isn't actually used ?
	printf("Calculated Main CRC: %x	\n", content_CRC_Check + 0xE0);
	return 0;
}

int write_content()
{
		int usbdev; /* handle to FTDI device */
		int length, i;
		
		system("stty -F /dev/ttyUSB0 115200 cs8 min 1 time 1");
	
		usbdev = open("/dev/ttyUSB0", O_RDWR);
		
		length = sizeof(first_header_final);

		printf("\nLength of First Message: %d", length);
	
		write(usbdev, first_header_final,length);

		usleep(250000);

		
		length = sizeof(second_header_final);

		printf("\nLength of Second Message: %d", length);
		
		write(usbdev, second_header_final, length); 

		usleep(250000);
	
		length = sizeof(first_content_final);

		printf("\nLength of Second Message: %d", length);
		
		write(usbdev, first_content_final, length); 

		usleep(250000);
		
		length = sizeof(second_content_final);

		printf("\nLength of Third Message: %d", length);
		
		write(usbdev, second_content_final, length); 

		usleep(250000);

	
		length = sizeof(third_content_final);

		printf("\nLength of Fourth Message: %d", length);
		
		write(usbdev, third_content_final, length); 

		usleep(20000);

		
		close(usbdev); 
return 0;	
}
