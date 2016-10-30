/*
 * DS18B20Driver.h
 *
 *  Created on: 7 oct. 2016
 *      Author: Julien
 */

#ifndef SOURCES_DS18B20DRIVER_H_
#define SOURCES_DS18B20DRIVER_H_

#include <stdint.h>

typedef struct DS18B20_scratchpad_s
{
	uint16_t 	Temperature;
	uint8_t 	Th_register;
	uint8_t 	Tl_register;
	uint8_t 	Config_register;
	uint8_t 	Reserved1;
	uint8_t 	Reserved2;
	uint8_t 	Reserved3;
	uint8_t 	CRC;

} DS18B20_scratchpad_t;

float DS18B20_readTemperature();

void DS18B20_readScratchpad(DS18B20_scratchpad_t* scratchpad);

#endif /* SOURCES_DS18B20DRIVER_H_ */
