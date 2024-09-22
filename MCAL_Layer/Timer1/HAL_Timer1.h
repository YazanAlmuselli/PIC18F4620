/* 
 * File:   HAL_Timer1.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 30, 2023, 1:26 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* ----------------- Includes -----------------*/
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/
#define TIMER1_TIMER_MODE_CFG             0
#define TIMER1_COUNTER_MODE_CFG           1

#define TIMER1_ASYNC_COUNTER_MODE_CFG      1
#define TIMER1_SYNC_COUNTER_MODE_CFG       0

#define TIMER1_OSC_HW_ENABLE_CFG          1
#define TIMER1_OSC_HW_DISABLE_CFG         0

#define TIMER1_PRESCALER_VALUE_DIV_BY_1   0
#define TIMER1_PRESCALER_VALUE_DIV_BY_2   1
#define TIMER1_PRESCALER_VALUE_DIV_BY_4   2
#define TIMER1_PRESCALER_VALUE_DIV_BY_8   3

#define TIMER1_8BIT_CFG                   0
#define TIMER1_16BIT_CFG                  1

/* ----------------- Macro Functions Declarations -----------------*/
/* Timer1 Turn ON/OFF */
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)  
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)
/* Timer1 Mode */
#define TIMER1_TIMER_MODE()                 (T1CONbits.TMR1CS = 0)  
#define TIMER1_COUNTER_MODE()               (T1CONbits.TMR1CS = 1)
/* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 1)  
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0)
/* Timer1 OSC Configurations */
#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1) 
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0) 
/* Timer1 Pre-scaler Value Select */
#define TIMER1_PRESCALER_VALUE(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)
/* Timer1 Clock Source */
#define TIMER1_SYSTEM_ClOCK_SOURCE()        (T1CONbits.T1RUN)
/* 8/16 Bit Mpde Select */
#define TIMER1_8BIT_SELECT                  (T1CONbits.RD16 = 0)
#define TIMER1_16BIT_SELECT                 (T1CONbits.RD16 = 1)

/* ----------------- Data Type Declarations -----------------*/

typedef struct{
#if TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*TIMER1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preload_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_rw_register_size : 1;
    uint8 reserved : 2;
}timer1_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type Timer1_Init(const timer1_t *_timer);
Std_Return_Type Timer1_DeInit(const timer1_t *_timer);
Std_Return_Type Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
Std_Return_Type Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER1_H */

