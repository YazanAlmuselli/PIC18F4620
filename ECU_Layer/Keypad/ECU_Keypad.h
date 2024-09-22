/* 
 * File:   ECU_Keypad.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 10, 2023, 12:03 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------- Includes -----------------*/
#include "ECU_Keypad_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* ----------------- Macro Declarations -----------------*/
#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4 

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type keypad_initialize(const keypad_t *_keypad_obj);
Std_Return_Type keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */
