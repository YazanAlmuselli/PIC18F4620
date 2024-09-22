/* 
 * File:   MCAL_Interrupt_Manager.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 19, 2023, 4:24 PM
 */

#include "MCAL_Interrupt_Manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
void __interrupt() InterruptManage_High(void)
{
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }else{/*  Nothing */}
}

void __interrupt(low_priority) InterruptManage_Low(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }else{/*  Nothing */}
}
#else
void __interrupt() InterruptManage(void)
{
    /*------------------External Interrupt ISR start ----------------------*/
    /*------------------INTx Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }else{/*  Nothing */}
    /*------------------INTx Interrupt ISR End ----------------------*/
    /*------------------RBx Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_HIGH == PORTBbits.RB4) && (1 == RB4_Flag))
    {
        RB4_Flag = 0;
        RB4_ISR(1);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_LOW == PORTBbits.RB4) && (0 == RB4_Flag))
    {
        RB4_Flag = 1;
        RB4_ISR(0);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_HIGH == PORTBbits.RB5) && (1 == RB5_Flag))
    {
        RB5_Flag = 0;
        RB5_ISR(1);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_LOW == PORTBbits.RB5) && (0 == RB5_Flag))
    {
        RB5_Flag = 1;
        RB5_ISR(0);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_HIGH == PORTBbits.RB6) && (1 == RB6_Flag))
    {
        RB6_Flag = 0;
        RB6_ISR(1);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_LOW == PORTBbits.RB6) && (0 == RB6_Flag))
    {
        RB6_Flag = 1;
        RB6_ISR(0);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
        (GPIO_HIGH == PORTBbits.RB7) && (1 == RB7_Flag))
    {
        RB7_Flag = 0;
        RB7_ISR(1);
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (GPIO_LOW == PORTBbits.RB7) && (0 == RB7_Flag))
    {
        RB7_Flag = 1;
        RB7_ISR(0);
    }else{/*  Nothing */}
    /*------------------RBx Interrupt ISR End ----------------------*/
    /*------------------External Interrupt ISR End ----------------------*/
    /*------------------Internal Interrupt ISR start ----------------------*/
    /*------------------ADC Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }else{/*  Nothing */}
    /*------------------ADC Interrupt ISR End ----------------------*/
    /*------------------TIMERs Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }else{/*  Nothing */}
    /*------------------TIMERs Interrupt ISR End ----------------------*/
    /*------------------CCP Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }else{/*  Nothing */}
    /*------------------CCP Interrupt ISR End ----------------------*/
    /*------------------EUSART Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_TX_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_RX_ISR();
    }else{/*  Nothing */}
    /*------------------EUSART Interrupt ISR End ----------------------*/
    /*------------------MSSP Interrupt ISR Start ----------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        MSSP_SPI_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        MSSP_I2C_ISR();
    }else{/*  Nothing */}
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        MSSP_I2C_BC_ISR();
    }else{/*  Nothing */}
    /*------------------MSSP Interrupt ISR End ----------------------*/
}
#endif