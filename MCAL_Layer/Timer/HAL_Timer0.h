/* 
 * File:   HAL_Timer0.h
 * Author: Yazan Abd-Almajeed
 * Created on August 29, 2023, 11:43 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* ----------------- Includes -----------------*/
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/

#define TIMER0_PRESCALER_ON               1
#define TIMER0_PRESCALER_OFF              0

#define TIMER0_COUNTER_RISING_EDGE_CFG    1
#define TIMER0_COUNTER_FALLING_EDGE_CFG   0

#define TIMER0_TIMER_MODE_CFG             1
#define TIMER0_COUNTER_MODE_CFG           0

#define TIMER0_8BIT_CFG                   1
#define TIMER0_16BIT_CFG                  0

/* ----------------- Macro Functions Declarations -----------------*/

#define TIMER0_PRESCALER_ENABLE()     (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()    (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE()          (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()         (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE()           (T0CONbits.T0CS = 0)  
#define TIMER0_COUNTER_MODE()         (T0CONbits.T0CS = 1)

#define TIMER0_16BIT_REGISTER_MODE()  (T0CONbits.T08BIT = 0)
#define TIMER0_8BIT_REGISTER_MODE()   (T0CONbits.T08BIT = 1)

#define TIMER0_MODULE_ENABLE()        (T0CONbits.TMR0ON = 1)  
#define TIMER0_MODULE_DISABLE()       (T0CONbits.TMR0ON = 0)  

/* ----------------- Data Type Declarations -----------------*/

typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*TIMER0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 presscaler_cfg : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 reserved : 4;
}timer0_t;
/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type Timer0_Init(const timer0_t *_timer);
Std_Return_Type Timer0_DeInit(const timer0_t *_timer);
Std_Return_Type Timer0_Write_Value(const timer0_t *_timer, uint16 _value);
Std_Return_Type Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER0_H */

