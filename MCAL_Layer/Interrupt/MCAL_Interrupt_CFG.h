/* 
 * File:   MCAL_Interrupt_CFG.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:18 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/* ----------------- Includes -----------------*/
#include "../MCAL_STD_Types.h"
#include "MCAL_Interrupt_GEN_CFG.h"
#include "../../MCAL_Layer/HAL_GPIO.h"

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0

#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0

#define INTERRUPT_HIGH_PRIORITY     1
#define INTERRUPT_LOW_PRIORITY      0

/* ----------------- Macro Functions Declarations -----------------*/
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
/* This macro will enable priority levels on interrupts. */
#define INTERRUPT_PRIORITY_LEVELS_ENABLE()      (RCONbits.IPEN = 1)
/* This macro will disable priority levels on interrupts. */
#define INTERRUPT_PRIORITY_LEVELS_DISABLE()      (RCONbits.IPEN = 0)

/* This macro will enable high priority global interrupts. */
#define INTERRUPT_HIGH_PRIORITY_ENABLE()        (INTCONbits.GIEH = 1)
/* This macro will disable high priority global interrupts. */
#define INTERRUPT_HIGH_PRIORITY_DISABLE()       (INTCONbits.GIEH = 0)


/* This macro will enable low priority global interrupts. */
#define INTERRUPT_LOW_PRIORITY_ENABLE()         (INTCONbits.GIEL = 1)
/* This macro will disable low priority global interrupts. */
#define INTERRUPT_LOW_PRIORITY_DISABLE()        (INTCONbits.GIEL = 0)

#else
/* This macro will enable global interrupts. */
#define INTERRUPT_GLOBAL_ENABLE()               (INTCONbits.GIE = 1)
/* This macro will disable global interrupts. */
#define INTERRUPT_GLOBAL_DISABLE()              (INTCONbits.GIE = 0)

/* This macro will enable peripheral interrupts. */
#define INTERRUPT_PERIPHERLAS_ENABLE()          (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts. */
#define INTERRUPT_PERIPHERLAS_DISABLE()         (INTCONbits.PEIE = 0)  

#endif

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    INTERRUPT_PRIORITY_LOW = 0,
    INTERRUPT_PRIORITY_HIGH
}interrupt_priority_cfg;

/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* MCAL_INTERRUPT_CFG_H */

