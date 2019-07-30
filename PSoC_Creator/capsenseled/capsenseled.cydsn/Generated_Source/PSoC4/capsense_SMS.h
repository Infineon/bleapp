/*******************************************************************************
* File Name: capsense_SMS.h
* Version 2.60
*
* Description:
*  This file provides the declarations of the wrapper between the CapSense CSD component
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_CAPSENSE_CSD_SMS_capsense_H)
#define CY_CAPSENSE_CSD_SMS_capsense_H

#include "capsense.h"
#include "capsense_PVT.h"

#if(0u != capsense_CSHL_API_GENERATE)
    #include "capsense_CSHL.h"
#endif /* (0u != capsense_CSHL_API_GENERATE) */

#define capsense_PRESCALERS_TBL_SIZE        (16u)

#define capsense_CALIBRATION_FREQ_KHZ       (3000u)
#define capsense_CALIBRATION_MD             (4u)

#define capsense_MAX_RESOLUTION         (65535u)
#define capsense_CALIBRATION_RESOLUTION (0x0FFF0000u)

#define capsense_PRS_CORRECTION_DIVIDER (4u)
#define capsense_SENSITIVITY_DIVIDER    (10u)

#define capsense_SENSITIVITY_MASK           (0x0Fu)
#define capsense_FLEXIBLE_THRESHOLDS_EN     (0u)
#define capsense_CAL_RAW_COUNT              (3482u)

#define capsense_THRESHOLD_1                (220u)
#define capsense_THRESHOLD_2                (237u)
#define capsense_THRESHOLD_3                (245u)
#define capsense_THRESHOLD_4                (250u)


#if (0u != capsense_IS_M0S8PERI_BLOCK)
    #define capsense_CALIBRATION_ASD        (CYDEV_BCLK__HFCLK__KHZ /\
                                                     capsense_CALIBRATION_FREQ_KHZ)
#else
    #define capsense_MIN_IMO_FREQ_KHZ       (6000u)
    #if(CYDEV_BCLK__HFCLK__KHZ < capsense_MIN_IMO_FREQ_KHZ)
        #define capsense_CALIBRATION_ASD            (1u)
    #else
        #define capsense_CALIBRATION_ASD    (CYDEV_BCLK__HFCLK__KHZ / capsense_CALIBRATION_MD /\
                                                     capsense_CALIBRATION_FREQ_KHZ)
    #endif /* (CYDEV_BCLK__HFCLK__KHZ < capsense_MIN_IMO_FREQ_KHZ) */
#endif /* (0u != capsense_IS_M0S8PERI_BLOCK) */

#if (0u != capsense_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained */
    #if(capsense_PRS_OPTIONS != capsense__PRS_NONE)
        #define capsense_SENSETIVITY_FACTOR (1228u)
    #else
        #define capsense_SENSETIVITY_FACTOR (2456u)
    #endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */
#else
    /*  Dividers are chained */
    #if(capsense_PRS_OPTIONS != capsense__PRS_NONE)
        #define capsense_SENSETIVITY_FACTOR (1228u/capsense_CALIBRATION_MD)
    #else
        #define capsense_SENSETIVITY_FACTOR (2456u/capsense_CALIBRATION_MD)
    #endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */
#endif /* (0u != capsense_IS_M0S8PERI_BLOCK) */


/***************************************
*        Function Prototypes
***************************************/
void capsense_AutoTune(void);
void capsense_UpdateThresholds(uint32 sensor);
void capsense_SetSensitivity(uint32 sensor, uint32 value);
void capsense_SetAnalogSwitchesSrcDirect(void);
uint16 capsense_GetNoiseEnvelope(uint32 sensor);
uint8 capsense_GetSensitivityCoefficient(uint32 sensor);
uint16 capsense_GetNormalizedDiffCountData(uint32 sensor);


/***************************************
*     Vars with External Linkage
***************************************/

/*  Real Charge Divider values */
#if (0u != capsense_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained */
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #else
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
#else
    /*  Dividers are chained */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        extern const uint8 prescalerTable[capsense_PRESCALERS_TBL_SIZE];
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* (0u != capsense_IS_M0S8PERI_BLOCK) */


extern uint8 capsense_noiseEnvelopeTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_runningDifferenceTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_signRegisterTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint16 capsense_sampleMinTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint16 capsense_sampleMaxTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint16 capsense_previousSampleTbl[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_kValueTbl[capsense_TOTAL_SENSOR_COUNT];


#endif  /* (CY_CAPSENSE_CSD_SMS_capsense_H) */

/* [] END OF FILE */
