/* 
 * File:   HAL_CCP1.c
 * Author: Yazan Abd-Almajeed
 * Created on September 2, 2023, 11:43 AM
 */

/* ----------------- Includes -----------------*/
#include "HAL_CCP1.h"

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj);
static Std_Return_Type CCP_Capture_Mode_Config(const ccp_t *_ccp_obj);
static Std_Return_Type CCP_Compare_Mode_Config(const ccp_t *_ccp_obj);

#if CCP1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*CCP1_InterruptHandler)(void) = NULL;
#endif

#if CCP2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*CCP2_InterruptHandler)(void) = NULL;
#endif

Std_Return_Type CCP_Init(const ccp_t *_ccp_obj){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else{/* Nothing */}
        
        /* CCP Module Capture Mode Initialization */
        if(CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Capture_Mode_Config(_ccp_obj);
        }
        /* CCP Module Compare Mode Initialization */
        else if(CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            CCP_Compare_Mode_Config(_ccp_obj);
        }
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
        /* CCP Module PWM Mode Initialization */
        else if(CCP1_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            CCP_PWM_Mode_Config(_ccp_obj);
        }
#endif
        else{ /*Nothing*/ }
        /* PIN Configurations */
        ret = gpio_pin_intialize(&(_ccp_obj->ccp_pin));
        /* Interrupt Configurations for CCP1 and CCP2 Modules */
        CCP_Interrupt_Config(_ccp_obj);
    }
    
    return ret;
}

Std_Return_Type CCP_DeInit(const ccp_t *_ccp_obj){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
/* Interrupt Configurations */ 
#if CCP1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        CCP1_INTERRUPT_DISABLE();   /* CCP1 Module Disable */
#endif
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        CCP2_INTERRUPT_DISABLE();   /* CCP2 Module Disable */
#endif
        }
        else{/* Nothing */}
    }
    
    return ret;
}


#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED
Std_Return_Type CCP_IsCapturedDataReady(const ccp_t *_ccp_obj, uint8 *_capture_status){
    Std_Return_Type ret = E_OK;
    
    if((NULL == _capture_status) || (NULL == _capture_status)){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP_CAPTURE_READY;
            CCP1_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
            *_capture_status = CCP_CAPTURE_READY;
            CCP2_INTERRUPT_FLAG_CLEAR();
            }
            else{
                *_capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
        else{/* Nothing */}
        
    }
    
    return ret;
}

Std_Return_Type CCP_Capture_Mode_Read_Value(const ccp_t *_ccp_obj, uint16 *capture_value){
    Std_Return_Type ret = E_OK;
    
    if(NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
        /* Copy captured value */
        CCP_REGISTER_T capture_temp_value = {.ccp_low = 0, .ccp_high = 0};
        if(CCP1_INST == _ccp_obj->ccp_inst){
            capture_temp_value.ccp_low = CCPR1L;
            capture_temp_value.ccp_high = CCPR1H;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            capture_temp_value.ccp_low = CCPR2L;
            capture_temp_value.ccp_high = CCPR2H;
        }
        else{ /* Nothing */ }
        
        /* Write the 16-bit capture value */
        *capture_value = capture_temp_value.ccp_16Bit;
    }
    
    return ret;
}

#endif

#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_COMPARE_MODE_SELECTED
Std_Return_Type CCP_IsComparedDataReady(const ccp_t *_ccp_obj, uint8 *_compare_status){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _compare_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP1_COMPARE_READY;
            CCP1_INTERRUPT_FLAG_CLEAR();
        }
        else{
            *_compare_status = CCP1_COMPARE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

Std_Return_Type CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16 compare_value){
    Std_Return_Type ret = E_NOT_OK;
    CCP_REGISTER_T capture_temp_value = {.ccp_low = 0, .ccp_high = 0};
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Copy compared value */
        capture_temp_value.ccp_16Bit = compare_value;

        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccp_low;
            CCPR1H = capture_temp_value.ccp_high;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccp_low;
            CCPR2H = capture_temp_value.ccp_high;
        }
        else{ /* Nothing */ }
        
        ret = E_OK;
    }
    return ret;
}

#endif

#if CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED
Std_Return_Type CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint8 _duty){
    Std_Return_Type ret = E_OK;
    uint16 duty_temp = 0;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        duty_temp = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
        
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (uint8)(duty_temp & 0x0003);
            CCPR1L = (uint8)(duty_temp >> 2);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (uint8)(duty_temp & 0x0003);
            CCPR2L = (uint8)(duty_temp >> 2);
        }
        else{/* Nothing */}
    }
    
    return ret;
}

Std_Return_Type CCP_PWM_Start(const ccp_t *_ccp_obj){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{/* Nothing */}
    }
    
    return ret;
}

Std_Return_Type CCP_PWM_Stop(const ccp_t *_ccp_obj){
    Std_Return_Type ret = E_OK;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else{/* Nothing */}
    }
    
    return ret;
}

#endif

void CCP1_ISR(void){
    CCP1_INTERRUPT_FLAG_CLEAR();
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}

void CCP2_ISR(void){
    CCP2_INTERRUPT_FLAG_CLEAR();
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj){
    /* PWM Frequency Initialization */
    PR2 = (uint8) ((_XTAL_FREQ / (_ccp_obj->PWM_Freq * 4.0 * _ccp_obj->timer2_postscaler_value
            * _ccp_obj->timer2_prescaler_value)) - 1);
    if (CCP1_INST == _ccp_obj->ccp_inst) {
        if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant) {
            CCP1_SET_MODE(CCP_PWM_MODE);
        } else {
            /*Nothing*/
        }
    } else if (CCP2_INST == _ccp_obj->ccp_inst) {
        if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant) {
            CCP2_SET_MODE(CCP_PWM_MODE);
        } else {
            /*Nothing*/
        }
    } else {
        /* Nothing */
    }
}
#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
    /* CCP1 Interrupt Configurations */ 
#if CCP1_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    CCP1_INTERRUPT_ENABLE();
    CCP1_INTERRUPT_FLAG_CLEAR();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    /* Enables all high-priority interrupts */
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP1_priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_LOW_PRIORITY_ENABLE();
        CCP1_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP1_priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_HIGH_PRIORITY_ENABLE();
        CCP1_INTERRUPT_PRIORITY_HIGH();
    }
    else{
        /* Nothing */
    }
    
#else
    INTERRUPT_GLOBAL_ENABLE();
    INTERRUPT_PERIPHERLAS_ENABLE();
    
#endif
    
#endif
    
    /* CCP2 Interrupt Configurations */ 
#if CCP2_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    CCP2_INTERRUPT_ENABLE();
    CCP2_INTERRUPT_FLAG_CLEAR();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP2_priority){
        /* Enables all unmasked peripheral interrupts */
        CCP2_INTERRUPT_PRIORITY_LOW();
    }
    else if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP2_priority){
        CCP2_INTERRUPT_PRIORITY_HIGH();
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

static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj){
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
        
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_Capture_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}

static Std_Return_Type CCP_Capture_Mode_Config(const ccp_t *_ccp_obj) {
    Std_Return_Type ret = E_OK;

    if (CCP1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;
        }
    } else if (CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;
        }
    } else {
        /* Nothing */
    }

    CCP_Mode_Timer_Select(_ccp_obj);

    return ret;
}

static Std_Return_Type CCP_Compare_Mode_Config(const ccp_t *_ccp_obj) {
    Std_Return_Type ret = E_OK;

    if (CCP1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_COMPARE_MODE_SET_PIN_LOW: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default: ret = E_NOT_OK;
        }
    } else if (CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_Capture_timer) {
        switch (_ccp_obj->ccp_mode_variant) {
            case CCP_COMPARE_MODE_SET_PIN_LOW: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_GEN_EVENT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                break;
            default: ret = E_NOT_OK;
        }
    } else {
        /* Nothing */
    }

    CCP_Mode_Timer_Select(_ccp_obj);

    return ret;
}