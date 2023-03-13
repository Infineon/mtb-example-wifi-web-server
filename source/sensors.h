/******************************************************************************
* File Name: sensors.h
*
* Description: This file contains configuration parameters for configuring the
*              sensors.
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

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef SENSORS_H_
#define SENSORS_H_


/* PWM LED frequency in Hz */
#define PWM_LED_FREQ_HZ                                 (1000000lu)

/* Returns duty cycle */
#define GET_DUTY_CYCLE(x)                               (100 - x)

 /* Default LED dutycycle */
#define DEFAULT_DUTYCYCLE                               (50u)

 /* Maximum dutycycle */
#define MAX_DUTYCYCLE                                   (100u)

/* Minimum dutycycle */
#define MIN_DUTYCYCLE                                   (2u)

/* Dutycycle increment/decrement by 10% */
#define DUTYCYCLE_INCREMENT                             (10u)

/* CAPSENSE task stack size */
#define CAPSENSE_TASK_STACK_SIZE                        (5 * 1024)

/* CAPSENSE task priority */
#define CAPSENSE_TASK_PRIORITY                          (1u)

/* CAPSENSE interrupt priority */
#define CAPSENSE_INTR_PRIORITY                          (7u)

#ifdef ENABLE_TFT
/* Light sensor pin mapped to red led */
#define LIGHT_SENSOR_PIN                                (CYBSP_A0)

/* Max voltage of ADC reading  */
#define LIGHTSENSOR_ADC_MAX_VOLTAGE                     (3300u)

/* Max count of ADC reading  */
#define LIGHTSENSOR_ADC_MAX_COUNT                       (100u)

/* Initial row position on TFT display */
#define TOP_DISPLAY                                     (0u)

#endif /* #ifdef ENABLE_TFT */

/* Timeout value to get mutex */
#define GET_MUTEX_DELAY                                 (200u)
/*******************************************************************************
 *                    Structures
*******************************************************************************/
typedef struct
{
    uint8_t         duty;
    SemaphoreHandle_t xpwm_mutex;
} pwm_duty_t;

/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
uint32_t initialize_led(void);
uint32_t initialize_capsense(void);
void capsense_callback(cy_stc_active_scan_sns_t * ptrActiveScan);
void adjust_led_brightness(void);
void increase_duty_cycle(void);
void decrease_duty_cycle(void);
void set_duty_cycle(uint32_t duty_cycle);
uint8_t get_duty_cycle(void);
void process_touch(void);
void initialize_sensors(void);

#ifdef ENABLE_TFT
    uint32_t initialize_light_sensor(void);
#endif /* #ifdef ENABLE_TFT */

#endif
