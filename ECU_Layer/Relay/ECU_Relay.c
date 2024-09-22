/* 
 * File:   ECU_Relay.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 6, 2023, 3:51 PM
 */

#include "ECU_Relay.h"

/**
 * @brief  : Initialize the assigned pin to be OUTPUT and turn the relay off
 * @param  : _relay is a pointer to the configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type relay_initialize(const relay_t *_relay)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
        ret = gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief  : Relay on
 * @param  : _relay is a pointer to the configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type relay_turn_on(const relay_t *_relay)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief  : Realy off
 * @param  : _relay is a pointer to the configuration.
 * @return : Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type relay_turn_off(const relay_t *_relay)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _relay->relay_port, .pin = _relay->relay_pin, 
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

