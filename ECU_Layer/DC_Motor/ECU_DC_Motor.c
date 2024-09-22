/* 
 * File:   ECU_DC_Motor.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 6, 2023, 9:36 PM
 */

#include "ECU_DC_Motor.h"

static pin_config_t motor_pin1;
static pin_config_t motor_pin2;


/**
 * @brief  : Initialize the assigned pin to be OUTPUT and turn the motor off
 * @param  : _dc_motor is a pointer holding configurations.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(_dc_motor->dc_motor[0]));
        ret = gpio_pin_intialize(&(_dc_motor->dc_motor[1]));
    }
    return ret;
}

/**
 * @brief  : Move the motor right.
 * @param  : _dc_motor is a pointer holding configurations.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_LOW);
    }
    return ret;
}

/**
 * @brief  : Move the motor left.
 * @param  : _dc_motor is a pointer holding configurations.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief  : Stop the motor.
 * @param  : _dc_motor is a pointer holding configurations.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]), GPIO_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]), GPIO_LOW);
    }
    return ret;
}
