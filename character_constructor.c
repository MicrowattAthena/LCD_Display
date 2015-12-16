
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
char convert_char(char* content, int contentlength, int effect_type_recieved)
{
	int messagelength =0;
	int i, h,g,f, no_screens;
	int charlength, charpos;
	
	effect_type = effect_type_recieved;
	printf( "\nDisplaying: %s\n", content );
	printf("Generating Characters: ");
		for (h=0; h < contentlength; h++)
			{
				printf("%c", content[h]);
				charpos = get_array(content[h]);
				charlength = arrOffset[charpos+1] - arrOffset[charpos];
				messagelength += charlength;
				charpos = arrOffset[charpos];
				generate_screen(charpos, charlength); 
			}	
	printf("\n");
		messagelength = (messagelength / 64) + 1;
		converttobytearray(); 
		createmessage();
		
	return messagelength;
}

int generate_screen(int charpos, int charlength)
{
	
	int h, i, bit, input;

	if (effect_type != EFFECT_MOVE_LEFT_FULL && effect_type !=  EFFECT_MOVE_RIGHT_FULL)
	{
		
		if (currentposition + charlength >= 128)
		{
			currentscreen++;
			currentposition =0;
		}
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
	/*	FILE *debug = fopen("output.txt", "w");
	fprintf(debug, "\nScreen%d\n", 0);
	
for (i=0; i <512; i++)
		{
			if (complete_messages[0][i] == 10)
			fprintf(debug, "%d = %d\t", i, complete_messages[0][i]);
		}
		* 
		* */
		printf("Writing Main Message");
	for (screen = 0; screen < 4; screen ++)
	{

		write(usbdev, &complete_messages[screen][0],256);
		usleep(250000);
		write(usbdev, &complete_messages[screen][256],256);
		usleep(250000);
	}
	//fclose(debug);
}
