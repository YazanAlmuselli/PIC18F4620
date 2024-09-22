/* 
 * File:   HAL_USART.h
 * Author: Yazan Abd-Almajeed
 *
 * Created on September 6, 2023, 4:01 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* ----------------- Includes -----------------*/
#include "HAL_USART_CFG.h"
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable : 1;
	uint8 usart_tx_9bit_enable : 1;
	uint8 usart_tx_interrupt_enable : 1;
    interrupt_priority_cfg usart_tx_int_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable : 1;
	uint8 usart_rx_9bit_enable : 1;
	uint8 usart_rx_interrupt_enable : 1;
    interrupt_priority_cfg usart_rx_int_priority;
}usart_rx_cfg_t;

typedef union{
    struct{
        uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct{
    float baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t usart_error_status;
    void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return_Type EUSART_ASYNC_Init(const usart_t *_eusart);
Std_Return_Type EUSART_ASYNC_DeInit(const usart_t *_eusart);

Std_Return_Type EUSART_ASYNC_ReadByteBlocking(uint8 *_data);
Std_Return_Type EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);
Std_Return_Type EUSART_ASYNC_Rx_OverRun_Flag_Clear(void);
Std_Return_Type EUSART_ASYNC_Rx_FramingError_Flag_Clear(void);

Std_Return_Type EUSART_ASYNC_WriteByteBlocking(uint8 _data);
Std_Return_Type EUSART_ASYNC_WriteStringBlocking(uint8 *_data, uint16 str_len);
Std_Return_Type EUSART_ASYNC_WriteByteNonBlocking(uint8 _data);
Std_Return_Type EUSART_ASYNC_WriteStringNonBlocking(uint8 *_data, uint16 str_len);

#endif	/* HAL_USART_H */

