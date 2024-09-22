/* 
 * File:   ECU_LED.h
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 1:07 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/* Section : Includes */

#include "../MCAL_Layer/HAL_GPIO.h"
#include "../ECU_Layer/LED/ECU_LED_CFG.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef enum {
    LED_OFF = 0,
    LED_ON        
}les_status_t;

typedef struct {
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;

/* Section : Function Declaration */
Std_Return_Type led_intialize(const led_t *led);
Std_Return_Type led_turn_on(const led_t *led);
Std_Return_Type led_turn_off(const led_t *led);
Std_Return_Type led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

