/* 
 * File:   Application.h
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 12:53 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/* Section : Includes */
#include "../ECU_Layer/ECU_Layer_Init.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declarations */

/* Section : Data Type Declaration */
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;
extern led_t led1;
extern led_t led2;
extern keypad_t keypad;
extern chr_lcd_4bit_t lcd_4bit;

/* Section : Function Declaration */
void application_intialize(void);

#endif	/* APPLICATION_H */

