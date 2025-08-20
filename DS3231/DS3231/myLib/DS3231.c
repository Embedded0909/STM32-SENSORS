#include "DS3231.h"

//I2C Handle
extern I2C_HandleTypeDef hi2c2;

//convert Dec to BCD
uint8_t Decimal2BCD(uint8_t num)
{ 
  return (num/10)<<4|(num%10);
}

//convert BCD to Dec
uint8_t BCD2Decimal(uint8_t num) {
 return (num>>4)*10+(num&0x0F);
}

void RTC_Init(Datetime *dt){
	dt->hour = 0;
	dt->min = 0;
	dt->second = 0;
}
void RTC_Write(Datetime *dt){
	uint8_t buff[4];
	buff[0] = 0x00;
	buff[1] = Decimal2BCD(dt->second);
	buff[2] = Decimal2BCD(dt->min);
	buff[3] = Decimal2BCD(dt->hour);
	HAL_I2C_Master_Transmit(&hi2c2, RTC_ADDR, buff, 4, 100);
	
}


void RTC_Read(Datetime *dt){
	uint8_t buff[3];
	uint8_t addr_reg = 0x00;
	HAL_I2C_Master_Transmit(&hi2c2, RTC_ADDR,&addr_reg,1, 100);
	HAL_I2C_Master_Receive(&hi2c2,RTC_ADDR, buff, 3, 100);
	dt->second = BCD2Decimal(buff[0]);
	dt->min = BCD2Decimal(buff[1]);
	dt->hour = BCD2Decimal(buff[2]);
}
