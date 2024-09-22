/* 
 * File:   ECU_Chr_LCD.c
 * Author: Yazan Abd-Almajeed
 * Created on August 13, 2023, 12:46 PM
 */

#include "ECU_Chr_LCD.h"

static Std_Return_Type lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _data_command);

static Std_Return_Type lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_Return_Type lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);

static Std_Return_Type lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);
static Std_Return_Type lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);

/**
 * 
 * @param lcd
 * @return 
 */
Std_Return_Type lcd_4bit_initialize(const chr_lcd_4bit_t *lcd)
{
    Std_Return_Type ret = E_OK;
    uint8 l_data_pins_counter = 0;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = 0; l_data_pins_counter < DATA_PINS_4BIT; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_Return_Type lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bit(lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_Return_Type lcd_4bit_send_data(const chr_lcd_4bit_t *lcd, uint8 data)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bit(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_Return_Type lcd_4bit_send_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_Return_Type lcd_4bit_send_str(const chr_lcd_4bit_t *lcd, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {    
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_Return_Type lcd_4bit_send_str_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_4bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_Return_Type lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                          const uint8 _chr[], uint8 mem_pos)

{
    Std_Return_Type ret = E_OK;
    uint8 cc_counter = 0;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(cc_counter = 0; cc_counter < DATA_PINS_4BIT; cc_counter++)
        {
            ret = lcd_4bit_send_data(lcd, _chr[cc_counter]);
        }
        ret = lcd_4bit_send_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
Std_Return_Type lcd_8bit_initialize(const chr_lcd_8bit_t *lcd)
{
    Std_Return_Type ret = E_OK;
    uint8 l_data_pins_counter = 0;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = 0; l_data_pins_counter < DATA_PINS_8BIT; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_Return_Type lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command)
{
    Std_Return_Type ret = E_OK;
    Std_Return_Type pins_counter = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(pins_counter = 0; pins_counter < DATA_PINS_8BIT; pins_counter++)
        {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (command >> pins_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_Return_Type lcd_8bit_send_data(const chr_lcd_8bit_t *lcd, uint8 data)
{
    Std_Return_Type ret = E_OK;
    Std_Return_Type pins_counter = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(pins_counter = 0; pins_counter < DATA_PINS_8BIT; pins_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (data >> pins_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_Return_Type lcd_8bit_send_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_data(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_Return_Type lcd_8bit_send_str(const chr_lcd_8bit_t *lcd, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {    
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_Return_Type lcd_8bit_send_str_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if((NULL == lcd) || (NULL == str))
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_8bit_send_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_Return_Type lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                          const uint8 _chr[], uint8 mem_pos)
{
    Std_Return_Type ret = E_OK;
    uint8 cc_counter = 0;
    
   
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(cc_counter = 0; cc_counter < DATA_PINS_8BIT; cc_counter++)
        {
            ret = lcd_8bit_send_data(lcd, _chr[cc_counter]);
        }
        ret = lcd_8bit_send_data_pos(lcd, row, column, mem_pos);
    }
    
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_Return_Type convert_byte_to_string(uint8 value, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_Return_Type convert_short_to_string(uint16 value, uint8 *str)
{
    Std_Return_Type ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 Data_Counter = 0;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset(str, ' ', 6);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[Data_Counter] != '\0'){
            str[Data_Counter] = Temp_String[Data_Counter];
            Data_Counter++;
        }
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return 
 */
Std_Return_Type convert_int_to_string(uint32 value, uint8 *str)
{
    Std_Return_Type ret = E_OK;
   
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param _data_command
 * @return 
 */

static Std_Return_Type lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _data_command)
{
    Std_Return_Type ret = E_OK;
    Std_Return_Type pins_counter = E_OK;
    
    for(pins_counter = 0; pins_counter < DATA_PINS_4BIT; pins_counter++)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (_data_command >> pins_counter) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (_data_command >> pins_counter) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (_data_command >> pins_counter) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (_data_command >> pins_counter) & (uint8)0x01);
    }
    
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static Std_Return_Type lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    Std_Return_Type ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static Std_Return_Type lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd)
{
    Std_Return_Type ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static Std_Return_Type lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column)
{
    Std_Return_Type ret = E_OK;
    
    column--;
    switch(row)
    {
        case ROW1 : ret = lcd_8bit_send_command(lcd, (0x80 + column)); break ;
        case ROW2 : ret = lcd_8bit_send_command(lcd, (0xc0 + column)); break ;
        case ROW3 : ret = lcd_8bit_send_command(lcd, (0x94 + column)); break ;
        case ROW4 : ret = lcd_8bit_send_command(lcd, (0xd4 + column)); break ;
        default : ;
    }
    
    return ret;
}


/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @return 
 */
static Std_Return_Type lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column)
{
    Std_Return_Type ret = E_OK;
    
    column--;
    switch(row)
    {
        case ROW1 : ret = lcd_4bit_send_command(lcd, (0x80 + column)); break ;
        case ROW2 : ret = lcd_4bit_send_command(lcd, (0xc0 + column)); break ;
        case ROW3 : ret = lcd_4bit_send_command(lcd, (0x94 + column)); break ;
        case ROW4 : ret = lcd_4bit_send_command(lcd, (0xd4 + column)); break ;
        default : ;
    }
    
    return ret;
}