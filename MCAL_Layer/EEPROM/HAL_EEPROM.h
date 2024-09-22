/* 
 * File:   HAL_EEPROM.h
 * Author: Yazan Abd-Almajeed
 * Created on August 22, 2023, 1:47 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/MCAL_STD_Types.h"
#include "../Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/

/* Flash Program or Data EEPROM Memory Select bit */
#define ACCESS_FLASH_PROGRAM_MEMORY      1
#define ACCESS_EEPROM_PROGRAM_MEMORY     0

/* Flash Program/Data EEPROM or Configuration Select bit */
#define ACCESS_CONFIGURATION_REGISTERS   1
#define ACCESS_FLASH_EEPROM_MEMORY       0

/* Flash Program/Data EEPROM Write Enable bit */
#define ALLOW_WRITE_CYCLE_EEPROM         1
#define INHIBITS_WRITE_CYCLE_EEPROM      0

/* Write Control bit */
#define INITIATE_DATA_EEPROM_WRITE_ERASE 1
#define DATA_EEPROM_WRITE_ERASE_COMPLETE 0

/* Read Control bit */
#define INITIATE_DATA_EEPROM_READ_ERASE 1
#define NEVER_INITIATE_DATA_EEPROM_READ 0

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type Data_EEPROM_Write_Byte(uint16 bAdd, uint8 bData);
Std_Return_Type Data_EEPROM_Read_Byte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

