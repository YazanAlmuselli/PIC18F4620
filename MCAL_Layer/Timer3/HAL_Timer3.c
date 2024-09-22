/* 
 * File:   HAL_Timer3.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 31, 2023, 10:17 AM
 */

#include "HAL_Timer3.h"

#if TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif

uint16 timer3_preload = 0;

static inline void Timer3_Mode_Select(const timer3_t *_timer);

Std_Return_Type Timer3_Init(const timer3_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_VALUE(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
#if TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    TIMER3_INTERRUPT_ENABLE();
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler;
    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _timer->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        TIMER3_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _timer->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        TIMER3_INTERRUPT_PRIORITY_HIGH();
    }
    else{
        /* Nothing */
    }
    
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
    
#endif
    
#endif
        TIMER3_MODULE_ENABLE();
    }
    
    return ret;
}

Std_Return_Type Timer3_DeInit(const timer3_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        TIMER3_INTERRUPT_DISABLE();
#endif
    }
    
    return ret;
}

Std_Return_Type Timer3_Write_Value(const timer3_t *_timer, uint16 _value){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
    }
    
    return ret;
}

Std_Return_Type Timer3_Read_Value(const timer3_t *_timer, uint16 *_value){
    Std_Return_Type ret = E_OK;
    uint8 tmr3_h, tmr3_l = 0;
    
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        tmr3_h = (uint8)TMR3H;
        tmr3_l = (uint8)TMR3L;
        *_value = (uint16)((tmr3_h << 8) + tmr3_l);
    }
    
    return ret;
}

void TIMER3_ISR(void){
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    if(TIMER3_InterruptHandler)
    {
        TIMER3_InterruptHandler();
    }
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE_CFG == _timer->timer3_mode){
        TIMER3_TIMER_MODE();  
    }
    else if(TIMER3_COUNTER_MODE_CFG == _timer->timer3_mode){
        TIMER3_COUNTER_MODE();
        if(TIMER3_ASYNC_COUNTER_MODE_CFG == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE_CFG == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}