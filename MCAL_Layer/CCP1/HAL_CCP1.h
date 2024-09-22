/* 
 * File:   HAL_CCP1.h
 * Author: Yazan Abd-Almajeed
 * Created on September 2, 2023, 11:43 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* ----------------- Includes -----------------*/
#include "CCP1_CFG.h"
#include "../HAL_GPIO.h"
#include "../MCAL_STD_Types.h"
#include "../../MCAL_Layer/Interrupt/MCAL_Internal_Interrupt.h"

/* ----------------- Macro Declarations -----------------*/

/* CCP1 Module Mode Select  */
#define CCP_MODULE_DISABLE                 ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP_PWM_MODE                       ((uint8)0x0C)

/* CCP1 Capture Mode State  */
#define CCP_CAPTURE_NOT_READY             0x00
#define CCP_CAPTURE_READY                 0x01

/* CCP1 Compare Mode State  */
#define CCP1_COMPARE_NOT_READY             0x00
#define CCP1_COMPARE_READY                 0x01

/* Post-Scaler Value */
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_1    1
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_2    2
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_3    3
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_4    4
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_5    5
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_6    6
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_7    7
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_8    8
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_9    9
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_10   10
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_11   11
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_12   12
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_13   13
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_14   14
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_15   15
#define CCP_TIMER2_POSTSCALER_VALUE_DIV_BY_16   16

/* Pre-Scaler Value */
#define CCP_TIMER2_PRESCALER_VALUE_DIV_BY_1    1
#define CCP_TIMER2_PRESCALER_VALUE_DIV_BY_4    4
#define CCP_TIMER2_PRESCALER_VALUE_DIV_BY_16   16

/* ----------------- Macro Functions Declarations -----------------*/
#define CCP1_SET_MODE(_CONFIG)      (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)      (CCP2CONbits.CCP2M = _CONFIG)

/* ----------------- Data Type Declarations -----------------*/

/*
  @Summary      Define the values to select the CCP1 Main mode
*/
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED
}ccp1_mode_t;


typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_Capture_timer_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union{
    struct{
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct{
        uint16 ccp_16Bit;
    };
}CCP_REGISTER_T;

/*
  @Summary      CCP Module configurations
  @Description  This data type used to describe the module initialization configuration
*/
typedef struct{
    ccp_inst_t ccp_inst;
    ccp1_mode_t ccp_mode;       /* CCP main mode */
    uint8 ccp_mode_variant;     /* CCP selected mode variant */
    pin_config_t ccp_pin;       /* CCP Pin I/O configurations */
    ccp_Capture_timer_t ccp_Capture_timer;
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
    uint32 PWM_Freq;            /* CCP PWM mode frequency */
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
#endif
#if CCP1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*CCP1_InterruptHandler)(void);         /* Call back used for all CCP1 Modes */
    interrupt_priority_cfg CCP1_priority;       /* Configure the CCP1 mode interrupt */
#endif
#if CCP2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    void(*CCP2_InterruptHandler)(void);         /* Call back used for all CCP2 Modes */
    interrupt_priority_cfg CCP2_priority;       /* Configure the CCP2 mode interrupt */
#endif
    
}ccp_t;

/* ----------------- Software Interfaces Declarations -----------------*/

Std_Return_Type CCP_Init(const ccp_t *_ccp_obj);
Std_Return_Type CCP_DeInit(const ccp_t *_ccp_obj);

#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED
Std_Return_Type CCP_IsCapturedDataReady(const ccp_t *_ccp_obj, uint8 *_capture_status);
Std_Return_Type CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj, uint16 *capture_value);
#endif

#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_COMPARE_MODE_SELECTED
Std_Return_Type CCP_IsComparedDataReady(const ccp_t *_ccp_obj, uint8 *_compare_status);
Std_Return_Type CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16 compare_value);
#endif

#if CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED
Std_Return_Type CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint8 _duty);
Std_Return_Type CCP_PWM_Start(const ccp_t *_ccp_obj);
Std_Return_Type CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif

#endif	/* HAL_CCP1_H */

