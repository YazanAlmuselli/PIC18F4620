/* 
 * File:   HAL_ADC.c
 * Author: Yazan Abd-Almajeed
 *
 * Created on August 24, 2023, 3:25 PM
 */

#include "HAL_ADC.h"

#if ADC_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_port_configure(adc_channel_select_t Channel);
static inline void result_format_select(const adc_cfg_t *_adc);
static inline void voltage_reference_select(const adc_cfg_t *_adc);

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Init(const adc_cfg_t *_adc)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure Acquisition Time */
        ADCON2bits.ACQT = _adc->adc_acquisition_time;
        /* Configure Conversion Clock */
        ADCON2bits.ADCS = _adc->adc_conversion_clock;
        /* Configure Channel */
        ADCON0bits.CHS = _adc->adc_channel_select;
        adc_input_channel_port_configure(_adc->adc_channel_select);
        /* Configure Interrupt */
#if ADC_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_CLEAR();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        if(INTERRUPT_PRIORITY_LOW == _adc->priority){  
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_LOW_PRIORITY_ENABLE();
            ADC_INTERRUPT_PRIORITY_LOW();  
        }
        else if(INTERRUPT_PRIORITY_HIGH == _adc->priority) {  
            /* Enables all high-priority interrupts */
            INTERRUPT_HIGH_PRIORITY_ENABLE();
            ADC_INTERRUPT_PRIORITY_HIGH(); 
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERLAS_ENABLE();
#endif
#endif
        /* Configure Result Format */
        result_format_select(_adc);
        
        /* Configure Voltage Reference */
        voltage_reference_select(_adc);
        
        /* Enable ADC */
        ADC_CONVERTER_ENABLE();
    }
    
    return ret;
}

/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_DeInit(const adc_cfg_t *_adc)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure Interrupt */
        #if ADC_INTERRUPT_PRIORITY_LEVEL_GEN==ENABLED
        ADC_INTERRUPT_DISABLE();
        #endif
    }
    
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Channel_select(const adc_cfg_t *_adc, adc_channel_select_t Channel)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADCON0bits.CHS = Channel;
        adc_input_channel_port_configure(Channel);
    }
    
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Start_Conversion(const adc_cfg_t *_adc)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_CONVERION_START();
    }
    
    return ret;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Conversion_Status(const adc_cfg_t *_adc, uint8 *conversion_status)
{
    Std_Return_Type ret = E_OK;
    
    if((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Save_Result(const adc_cfg_t *_adc, adc_result_t *conversion_result)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_result = (uint16)(((ADRESH << 8) + (ADRESL)) >> 6);
        }
        else
        {
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
    }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Get_Conversion_Blocking(const adc_cfg_t *_adc, adc_channel_select_t Channel,
                                   adc_result_t *conversion_result)
{
    Std_Return_Type ret = E_OK;
    
    if((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Select Channel */
        ret = ADC_Channel_select(_adc, Channel);
        /* Start Conversion */
        ret = ADC_Start_Conversion(_adc);
        /* Check Conversion Status */
        while(ADCON0bits.GO_nDONE);
        /* Save Result */
        ret = ADC_Save_Result(_adc, conversion_result);
    }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_Return_Type ADC_Start_Conversion_Interrupt(const adc_cfg_t *_adc, adc_channel_select_t Channel)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Select Channel */
        ret = ADC_Channel_select(_adc, Channel);
        /* Start Conversion */
        ret = ADC_Start_Conversion(_adc);
    }
    
    return ret;
}

static inline void adc_input_channel_port_configure(adc_channel_select_t Channel) {
    switch (Channel) {
        case ADC_CHANNEL_AN0: SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1: SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2: SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3: SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4: SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5: SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6: SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7: SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8: SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9: SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        default : /* Nothing */ ;
    }
}

static inline void result_format_select(const adc_cfg_t *_adc)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_RESULT_RIGHT == _adc->result_format)
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
        else if(ADC_RESULT_LEFT == _adc->result_format)
        {
            ADC_RESULT_LEFT_FORMAT();
        }
        else
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
    }
}

static inline void voltage_reference_select(const adc_cfg_t *_adc)
{
    Std_Return_Type ret = E_OK;
    
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_ref)
        {
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_ref)
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        else
        {
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
    }
}

void ADC_ISR(void){
    ADC_INTERRUPT_FLAG_CLEAR();
    
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}