/* 
 * File:   HAL_EEPROM.c
 * Author: Yazan Abd-Almajeed
 * Created on August 22, 2023, 1:48 PM
 */

#include "HAL_EEPROM.h"

/**
 * @brieaf : Write Data in EEPROM.
 * @param  : bAdd is the adress to write data at.
 * @param  : bData is the data to write.
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_Return_Type Data_EEPROM_Write_Byte(uint16 bAdd, uint8 bData)
{
    Std_Return_Type ret = E_OK;
    
    /* Read the Interrupt Status "H/L" */
    uint8 Global_Interrupt_status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x3);
    EEADR = (uint8)(bAdd & 0xFF);
    /* Update the Data Address */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLE_EEPROM;
    /* Disable all Interrupts "General Interrupt" */
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    
#else 
    INTERRUPT_GLOBAL_DISABLE(); 
#endif
    /* Write the required Sequence 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for Write to Complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to data EEPROM */
    EECON1bits.WREN = INHIBITS_WRITE_CYCLE_EEPROM;
    /* Restore the Global Interrupt Status  */
    INTCONbits.GIE = Global_Interrupt_status;
    
    return ret;
}

/**
 * @brieaf : Read Data in EEPROM.
 * @param  : bAdd is the adress to write data at.
 * @param  : bData is pointer to hold the data.
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action.
 */
Std_Return_Type Data_EEPROM_Read_Byte(uint16 bAdd, uint8 *bData)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Update the Address Registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x3);
        EEADR = (uint8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY;
        /* Allows Read cycles to data EEPROM */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ_ERASE;
        NOP();
        NOP();
        /* Return Data */
        *bData = EEDATA;
    }
    
    return ret;
}