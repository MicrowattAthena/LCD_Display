
#include "character_constructor.h"
#include "character_arrays.h"
#include <stdio.h>

char convert_char(char input, int position)
{
	
	switch (input) {
		
		case 'A' :
			return a_capital[position];
		case 'F' :
			return f_capital[position];
		default :
			return empty[position];
	}
	return empty[position];
}
