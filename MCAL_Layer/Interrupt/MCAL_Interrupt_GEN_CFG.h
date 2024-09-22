/* 
 * File:   MCAL_Interrupt_GEN_CFG.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 6:22 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* ----------------- Includes -----------------*/

/* ----------------- Macro Declarations -----------------*/
#define ENABLED                               1
#define DISABLED                              0
//#define INTERRUPT_PRIORITY_LEVEL_GEN          ENABLED

#define EXTERNAL_INTERRUPT_INTx_ENABLE        ENABLED
#define EXTERNAL_INTERRUPT_OnChange_ENABLE    ENABLED

#define ADC_INTERRUPT_PRIORITY_LEVEL_GEN      ENABLED

#define TIMER0_INTERRUPT_PRIORITY_LEVEL_GEN   ENABLED
#define TIMER1_INTERRUPT_PRIORITY_LEVEL_GEN   ENABLED
#define TIMER2_INTERRUPT_PRIORITY_LEVEL_GEN   ENABLED
#define TIMER3_INTERRUPT_PRIORITY_LEVEL_GEN   ENABLED

#define CCP1_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED
#define CCP2_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED

#define EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED
#define EUSART_RX_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED

#define MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED
#define MSSP_I2C_INTERRUPT_PRIORITY_LEVEL_GEN     ENABLED

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

