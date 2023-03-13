/******************************************************************************
* File Name: sensors.c
*
* Description: This file contains necessary functions to increase/decrease PWM
*              duty cycle either after detecting a touch on the CAPSENSE
*              slider/buttons or after recieving a POST command from html
*              web page.
*
*
********************************************************************************
* Copyright 2021-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "web_server.h"

 pwm_duty_t pwm_duty;

 /* PWM used to change LED brightness */
 cyhal_pwm_t pwm_led;

 /* Flag to indicate CAPSENSE scan completion */
 volatile bool capsense_scan_complete = false;

#ifdef ENABLE_TFT
    /* ADC used for Light sensor */
    cyhal_adc_t adc;

    /* Light sensor object */
    mtb_light_sensor_t light_sensor_obj;
#endif /* #ifdef ENABLE_TFT */

/********************************************************************************
 * Function Name: initialize_led
 ********************************************************************************
 * Summary:
 *  The function initializes a PWM resource for driving an LED.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  Returns CY_RSLT_SUCCESS when the PWM resource is successfully initialized.
 *
 *******************************************************************************/
uint32_t initialize_led(void)
{
    cy_rslt_t result;

    /* Initialize led using pwm */
    result = cyhal_pwm_init(&pwm_led, CYBSP_USER_LED, NULL);
    if (CY_RSLT_SUCCESS == result)
    {
        result = cyhal_pwm_set_duty_cycle(&pwm_led,
                                        GET_DUTY_CYCLE(MAX_DUTYCYCLE),
                                        PWM_LED_FREQ_HZ);
        if (CY_RSLT_SUCCESS == result)
        {
            result = cyhal_pwm_start(&pwm_led);
        }
    }
    return result;
}

#ifdef ENABLE_TFT
/********************************************************************************
 * Function Name: initialize_light_sensor
 ********************************************************************************
 * Summary:
 *  The function initializes adc and light sensor
 *
 * Parameters:
 *  void
 *
 * Return:
 *  uint32_t -Returns CY_RSLT_SUCCESS when the light sensor is successfully
 *            initialized.
 *
 *******************************************************************************/
uint32_t initialize_light_sensor(void)
{
    cy_rslt_t result;

    result = cyhal_adc_init(&adc, LIGHT_SENSOR_PIN, NULL);
    PRINT_AND_ASSERT(result, "ADC init error\r\n");

    result = mtb_light_sensor_init(&light_sensor_obj, &adc, LIGHT_SENSOR_PIN);
    PRINT_AND_ASSERT(result, "Light sensor init error\r\n");

    return result;
}
#endif /* #ifdef ENABLE_TFT */

/********************************************************************************
 * Function Name: capsense_isr
 ********************************************************************************
 * Summary:
 * Wrapper function for handling interrupts from CSD block.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  void
 *
 *******************************************************************************/
static void capsense_isr(void)
{
    Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);
}

/********************************************************************************
 * Function Name: capsense_callback
 ********************************************************************************
 * Summary:
 *  This functions sets the capsense_scan_complete flag to true when CAPSENSE scan
 *  is complete.
 *
 * Parameters:
 *  cy_stc_active_scan_sns_t * ptrActiveScan (unused)
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void capsense_callback(cy_stc_active_scan_sns_t * ptrActiveScan)
{
    capsense_scan_complete = true;
}

/********************************************************************************
 * Function Name: initialize_capsense
 ********************************************************************************
 * Summary:
 *  The function initializes CAPSENSE buttons and slider.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  uint32_t - Returns CY_RSLT_SUCCESS if CAPSENSE is successfully initialized.
 *
 *******************************************************************************/
uint32_t initialize_capsense(void)
{
    cy_rslt_t result;

    /* CAPSENSE interrupt configuration */
    const cy_stc_sysint_t CapSense_interrupt_config =
    {
            .intrSrc = CYBSP_CSD_IRQ,
            .intrPriority = CAPSENSE_INTR_PRIORITY,
    };

    /* Capture the CSD HW block and initialize it to the default state. */
    result = Cy_CapSense_Init(&cy_capsense_context);
    PRINT_AND_ASSERT(result, "CAPSENSE init error\r\n");

    /* Initialize CAPSENSE interrupt */
    Cy_SysInt_Init(&CapSense_interrupt_config, capsense_isr);
    NVIC_ClearPendingIRQ(CapSense_interrupt_config.intrSrc);
    NVIC_EnableIRQ(CapSense_interrupt_config.intrSrc);

    /* Initialize the CAPSENSE firmware modules. */
    result = Cy_CapSense_Enable(&cy_capsense_context);
    PRINT_AND_ASSERT(result, "CAPSENSE enable error\r\n");

    /* Assign a callback function to indicate end of CAPSENSE scan. */
    result = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E,
            capsense_callback, &cy_capsense_context);
    PRINT_AND_ASSERT(result, "register callback failed\r\n");

    return result;
}

/********************************************************************************
 * Function Name: adjust_led_brightness
 ********************************************************************************
 * Summary:
 *  The function drives the LED with the current duty cycle.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  Returns CY_RSLT_SUCCESS when the PWM is successfully initialized.
 *
 *******************************************************************************/
void adjust_led_brightness(void)
{
    cy_rslt_t result;
    xSemaphoreTakeRecursive(pwm_duty.xpwm_mutex, portMAX_DELAY);

    /* Drive the LED with brightness */
    result = cyhal_pwm_set_duty_cycle(&pwm_led, GET_DUTY_CYCLE(pwm_duty.duty), PWM_LED_FREQ_HZ);
    if (CY_RSLT_SUCCESS == result)
    {
        result = cyhal_pwm_start(&pwm_led);
    }
    xSemaphoreGiveRecursive(pwm_duty.xpwm_mutex);
}

/********************************************************************************
 * Function Name: adjust_led_brightness
 ********************************************************************************
 * Summary:
 *  The function increases PWM duty cycle by 10%.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void increase_duty_cycle(void)
{
    xSemaphoreTakeRecursive(pwm_duty.xpwm_mutex, portMAX_DELAY);
    pwm_duty.duty += ( pwm_duty.duty < (MAX_DUTYCYCLE - (DUTYCYCLE_INCREMENT - 1)) ) ? DUTYCYCLE_INCREMENT : 0;
    adjust_led_brightness();
    xSemaphoreGiveRecursive(pwm_duty.xpwm_mutex);
}

/********************************************************************************
 * Function Name: decrease_duty_cycle
 ********************************************************************************
 * Summary:
 *  The function decreases PWM duty cycle by 10%.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void decrease_duty_cycle(void)
{
    xSemaphoreTakeRecursive(pwm_duty.xpwm_mutex, portMAX_DELAY);
    pwm_duty.duty -= ( pwm_duty.duty > (MIN_DUTYCYCLE + (DUTYCYCLE_INCREMENT - 1)) ) ? DUTYCYCLE_INCREMENT : 0;
    adjust_led_brightness();
    xSemaphoreGiveRecursive(pwm_duty.xpwm_mutex);
}

/********************************************************************************
 * Function Name: set_duty_cycle
 ********************************************************************************
 * Summary:
 *  The function sets the PWM duty cycle.
 *
 * Parameters:
 *  duty_cycle - the duty cycle to be set.
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void set_duty_cycle(uint32_t duty_cycle)
{
    xSemaphoreTakeRecursive(pwm_duty.xpwm_mutex, portMAX_DELAY);
    if(duty_cycle < DUTYCYCLE_INCREMENT)
    {
        pwm_duty.duty = DUTYCYCLE_INCREMENT;
    }
    else
    {
        pwm_duty.duty = duty_cycle;
    }
    adjust_led_brightness();
    xSemaphoreGiveRecursive(pwm_duty.xpwm_mutex);
}

/********************************************************************************
 * Function Name: get_duty_cycle
 ********************************************************************************
 * Summary:
 *  This function returns the current duty cycle.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  uint8_t the current duty cycle.
 *
 *******************************************************************************/
uint8_t get_duty_cycle(void)
{
    uint8_t current_duty_cycle;

    xSemaphoreTakeRecursive(pwm_duty.xpwm_mutex, portMAX_DELAY);
    current_duty_cycle = pwm_duty.duty;
    xSemaphoreGiveRecursive(pwm_duty.xpwm_mutex);

    return current_duty_cycle;
}

/********************************************************************************
 * Function Name: process_touch
 ********************************************************************************
 * Summary:
 *  The function handles the touchs on CAPSENSE button and slider.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void process_touch(void)
{
    uint32_t button0_status;
    uint32_t button1_status;
    cy_stc_capsense_touch_t *slider_touch_info;
    uint16_t slider_pos;
    uint8_t slider_touch_status;

    uint32_t pwm_value = pwm_duty.duty;

    static uint32_t button0_status_prev;
    static uint32_t button1_status_prev;
    static uint16_t slider_pos_prev;

    /* Get button 0 status */
    button0_status = Cy_CapSense_IsSensorActive(
        CY_CAPSENSE_BUTTON0_WDGT_ID,
        CY_CAPSENSE_BUTTON0_SNS0_ID,
        &cy_capsense_context);

    /* Get button 1 status */
    button1_status = Cy_CapSense_IsSensorActive(
        CY_CAPSENSE_BUTTON1_WDGT_ID,
        CY_CAPSENSE_BUTTON1_SNS0_ID,
        &cy_capsense_context);

    /* Get slider status */
    slider_touch_info = Cy_CapSense_GetTouchInfo(
        CY_CAPSENSE_LINEARSLIDER0_WDGT_ID, &cy_capsense_context);
    slider_touch_status = slider_touch_info->numPosition;
    slider_pos = slider_touch_info->ptrPosition->x;

    /* Detect new touch on Button0 */
    if ((0u != button0_status) &&
        (0u == button0_status_prev))
    {
        decrease_duty_cycle();
    }

    /* Detect new touch on Button1 */
    if ((0u != button1_status) &&
        (0u == button1_status_prev))
    {
        increase_duty_cycle();
    }

    /* Detect the new touch on slider */
    if ((0 != slider_touch_status) &&
        (slider_pos != slider_pos_prev))
    {
        pwm_value = (slider_pos * 100)
                / cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LINEARSLIDER0_WDGT_ID].xResolution;
        set_duty_cycle(pwm_value);
    }

    /* Update previous touch status */
    button0_status_prev = button0_status;
    button1_status_prev = button1_status;
    slider_pos_prev = slider_pos;
}

/*******************************************************************************
* Function Name: initialize_sensors
********************************************************************************
* Summary:
*  Initializes ambient light sensor, CAPSENSE and LED. Updates duty cycle based
*  on user input.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void initialize_sensors(void)
{

    cy_rslt_t result;

    pwm_duty.duty = DEFAULT_DUTYCYCLE;

    pwm_duty.xpwm_mutex = xSemaphoreCreateRecursiveMutex();;

    result = initialize_led();
    PRINT_AND_ASSERT(result, "Failed to initialize led.\r\n");

    result = initialize_capsense();
    PRINT_AND_ASSERT(result, "Failed to initialize CAPSENSE\r\n");

#ifdef ENABLE_TFT
    result = initialize_light_sensor();
    PRINT_AND_ASSERT(result, "Failed to initialize light sensor\r\n");
#endif
    /* Initiate first scan */
    result = Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
    PRINT_AND_ASSERT(result, "CAPSENSE error\r\n");

    APP_INFO(("Please wait...\r\n"));
    while(CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(&cy_capsense_context));

    APP_INFO(("CAPSENSE ready, LED ready\r\n"));
}

/* [] END OF FILE */
