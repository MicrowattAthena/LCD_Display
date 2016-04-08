
#include "body_generator.h"
#include "message_generator.h"
#include "character_arrays.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h> // UNIX standard function definitions

int currentposition = 0;
int currentscreen= 0;
int led_array[512][16];
int led_byte_array[4][16][16];
char complete_messages[4][512];
int effect_type;
int screen_breakpoints[5];
int messagelength = 0;
int char_index;
int screen_index = 0;
int charlength[90], charpos[90];

int prepare_body(char* content, int contentlength, int effect_type_recieved)
{
	effect_type = effect_type_recieved;
	convert_char(content, contentlength);

	//For Each Character In Message
	for (char_index=0; char_index < contentlength; char_index++)
	{
		generate_screen(charpos[char_index], charlength[char_index]);
	}

	converttobytearray();

	//Converts Message Length from Bit Length to Number Of Messages to Be Sent (No. Screens * 2)
	messagelength = ((((messagelength -1)/ 128) + 1) * 2);
	createmessage();

return messagelength;
}
char convert_char(char* content, int contentlength)
{
	//Gets ASCII Chars from Message and maps out the values from character array, and sets screen breakpoints

	int i;
	int currentbreakpoint;


	printf( "\nDisplaying: %s\n", content );
	printf("Generating Characters: ");

		//For Each Character in Message:
		for (char_index=0; char_index < contentlength; char_index++)
			{
				printf("%c", content[char_index]);
				//Find the ASCII Character in Character Array
				charpos[char_index] = get_array(content[char_index]);

				//Get Character length from the Offset Values in Array
				charlength[char_index] = arrOffset[charpos[char_index]+1] - arrOffset[charpos[char_index]];
				messagelength += charlength[char_index];

				//If Message Would Overflow the screen, go to the next screen
				if (messagelength > screen_breakpoints[screen_index -1] + 128)
				{
					screen_breakpoints[screen_index] = currentbreakpoint;
					screen_index++;
				}
				//If Character is an allowed character to end on (e.g. punctuation or space, set screen breakpoint to char position)
				if (content[char_index] == ' ' || content[char_index] == '?' || content[char_index] == '!' || content[char_index] == '.')
				{
					currentbreakpoint = messagelength;
				}

				charpos[char_index] = arrOffset[charpos[char_index]];

			}

			//Finally, add a final screen breakpoint to the end of messagee

		screen_breakpoints[screen_index] = screen_breakpoints[screen_index -1] + 128;

		for (i=3; i >= 0; i--)
		{
			if (screen_breakpoints[i] != 0)
			screen_breakpoints[i] -= screen_breakpoints[i -1];
		}

		for (i = 0; i < 4; i++)
		{
			printf("\nScreen Breakpoints: %d\t\n", screen_breakpoints[i]);
		}


	return 0;
}

int generate_screen(int charpos, int charlength)
{

	int h, bit, input;

	// If the screen is not of these types, the character at the end of a screen must be end of word or end of sentence.
	if (effect_type != EFFECT_MOVE_LEFT_FULL && effect_type !=  EFFECT_MOVE_RIGHT_FULL)

		//If the character exceeds the breakpoints, start a new screen and reset values
		 if (currentposition+ charlength > screen_breakpoints[currentscreen])
		{
			currentscreen++;
		 	messagelength+= (128 - currentposition);
			currentposition =0;
			screen_breakpoints[currentscreen-1] -= (128 - currentposition);
		}

	//For each row of the character
	for (h=0; h < charlength; h++)
	{
		//Get the bit array of the row
		input = arrDataBytes[charpos + h];

		//Using Bitmagic, append bit value to correct position in array
		for (bit = 0; bit < 16; ++bit, input >>= 1)
		{
			led_array[ (( currentscreen * 128) + currentposition)][bit] = (input & 1);
		}

		currentposition++;
	}
}

int get_array(char input)
{
	//Fetches The Character Position in Array from Char Array
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
	/*This mess transfers the LED MultiDimensional Array we have now into the messages sent to the screen.
	//The screen does not display the leds in a sensible order, but instead displays the first 16 values (as two bytes) of the top row,
	// the first 16 values of the second row, etc., then to the second values of the top row etc etc.
	* It also expects an 0x00 between each value.
		*/
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
	//Writes the Message to the USB

		printf("Writing Main Message");
	for (screen = 0; screen < 4; screen ++)
	{
		write(usbdev, &complete_messages[screen][0],256);
		usleep(250000);
		write(usbdev, &complete_messages[screen][256],256);
		usleep(250000);
	}
}
