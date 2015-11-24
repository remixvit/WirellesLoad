/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
//#include "Math.h"
//#include "bcd.h"

/* Slave address */
#define OPT3001_I2C_ADDRESS             0x45
/*---------------------------------------------------------------------------*/
/* Register addresses */
#define REG_RESULT                      0x00
#define REG_CONFIGURATION               0x01
#define REG_LOW_LIMIT                   0x02
#define REG_HIGH_LIMIT                  0x03

#define REG_MANUFACTURER_ID             0x7E
#define REG_DEVICE_ID                   0x7F
/*---------------------------------------------------------------------------*/
/*
 * Configuration Register Bits and Masks.
 * We use uint16_t to read from / write to registers, meaning that the
 * register's MSB is the variable's LSB.
 */
#define CONFIG_RN      0x00F0 /* [15..12] Range Number */
#define CONFIG_CT      0x0008 /* [11] Conversion Time */
#define CONFIG_M       0x0006 /* [10..9] Mode of Conversion */
#define CONFIG_OVF     0x0001 /* [8] Overflow */
#define CONFIG_CRF     0x8000 /* [7] Conversion Ready Field */
#define CONFIG_FH      0x4000 /* [6] Flag High */
#define CONFIG_FL      0x2000 /* [5] Flag Low */
#define CONFIG_L       0x1000 /* [4] Latch */
#define CONFIG_POL     0x0800 /* [3] Polarity */
#define CONFIG_ME      0x0400 /* [2] Mask Exponent */
#define CONFIG_FC      0x0300 /* [1..0] Fault Count */

/* Possible Values for CT */
#define CONFIG_CT_100      0x0000
#define CONFIG_CT_800      CONFIG_CT

/* Possible Values for M */
#define CONFIG_M_CONTI     0x0004
#define CONFIG_M_SINGLE    0x0002
#define CONFIG_M_SHUTDOWN  0x0000

/* Reset Value for the register 0xC810. All zeros except: */
#define CONFIG_RN_RESET    0x00C0
#define CONFIG_CT_RESET    CONFIG_CT_800
#define CONFIG_L_RESET     0x1000
#define CONFIG_DEFAULTS    (CONFIG_RN_RESET | CONFIG_CT_100 | CONFIG_L_RESET)

/* Enable / Disable */
#define CONFIG_ENABLE_CONTINUOUS  (CONFIG_M_CONTI | CONFIG_DEFAULTS)
#define CONFIG_ENABLE_SINGLE_SHOT (CONFIG_M_SINGLE | CONFIG_DEFAULTS)
#define CONFIG_DISABLE             CONFIG_DEFAULTS
/*---------------------------------------------------------------------------*/
/* Register length */
#define REGISTER_LENGTH                 2
/*---------------------------------------------------------------------------*/
/* Sensor data size */
#define DATA_LENGTH                     2
/*---------------------------------------------------------------------------*/
/*
 * SENSOR_STATE_SLEEPING and SENSOR_STATE_ACTIVE are mutually exclusive.
 * SENSOR_STATE_DATA_READY can be ORd with both of the above. For example the
 * sensor may be sleeping but with a conversion ready to read out.
 */
#define SENSOR_STATE_SLEEPING     0
#define SENSOR_STATE_ACTIVE       1
#define SENSOR_STATE_DATA_READY   2
#define SENSOR_STARTUP_DELAY (CLOCK_SECOND >> 3)

char OPT_Out_String[25];

uint8 OPT_IsReady(void); //Проверка готовности измерений
void OPT_Enable(uint8 enable);// Инициализация датчика
uint8 I2C_ReadRegister(uint8 ADR, uint8 Reg, uint16 *RetValue);// Чтение регистра
uint8 I2C_WriteRegister(uint8 ADR, uint8 Reg, uint16 *RetValue);// Запись в регистр
uint8 OPT_ReadResult(uint32 *Result);// Чтение результата измерения и перевод значения в Люксы
uint8 OPT_StartConvert();//Запуск процесса измерения освещенности
uint16 OPT_Status(int type);
char *OPT_GetResultString(volatile uint32 *Lux);// Конверсия значения в строку



/*---------------------------------------------------------------------------*/
/* [] END OF FILE */
