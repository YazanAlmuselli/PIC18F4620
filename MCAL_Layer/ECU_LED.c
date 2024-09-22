/* 
 * File:   ECU_LED.c
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 1:03 PM
 */

#include "ECU_LED.h"

/**
 * @brief  : Initialize the assigned pin to be OUTPUT and turn the led off.
 * @param  : *led is a pointer to the led configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type led_intialize(const led_t *led)
{
    Std_Return_Type ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_direction_intialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief  : Turn the led on.
 * @param  : *led is a pointer to the led configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type led_turn_on(const led_t *led)
{
     Std_Return_Type ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief  : Turn the led off.
 * @param  : *led is a pointer to the led configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type led_turn_off(const led_t *led)
{
    Std_Return_Type ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

/**
 * @brief  : Toggle the led.
 * @param  : *led is a pointer to the led configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type led_turn_toggle(const led_t *led)
{
    Std_Return_Type ret = E_NOT_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name, .pin = led->pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status};
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}