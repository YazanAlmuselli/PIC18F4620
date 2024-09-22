/* 
 * File:   ECU_Layer_Init.c
 * Author: Yazan Abd-Almajeed
 * Created on August 10, 2023, 1:21 PM
 */

#include "ECU_Layer_Init.h"

Std_Return_Type ret = E_OK;


led_t led1 = {.port_name = PORTA_INDEX, .pin = GPIO_PIN0, .led_status = LED_OFF};
led_t led2 = {.port_name = PORTA_INDEX, .pin = GPIO_PIN1, .led_status = LED_OFF};
//
//button_t btn_high = {
//    .button_pin.port = PORTA_INDEX,
//    .button_pin.pin = GPIO_PIN4,
//    .button_pin.direction = GPIO_DIRECTION_INPUT,
//    .button_pin.logic = GPIO_LOW,
//    .button_connection = BUTTON_ACTIVE_HIGH,
//    .button_state = BUTTON_RELEASED
//};
//
//dc_motor_t dc_motor_1 = {
//    .dc_motor[0].port = PORTD_INDEX,
//    .dc_motor[0].pin = GPIO_PIN0,
//    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
//    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
//    .dc_motor[1].port = PORTD_INDEX,
//    .dc_motor[1].pin = GPIO_PIN1,
//    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
//    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
//};
//
//dc_motor_t dc_motor_2 = {
//    .dc_motor[0].port = PORTD_INDEX,
//    .dc_motor[0].pin = GPIO_PIN2,
//    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
//    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
//    .dc_motor[1].port = PORTD_INDEX,
//    .dc_motor[1].pin = GPIO_PIN3,
//    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
//    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT
//};
//
//chr_lcd_4bit_t lcd_1 = {
//    .lcd_rs.port = PORTC_INDEX,
//    .lcd_rs.pin = GPIO_PIN0,
//    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_rs.logic = GPIO_LOW,
//    .lcd_en.port = PORTC_INDEX,
//    .lcd_en.pin = GPIO_PIN1,
//    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_en.logic = GPIO_LOW,
//    .lcd_data[0].port = PORTC_INDEX,
//    .lcd_data[0].pin = GPIO_PIN2,
//    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[0].logic = GPIO_LOW,
//    .lcd_data[1].port = PORTC_INDEX,
//    .lcd_data[1].pin = GPIO_PIN3,
//    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[1].logic = GPIO_LOW,
//    .lcd_data[2].port = PORTC_INDEX,
//    .lcd_data[2].pin = GPIO_PIN4,
//    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[2].logic = GPIO_LOW,
//    .lcd_data[3].port = PORTC_INDEX,
//    .lcd_data[3].pin = GPIO_PIN5,
//    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[3].logic = GPIO_LOW
//};
//
//adc_cfg_t adc_1 = {
//    .ADC_InterruptHandler  = NULL,
//    .priority              = INTERRUPT_PRIORITY_HIGH,
//    .adc_acquisition_time  = ADC_12_TAD,
//    .adc_channel_select    = ADC_CHANNEL_AN0,
//    .adc_conversion_clock  = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
//    .result_format         = ADC_RESULT_RIGHT,
//    .voltage_ref           = ADC_VOLTAGE_REFERENCE_DISABLED
//};
//
//timer0_t timer0_timer_obj = {
//    .TIMER0_InterruptHandler = NULL,
//    .timer0_mode = TIMER0_TIMER_MODE_CFG,
//    .timer0_register_size = TIMER0_16BIT_CFG,
//    .presscaler_cfg = TIMER0_PRESCALER_ON,
//    .prescaler_value = TIMER0_PRESCALER_DIV_BY_8,
//    .timer0_preload_value = 3036
//};
//
//timer0_t timer0_counter_obj = {
//    .TIMER0_InterruptHandler = NULL,
//    .timer0_mode = TIMER0_COUNTER_MODE_CFG,
//    .timer0_register_size = TIMER0_16BIT_CFG,
//    .presscaler_cfg = TIMER0_PRESCALER_OFF,
//    .timer0_counter_edge = TIMER0_COUNTER_RISING_EDGE_CFG,
//    .timer0_preload_value = 0,
//};
//
//timer1_t counter_obj = {
//    .TIMER1_InterruptHandler = NULL,
//    .priority = INTERRUPT_PRIORITY_LOW,
//    .timer1_mode = TIMER1_COUNTER_MODE_CFG,
//    .timer1_preload_value = 0,
//    .timer1_prescaler_value = TIMER1_PRESCALER_VALUE_DIV_BY_1,
//    .timer1_rw_register_size = TIMER1_16BIT_CFG,
//    .timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE_CFG
//};
/*
timer3_t timer3_obj;
    timer3_obj.TIMER3_InterruptHandler = NULL;
    timer3_obj.priority = INTERRUPT_PRIORITY_LOW;
    timer3_obj.timer3_mode = TIMER3_TIMER_MODE_CFG;
    timer3_obj.timer3_rw_register_size = TIMER3_16BIT_CFG;
    timer3_obj.timer3_prescaler_value = TIMER3_PRESCALER_VALUE_DIV_BY_8;
    timer3_obj.timer3_preload_value  = 15536;

timer2_t timer2_obj;
ccp_t ccp1_obj;
ccp_t ccp2_obj;
    
    ccp1_obj.ccp_inst = CCP1_INST;
    ccp1_obj.CCP1_InterruptHandler = NULL;
    ccp1_obj.ccp_mode = CCP1_PWM_MODE_SELECTED;
    ccp1_obj.PWM_Freq = 20000;
    ccp1_obj.ccp_pin.port = PORTC_INDEX;
    ccp1_obj.ccp_pin.pin = GPIO_PIN2;
    ccp1_obj.ccp_pin.direction = GPIO_DIRECTION_OUTPUT;
    ccp1_obj.timer2_postscaler_value = CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_1;
    ccp1_obj.timer2_prescaler_value = CCP_TIMER2_PRESCALER_VALUE_DIV_BY_1;
    
    ccp2_obj.ccp_inst = CCP2_INST;
    ccp2_obj.CCP1_InterruptHandler = NULL;
    ccp2_obj.ccp_mode = CCP1_PWM_MODE_SELECTED;
    ccp2_obj.PWM_Freq = 20000;
    ccp2_obj.ccp_pin.port = PORTC_INDEX;
    ccp2_obj.ccp_pin.pin = GPIO_PIN1;
    ccp2_obj.ccp_pin.direction = GPIO_DIRECTION_OUTPUT;
    ccp2_obj.timer2_postscaler_value = CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_1;
    ccp2_obj.timer2_prescaler_value = CCP_TIMER2_PRESCALER_VALUE_DIV_BY_1;
    
    timer2_obj.TIMER2_InterruptHandler = NULL;
    timer2_obj.timer2_postscaler_value = TIMER2_POSTSCALER_VALUE_DIV_BY_1;
    timer2_obj.timer2_prescaler_value = TIMER2_PRESCALER_VALUE_DIV_BY_1;
    timer2_obj.timer2_preload_value = 0;*/
/*
    void usart_module_init(void){
    usart_t usart_obj;
    
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    
    usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    
    ret = EUSART_ASYNC_Init(&usart_obj);
}

void usart_module_int_init(void){
    usart_t usart_obj;
    
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    
    usart_obj.EUSART_TxDefaultInterruptHandler = Tx_APP_ISR;
    usart_obj.EUSART_RxDefaultInterruptHandler = Rx_APP_ISR;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    
    ret = EUSART_ASYNC_Init(&usart_obj);
}*/

/*
 SPI_Config SPI_obj = {
    .MSSP_SPI_InterruptHandler = NULL,
    .priority = INTERRUPT_PRIORITY_LOW,
    .spi_mode = SPI_MASTER_FOSC_DIV4,
    .spi_config.ClockPolarity = SPI_IDLE_STATE_LOW_LEVEL,
    .spi_config.ClockSelect = SPI_TRANSMIT_IDLE_TO_ACTIVE,
    .spi_config.SampleSelect = SPI_DATA_SAMPLE_MIDDLE
};
 */

keypad_t keypad = {
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};

chr_lcd_4bit_t lcd_4bit = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};

void ecu_layer_intialize(void)
{   
    Std_Return_Type ret = E_OK;
    
    ret = keypad_initialize(&keypad);
    ret = lcd_4bit_initialize(&lcd_4bit);
    
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    
    //ret = led_intialize(&(led1));
    //ret = led_intialize(&(led2));
    //ret = button_initialize(&btn_high);
}