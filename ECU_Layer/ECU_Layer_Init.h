/* 
 * File:   ECU_Layer_Init.h
 * Author: Yazan Abd-Almajeed
 * Created on August 10, 2023, 1:20 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "../MCAL_Layer/ECU_LED.h"
#include "../ECU_Layer/Button/ECU_Button.h"
#include "../ECU_Layer/Relay/ECU_Relay.h"
#include "../ECU_Layer/DC_Motor/ECU_DC_Motor.h"
#include "../ECU_Layer/7-segment/ECU_Seven_Segment.h"
#include "../ECU_Layer/Keypad/ECU_Keypad.h"
#include "Chr_LCD/ECU_Chr_LCD.h"
#include "../MCAL_Layer/Interrupt/MCAL_External_Interrupt.h"
#include "../MCAL_Layer/EEPROM/HAL_EEPROM.h"
#include "../MCAL_Layer/ADC/HAL_ADC.h"
#include "../MCAL_Layer/Timer/HAL_Timer0.h"
#include "../MCAL_Layer/Timer1/HAL_Timer1.h"
#include "../MCAL_Layer/Timer2/HAL_Timer2.h"
#include "../MCAL_Layer/Timer3/HAL_Timer3.h"
#include "../MCAL_Layer/CCP1/HAL_CCP1.h"
#include "../MCAL_Layer/USART/HAL_USART.h"
#include "../MCAL_Layer/SPI/HAL_SPI.h"
#include "../MCAL_Layer/I2C/HAL_I2C.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */

/* Section : Function Declaration */
void ecu_layer_intialize(void);

#endif	/* ECU_LAYER_INIT_H */

