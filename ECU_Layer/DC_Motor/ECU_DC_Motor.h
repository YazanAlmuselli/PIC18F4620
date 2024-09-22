/* 
 * File:   ECU_DC_Motor.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 6, 2023, 9:34 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */
#include "ECU_DC_Motor_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* Section : Macro Declarations */
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1       0x00U
#define DC_MOTOR_PIN2       0x01U

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
typedef struct{
    pin_config_t dc_motor[2];
}dc_motor_t;

/* Section : Function Declaration */
Std_Return_Type dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_Return_Type dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_Return_Type dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_Return_Type dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

