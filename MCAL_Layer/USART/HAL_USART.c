/* 
 * File:   HAL_USART.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on September 6, 2023, 4:01 PM
 */

#include "HAL_USART.h"

static void EUSART_Baud_Rate_Calculations(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*EUSART_TX_InterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*EUSART_RX_InterruptHandler)(void) = NULL;
static void (*EUSART_RxOverrunError_InterruptHandler)(void) = NULL;
static void (*EUSART_RxFramingError_InterruptHandler)(void) = NULL;
#endif

Std_Return_Type EUSART_ASYNC_Init(const usart_t *_eusart){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        EUSART_Baud_Rate_Calculations(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_DeInit(const usart_t *_eusart){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        EUSART_MODULE_DISABLE;
    }
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_ReadByteBlocking(uint8 *_data){
    Std_Return_Type ret = E_OK;
    
    while(!PIR1bits.RCIF);
    *_data = RCREG;
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data){
    Std_Return_Type ret = E_OK;
    
    if(1 == PIR1bits.RCIF){
        *_data = RCREG;
    }
    else{
        ret = E_NOT_OK;
    }
    
    return ret;
}
/* Use When OverRun Error ISR being Executed */
Std_Return_Type EUSART_ASYNC_Rx_OverRun_Flag_Clear(void){
    Std_Return_Type ret = E_OK;
    
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
            
    return ret;
}
/* Use When Framing Error ISR being Executed */
Std_Return_Type EUSART_ASYNC_Rx_FramingError_Flag_Clear(void){
    Std_Return_Type ret = E_OK;
    uint8 temp = 0;
    
    temp = RCREG;
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_WriteByteBlocking(uint8 _data){
    Std_Return_Type ret = E_OK;
    
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    EUSART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _data;
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len){
    Std_Return_Type ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    
    for(char_counter = ZERO_INIT; char_counter < str_len; char_counter++){
        ret = EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
    }
    
    return ret;
}

Std_Return_Type EUSART_ASYNC_WriteByteNonBlocking(uint8 _data){
    Std_Return_Type ret = E_OK;
    
    if(1 == TXSTAbits.TRMT){
#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    EUSART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _data;
    }
    else{
        ret = E_NOT_OK;
    }

    return ret;
}
Std_Return_Type EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    Std_Return_Type ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    
    if(1 == TXSTAbits.TRMT){
        for(char_counter = ZERO_INIT; char_counter < str_len; char_counter++){
        ret = EUSART_ASYNC_WriteByteBlocking(_data[char_counter]);
        }
    }
    else{
        ret = E_NOT_OK;
    }

    return ret;
}

static void EUSART_Baud_Rate_Calculations(const usart_t *_eusart){
    float Baud_Rate_Temp = 0;
    
    switch(_eusart->baudrate_gen_gonfig){
        case BAUDRATE_ASYN_8BIT_lOW_SPEED: 
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED: 
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED: 
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED: 
            TXSTAbits.SYNC    = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH    = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT: 
            TXSTAbits.SYNC    = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT: 
            TXSTAbits.SYNC    = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = (((_XTAL_FREQ) / (_eusart->baudrate)) / 4) - 1;
            break;
        default : ;
    }
    SPBRG = (uint8)((uint16)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint16)Baud_Rate_Temp) >> 8);
}

static void EUSART_ASYNC_TX_Init(const usart_t *_eusart){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
/* Interrupt Configurations */
#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
            EUSART_TX_INTERRUPT_ENABLE();
            EUSART_TX_InterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
/* Interrupt priority Configurations */    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(INTERRUPT_PRIORITY_LOW == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_LOW_PRIORITY_ENABLE();
                EUSART_TX_INTERRUPT_PRIORITY_LOW();
            }
            else if(INTERRUPT_PRIORITY_HIGH == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_HIGH_PRIORITY_ENABLE();
                EUSART_TX_INTERRUPT_PRIORITY_HIGH();
            }
            else{ /* Nothing */ }

#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERLAS_ENABLE();
#endif
    
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{ /* Nothing */ }
        /* EUSART  9-Bit Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static void EUSART_ASYNC_RX_Init(const usart_t *_eusart){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        /* EUSART Receiver Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
/* Interrupt Configurations */
#if EUSART_RX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
            EUSART_RX_INTERRUPT_ENABLE();
            EUSART_RX_InterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
            EUSART_RxOverrunError_InterruptHandler = _eusart->EUSART_OverrunErrorHandler;
            EUSART_RxFramingError_InterruptHandler = _eusart->EUSART_FramingErrorHandler;
/* Interrupt priority Configurations */    
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(INTERRUPT_PRIORITY_LOW == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_LOW_PRIORITY_ENABLE();
                EUSART_RX_INTERRUPT_PRIORITY_LOW();
            }
            else if(INTERRUPT_PRIORITY_HIGH == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_HIGH_PRIORITY_ENABLE();
                EUSART_RX_INTERRUPT_PRIORITY_HIGH();
            }
            else{
                /* Nothing */
            }

#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERLAS_ENABLE();
#endif
    
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{
            /* Nothing */
        }
        /* EUSART  9-Bit Receiver Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        }
        else{
            /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}

void EUSART_TX_ISR(void){
#if EUSART_TX_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    EUSART_TX_INTERRUPT_DISABLE();
#endif
    if(EUSART_TX_InterruptHandler)
    {
        EUSART_TX_InterruptHandler();
    }
    else{ /* Nothing */ }
}

void EUSART_RX_ISR(void){
    if(EUSART_RX_InterruptHandler)
    {
        EUSART_RX_InterruptHandler();
    }
    else{ /* Nothing */ }
    if(EUSART_RxOverrunError_InterruptHandler)
    {
        EUSART_RxOverrunError_InterruptHandler();
    }
    else{ /* Nothing */ }
    if(EUSART_RxFramingError_InterruptHandler)
    {
        EUSART_RxFramingError_InterruptHandler();
    }
    else{ /* Nothing */ }
}