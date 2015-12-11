
#include "character_constructor.h"
#include "character_arrays.h"
#include <stdio.h>

char convert_char(char input, int position)
{
	int i;
	for (i=0; i < 94; i++)
	{
		if (input == charOffset[i])
		{
			return arrDataBytes[position + arrOffset[i]];
		}
	}
/*	switch (input) {
		
		case 'A' :
			return arrDataBytes[position];
		case 'B' :
			return arrDataBytes[position + 16];
		case 'C' :
			return arrDataBytes[position + 32];
		case 'F' :
			return arrDataBytes[position + 48];
		default :
			return empty[position];
	} */
	return empty[position];
}
