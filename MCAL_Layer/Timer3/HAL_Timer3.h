/* 
 * File:   HAL_Timer3.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 31, 2023, 10:17 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* ----------------- Includes -----------------*/
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Timer3 Mode */
#define TIMER3_TIMER_MODE_CFG             0
#define TIMER3_COUNTER_MODE_CFG           1

/* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE_CFG      1
#define TIMER3_SYNC_COUNTER_MODE_CFG       0

/* Timer3 Pre-scaler Value Select */
#define TIMER3_PRESCALER_VALUE_DIV_BY_1   0
#define TIMER3_PRESCALER_VALUE_DIV_BY_2   1
#define TIMER3_PRESCALER_VALUE_DIV_BY_4   2
#define TIMER3_PRESCALER_VALUE_DIV_BY_8   3

/* 8/16 Bit Mode Select */
#define TIMER3_8BIT_CFG                   0
#define TIMER3_16BIT_CFG                  1

/* ----------------- Macro Functions Declarations -----------------*/
/* Timer3 Turn ON/OFF */
#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)  
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)

/* Timer3 Mode */
#define TIMER3_TIMER_MODE()                 (T3CONbits.TMR3CS = 0)  
#define TIMER3_COUNTER_MODE()               (T3CONbits.TMR3CS = 1)

/* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 1)  
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()    (T3CONbits.T3SYNC = 0)

/* Timer3 Pre-scaler Value Select */
#define TIMER3_PRESCALER_VALUE(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)

/* 8/16 Bit Mode Select */
#define TIMER3_8BIT_SELECT                  (T3CONbits.RD16 = 0)
#define TIMER3_16BIT_SELECT                 (T3CONbits.RD16 = 1)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*TIMER3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_rw_register_size : 1;
    uint8 reserved : 3;
}timer3_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type Timer3_Init(const timer3_t *_timer);
Std_Return_Type Timer3_DeInit(const timer3_t *_timer);
Std_Return_Type Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
Std_Return_Type Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER3_H */

