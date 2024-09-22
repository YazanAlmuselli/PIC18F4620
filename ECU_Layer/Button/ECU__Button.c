/* 
 * File:   ECU_Button.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 3, 2023, 6:12 PM
 */

#include "ECU_Button.h"

/**
 * 
 * @param *btn is a pointer to the button configuration. 
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type button_initialize(const button_t *btn)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
    return ret;
}

/**
 * 
 * @param *btn is a pointer to the button configuration.
 * @param *btn_state a pointer to hold button status.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */
Std_Return_Type button_read_state(const button_t *btn, button_state_t *btn_state)
{
    Std_Return_Type ret = E_OK;
    logic_t pin_logic_status = GPIO_LOW;
    
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_RELEASED;
            }
            else
            {
                *btn_state = BUTTON_PRESSED;
            }
        }
        else
        {/* Nothing */}
    ret = E_OK;
    }
    return ret;
}

