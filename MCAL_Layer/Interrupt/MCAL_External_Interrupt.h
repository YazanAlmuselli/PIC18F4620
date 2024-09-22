/* 
 * File:   MCAL_External_Interrupt.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:15 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* ----------------- Includes -----------------*/
#include "MCAL_Interrupt_CFG.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#if EXTERNAL_INTERRUPT_INTx_ENABLE
/* This routine clears the interrupt disable for the external interrupt, INT0 */
#define INTERRUPT_INT0_DISABLE()         (INTCONbits.INT0IE = 0)
/* This routine set the interrupt enable for the external interrupt, INT0 */
#define INTERRUPT_INT0_ENABLE()          (INTCONbits.INT0IE = 1)

/* This routine clears the interrupt flag for the external interrupt, INT0 */
#define INTERRUPT_INT0_FLAG_CLEAR()      (INTCONbits.INT0IF = 0)

/* This routine clear the edge detect of the extern interrupt to negative edge */
#define INTERRUPT_INT0_FALLING_EDGE()     (INTCON2bits.INTEDG0 = 0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define INTERRUPT_INT0_RAISING_EDGE()    (INTCON2bits.INTEDG0 = 1)


/* This routine clears the interrupt disable for the external interrupt, INT1 */
#define INTERRUPT_INT1_DISABLE()         (INTCON3bits.INT1IE = 0)
/* This routine set the interrupt enable for the external interrupt, INT1 */
#define INTERRUPT_INT1_ENABLE()          (INTCON3bits.INT1IE = 1)

/* This routine clears the interrupt flag for the external interrupt, INT1 */
#define INTERRUPT_INT1_FLAG_CLEAR()      (INTCON3bits.INT1IF = 0)

/* This routine clear the edge detect of the extern interrupt to negative edge */
#define INTERRUPT_INT1_FALLING_EDGE()     (INTCON2bits.INTEDG1 = 0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define INTERRUPT_INT1_RAISING_EDGE()    (INTCON2bits.INTEDG1 = 1)


/* This routine clears the interrupt disable for the external interrupt, INT2 */
#define INTERRUPT_INT2_DISABLE()         (INTCON3bits.INT2IE = 0)
/* This routine set the interrupt enable for the external interrupt, INT2 */
#define INTERRUPT_INT2_ENABLE()          (INTCON3bits.INT2IE = 1)

/* This routine clears the interrupt flag for the external interrupt, INT2 */
#define INTERRUPT_INT2_FLAG_CLEAR()      (INTCON3bits.INT2IF = 0)

/* This routine clear the edge detect of the extern interrupt to negative edge */
#define INTERRUPT_INT2_FALLING_EDGE()     (INTCON2bits.INTEDG2 = 0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define INTERRUPT_INT2_RISING_EDGE()    (INTCON2bits.INTEDG2 = 1)

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
/* This routine clear the INT1 External Interrupt Priority to be low priority */
#define INTERRUPT_INT1_PRIORITY_LOW()   (INTCON3bits.INT1IP = 0)
/* This routine set the INT1 External Interrupt Priority to be High priority */
#define INTERRUPT_INT1_PRIORITY_HIGH()   (INTCON3bits.INT1IP = 1)

/* This routine clear the INT2 External Interrupt Priority to be low priority */
#define INTERRUPT_INT2_PRIORITY_LOW()   (INTCON3bits.INT2IP = 0)
/* This routine set the INT2 External Interrupt Priority to be High priority */
#define INTERRUPT_INT2_PRIORITY_HIGH()   (INTCON3bits.INT2IP = 1)

#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_ENABLE
/* This routine clears the interrupt disable for the external interrupt, RBx */
#define INTERRUPT_RBx_DISABLE()       (INTCONbits.RBIE = 0)
/* This routine set the interrupt enable for the external interrupt, RBx */
#define INTERRUPT_RBx_ENABLE()        (INTCONbits.RBIE = 1)

/* This routine clears the interrupt flag for the external interrupt, RBx */
#define INTERRUPT_RBx_FLAG_CLEAR()    (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
/* This routine set the RBx External Interrupt Priority to be Low priority */
#define INTERRUPT_RBx_PRIORITY_LOW()    (INTCON2bits.RBIP = 0)
/* This routine set the RBx External Interrupt Priority to be High priority */
#define INTERRUPT_RBx_PRIORITY_HIGH()    (INTCON2bits.RBIP = 1)

#endif

#endif

/* ----------------- Data Type Declarations -----------------*/
typedef void(*InterruptHandler)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE        
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_INT0 = 0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
}interrupt_INTx_src;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_src source;
    interrupt_INTx_edge edge;
    interrupt_priority_cfg priority;
}interrupt_INTx_T;

typedef struct{
    void (* EXT_InterruptHandler_Low)(void);
    void (* EXT_InterruptHandler_High)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_T;

/* ----------------- Software Interfaces Declarations -----------------*/

/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_INTx_Initialize(const interrupt_INTx_T *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_INTx_DeInitialize(const interrupt_INTx_T *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_RBx_Initialize(const interrupt_RBx_T *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_Return_Type Interrupt_RBx_DeInitialize(const interrupt_RBx_T *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

