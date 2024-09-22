/* 
 * File:   HAL_Timer2.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 31, 2023, 10:14 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* ----------------- Includes -----------------*/
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Post-Scaler Value */
#define TIMER2_POSTSCALER_VALUE_DIV_BY_1    0
#define TIMER2_POSTSCALER_VALUE_DIV_BY_2    1
#define TIMER2_POSTSCALER_VALUE_DIV_BY_3    2
#define TIMER2_POSTSCALER_VALUE_DIV_BY_4    3
#define TIMER2_POSTSCALER_VALUE_DIV_BY_5    4
#define TIMER2_POSTSCALER_VALUE_DIV_BY_6    5
#define TIMER2_POSTSCALER_VALUE_DIV_BY_7    6
#define TIMER2_POSTSCALER_VALUE_DIV_BY_8    7
#define TIMER2_POSTSCALER_VALUE_DIV_BY_9    8
#define TIMER2_POSTSCALER_VALUE_DIV_BY_10   9
#define TIMER2_POSTSCALER_VALUE_DIV_BY_11   10
#define TIMER2_POSTSCALER_VALUE_DIV_BY_12   11
#define TIMER2_POSTSCALER_VALUE_DIV_BY_13   12
#define TIMER2_POSTSCALER_VALUE_DIV_BY_14   13
#define TIMER2_POSTSCALER_VALUE_DIV_BY_15   14
#define TIMER2_POSTSCALER_VALUE_DIV_BY_16   15

/* Pre-Scaler Value */
#define TIMER2_PRESCALER_VALUE_DIV_BY_1    0
#define TIMER2_PRESCALER_VALUE_DIV_BY_4    1
#define TIMER2_PRESCALER_VALUE_DIV_BY_16   2

/* ----------------- Macro Functions Declarations -----------------*/
/* Timer2 Turn ON/OFF */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)  
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

/* Timer2 Pre-scaler Value Select */
#define TIMER2_PRESCALER_VALUE(_PRESCALER_) (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer2 Post-scaler Value Select */
#define TIMER2_POSTSCALER_VALUE(_POSTSCALER_) (T2CONbits.TOUTPS = _POSTSCALER_)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*TIMER2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
    uint8 reserved : 2;
}timer2_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type Timer2_Init(const timer2_t *_timer);
Std_Return_Type Timer2_DeInit(const timer2_t *_timer);
Std_Return_Type Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_Return_Type Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);

#endif	/* HAL_TIMER2_H */

