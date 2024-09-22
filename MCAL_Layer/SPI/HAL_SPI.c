/* 
 * File:   HAL_SPI.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on September 10, 2023, 3:07 PM
 */

#include "HAL_SPI.h"

#if MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
static void MSSP_SPI_Master_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);

Std_Return_Type SPI_Init(const SPI_Config *Config){
    Std_Return_Type ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if((Config->spi_mode == SPI_MASTER_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV16) ||
            (Config->spi_mode == SPI_MASTER_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)){
            MSSP_SPI_Master_Mode_GPIO_PIN_Configurations(Config);
        }
        else if((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DISABLE)){
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        else{/* Nothing */}
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        /* SPI Clock Select */
         SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
        MSSP_SPI_Interrupt_Init(Config);
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }
    
    return ret;
}

Std_Return_Type SPI_DeInit(const SPI_Config *Config){
    Std_Return_Type ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
/* Interrupt Configurations */        
#if MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        MSSP_SPI_INTERRUPT_DISABLE();
#endif
    }
    
    return ret;
}

Std_Return_Type SPI_Send_Byte(const SPI_Config *Config, const uint8 _data){
    Std_Return_Type ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = _data;
        while(!(PIR1bits.SSPIF)); /* Waiting to transmit */
        PIR1bits.SSPIF = 0;
    }
    
    return ret;
}

Std_Return_Type SPI_Read_Byte(const SPI_Config *Config, uint8 *_data){
    Std_Return_Type ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        while(SSPSTATbits.BF == 0); /* Receive not complete, SSPBUF is empty */
        *_data = SSPBUF;
    }
    
    return ret;
}

Std_Return_Type SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data){
    Std_Return_Type ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        if(1 == SSPSTATbits.BF){
        SSPBUF = _data;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    
    return ret;
}

Std_Return_Type SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data){
    Std_Return_Type ret = E_OK;
    
    if((NULL == Config) || (NULL == _data)){
        ret = E_NOT_OK;
    }
    else{
        if(1 == SSPSTATbits.BF){
        *_data = SSPBUF;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    
    return ret;
}

void MSSP_SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    MSSP_SPI_INTERRUPT_FLAG_CLEAR();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config){
    /* Interrupt Configurations */        
#if MSSP_SPI_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    MSSP_SPI_INTERRUPT_ENABLE();
    MSSP_SPI_INTERRUPT_FLAG_CLEAR();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_HIGH_PRIORITY == Config->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        MSSP_SPI_INTERRUPT_PRIORITY_HIGH();
    }
    else if(INTERRUPT_LOW_PRIORITY == Config->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        MSSP_SPI_INTERRUPT_PRIORITY_LOW();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
#endif      
#endif        
}

static void MSSP_SPI_Master_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_Return_Type ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    
    ret = gpio_pin_direction_intialize(&SPI_SDO); 
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_CLK);
}

static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_Return_Type ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};
    
    ret = gpio_pin_direction_intialize(&SPI_SDO); 
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_CLK); 
    
    if(SPI_SLAVE_SS_ENABLE == Config->spi_mode){
        ret = gpio_pin_direction_intialize(&SPI_SS);
    }
}