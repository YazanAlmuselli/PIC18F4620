/* 
 * File:   ECU_Button.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 3, 2023, 6:09 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL_Layer/HAL_GPIO.h"
#include "ECU_Button_CFG.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED       
}button_state_t;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW       
}button_active_state;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_state button_connection;
}button_t;

/* Section : Function Declaration */
Std_Return_Type button_initialize(const button_t *btn);
Std_Return_Type button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

