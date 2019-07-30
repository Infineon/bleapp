/*******************************************************************************
* File Name: capsense_SMS.c
* Version 2.60
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component
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

#include "capsense_SMS.h"
#include "capsense_PVT.h"

#include "cytypes.h"

#if (capsense_TUNING_METHOD == capsense__TUNING_AUTO)


/*  Real Charge Divider values */
#if ((0u != capsense_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000))
    /*  Dividers are not chained */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            4u,     4u,     4u,    8u,    8u,    8u,    8u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u
        };
    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */

#elif (0u != capsense_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained (PSoC 4000) */
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #else
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

#else
    /*  Dividers are chained (PSoC 4100, PSoC 4200) */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 capsense_prescalerTable[capsense_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* ((0u != capsense_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000)) */


uint8 capsense_noiseEnvelopeTbl[capsense_TOTAL_SENSOR_COUNT];
uint8 capsense_runningDifferenceTbl[capsense_TOTAL_SENSOR_COUNT];
uint8 capsense_signRegisterTbl[capsense_TOTAL_SENSOR_COUNT];
uint16 capsense_sampleMinTbl[capsense_TOTAL_SENSOR_COUNT];
uint16 capsense_sampleMaxTbl[capsense_TOTAL_SENSOR_COUNT];
uint16 capsense_previousSampleTbl[capsense_TOTAL_SENSOR_COUNT];
uint8 capsense_kValueTbl[capsense_TOTAL_SENSOR_COUNT];

uint8 capsense_sensorSensitivity[] = {
    2u, 2u, 2u, 2u, 2u, 
};

capsense_CONFIG_TYPE_P4_v2_60 capsense_config;
capsense_CONFIG_TYPE_POINTERS_P4_v2_60 const capsense_configPointers = {
    capsense_modulationIDAC,
    capsense_compensationIDAC,
    capsense_sensorSensitivity,
    capsense_senseClkDividerVal,
    capsense_sampleClkDividerVal,
    capsense_widgetNumber,
    capsense_widgetResolution,
    capsense_noiseEnvelopeTbl,
    capsense_runningDifferenceTbl,
    capsense_signRegisterTbl,
    capsense_sampleMinTbl,
    capsense_sampleMaxTbl,
    capsense_previousSampleTbl,
    capsense_kValueTbl,
    capsense_scanSpeedTbl,
    capsense_prescalerTable,
    (const uint8  *)capsense_rawDataIndex,
    (const uint8  *)capsense_numberOfSensors,
    &capsense_GetSensorRaw,
    &capsense_PreScan,
    &capsense_ReadSensorRaw,
    &capsense_GetBitValue,
    &capsense_SetBitValue
};


/*******************************************************************************
* Function Name: capsense_AutoTune
********************************************************************************
*
* Summary:
*  Provides the tuning procedure for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   capsense_config: the structure which contains configuration parameters
*   capsense_senseClkDividerVal[]: used to store the Analog Switch
*   dividers for each sensor.
*   capsense_senseClkDividerVal[]: used to store the
*    Analog Switch divider for all sensors.
*   capsense_prescalersTuningDone - used to notify the Tuner GUI that
*   the pre-scalers tuning  is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_AutoTune(void)
{
    uint32 curSensor;
    uint32 widget;

    capsense_config.totalScanslotsNum = capsense_TOTAL_SCANSLOT_COUNT;
    capsense_config.totalWidgetsNum = capsense_END_OF_WIDGETS_INDEX;
    capsense_config.totalSensorsNum = capsense_TOTAL_SENSOR_COUNT;

    capsense_config.hfclkFreq_MHz = CYDEV_BCLK__HFCLK__MHZ;
    capsense_config.sensetivitySeed = capsense_SENSETIVITY_FACTOR;

    capsense_config.pointers = &capsense_configPointers;

    capsense_SetAnalogSwitchesSrcDirect();

    for(widget = 0u; widget < capsense_config.totalWidgetsNum; widget++)
    {
        capsense_widgetResolution[widget] = capsense_CALIBRATION_RESOLUTION;
    }


    for(curSensor = 0u; curSensor < capsense_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        capsense_senseClkDividerVal[curSensor] = capsense_CALIBRATION_ASD;
        capsense_sampleClkDividerVal[curSensor] = capsense_CALIBRATION_MD;
    }

    capsense_DisableBaselineIDAC();

    CalibrateSensors_P4_v2_60(&capsense_config, capsense_CAL_RAW_COUNT);

    #if(0u != capsense_TOTAL_CENTROIDS_COUNT)
        capsense_NormalizeWidgets(capsense_END_OF_WIDGETS_INDEX, capsense_modulationIDAC);
    #endif /* (0u != capsense_TOTAL_CENTROIDS_COUNT)  */

    TunePrescalers_P4_v2_60(&capsense_config);

    #if(capsense_PRS_OPTIONS != capsense__PRS_NONE)
        capsense_prescalersTuningDone = 1u;
    #endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */

    CalibrateSensors_P4_v2_60(&capsense_config, capsense_CAL_RAW_COUNT);
    #if(0u != capsense_TOTAL_CENTROIDS_COUNT)
        capsense_NormalizeWidgets(capsense_END_OF_WIDGETS_INDEX, capsense_modulationIDAC);
    #endif /* (0u != capsense_TOTAL_CENTROIDS_COUNT)  */
    TuneSensitivity_P4_v2_60(&capsense_config);

    capsense_EnableBaselineIDAC(&capsense_config);

    for(curSensor = 0u; curSensor < capsense_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        capsense_UpdateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: capsense_UpdateThresholds
********************************************************************************
*
* Summary:
*  The API updates the Finger Threshold, Hysteresis, Noise Threshold, and
*  Negative Noise Threshold in the AutoTuning (Smartsense) Mode.
*
* Parameters:
*  sensor: sensor number.
*
* Return:
*  None
*
* Global Variables:
*  capsense_widgetNumber[] - contains widget Number for given sensor.
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  For other sensors the array element equals to 255.
*  capsense_numberOfSensors[widget] - Number of sensors in the widget.
*   capsense_fingerThreshold[] - contains the level of signal for each sensor
*   that determines if a finger present on the sensor.
*   capsense_negativeNoiseThreshold[] - negative Noise Threshold
*   capsense_hysteresis[] - the array with hysteresis values.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_UpdateThresholds(uint32 sensor)
{
    uint8 fingerThreshold;
    uint32 widget;

    widget = capsense_widgetNumber[sensor];

    #if(0u != capsense_FLEXIBLE_THRESHOLDS_EN)
        fingerThreshold = capsense_fingerThreshold[widget];
        /* Update Threshold manually (flexible) */
        capsense_noiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        capsense_negativeNoiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        capsense_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
    #else
        /* Calculate Finger Threshold and Noise Threshold with Smartsense (automatic) */
        CalculateThresholds_P4_v2_60(&capsense_config, (uint8)sensor, (uint8)widget, capsense_fingerThreshold, capsense_noiseThreshold);

        fingerThreshold = capsense_fingerThreshold[widget];

        /* Update Threshold based on calculated with Smartsense (automatic) */
        capsense_negativeNoiseThreshold[widget] = capsense_noiseThreshold[widget];

        if(fingerThreshold < capsense_THRESHOLD_1)
        {
            capsense_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
        }
        else if(fingerThreshold <  capsense_THRESHOLD_2)
        {
            capsense_hysteresis[widget] = (uint8)(fingerThreshold >> 4u);
        }
        else if(fingerThreshold <  capsense_THRESHOLD_3)
        {
            capsense_hysteresis[widget] = (uint8)(fingerThreshold >> 5u);
        }
        else if(fingerThreshold <  capsense_THRESHOLD_4)
        {
            capsense_hysteresis[widget] = (uint8)(fingerThreshold >> 6u);
        }
        else
        {
            capsense_hysteresis[widget] = 0u;
        }
    #endif /* (0u != capsense_FLEXIBLE_THRESHOLDS_EN)  */
}

/*******************************************************************************
* Function Name: capsense_SetAnalogSwitchesSrcDirect
********************************************************************************
*
* Summary:
*  This API switches the charge clock source to prescaler.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_SetAnalogSwitchesSrcDirect(void)
{
    capsense_CSD_CFG_REG &= ~(capsense_CSD_CFG_PRS_SELECT);
}


/*******************************************************************************
* Function Name: capsense_DisableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API disables the Compensation IDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_DisableBaselineIDAC(void)
{
    uint32 newRegValue;

    newRegValue = capsense_CSD_IDAC_REG;

    newRegValue &= ~(capsense_CSD_IDAC1_MODE_MASK | capsense_CSD_IDAC2_MODE_MASK);
    newRegValue |= capsense_CSD_IDAC1_MODE_VARIABLE;

    capsense_CSD_IDAC_REG = newRegValue;
}


/*******************************************************************************
* Function Name: capsense_EnableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API enables the Compensation IDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_compensationIDAC[] - used to store a 7-bit idac value for all the sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void  capsense_EnableBaselineIDAC(const capsense_CONFIG_TYPE_P4_v2_60 *config)
{
    uint32 curSensor;
    uint32 newRegValue;

    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        capsense_compensationIDAC[curSensor] = capsense_modulationIDAC[curSensor] / 2u;
        capsense_modulationIDAC[curSensor] = (capsense_modulationIDAC[curSensor] + 1u) / 2u;
    }

    CyIntDisable(capsense_ISR_NUMBER);

    newRegValue = capsense_CSD_IDAC_REG;
    newRegValue &= ~(capsense_CSD_IDAC1_MODE_MASK | capsense_CSD_IDAC2_MODE_MASK);
    newRegValue |= (capsense_CSD_IDAC1_MODE_VARIABLE | capsense_CSD_IDAC2_MODE_FIXED);
    capsense_CSD_IDAC_REG = newRegValue;

    CyIntEnable(capsense_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: capsense_SetSensitivity
********************************************************************************
*
* Summary:
*  This API sets the sensitivity value for the sensor. The sensitivity
*  value is used during the auto-tuning algorithm executed as part of the CapSense_Start API.
*  This API is called by the application layer prior to calling the CapSense_Start API.
*  Calling this API after execution of CapSense_Start API has no effect.
*
* Parameters:
*  sensor  Sensor index
*  data    Sensitivity of the sensor. Possible values are below
*  1 - 0.1pf sensitivity
*  2 - 0.2pf sensitivity
*  3 - 0.3pf sensitivity
*  4 - 0.4pf sensitivity
*  5 - 0.5pf sensitivity
*  6 - 0.6pf sensitivity
*  7 - 0.7pf sensitivity
*  8 - 0.8pf sensitivity
*  9 - 0.9pf sensitivity
*  10 - 1.0pf sensitivity
*  All other values, set sensitivity to 1.0pf
*
*  Return Value:
*   None
*
* Global Variables:
* capsense_sensorSensitivity[] - This 8-bits array contains Sensitivity in the LSB nibble
*                                and Noise Reset Counter value in the MSB nibble.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_SetSensitivity(uint32 sensor, uint32 value)
{
    if(value > 10u)
    {
        value = 10u;
    }

    /* Clear SensorSensitivity value in LSB nibble */
    capsense_sensorSensitivity[sensor] &= (uint8)~capsense_SENSITIVITY_MASK;
    /* Set SensorSensitivity value in LSB nibble */
    capsense_sensorSensitivity[sensor] |= (uint8)value;
}


/*******************************************************************************
* Function Name: capsense_GetSensitivityCoefficient
********************************************************************************
*
* Summary:
*  This API returns the K coefficient for the appropriate sensor.
*
* Parameters:
*  sensor:  Sensor index
*
*  Return Value:
*   K - value for the appropriate sensor.
*
* Global Variables:
*  capsense_kValueTbl[] - This 8-bits array contains the K value for each sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 capsense_GetSensitivityCoefficient(uint32 sensor)
{
    return (capsense_kValueTbl[sensor]);
}


/*******************************************************************************
* Function Name: capsense_GetNoiseEnvelope
********************************************************************************
*
* Summary:
*  This function returns the noise value of a
*  component.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  The noise envelope value of the sensor
*  indicated by argument.
*
* Global Variables:
*  capsense_noiseEnvelopeTbl[] - array with Noise Envelope.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 capsense_GetNoiseEnvelope(uint32 sensor)
{
    return((uint16)((uint16)capsense_noiseEnvelopeTbl[sensor] << 1u) + 1u);
}


/*******************************************************************************
* Function Name: capsense_GetNormalizedDiffCountData
********************************************************************************
*
* Summary:
*  This API returns normalized difference count data.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns a normalized count value of the sensor indicated by the
*  argument.
*
* Global Variables:
*  capsense_sensorSignal[] - array with difference counts for sensors
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 capsense_GetNormalizedDiffCountData(uint32 sensor)
{
    return (uint16)(((uint32)capsense_sensorSignal[sensor] << 7u) / capsense_kValueTbl[sensor]);
}

#endif /* (capsense_TUNING_METHOD == capsense__TUNING_AUTO) */

/* [] END OF FILE */
