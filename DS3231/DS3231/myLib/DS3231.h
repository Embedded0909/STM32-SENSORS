#ifndef __RTC_H
#define __RTC_H
#include <stdint.h>
#include "stm32f1xx_hal.h"
#define RTC_ADDR 		(0x68 << 1)

typedef struct {
	uint8_t second;
	uint8_t min;
	uint8_t hour;
}Datetime;

void RTC_Init(Datetime *dt);
void RTC_Write(Datetime *dt);
void RTC_Read(Datetime *dt);

#endif


