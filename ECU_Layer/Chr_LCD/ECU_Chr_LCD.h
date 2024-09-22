/* 
 * File:   ECU_Chr_LCD.h
 * Author: Yazan Abd-Almajeed
 * Created on August 13, 2023, 12:45 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* ----------------- Includes -----------------*/
#include "ECU_Chr_LCD_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* ----------------- Macro Declarations -----------------*/

/* To Read More About this Instructions Check the Page 26 in the Data Sheet */

#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02           // Return the cursor home.
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18            // Move the whole text into left one time.
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C            // Move the whole text into right one time.
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

#define DATA_PINS_4BIT  4
#define DATA_PINS_8BIT  8



/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);
Std_Return_Type lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);
Std_Return_Type lcd_4bit_send_data(const chr_lcd_4bit_t *lcd, uint8 data);
Std_Return_Type lcd_4bit_send_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_Return_Type lcd_4bit_send_str(const chr_lcd_4bit_t *lcd, uint8 *str);
Std_Return_Type lcd_4bit_send_str_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_Return_Type lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                          const uint8 _chr[], uint8 mem_pos);

Std_Return_Type lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
Std_Return_Type lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
Std_Return_Type lcd_8bit_send_data(const chr_lcd_8bit_t *lcd, uint8 data);
Std_Return_Type lcd_8bit_send_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
Std_Return_Type lcd_8bit_send_str(const chr_lcd_8bit_t *lcd, uint8 *str);
Std_Return_Type lcd_8bit_send_str_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
Std_Return_Type lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                          const uint8 _chr[], uint8 mem_pos);

Std_Return_Type convert_byte_to_string(uint8 value, uint8 *str);
Std_Return_Type convert_short_to_string(uint16 value, uint8 *str);
Std_Return_Type convert_int_to_string(uint32 value, uint8 *str);

#endif	/* ECU_CHR_LCD_H */

