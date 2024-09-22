/* 
 * File:   ECU_Seven_Segment.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 8, 2023, 4:28 PM
 */
#include "ECU_Seven_Segment.h"

/**
 * @brief  : Initialize the assigned pin to be OUTPUT and turn the segment off.
 * @param  : seg is a pointer to the configuration.
 * @return : Status of the function
 *          (E_OK)     mean the function has successfully called
 *          (E_NOT_OK) mean the function has problem while calling. 
 */
Std_Return_Type seven_segment_initialize(const segment_t *seg)
{
    Std_Return_Type ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}

/**
 * @brief  : Display number on the segment.
 * @param  : seg is a pointer to the configuration.
 * @param  : number is the number to be displayed.
 * @return : Status of the function
 *          (E_OK)     mean the function has successfully called
 *          (E_NOT_OK) mean the function has problem while calling. 
 */
Std_Return_Type seven_segment_write_number(const segment_t *seg, uint8 number) // 1001 
{
    Std_Return_Type ret = E_OK;
    if((NULL == seg) || (number > SEGMENT_MAX_NUMBER))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), (number & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), ((number>>1) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), ((number>>2) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), ((number>>3) & 0x01));       
    }
    return ret;
}
