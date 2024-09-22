/* 
 * File:   MCAL_Interrupt_Manager.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:17 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* ----------------- Includes -----------------*/
#include "MCAL_Interrupt_CFG.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_SPI_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

