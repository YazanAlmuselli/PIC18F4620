/* 
 * File:   HAL_Timer2.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 31, 2023, 10:14 AM
 */

#include "HAL_Timer2.h"

#if TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*TIMER2_InterruptHandler)(void) = NULL;
#endif

uint8 timer2_preload = 0;

Std_Return_Type Timer2_Init(const timer2_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_VALUE(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_VALUE(_timer->timer2_postscaler_value);
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
/* Interrupt Configurations */
#if TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    TIMER2_INTERRUPT_ENABLE();
    TIMER2_INTERRUPT_FLAG_CLEAR();
    TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler;
/* Interrupt priority Configurations */    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _timer->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        TIMER2_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _timer->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        TIMER2_INTERRUPT_PRIORITY_HIGH();
    }
    else{
        /* Nothing */
    }
    
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
    
#endif
    
#endif
        TIMER2_MODULE_ENABLE();
    }
    
    return ret;
}

Std_Return_Type Timer2_DeInit(const timer2_t *_timer){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        TIMER2_INTERRUPT_DISABLE();
#endif
    }
    
    return ret;
}

Std_Return_Type Timer2_Write_Value(const timer2_t *_timer, uint8 _value){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = _value;
    }
    
    return ret;
}

Std_Return_Type Timer2_Read_Value(const timer2_t *_timer, uint8 *_value){
    Std_Return_Type ret = E_OK;
    
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        *_value = TMR2; 
    }
    
    return ret;
}

void TIMER2_ISR(void){
    TIMER2_INTERRUPT_FLAG_CLEAR();
    TMR2 = timer2_preload;
    if(TIMER2_InterruptHandler)
    {
        TIMER2_InterruptHandler();
    }
}