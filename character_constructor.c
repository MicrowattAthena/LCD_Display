
#include "character_constructor.h"
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

char convert_char(char* content, int contentlength)
{
	
	int i, h,g,f, no_screens;
	int charlength, charpos;
	
	printf( "Displaying: %s\n", content );

		for (h=0; h < contentlength; h++)
			{
				printf( "Generating Character: %c\n", content[h]);
				charpos = get_array(content[h]);
				charlength = arrOffset[charpos+1] - arrOffset[charpos];
				charpos = arrOffset[charpos];
				generate_screen(charpos, charlength); // Works Correctly, character arrays are incorrect
			}	
		
 for (g = 0; g < 512; g++)
		{
		for (i = 0; i < 16; i++)
			{
			//	if (led_array[g][i] != 0)
		//	printf("%d\t%d\t%d\n", led_array[g][i],g,i);
			}
		}
		converttobytearray(); // Broken, pls fix
		createmessage();

	return 0x00;
}

int generate_screen(int charpos, int charlength)
{
	
	int h, i, bit, input;
	
	if (currentposition + charlength >= 128)
	{
		currentscreen++;
		currentposition =0;
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
		//printf("\nStandard Array\t\tLED Array\t\t\n");
		//	printf("\nColumn\t\tRow\t\t\n");
		//printf("\nSequence Number\t\tValue\t\t\n");
		for (screen =0; screen < 4; screen++)
		{
			sequencenumber = 0;
			for (column = 0; column < 8; column++)
				{
					for (row = 15; row >= 0; row--)
						for (pairofcolumns = 0; pairofcolumns < 2; pairofcolumns++)
						{	
					//		printf("\n%d\t\t%d\t\t",column * 2 + pairofcolumns, row);
				//	if (led_byte_array[screen][column * 2 + pairofcolumns][row] != 0)
					//		printf("%d\t",led_byte_array[screen][column * 2 + pairofcolumns][row]);
						if (led_byte_array[screen][column * 2 + pairofcolumns][row] != 0)
							printf("\n%d\t\t%d\t\t%d",led_byte_array[screen][column * 2 + pairofcolumns][row],(column * 2 + pairofcolumns),(row));
							complete_messages[screen][sequencenumber] = led_byte_array[screen][column * 2 + pairofcolumns][row];
							sequencenumber++;
							complete_messages[screen][sequencenumber] = 0x00;
							sequencenumber++;
							
						}
				}
		}
				
		int i;
		printf("\n");
		//for (i=0; i < 512; i++)
	//		printf("%d\t", complete_messages[0][i]);
		printf("Sequence Length: %d\n", sequencenumber);
		return 0;
}

int write_main(int usbdev)

{
	int screen;
	
	for (screen = 0; screen < 4; screen ++)
	{
		printf("\nLength of Main Message: %d", 256);
		write(usbdev, &complete_messages[screen][0],256);
		usleep(250000);
		printf("\nLength of Main Message: %d", 256);
		write(usbdev, &complete_messages[screen][256],256);
		usleep(250000);
	}
}
