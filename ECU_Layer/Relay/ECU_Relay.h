/* 
 * File:   ECU_Relay.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 6, 2023, 3:49 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include "ECU_Relay_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* Section : Macro Declarations */
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef struct{
    uint8 relay_port   : 4;
    uint8 relay_pin    : 3;
    uint8 relay_status : 1;
}relay_t;

/* Section : Function Declaration */
Std_Return_Type relay_initialize(const relay_t *_relay);
Std_Return_Type relay_turn_on(const relay_t *_relay);
Std_Return_Type relay_turn_off(const relay_t *_relay);


#endif	/* ECU_RELAY_H */

