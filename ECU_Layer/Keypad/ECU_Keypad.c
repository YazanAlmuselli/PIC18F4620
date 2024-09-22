/* 
 * File:   ECU_Keypad.c
 * Author: Yazan Abd-Almajeed
 * Created on July 16, 2023, 12:48 PM
 */

#include "ECU_Keypad.h"

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                     };

/*
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */

    Std_Return_Type keypad_initialize(const keypad_t *_keypad_obj){
    Std_Return_Type ret = E_OK;
   uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
  if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{    
        for(rows_counter=ZERO_INIT; rows_counter<KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_intialize(&(_keypad_obj->keypad_rows_pins[rows_counter]));
        }
        for(columns_counter=ZERO_INIT; columns_counter<KEYPAD_COLUMNS; columns_counter++){
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

/**
 * @brief Get the value of the button pressed by the user and performing the scanning algorithm
 * @param _keypad_obj pointer to the keypad configurations
 * @param value Value of the button pressed by the user
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_Return_Type keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_Return_Type ret = E_OK;
    uint8 l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    logic_t column_logic = ZERO_INIT;
    
    if((NULL == _keypad_obj) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{    
        for(l_rows_counter=ZERO_INIT; l_rows_counter<KEYPAD_ROWS; l_rows_counter++){
            for(l_counter=ZERO_INIT; l_counter<KEYPAD_ROWS; l_counter++){
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins[l_counter]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_rows_pins[l_rows_counter]), GPIO_HIGH);
            __delay_ms(30);
            for(l_columns_counter=ZERO_INIT; l_columns_counter<KEYPAD_COLUMNS; l_columns_counter++){
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic){
                    *value = btn_values[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return ret;
}
