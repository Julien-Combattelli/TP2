/*
 * DS18B20Driver.c
 *
 *  Created on: 26 oct. 2016
 *      Author: Julien
 */

#include "DS18B20Driver.h"
#include "1Wire/onewire.h"
#include "Console.h"

#define DS18B20_CMD_READ_ROM  			0x33
#define DS18B20_CMD_MATCH_ROM 			0x55
#define DS18B20_CMD_SEARCH_ROM 			0xF0
#define DS18B20_CMD_ALARM_SEARCH 		0xEC
#define DS18B20_CMD_SKIP_ROM 			0xCC
#define DS18B20_CMD_CONVERT_T 			0x44
#define DS18B20_CMD_READ_SCRATCHPAD 	0xBE
#define DS18B20_CMD_WRITE_SCRATCHPAD 	0x4E
#define DS18B20_CMD_COPY_SCRATCHPAD 	0x48
#define DS18B20_CMD_RECALL_E2 			0xB8
#define DS18B20_CMD_READ_POWER_SUPPLY 	0xB4

#define DS18B20_SCRATCHPAD_SIZE			(9U)

#define DS18B20_DECIMAL_COUNT			(4U)
#define DS18B20_DECIMAL_MASK			((DS18B20_DECIMAL_COUNT << 1U) - 1U)
#define DS18B20_UNIT_VALUE				(DS18B20_DECIMAL_COUNT << 1U)

float DS18B20_readTemperature()
{
	DS18B20_scratchpad_t scratchpad;

	if(OneWire_Reset() == 1)
		PRINTF("fail\n\r");
	OneWire_Write(DS18B20_CMD_SKIP_ROM);
	OneWire_Write(DS18B20_CMD_CONVERT_T);

	uint32_t freq = CLOCK_SYS_GetCoreClockFreq();
	for(int i = 0 ; i < freq ; i += 50)
	{
		__asm("NOP");
	}

	DS18B20_readScratchpad(&scratchpad);

	return 	(scratchpad.Temperature >> DS18B20_DECIMAL_COUNT) +
			(scratchpad.Temperature & DS18B20_DECIMAL_MASK)   / (float)DS18B20_UNIT_VALUE;
}

void DS18B20_readScratchpad(DS18B20_scratchpad_t* scratchpad)
{
	uint8_t tempLSB, tempMSB;

	if(OneWire_Reset() == 1)
		PRINTF("fail\n\r");
	OneWire_Write(DS18B20_CMD_SKIP_ROM);
	OneWire_Write(DS18B20_CMD_READ_SCRATCHPAD);

	OneWire_Read(&tempLSB);
	OneWire_Read(&tempMSB);
	OneWire_Read(&scratchpad->Th_register);
	OneWire_Read(&scratchpad->Tl_register);
	OneWire_Read(&scratchpad->Config_register);
	OneWire_Read(&scratchpad->Reserved1);
	OneWire_Read(&scratchpad->Reserved2);
	OneWire_Read(&scratchpad->Reserved3);
	OneWire_Read(&scratchpad->CRC);

	scratchpad->Temperature = (tempMSB << 8) | tempLSB;
}
