/* 
 * File:   HAL_Timer1.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 30, 2023, 1:26 PM
 */

#include "HAL_Timer1.h"

#if TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*TIMER1_InterruptHandler)(void) = NULL;
#endif

uint16 timer1_preload = 0;

static inline void Timer1_Mode_Select(const timer1_t *_timer);

Std_Return_Type Timer1_Init(const timer1_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_VALUE(_timer->timer1_prescaler_value);
        Timer1_Mode_Select(_timer);
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
#if TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    TIMER1_INTERRUPT_ENABLE();
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TIMER1_InterruptHandler = _timer->TIMER1_InterruptHandler;
    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _timer->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        TIMER1_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _timer->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        TIMER1_INTERRUPT_PRIORITY_HIGH();
    }
    else{
        /* Nothing */
    }
    
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
    
#endif
    
#endif
        TIMER1_MODULE_ENABLE();
    }
    
    return ret;
}

Std_Return_Type Timer1_DeInit(const timer1_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        TIMER1_INTERRUPT_DISABLE();
#endif
    }
    
    return ret;
}

Std_Return_Type Timer1_Write_Value(const timer1_t *_timer, uint16 _value){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
    }
    
    return ret;
}

Std_Return_Type Timer1_Read_Value(const timer1_t *_timer, uint16 *_value){
    Std_Return_Type ret = E_OK;
    uint8 tmr1_h, tmr1_l = 0;
    
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        tmr1_h = (uint8)TMR1H;
        tmr1_l = (uint8)TMR1L;
        *_value = (uint16)((tmr1_h << 8) + tmr1_l);
    }
    
    return ret;
}


void TIMER1_ISR(void){
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (uint8)(timer1_preload);
    if(TIMER1_InterruptHandler)
    {
        TIMER1_InterruptHandler();
    }
}

static inline void Timer1_Mode_Select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE_CFG == _timer->timer1_mode){
        TIMER1_TIMER_MODE();  
    }
    else if(TIMER1_COUNTER_MODE_CFG == _timer->timer1_mode){
        TIMER1_COUNTER_MODE();
        if(TIMER1_ASYNC_COUNTER_MODE_CFG == _timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE_CFG == _timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}