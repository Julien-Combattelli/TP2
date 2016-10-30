/*
 * Terminal.c
 *
 *  Created on: 4 oct. 2016
 *      Author: Julien
 */

#include "Terminal.h"
#include "StringUtility.h"

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

// Add user include here
#include "Console.h"

void Terminal_ReadChar_NonBlocking(char* c)
{
	if(Terminal_KeyPressed())
		Terminal_ReadChar(c);
}

uint32_t Terminal_ReadUInt32(size_t character_buffer_size)
{
	char buf[character_buffer_size];
	memset(buf,0,character_buffer_size);

	for(uint32_t i = 0 ; i < character_buffer_size ; i++)
	{
		char c = 0;
		Terminal_ReadChar(&c);

		if(i == 0 && (c < '0' || c > '9')) // skip trailing non numeric characters
		{
			i--;
			continue;
		}
		else if(i != 0 && (c < '0' || c > '9')) // break if one non numeric character is read
			break;

		buf[i] = c;
		Terminal_SendChar(c);
	}
	Terminal_CRLF();

	return (uint32_t)strtoul(buf, NULL, 0);
}

bool Terminal_KeyPressed()
{
	// TODO : implement
	return true;
}

void Terminal_ReadChar(char* value)
{
	*value = GETCHAR();
}

void Terminal_SendChar(char value)
{
	PUTCHAR(value);
}

/*
 * Send a character string to Console output.
 * Use it instead of PRINTF if you only want to print string and not number
 */
void Terminal_SendStr(char* str)
{
	char* ptr = str;
	while(*ptr)
	{
		PUTCHAR(*ptr);
		ptr++;
	}
}

void Terminal_Clear()
{
	Terminal_SendStr("\x1B[2J");
}

void Terminal_CRLF()
{
	Terminal_SendStr("\n\r");
}

void Terminal_CursorHome()
{
	Terminal_SendStr("\x1B[H");
}

void Terminal_SendNum(int number, int base)
{
	char temp[20];
	Terminal_SendStr(itoa(number, temp, base));
}
