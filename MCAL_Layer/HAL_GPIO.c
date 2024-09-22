/* 
 * File:   Application.h
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 1:02 PM
 */

#include "HAL_GPIO.h"

volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * 
 * @param _pin_config : pointer to the configuration.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_direction_intialize(const pin_config_t *_pin_config)
{
    Std_Return_Type ret = E_OK;
    if((NULL == _pin_config) || (_pin_config->pin > (PORT_PIN_MAX_NUMBER)))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);    
                break;
            case GPIO_DIRECTION_INPUT :
                SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    return ret;
}
#endif

/**
 * 
 * @param   : _pin_config       : pointer to the configuration.
 * @param   : direction_status  : pointer to hold the direction.
 * @return  : Status of the function
 *           (E_OK)     mean the function has successfully called
 *           (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin == PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : pointer to the configuration.
 * @param logic       : high or low.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic)
{
    Std_Return_Type ret = E_OK;
    if((NULL == _pin_config)  || (_pin_config->pin > (PORT_PIN_MAX_NUMBER))) 
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW :
                CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);    
                break;
            case GPIO_HIGH :
                SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

 /**
  * 
  * @param _pin_config : pointer to the configuration.
  * @param logic       : pointer to hold the logic.
  * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
  */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin == PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : pointer to the configuration.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_Return_Type ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin == PORT_PIN_MAX_NUMBER)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
    return ret;
}
#endif

/**
 * 
 * @param _pin_config : pointer to the configuration.
 * @return  Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_pin_intialize(const pin_config_t *_pin_config)
{
    Std_Return_Type ret = E_OK;
    if((NULL == _pin_config)  || (_pin_config->pin > (PORT_PIN_MAX_NUMBER)))
    {
        ret = E_NOT_OK;
    }
    else
    {
    ret = gpio_pin_direction_intialize(_pin_config);
    ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

/**
 * 
 * @param port      : A, B, C, D or E.
 * @param direction : input or output.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_port_direction_intialize(port_index_t port, uint8 direction)
{
    Std_Return_Type ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

/**
 * 
 * @param port : the configuration.
 * @param direction_status : pointer to hold the direction.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    Std_Return_Type ret = E_OK;
    if(port > PORT_MAX_NUMBER-1 || NULL == direction_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port  : the configuration.
 * @param logic : high or low.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_port_write_logic(port_index_t port, uint8 logic)
{
    Std_Return_Type ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif

/**
 * 
 * @param port  : the configuration.
 * @param logic : a pointer to hold the logic.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    Std_Return_Type ret = E_OK;
    if(NULL == logic || port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *lat_registers[port];
    }
    return ret;
}
#endif

/**
 * 
 * @param port : the configuration.
 * @return Status of the function
 *         (E_OK)     mean the function has successfully called
 *         (E_NOT_OK) mean the function has problem while calling.
 */

#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_Return_Type gpio_port_toggle_logic(port_index_t port)
{
    Std_Return_Type ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif