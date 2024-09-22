/* 
 * File:   MCAL_External_Interrupt.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:21 PM
 */

#include "MCAL_External_Interrupt.h"

/* Pointer to function to hold CallBacks functions of INTx */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

/* Pointer to function to hold CallBacks functions of RBx */
static InterruptHandler RB4_InterruptHandler_Low = NULL;
static InterruptHandler RB4_InterruptHandler_High = NULL;
static InterruptHandler RB5_InterruptHandler_Low = NULL;
static InterruptHandler RB5_InterruptHandler_High = NULL;
static InterruptHandler RB6_InterruptHandler_Low = NULL;
static InterruptHandler RB6_InterruptHandler_High = NULL;
static InterruptHandler RB7_InterruptHandler_Low = NULL;
static InterruptHandler RB7_InterruptHandler_High = NULL;

static Std_Return_Type Interrupt_INTx_Enable(const interrupt_INTx_T *int_obj);
static Std_Return_Type Interrupt_INTx_Disable(const interrupt_INTx_T *int_obj);
static Std_Return_Type Interrupt_INTx_Priority_Init(const interrupt_INTx_T *int_obj);
static Std_Return_Type Interrupt_INTx_Edge_Init(const interrupt_INTx_T *int_obj);
static Std_Return_Type Interrupt_INTx_Pin_Init(const interrupt_INTx_T *int_obj);
static Std_Return_Type Interrupt_INTx_Clear_Flag(const interrupt_INTx_T *int_obj);

static Std_Return_Type INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_Return_Type INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_Return_Type INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_Return_Type Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_T *int_obj);

static Std_Return_Type Interrupt_RBx_Enable(const interrupt_RBx_T *int_obj);
static Std_Return_Type Interrupt_RBx_Disable(const interrupt_RBx_T *int_obj);
static Std_Return_Type Interrupt_RBx_Priority_Init(const interrupt_RBx_T *int_obj);
static Std_Return_Type Interrupt_RBx_Pin_Init(const interrupt_RBx_T *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_INTx_Initialize(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        #if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        ret = Interrupt_INTx_Edge_Init(int_obj);
        ret = Interrupt_INTx_Pin_Init(int_obj);
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        ret = Interrupt_INTx_Enable(int_obj);
    }
    
    return ret;
}

void INT0_ISR(void)
{
    INTERRUPT_INT0_FLAG_CLEAR();
    
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
    else
    {
        /* Nothing */
    }
}

void INT1_ISR(void)
{
    INTERRUPT_INT1_FLAG_CLEAR();
    
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
    else
    {
        /* Nothing */
    }
}

void INT2_ISR(void)
{
    INTERRUPT_INT2_FLAG_CLEAR();
    
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
    else
    {
        /* Nothing */
    }
}

void RB4_ISR(uint8 RB4_source)
{
    INTERRUPT_RBx_FLAG_CLEAR();
    
    if(GPIO_LOW == RB4_source)
    {
        if(RB4_InterruptHandler_Low)
        {
            RB4_InterruptHandler_Low();
        }
    }
    else if(GPIO_HIGH == RB4_source)
    {
        if(RB4_InterruptHandler_High)
        {
            RB4_InterruptHandler_High();
        }
    }
    else
    {
        /* Nothing */
    }
}

void RB5_ISR(uint8 RB5_source)
{
    INTERRUPT_RBx_FLAG_CLEAR();
    
    if(GPIO_LOW == RB5_source)
    {
        if(RB5_InterruptHandler_Low)
        {
            RB5_InterruptHandler_Low();
        }
    }
    else if(GPIO_HIGH == RB5_source)
    {
        if(RB5_InterruptHandler_High)
        {
            RB5_InterruptHandler_High();
        }
    }
    else
    {
        /* Nothing */
    }
}

void RB6_ISR(uint8 RB6_source)
{
    INTERRUPT_RBx_FLAG_CLEAR();
    
    if(GPIO_LOW == RB6_source)
    {
        if(RB6_InterruptHandler_Low)
        {
            RB6_InterruptHandler_Low();
        }
    }
    else if(GPIO_HIGH == RB6_source)
    {
        if(RB6_InterruptHandler_High)
        {
            RB6_InterruptHandler_High();
        }
    }
    else
    {
        /* Nothing */
    }
}

void RB7_ISR(uint8 RB7_source)
{
    INTERRUPT_RBx_FLAG_CLEAR();
    
    if(GPIO_LOW == RB7_source)
    {
        if(RB7_InterruptHandler_Low)
        {
            RB7_InterruptHandler_Low();
        }
    }
    else if(GPIO_HIGH == RB7_source)
    {
        if(RB7_InterruptHandler_High)
        {
            RB7_InterruptHandler_High();
        }
    }
    else
    {
        /* Nothing */
    }
}


/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_INTx_DeInitialize(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_RBx_Initialize(const interrupt_RBx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
/* This routine clears the interrupt disable for the external interrupt, RBx */
        INTERRUPT_RBx_DISABLE();
/* This routine clears the interrupt flag for the external interrupt, RBx */
        INTERRUPT_RBx_FLAG_CLEAR();
/* This routine determine the interrupt priority, RBx */
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if(INTERRUPT_PRIORITY_LOW == int_obj->priority){
            INTERRUPT_LOW_PRIORITY_ENABLE();
            INTERRUPT_RBx_PRIORITY_LOW(); 
        }
        else if(INTERRUPT_PRIORITY_HIGH == int_obj->priority){ 
            INTERRUPT_HIGH_PRIORITY_ENABLE();
            INTERRUPT_RBx_PRIORITY_HIGH(); 
        }
        else { /* Nothing */}
        
#else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERLAS_ENABLE();
#endif
/* this routine determine the pin to be I/O*/
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
/* This routine set the interrupt call back function, RBx */
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 : 
                RB4_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                RB4_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                break;
            case GPIO_PIN5 : 
                RB5_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                RB5_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                break;
            case GPIO_PIN6 : 
                RB6_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                RB6_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                break;
            case GPIO_PIN7 : 
                RB7_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                RB7_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                break;
            default : ret = E_NOT_OK;
        }
/* This routine set the interrupt enable for the external interrupt, RBx */
        INTERRUPT_RBx_ENABLE();     
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_RBx_DeInitialize(const interrupt_RBx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INTERRUPT_RBx_DISABLE();
        INTERRUPT_RBx_FLAG_CLEAR();
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_Enable(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT0 : 
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
                INTERRUPT_HIGH_PRIORITY_ENABLE();
#else
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_PERIPHERLAS_ENABLE();
#endif
                INTERRUPT_INT0_ENABLE();
                break; 
            case INTERRUPT_INT1 : 
 #if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
                INTERRUPT_PRIORITY_LEVELS_ENABLE();
                if(INTERRUPT_PRIORITY_LOW == int_obj->priority){
                    INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else if(INTERRUPT_PRIORITY_HIGH == int_obj->priority){
                    INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_PERIPHERLAS_ENABLE();
#endif
                INTERRUPT_INT1_ENABLE(); 
                break;
            case INTERRUPT_INT2 : 
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
                INTERRUPT_PRIORITY_LEVELS_ENABLE();
                if(INTERRUPT_PRIORITY_LOW == int_obj->priority){
                    INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else if(INTERRUPT_PRIORITY_HIGH == int_obj->priority){
                    INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GLOBAL_ENABLE();
                INTERRUPT_PERIPHERLAS_ENABLE();
#endif
                INTERRUPT_INT2_ENABLE();
                break;
            default : ret = E_NOT_OK;
        }
    }
   
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_Disable(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT0 : 
                INTERRUPT_INT0_DISABLE();
                break; 
            case INTERRUPT_INT1 : 
                INTERRUPT_INT1_DISABLE(); 
                break;
            case INTERRUPT_INT2 : 
                INTERRUPT_INT2_DISABLE();
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static Std_Return_Type Interrupt_INTx_Priority_Init(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT1 : 
                if(INTERRUPT_PRIORITY_LOW == int_obj->priority)        { INTERRUPT_INT1_PRIORITY_LOW();  }
                else if(INTERRUPT_PRIORITY_HIGH == int_obj->priority)  { INTERRUPT_INT1_PRIORITY_HIGH(); }
                else { /* Nothing */}
                break;
            case INTERRUPT_INT2 : 
                if(INTERRUPT_PRIORITY_LOW == int_obj->priority)        { INTERRUPT_INT2_PRIORITY_LOW();  }
                else if(INTERRUPT_PRIORITY_HIGH == int_obj->priority)  { INTERRUPT_INT2_PRIORITY_HIGH(); }
                else { /* Nothing */}
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_Edge_Init(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)        { INTERRUPT_INT0_FALLING_EDGE(); }
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge)   { INTERRUPT_INT0_RAISING_EDGE(); }
                else { /* Nothing */}
                break;
            case INTERRUPT_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)        { INTERRUPT_INT1_FALLING_EDGE(); }
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge)   { INTERRUPT_INT1_RAISING_EDGE(); }
                else { /* Nothing */}
                break;
            case INTERRUPT_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)        { INTERRUPT_INT2_FALLING_EDGE(); }
                else if(INTERRUPT_RAISING_EDGE == int_obj->edge)   { INTERRUPT_INT2_RISING_EDGE();  }
                else { /* Nothing */}
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_Pin_Init(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_Clear_Flag(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT0 : 
                INTERRUPT_INT0_FLAG_CLEAR();
                break;
            case INTERRUPT_INT1 : 
                INTERRUPT_INT1_FLAG_CLEAR();
                break;
            case INTERRUPT_INT2 : 
                INTERRUPT_INT2_FLAG_CLEAR();
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param INT0_InterruptHandler
 * @return 
 */
static Std_Return_Type INT0_SetInterruptHandler(void(*InterruptHandler)(void))
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
    }
    
    return ret;
}

/**
 * 
 * @param INT1_InterruptHandler
 * @return 
 */
static Std_Return_Type INT1_SetInterruptHandler(void(*InterruptHandler)(void))
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
    }
    
    return ret;
}

/**
 * 
 * @param INT2_InterruptHandler
 * @return 
 */
static Std_Return_Type INT2_SetInterruptHandler(void(*InterruptHandler)(void))
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
    }
    
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_Return_Type Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_T *int_obj)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_INT0 : 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT1 : 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT2 : 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}