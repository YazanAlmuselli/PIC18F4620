/* 
 * File:   MCAL_Internal_Interrupt.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:14 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* ----------------- Includes -----------------*/
#include "MCAL_Interrupt_CFG.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#if ADC_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable ADC interrupt */
    #define ADC_INTERRUPT_DISABLE()         (PIE1bits.ADIE = 0)
    /* This routine set the interrupt enable ADC interrupt */
    #define ADC_INTERRUPT_ENABLE()          (PIE1bits.ADIE = 1)

    /* This routine clears the interrupt flag of ADC interrupt */
    #define ADC_INTERRUPT_FLAG_CLEAR()      (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the ADC Interrupt Priority to be low priority */
    #define ADC_INTERRUPT_PRIORITY_LOW()   (IPR1bits.ADIP = 0)
    /* This routine clear the ADC Interrupt Priority to be wHigh priority */
    #define ADC_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.ADIP = 1)
#endif
#endif

#if TIMER0_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable TIMER0 interrupt */
    #define TIMER0_INTERRUPT_DISABLE()         (INTCONbits.TMR0IE = 0)
    /* This routine set the interrupt enable TIMER0 interrupt */
    #define TIMER0_INTERRUPT_ENABLE()          (INTCONbits.TMR0IE = 1)

    /* This routine clears the interrupt flag of TIMER0 interrupt */
    #define TIMER0_INTERRUPT_FLAG_CLEAR()      (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the TIMER0 Interrupt Priority to be low priority */
    #define TIMER0_INTERRUPT_PRIORITY_LOW()   (INTCON2bits.TMR0IP = 0)
    /* This routine clear the TIMER0 Interrupt Priority to be wHigh priority */
    #define TIMER0_INTERRUPT_PRIORITY_HIGH()   (INTCON2bits.TMR0IP = 1)
#endif
#endif

#if TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable TIMER1 interrupt */
    #define TIMER1_INTERRUPT_DISABLE()         (PIE1bits.TMR1IE = 0)
    /* This routine set the interrupt enable TIMER1 interrupt */
    #define TIMER1_INTERRUPT_ENABLE()          (PIE1bits.TMR1IE = 1)

    /* This routine clears the interrupt flag of TIMER1 interrupt */
    #define TIMER1_INTERRUPT_FLAG_CLEAR()      (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the TIMER1 Interrupt Priority to be low priority */
    #define TIMER1_INTERRUPT_PRIORITY_LOW()   (IPR1bits.TMR1IP = 0)
    /* This routine clear the TIMER1 Interrupt Priority to be wHigh priority */
    #define TIMER1_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.TMR1IP = 1)
#endif
#endif

#if TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable TIMER2 interrupt */
    #define TIMER2_INTERRUPT_DISABLE()         (PIE1bits.TMR2IE = 0)
    /* This routine set the interrupt enable TIMER2 interrupt */
    #define TIMER2_INTERRUPT_ENABLE()          (PIE1bits.TMR2IE = 1)

    /* This routine clears the interrupt flag of TIMER2 interrupt */
    #define TIMER2_INTERRUPT_FLAG_CLEAR()      (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the TIMER2 Interrupt Priority to be low priority */
    #define TIMER2_INTERRUPT_PRIORITY_LOW()   (IPR1bits.TMR2IP = 0)
    /* This routine clear the TIMER2 Interrupt Priority to be wHigh priority */
    #define TIMER2_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.TMR2IP = 1)
#endif
#endif

#if TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable TIMER3 interrupt */
    #define TIMER3_INTERRUPT_DISABLE()         (PIE2bits.TMR3IE = 0)
    /* This routine set the interrupt enable TIMER3 interrupt */
    #define TIMER3_INTERRUPT_ENABLE()          (PIE2bits.TMR3IE = 1)

    /* This routine clears the interrupt flag of TIMER3 interrupt */
    #define TIMER3_INTERRUPT_FLAG_CLEAR()      (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the TIMER3 Interrupt Priority to be low priority */
    #define TIMER3_INTERRUPT_PRIORITY_LOW()   (IPR2bits.TMR3IP = 0)
    /* This routine clear the TIMER3 Interrupt Priority to be wHigh priority */
    #define TIMER3_INTERRUPT_PRIORITY_HIGH()   (IPR2bits.TMR3IP = 1)
#endif
#endif

#if CCP1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable CCP1 interrupt */
    #define CCP1_INTERRUPT_DISABLE()         (PIE1bits.CCP1IE = 0)
    /* This routine set the interrupt enable CCP1 interrupt */
    #define CCP1_INTERRUPT_ENABLE()          (PIE1bits.CCP1IE = 1)

    /* This routine clears the interrupt flag of CCP1 interrupt */
    #define CCP1_INTERRUPT_FLAG_CLEAR()      (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the CCP1 Interrupt Priority to be low priority */
    #define CCP1_INTERRUPT_PRIORITY_LOW()   (IPR1bits.CCP1IP = 0)
    /* This routine clear the CCP1 Interrupt Priority to be wHigh priority */
    #define CCP1_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.CCP1IP = 1)
#endif
#endif

#if CCP2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable CCP2 interrupt */
    #define CCP2_INTERRUPT_DISABLE()         (PIE2bits.CCP2IE = 0)
    /* This routine set the interrupt enable CCP2 interrupt */
    #define CCP2_INTERRUPT_ENABLE()          (PIE2bits.CCP2IE = 1)

    /* This routine clears the interrupt flag of CCP2 interrupt */
    #define CCP2_INTERRUPT_FLAG_CLEAR()      (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the CCP2 Interrupt Priority to be low priority */
    #define CCP2_INTERRUPT_PRIORITY_LOW()   (IPR2bits.CCP2IP = 0)
    /* This routine clear the CCP2 Interrupt Priority to be wHigh priority */
    #define CCP2_INTERRUPT_PRIORITY_HIGH()   (IPR2bits.CCP2IP = 1)
#endif
#endif

#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable EUSART TX interrupt */
    #define EUSART_TX_INTERRUPT_DISABLE()         (PIE1bits.TXIE = 0)
    /* This routine set the interrupt enable EUSART TX interrupt */
    #define EUSART_TX_INTERRUPT_ENABLE()          (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the EUSART TX Interrupt Priority to be low priority */
    #define EUSART_TX_INTERRUPT_PRIORITY_LOW()   (IPR1bits.TXIP = 0)
    /* This routine clear the EUSART TX Interrupt Priority to be wHigh priority */
    #define EUSART_TX_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.TXIP = 1)
#endif
#endif

#if EUSART_RX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable EUSART RX interrupt */
    #define EUSART_RX_INTERRUPT_DISABLE()         (PIE1bits.RCIE = 0)
    /* This routine set the interrupt enable EUSART RX interrupt */
    #define EUSART_RX_INTERRUPT_ENABLE()          (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the EUSART RX Interrupt Priority to be low priority */
    #define EUSART_RX_INTERRUPT_PRIORITY_LOW()   (IPR1bits.RCIP = 0)
    /* This routine clear the EUSART RX Interrupt Priority to be wHigh priority */
    #define EUSART_RX_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.RCIP = 1)
#endif
#endif

#if MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable MSSP SPI interrupt */
    #define MSSP_SPI_INTERRUPT_DISABLE()         (PIE1bits.SSPIE = 0)
    /* This routine set the interrupt enable MSSP SPI interrupt */
    #define MSSP_SPI_INTERRUPT_ENABLE()          (PIE1bits.SSPIE = 1)

    /* This routine clears the interrupt flag of MSSP SPI interrupt */
    #define MSSP_SPI_INTERRUPT_FLAG_CLEAR()      (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the MSSP SPI Interrupt Priority to be low priority */
    #define MSSP_SPI_INTERRUPT_PRIORITY_LOW()   (IPR1bits.SSPIP = 0)
    /* This routine clear the MSSP SPI Interrupt Priority to be wHigh priority */
    #define MSSP_SPI_INTERRUPT_PRIORITY_HIGH()   (IPR1bits.SSPIP = 1)
#endif
#endif

#if MSSP_I2C_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clears the interrupt disable MSSP I2C interrupt */
    #define MSSP_I2C_INTERRUPT_DISABLE()         (PIE1bits.SSPIE = 0)
    #define MSSP_I2C_BUS_COL_INTERRUPT_DISABLE() (PIE2bits.BCLIE = 0)
    /* This routine set the interrupt enable MSSP I2C interrupt */
    #define MSSP_I2C_INTERRUPT_ENABLE()          (PIE1bits.SSPIE = 1)
    #define MSSP_I2C_BUS_COL_INTERRUPT_ENABLE()  (PIE2bits.BCLIE = 1)
    /* This routine clears the interrupt flag of MSSP I2C interrupt */
    #define MSSP_I2C_INTERRUPT_FLAG_CLEAR()      (PIR1bits.SSPIF = 0)
    #define MSSP_I2C_BUS_COL_FLAG_CLEAR()        (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* This routine clear the MSSP I2C Interrupt Priority to be low priority */
    #define MSSP_I2C_INTERRUPT_PRIORITY_LOW()           (IPR1bits.SSPIP = 0)
    #define MSSP_I2C_BUS_COL_INTERRUPT_PRIORITY_LOW()   (IPR2bits.BCLIP = 0)
    /* This routine clear the MSSP I2C Interrupt Priority to be wHigh priority */
    #define MSSP_I2C_INTERRUPT_PRIORITY_HIGH()          (IPR1bits.SSPIP = 1)
    #define MSSP_I2C_BUS_COL_INTERRUPT_PRIORITY_HIGH()  (IPR2bits.BCLIP = 1)
#endif
#endif

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

