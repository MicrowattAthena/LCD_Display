
#include "character_constructor.h"
#include "command_generator.h"
#include "character_arrays.h"
#include <stdio.h>
#include <stdlib.h>	
#include <math.h>
#include <unistd.h> // UNIX standard function definitions

int currentposition =0;
int currentscreen=0;
int led_array[512][16];
int led_byte_array[4][16][16];
char complete_messages[4][512];
int effect_type;
int screen_breakpoints[5];
	int messagelength =0;
char convert_char(char* content, int contentlength, int effect_type_recieved)
{
	
	int i, h,g,f, no_screens;
	int charlength[90], charpos[90];
	int char_index;
	int screen_index =0;
	int currentbreakpoint;
	effect_type = effect_type_recieved;
	printf( "\nDisplaying: %s\n", content );
	printf("Generating Characters: ");
		for (char_index=0; char_index < contentlength; char_index++)
			{
			printf("%c", content[char_index]);
				
				charpos[char_index] = get_array(content[char_index]);
				charlength[char_index] = arrOffset[charpos[char_index]+1] - arrOffset[charpos[char_index]];
				messagelength += charlength[char_index];
				if (messagelength > screen_breakpoints[screen_index -1] + 128)
					{
			//			printf("\nCurrent Message Length: %d\tScreenPoint:%d\n", messagelength, screen_breakpoints[screen_index-1] + 128);
					screen_breakpoints[screen_index] = currentbreakpoint;
				//	printf("New Screen Breakpoint: %d\t%d\n", currentbreakpoint, screen_index);
						
					screen_index++;
				
					}
				if (content[char_index] == ' ' || content[char_index] == '?' || content[char_index] == '!' || content[char_index] == '.')
					{
				//	printf("%c\t", content[char_index]);
				//	printf("%d\t", messagelength);
			//		printf("\n%d > %d?\n", messagelength, screen_breakpoints[screen_index - 1] + 128);
					
					currentbreakpoint = messagelength;
					
				}
					
				charpos[char_index] = arrOffset[charpos[char_index]];
				
			}	
			

		//	printf("Screen Index: %d", screen_index);
			screen_breakpoints[screen_index] = screen_breakpoints[screen_index -1] + 128;
		//	printf("\nEND OF MESSAGE: \n", screen_breakpoints[screen_index] );
			//		screen_breakpoints[screen_index -1] = currentbreakpoint;
			//		screen_breakpoints[screen_index] = currentbreakpoint + 128;
			//		printf("New Screen Breakpoint: %d\t%d\n", currentbreakpoint, screen_index);
					
			
				
				for (i=3; i >= 0; i--)
				{
					if (screen_breakpoints[i] != 0)
					screen_breakpoints[i] -= screen_breakpoints[i -1];
				}
				
				for (i = 0; i < 4; i++)
				{
					printf("\nScreen Breakpoints: %d\t\n", screen_breakpoints[i]);
				}
		for (char_index=0; char_index < contentlength; char_index++)
		{
		generate_screen(charpos[char_index], charlength[char_index]); 
		}
			
	printf("\n");
		messagelength = ((((messagelength -1/) 128) + 1) * 2);
		converttobytearray(); 
		createmessage();
		
	return messagelength;
}

int generate_screen(int charpos, int charlength)
{
	
	int h, bit, input;


	if (effect_type != EFFECT_MOVE_LEFT_FULL && effect_type !=  EFFECT_MOVE_RIGHT_FULL)

		
	//	if (currentposition + charlength >= 128)
	//	printf("%d\t%d\n", currentposition+charlength, screen_breakpoints[currentscreen]);
		 if (currentposition+ charlength > screen_breakpoints[currentscreen])
		{
		//	printf("\nMatch! Breakpoint: %d\n", currentposition+charlength );
			currentscreen++;
		//	printf("\nExtra length; %d\n", (128 - currentposition));
		 	messagelength+= (128 - currentposition);
			currentposition =0;
			
		
			 screen_breakpoints[currentscreen-1] -= (128 - currentposition);
			
		}

	
	for (h=0; h < charlength; h++)
	{
		//printf( "\n");
		input = arrDataBytes[charpos + h];
		//printf("%x", input);
		for (bit = 0; bit < 16; ++bit, input >>= 1)
		{
	//		printf( "%d", (input & 1));
			led_array[ (( currentscreen * 128) + currentposition)][bit] = (input & 1);
		}
		currentposition++;
	}
}

int get_array(char input)
{
	int i;
	
	for (i=0; i < 94; i++)
		{
			if (input == charOffset[i])
			{
				return i;
			}
		}
		
	return 7; // Space Character
};

int converttobytearray()
{
	int screen, column, row, bitrow, value;
	int i;
	int temptest = 0;
	

		for (screen = 0; screen <4; screen++)
		{
			for (column =0; column <128; column = column +8)
			{
				for (row =0; row < 16; row ++)
				{
			        value =0;		
					for (bitrow = 0; bitrow <8; bitrow++)
					{
						value += (1 << bitrow) * (led_array[column + (screen * 128) + (7-bitrow)][15 - row]);		//Work out value of 8 bits  led_array[0][row]
						
					}
					
					
					
					led_byte_array[screen][column / 8][row] = value;
					
				//	if (value !=0)
				//	printf("Next: %d\t", led_byte_array[screen][column / 8][row]);
		
				}
			}
		}
}
int createmessage()
{
	
		int screen, pairofcolumns, column, row, sequencenumber;
		
		int counter;
		for (screen =0; screen < 4; screen++)
		{
			sequencenumber = 0;
			for (column = 0; column < 8; column++)
				{
					for (row = 15; row >= 0; row--)
						for (pairofcolumns = 0; pairofcolumns < 2; pairofcolumns++)
						{	
				
						if (((led_byte_array[screen][column * 2 + pairofcolumns][row]) == 10) ||((led_byte_array[screen][column * 2 + pairofcolumns][row]) == 13));
							complete_messages[screen][sequencenumber] = (led_byte_array[screen][column * 2 + pairofcolumns][row]);
							sequencenumber++;
							complete_messages[screen][sequencenumber] = 0x00;
							sequencenumber++;
							
						}
				}
		}
				
		return 0;
}

int write_main(int usbdev)

{
	int i, screen;
	
		printf("Writing Main Message");
	for (screen = 0; screen < 4; screen ++)
	{
		write(usbdev, &complete_messages[screen][0],256);
		usleep(250000);
		write(usbdev, &complete_messages[screen][256],256);
		usleep(250000);
	}
}
