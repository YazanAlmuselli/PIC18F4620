/* 
 * File:   HAL_Timer0.h
 * Author: Yazan Abd-Almajeed
 * Created on August 29, 2023, 11:43 AM
 */

#include "HAL_Timer0.h"

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size(const timer0_t *_timer);

uint16 timer0_preload = 0;

#if TIMER0_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*TIMER0_InterruptHandler)(void) = NULL;
#endif

Std_Return_Type Timer0_Init(const timer0_t *_timer){
    
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size(_timer);
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        timer0_preload = _timer->timer0_preload_value;
#if TIMER0_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    TIMER0_INTERRUPT_ENABLE();
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _timer->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        TIMER0_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _timer->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        TIMER0_INTERRUPT_PRIORITY_HIGH();
    }
    else{
        /* Nothing */
    }
    
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
    
#endif
    
#endif
    
        TIMER0_MODULE_ENABLE();
    }
    
    return ret;
}

Std_Return_Type Timer0_DeInit(const timer0_t *_timer){
    
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
#endif
    }
    
    return ret;
}

Std_Return_Type Timer0_Write_Value(const timer0_t *_timer, uint16 _value){
    
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
    }
    
    return ret;
}

Std_Return_Type Timer0_Read_Value(const timer0_t *_timer, uint16 *_value){
    
    Std_Return_Type ret = E_OK;
    uint8 tmr0_l, tmr0_h;
    
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        tmr0_l = (uint8)TMR0L;
        tmr0_h = (uint8)TMR0H;
        *_value = (uint16)((tmr0_h << 8) + tmr0_l);
    }
    
    return ret;
}


void TIMER0_ISR(void){
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TIMER0_InterruptHandler)
    {
        TIMER0_InterruptHandler();
    }
}

static inline void Timer0_Prescaler_Config(const timer0_t *_timer){
    
    if(TIMER0_PRESCALER_ON == _timer->presscaler_cfg){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_OFF == _timer->presscaler_cfg){
        TIMER0_PRESCALER_DISABLE();
    }
    else{
        /* Nothing */
    }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    
    if(TIMER0_TIMER_MODE_CFG == _timer->timer0_mode){
        TIMER0_TIMER_MODE();
    }
    else if(TIMER0_COUNTER_MODE_CFG == _timer->timer0_mode){
        TIMER0_COUNTER_MODE();
        if(TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE();
        }
        else if(TIMER0_COUNTER_FALLING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE();
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}

static inline void Timer0_Register_Size(const timer0_t *_timer){
    if(TIMER0_8BIT_CFG == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE();
    }
    else if(TIMER0_16BIT_CFG == _timer->timer0_register_size){
        TIMER0_16BIT_REGISTER_MODE();
    }
    else{
        /* Nothing */
    }
}