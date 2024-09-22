/* 
 * File:   ECU_Seven_Segment.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 8, 2023, 4:26 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include "ECU_Seven_Segment_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* Section : Macro Declarations */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

#define SEGMENT_MAX_NUMBER 9

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Function Declaration */
Std_Return_Type seven_segment_initialize(const segment_t *seg);
Std_Return_Type seven_segment_write_number(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

