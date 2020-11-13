///*
// * debug.c
// *
// *  Created on: Nov 10, 2020
// *      Author: ludivineo
// */
//
#include <ctype.h>
#include <string.h>
#include "mydebug.h"




void debug_frame_to_upper (char* debug_frame, int size)
{
	for(int i = 1; i<size-1; i++)
	{
		debug_frame[i] = toupper(debug_frame[i]);
	}
}

void  debug_frame_to_lower (char* debug_frame, int size)
{
	for(int i = 1; i<size-1; i++)
	{
		debug_frame[i] = tolower(debug_frame[i]);
	}
}

void  debug_frame_reverse (char* debug_frame, int size)
{
	char var;
	int j = size-2;
	for(int i = 1; i<j; i++)
	{
		var = debug_frame[j];
		debug_frame[j] = debug_frame[i] ;
		debug_frame[i] = var;
		j--;
	}
}

