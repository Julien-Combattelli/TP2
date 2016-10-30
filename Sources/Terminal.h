/*
 * Terminal.h
 *
 *  Created on: 4 oct. 2016
 *      Author: Julien
 */

#ifndef SOURCES_TERMINAL_H_
#define SOURCES_TERMINAL_H_

#include <stdbool.h>
#include <stdint.h>

void Terminal_ReadChar_NonBlocking(char* c);

bool Terminal_KeyPressed();

void Terminal_ReadChar(char* value);

void Terminal_SendChar(char value);

/*
 * Send a character string to Console output.
 * Use it instead of PRINTF if you only want to print string and not number
 */
void Terminal_SendStr(char* str);

void Terminal_Clear();

void Terminal_CRLF();

void Terminal_CursorHome();

void Terminal_SendNum(int number, int base);

/*
 * Read unsigned 32-bits integer from terminal
 * The entered characters are send one by one to terminal
 */
uint32_t Terminal_ReadUInt32();

#endif /* SOURCES_TERMINAL_H_ */
