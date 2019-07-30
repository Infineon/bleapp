/*******************************************************************************
* File Name: capsense.c
* Version 2.60
*
* Description:
*  This file provides the source code for scanning APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "capsense.h"
#include "capsense_PVT.h"
#include "cypins.h"


#if(0u != capsense_CSHL_API_GENERATE)
    #include "capsense_CSHL.h"
#endif /* (0u != capsense_CSHL_API_GENERATE) */

/* This definition is intended to prevent unexpected linker error.
   For more details please see the IAR Technical Note 49981 */
#if defined(__ICCARM__)
    extern void capsense_EnableSensor(uint32 sensor);
    extern void capsense_DisableSensor(uint32 sensor);
#endif /* (__ICCARM__) */

/* SmartSense functions */
#if (capsense_TUNING_METHOD == capsense__TUNING_AUTO)
    uint8 capsense_lowLevelTuningDone = 0u;
    uint8 capsense_scanSpeedTbl[((capsense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
#endif /* (capsense_TUNING_METHOD == capsense__TUNING_AUTO) */

#if(capsense_PRS_OPTIONS != capsense__PRS_NONE)
    uint8 capsense_prescalersTuningDone = 0u;
#endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */

/* Global software variables */
volatile uint8 capsense_csdStatusVar = 0u;   /* CapSense CSD status, variable */
volatile uint8 capsense_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 capsense_sensorRaw[capsense_TOTAL_SENSOR_COUNT] = {0u};

/* Backup variables for trim registers*/
#if (capsense_IDAC1_POLARITY == capsense__IDAC_SINK)
    uint8 capsense_csdTrim2;
#else
    uint8 capsense_csdTrim1;
#endif /* (capsense_IDAC1_POLARITY == capsense__IDAC_SINK) */

/* Global array of un-scanned sensors state */
uint8 capsense_unscannedSnsDriveMode[capsense_PORT_PIN_CONFIG_TBL_ZISE];

/* Backup array for capsense_sensorEnableMask */
uint8 capsense_sensorEnableMaskBackup[(((capsense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];

/* Configured constants and arrays by Customizer */
uint8 capsense_sensorEnableMask[(((capsense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {
0x1Fu, };

reg32 * capsense_pcTable[] = {
    (reg32 *)capsense_Sns__LinearSlider0_e0__LS__PC, 
    (reg32 *)capsense_Sns__LinearSlider0_e1__LS__PC, 
    (reg32 *)capsense_Sns__LinearSlider0_e2__LS__PC, 
    (reg32 *)capsense_Sns__LinearSlider0_e3__LS__PC, 
    (reg32 *)capsense_Sns__LinearSlider0_e4__LS__PC, 
};

const uint8 capsense_portTable[] = {
    capsense_Sns__LinearSlider0_e0__LS__PORT, 
    capsense_Sns__LinearSlider0_e1__LS__PORT, 
    capsense_Sns__LinearSlider0_e2__LS__PORT, 
    capsense_Sns__LinearSlider0_e3__LS__PORT, 
    capsense_Sns__LinearSlider0_e4__LS__PORT, 
};

const uint32 capsense_maskTable[] = {
    capsense_Sns__LinearSlider0_e0__LS__MASK, 
    capsense_Sns__LinearSlider0_e1__LS__MASK, 
    capsense_Sns__LinearSlider0_e2__LS__MASK, 
    capsense_Sns__LinearSlider0_e3__LS__MASK, 
    capsense_Sns__LinearSlider0_e4__LS__MASK, 
};

const uint8 capsense_pinShiftTbl[] = {
    (uint8) capsense_Sns__LinearSlider0_e0__LS__SHIFT, 
    (uint8) capsense_Sns__LinearSlider0_e1__LS__SHIFT, 
    (uint8) capsense_Sns__LinearSlider0_e2__LS__SHIFT, 
    (uint8) capsense_Sns__LinearSlider0_e3__LS__SHIFT, 
    (uint8) capsense_Sns__LinearSlider0_e4__LS__SHIFT, 
};

uint8 capsense_modulationIDAC[capsense_TOTAL_SENSOR_COUNT];
uint8 capsense_compensationIDAC[capsense_TOTAL_SENSOR_COUNT];

uint32 capsense_widgetResolution[capsense_RESOLUTIONS_TBL_SIZE] = {
    capsense_RESOLUTION_12_BITS,
};

uint8 capsense_senseClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];
uint8 capsense_sampleClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];

const uint8 capsense_widgetNumber[capsense_TOTAL_SENSOR_COUNT] = {
    0u, 0u, 0u, 0u, 0u, /* LinearSlider0__LS */
};

reg32* const capsense_prtSelTbl[capsense_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_HSIOM_PORT_SEL0),
    ((reg32 *) CYREG_HSIOM_PORT_SEL1),
    ((reg32 *) CYREG_HSIOM_PORT_SEL2),
    ((reg32 *) CYREG_HSIOM_PORT_SEL3),
    ((reg32 *) CYREG_HSIOM_PORT_SEL4),
    ((reg32 *) CYREG_HSIOM_PORT_SEL5),
    ((reg32 *) CYREG_HSIOM_PORT_SEL6),
};

reg32* const capsense_prtCfgTbl[capsense_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_GPIO_PRT0_PC),
    ((reg32 *) CYREG_GPIO_PRT1_PC),
    ((reg32 *) CYREG_GPIO_PRT2_PC),
    ((reg32 *) CYREG_GPIO_PRT3_PC),
    ((reg32 *) CYREG_GPIO_PRT4_PC),
    ((reg32 *) CYREG_GPIO_PRT5_PC),
    ((reg32 *) CYREG_GPIO_PRT6_PC),
};

reg32* const capsense_prtDRTbl[capsense_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_GPIO_PRT0_DR),
    ((reg32 *) CYREG_GPIO_PRT1_DR),
    ((reg32 *) CYREG_GPIO_PRT2_DR),
    ((reg32 *) CYREG_GPIO_PRT3_DR),
    ((reg32 *) CYREG_GPIO_PRT4_DR),
    ((reg32 *) CYREG_GPIO_PRT5_DR),
    ((reg32 *) CYREG_GPIO_PRT6_DR),
};



/*******************************************************************************
* Function Name: capsense_Init
********************************************************************************
*
* Summary:
*  API initializes default CapSense configuration provided by the customizer that defines
*  the mode of component operations and resets all the sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_immunityIndex - defines immunity level.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_Init(void)
{
    uint32 curSensor;

    #if(capsense_IS_SHIELD_ENABLE)

        #if((capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRIOBUF) || (0u != capsense_CSH_TANK_ENABLE))
            uint32 newRegValue;

            newRegValue = capsense_CTANK_CONNECTION_REG;
            newRegValue &= ~(capsense_CSD_CTANK_CONNECTION_MASK);
            newRegValue |= capsense_CSD_CTANK_TO_AMUXBUS_B;
            capsense_CTANK_CONNECTION_REG = newRegValue;

            #if(capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRIOBUF)
                newRegValue = capsense_CTANK_PORT_PC_REG;
                newRegValue &= ~(capsense_CSD_CTANK_PC_MASK);
                newRegValue |= capsense_CTANK_PC_STRONG_MODE;
                capsense_CTANK_PORT_PC_REG = newRegValue;

                newRegValue = capsense_CTANK_PORT_DR_REG;
                newRegValue &= ~(capsense_CTANK_DR_MASK);
                newRegValue |= capsense_CTANK_DR_CONFIG;
                capsense_CTANK_PORT_DR_REG = newRegValue;
            #endif /* (capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRIOBUF) */

        #endif /* ((capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRIOBUF) || (capsense_CSH_TANK_ENABLE)) */

        capsense_EnableShieldElectrode((uint32)capsense_SHIELD_PIN_NUMBER, (uint32)capsense_SHIELD_PORT_NUMBER);

    #endif /* (capsense_IS_SHIELD_ENABLE) */

    for(curSensor = 0u; curSensor < capsense_TOTAL_SENSOR_COUNT; curSensor++)
    {
        capsense_SetUnscannedSensorState(curSensor, capsense_CONNECT_INACTIVE_SNS);
    }

    capsense_CsdHwBlockInit();
    capsense_SetShieldDelay(capsense_SHIELD_DELAY );

    /* Clear all sensors */
    capsense_ClearSensors();
}

/*******************************************************************************
* Function Name: capsense_CsdHwBlockInit
********************************************************************************
*
* Summary:
*  Initialises the hardware parameters of the CSD block
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_csdTrim1 - Contains IDAC trim register value for Sourcing Mode.
*  capsense_csdTrim2 - Contains IDAC trim register value for Sinking Mode.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_CsdHwBlockInit(void)
{
    uint32 newRegValue;

        /* Set trim registers for CSD Mode */
    #if (capsense_IDAC1_POLARITY == capsense__IDAC_SINK)
        /* iDAC1 Sinking Mode */
        capsense_csdTrim2 = (uint8)capsense_CSD_TRIM2_REG;
        newRegValue = capsense_csdTrim2;
        newRegValue &= capsense_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)capsense_SFLASH_CSD_TRIM2_REG & (uint32)capsense_CSFLASH_TRIM_IDAC1_MASK);

        #if (capsense_IDAC_CNT == 2u)
            /* iDAC2 Sinking Mode */
            newRegValue &= capsense_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)capsense_SFLASH_CSD_TRIM2_REG & (uint32)capsense_CSFLASH_TRIM_IDAC2_MASK);
        #endif /* (capsense_IDAC_CNT == 2u) */
        capsense_CSD_TRIM2_REG = newRegValue;
    #else
        /* iDAC1 Sourcing Mode */
        capsense_csdTrim1 = (uint8)capsense_CSD_TRIM1_REG;
        newRegValue = capsense_csdTrim1;
        newRegValue &= capsense_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)capsense_SFLASH_CSD_TRIM1_REG & (uint32)capsense_CSFLASH_TRIM_IDAC1_MASK);
        #if (capsense_IDAC_CNT == 2u)
             /* iDAC2 Sourcing Mode */
            newRegValue &= capsense_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)capsense_SFLASH_CSD_TRIM1_REG & (uint32)capsense_CSFLASH_TRIM_IDAC2_MASK);
        #endif
        capsense_CSD_TRIM1_REG = newRegValue;
    #endif /* (capsense_IDAC1_POLARITY == capsense__IDAC_SINK) */

    /* Configure CSD and IDAC */
    #if (capsense_IDAC_CNT > 1u)
        capsense_CSD_IDAC_REG = capsense_DEFAULT_CSD_IDAC_CONFIG;
        capsense_CSD_CFG_REG = capsense_DEFAULT_CSD_CONFIG;
    #else
        capsense_CSD_IDAC_REG &= ~(capsense_CSD_IDAC1_MODE_MASK  | capsense_CSD_IDAC1_DATA_MASK);
        capsense_CSD_IDAC_REG |= capsense_DEFAULT_CSD_IDAC_CONFIG;

        capsense_CSD_CFG_REG &= ~(capsense_CSD_CONFIG_MASK);
        capsense_CSD_CFG_REG |= (capsense_DEFAULT_CSD_CONFIG);
    #endif /* (capsense_IDAC_CNT > 1u) */


    /* Connect Cmod to AMUX bus */
    newRegValue = capsense_CMOD_CONNECTION_REG;
    newRegValue &= ~(capsense_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= capsense_CSD_CMOD_TO_AMUXBUS_A;
    capsense_CMOD_CONNECTION_REG = newRegValue;

    /* Configure Dead Band PWM if it is enabled */
    #if(capsense_CSD_4B_PWM_MODE != capsense__PWM_OFF)
        capsense_CSD_4B_PWM_REG = capsense_DEFAULT_CSD_4B_PWM_CONFIG;
    #endif /* (capsense_CSD_4B_PWM_MODE != capsense__PWM_OFF) */

    /* Setup ISR */
    CyIntDisable(capsense_ISR_NUMBER);
    #if !defined(CY_EXTERNAL_INTERRUPT_CONFIG)
        (void)CyIntSetVector(capsense_ISR_NUMBER, &capsense_ISR);
        CyIntSetPriority(capsense_ISR_NUMBER, capsense_ISR_PRIORITY);
    #endif /* (CY_EXTERNAL_INTERRUPT_CONFIG) */
}


/*******************************************************************************
* Function Name: capsense_Enable
********************************************************************************
*
* Summary:
*  Enables the CSD block and related resources to an active mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_Enable(void)
{
    uint32 newRegValue;

    /* Enable Clocks */
    capsense_SenseClk_Stop();
    capsense_SampleClk_Stop();

    capsense_SampleClk_SetDividerValue((uint16)capsense_INITIAL_CLK_DIVIDER);
    capsense_SenseClk_SetDividerValue((uint16)capsense_INITIAL_CLK_DIVIDER);

    #if (0u == capsense_IS_M0S8PERI_BLOCK)
        capsense_SenseClk_Start();
        capsense_SampleClk_Start();
    #else
        capsense_SampleClk_Start();
        capsense_SenseClk_StartEx(capsense_SampleClk__DIV_ID);
    #endif /* (0u == capsense_IS_M0S8PERI_BLOCK) */

    /* Enable the CSD block */
    newRegValue = capsense_CSD_CFG_REG;
    newRegValue |= (capsense_CSD_CFG_ENABLE | capsense_CSD_CFG_SENSE_COMP_EN
                                                   | capsense_CSD_CFG_SENSE_EN);
    capsense_CSD_CFG_REG = newRegValue;

    /* Enable interrupt */
    CyIntEnable(capsense_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: capsense_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin the component operation. CapSense_Start()
*  calls the CapSense_Init() function, and then calls the CapSense_Enable()
*  function. Initializes the registers and starts the CSD method of the CapSense
*  component. Resets all the sensors to an inactive state. Enables interrupts for
*  sensors scanning. When the SmartSense tuning mode is selected, the tuning procedure
*  is applied for all the sensors. The CapSense_Start() routine must be called before
*  any other API routines.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   capsense_initVar - used to check the initial configuration,
*   modified on the first function call.
*  capsense_lowLevelTuningDone - Used to notify the Tuner GUI that
*   tuning of the scanning parameters is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_Start(void)
{

    static uint8 capsense_initVar = 0u;

    #if((0u != capsense_AUTOCALIBRATION_ENABLE) && (capsense_TUNING_METHOD != capsense__TUNING_AUTO))
        uint32 curSensor;
        uint32 rawLevel;
        uint32 widget;
    #endif /* ((0u != capsense_AUTOCALIBRATION_ENABLE) && (capsense_TUNING_METHOD != capsense__TUNING_AUTO)) */

    if (capsense_initVar == 0u)
    {
        capsense_Init();
        capsense_initVar = 1u;
    }
    capsense_Enable();

    /* AutoTunning start */
    #if(capsense_TUNING_METHOD == capsense__TUNING_AUTO)
        #if(0u != capsense_CSHL_API_GENERATE)
            capsense_AutoTune();
            capsense_lowLevelTuningDone = 1u;
        #endif /* (0u != capsense_CSHL_API_GENERATE) */
    #else
        #if(0u != capsense_AUTOCALIBRATION_ENABLE)

            #if(capsense_IDAC_CNT > 1u)
                capsense_CSD_IDAC_REG &= ~(capsense_CSD_IDAC2_MODE_MASK);
            #endif /* (capsense_IDAC_CNT > 1u) */

            for(curSensor = 0u; curSensor < capsense_TOTAL_SCANSLOT_COUNT; curSensor++)
            {
                widget = capsense_widgetNumber[curSensor];
                rawLevel = capsense_widgetResolution[widget] >> capsense_RESOLUTION_OFFSET;

                /* Calibration level should be equal to 85% from scanning resolution */
                rawLevel = (rawLevel * 85u) / 100u;

                capsense_CalibrateSensor(curSensor, rawLevel, capsense_modulationIDAC);
            }

            #if(0u != capsense_TOTAL_CENTROIDS_COUNT)
                capsense_NormalizeWidgets(capsense_END_OF_WIDGETS_INDEX, capsense_modulationIDAC);
            #endif /* (0u != capsense_TOTAL_CENTROIDS_COUNT)  */

            #if(capsense_IDAC_CNT > 1u)
                for(curSensor = 0u; curSensor < capsense_TOTAL_SCANSLOT_COUNT; curSensor++)
                {
                    capsense_compensationIDAC[curSensor] = capsense_modulationIDAC[curSensor] / 2u;
                    capsense_modulationIDAC[curSensor] = (capsense_modulationIDAC[curSensor] + 1u) / 2u;
                }
                capsense_CSD_IDAC_REG |= capsense_CSD_IDAC2_MODE_FIXED;
            #endif /* (capsense_IDAC_CNT > 1u) */

        #endif /* (0u != capsense_AUTOCALIBRATION_ENABLE) */

    #endif /* ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) */

    /* Initialize Advanced Centroid */
    #if(capsense_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
        capsense_AdvancedCentroidInit();
    #endif /* (capsense_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

    /* Connect sense comparator input to AMUXA */
    capsense_CSD_CFG_REG |= capsense_CSD_CFG_SENSE_INSEL;
}


/*******************************************************************************
* Function Name: capsense_Stop
********************************************************************************
*
* Summary:
*  Stops the sensor scanning, disables component interrupts, and resets all the
*  sensors to an inactive state. Disables the Active mode power template bits for
*  the subcomponents used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_csdTrim1 - Contains the IDAC trim register value for the Sourcing Mode.
*  capsense_csdTrim2 - Contains the IDAC trim register value for vSinking Mode.
*
* Side Effects:
*  This function should be called after scans are completed.
*
*******************************************************************************/
void capsense_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(capsense_ISR_NUMBER);

    capsense_CSD_CFG_REG &= ~(capsense_CSD_CFG_SENSE_COMP_EN | capsense_CSD_CFG_SENSE_EN);

    #if(capsense_IDAC_CNT == 2u)
        capsense_CSD_CFG_REG &= ~(capsense_CSD_CFG_ENABLE);
    #endif /* (capsense_IDAC_CNT == 2u) */

    /* Disable the Clocks */
    capsense_SenseClk_Stop();
    capsense_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: capsense_FindNextSensor
********************************************************************************
*
* Summary:
*  Finds the next sensor to scan.
*
* Parameters:
*  snsIndex:  Current index of sensor.
*
* Return:
*  Returns the next sensor index to scan.
*
* Global Variables:
*  capsense_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*
* Side Effects:
*  This function affects the  current scanning and should not
*  be used outside the component.
*
*******************************************************************************/
uint8 capsense_FindNextSensor(uint8 snsIndex)
{
    uint32 enableFlag;

    /* Check if sensor enabled */
    do
    {
        /* Proceed with next sensor */
        snsIndex++;
        if(snsIndex == capsense_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        enableFlag = capsense_GetBitValue(capsense_sensorEnableMask, (uint32)snsIndex);
    }
    while(enableFlag == 0u);

    return ((uint8)snsIndex);
}


/*******************************************************************************
* Function Name: capsense_ScanSensor
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a sensor. After scanning is complete,
*  the ISR copies the measured sensor raw data to the global raw sensor array.
*  Use of the ISR ensures this function is non-blocking.
*  Each sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  capsense_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and mode of scan as single scan.
*  capsense_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to the provided sensor argument.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_ScanSensor(uint32 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    capsense_csdStatusVar = 0u;
    capsense_sensorIndex = (uint8)sensor;

    /* Start of sensor scan */
    capsense_csdStatusVar = (capsense_SW_STS_BUSY | capsense_SW_CTRL_SINGLE_SCAN);
    capsense_PreScan(sensor);
}


#if(0u != capsense_CSHL_API_GENERATE)
/*******************************************************************************
* Function Name: capsense_ScanWidget
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a widget.
*
* Parameters:
*  uint32 widget: Widget number.
*
* Return:
*  None
*
* Global Variables:
*  capsense_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  capsense_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function capsense_FindNextSensor or
*  capsense_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*  capsense_sensorEnableMaskBackup[] - used to backup bit masks of the enabled
*   sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_ScanWidget(uint32 widget)
{
    uint32 sensorsPerWidget;
    uint32 lastSensor;
    uint32 snsIndex;

    /* Get first sensor in widget */
    capsense_sensorIndex = capsense_rawDataIndex[widget];

    /* Get number of sensors in widget */
    sensorsPerWidget = capsense_numberOfSensors[widget];

    /* Check if generic Sensor */
    if(sensorsPerWidget == 0u)
    {
        sensorsPerWidget = 1u;
    }

    /* Get last sensor in widget */
    lastSensor = (capsense_rawDataIndex[widget] + sensorsPerWidget) - 1u;

    /* Backup sensorEnableMask array */
    for(snsIndex = 0u; snsIndex < capsense_TOTAL_SENSOR_MASK; snsIndex++)
    {
        /* Backup sensorEnableMask array */
        capsense_sensorEnableMaskBackup[snsIndex] = capsense_sensorEnableMask[snsIndex];
    }

    /* Update sensorEnableMask to scan the sensors that belong to widget */
    for(snsIndex = 0u; snsIndex < capsense_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        /* Update sensorEnableMask array bits to scan the widget only */
        if((snsIndex >= capsense_sensorIndex) && (snsIndex <= lastSensor))
        {
            /* Set sensor bit to scan */
            capsense_SetBitValue(capsense_sensorEnableMask, snsIndex, 1u);
        }
        else
        {
            /* Reset sensor bit to do not scan */
            capsense_SetBitValue(capsense_sensorEnableMask, snsIndex, 0u);
        }
    }

    /* Check end of scan condition */
    if(capsense_sensorIndex < capsense_TOTAL_SENSOR_COUNT)
    {
        /* Set widget busy bit in status/control variable*/
        capsense_csdStatusVar = (capsense_SW_STS_BUSY | capsense_SW_CTRL_WIDGET_SCAN);
        /* Scan first sensor of widget*/
        capsense_PreScan((uint32)capsense_sensorIndex);
    }
}
#endif /* (0u != capsense_CSHL_API_GENERATE) */


/*******************************************************************************
* Function Name: capsense_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  This is the preferred method to scan all of the enabled widgets.
*  The API starts scanning a sensor within the enabled widgets.
*  The ISR continues scanning the sensors until all the enabled widgets are scanned.
*  Use of the ISR ensures this function is non-blocking.
*  All the widgets are enabled by default except proximity widgets.
*  The proximity widgets must be manually enabled as their long scan time
*  is incompatible with a fast response required of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  capsense_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function capsense_FindNextSensor or
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    capsense_csdStatusVar = 0u;
    capsense_sensorIndex = 0xFFu;

    /* Find next sensor */
    capsense_sensorIndex = (uint8)capsense_FindNextSensor(capsense_sensorIndex);

    /* Check end of scan condition */
    if(capsense_sensorIndex < capsense_TOTAL_SENSOR_COUNT)
    {
        capsense_csdStatusVar |= capsense_SW_STS_BUSY;
        capsense_PreScan((uint32)capsense_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: capsense_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of the CapSense component. 1 means that scanning in
*  progress and 0 means that scanning is complete.
*
* Parameters:
*  None
*
* Return:
*  Returns the state of scanning. 1 - scanning in progress, 0 - scanning
*  completed.
*
* Global Variables:
*  capsense_csdStatusVar - used to provide the status and mode of the scanning process.
*  Checks the busy status.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_IsBusy(void)
{
    return ((uint32)((0u != (capsense_csdStatusVar & capsense_SW_STS_BUSY)) ? 1u : 0u));
}


/*******************************************************************************
* Function Name: capsense_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns sensor raw data from the global CapSense_sensorRaw[ ] array.
*  Each scan sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*  Raw data can be used to perform calculations outside of the CapSense
*  provided framework.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns the current raw data value for a defined sensor number.
*
* Global Variables:
*  capsense_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 capsense_ReadSensorRaw(uint32 sensor)
{
    return capsense_sensorRaw[sensor];
}


/*******************************************************************************
* Function Name: capsense_WriteSensorRaw
********************************************************************************
*
* Summary:
*  This API writes the raw count value passed as an argument to the sensor Raw count array.
*
* Parameters:
*  sensor:  Sensor number.
*  value: Raw count value.
*
* Global Variables:
*  capsense_sensorRaw[] - used to store sensors raw data.
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_WriteSensorRaw(uint32 sensor, uint16 value)
{
    capsense_sensorRaw[sensor] = value;
}


#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    /*******************************************************************************
    * Function Name: capsense_SetScanResolution
    ********************************************************************************
    *
    * Summary:
    *  Sets a value of the sensor scan resolution for a widget.
    *  The MIN resolution can be set 8-bit. The MAX Resolution can be set 16 bit.
    *  This function is not available for the tuning mode "None".
    *
    * Parameters:
    *  widget:     Widget index.
    *  resolution: Represents the resolution value. The following defines which are available in the
    *              capsense.h file should be used:
    *              capsense_RESOLUTION_6_BITS
    *              capsense_RESOLUTION_7_BITS
    *              capsense_RESOLUTION_8_BITS
    *              capsense_RESOLUTION_9_BITS
    *              capsense_RESOLUTION_10_BITS
    *              capsense_RESOLUTION_11_BITS
    *              capsense_RESOLUTION_12_BITS
    *              capsense_RESOLUTION_13_BITS
    *              capsense_RESOLUTION_14_BITS
    *              capsense_RESOLUTION_15_BITS
    *              capsense_RESOLUTION_16_BITS
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  capsense_widgetResolution[] - used to store scan resolution of each widget.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetScanResolution(uint32 widget, uint32 resolution)
    {
        capsense_widgetResolution[widget] = resolution;
    }
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */


/*******************************************************************************
* Function Name: capsense_GetScanResolution
********************************************************************************
*
* Summary:
*  Returns the resolution value for the appropriate sensor.
*  This function is not available for tuning mode "None".
*
* Parameters:
*  widget:     Widget index.
*
* Return:
*  resolution: Returns the resolution value for the appropriate sensor.
*              The resolution values are defined in the capsense.h file
*              The defines are encountered below:
*              capsense_RESOLUTION_6_BITS
*              capsense_RESOLUTION_7_BITS
*              capsense_RESOLUTION_8_BITS
*              capsense_RESOLUTION_9_BITS
*              capsense_RESOLUTION_10_BITS
*              capsense_RESOLUTION_11_BITS
*              capsense_RESOLUTION_12_BITS
*              capsense_RESOLUTION_13_BITS
*              capsense_RESOLUTION_14_BITS
*              capsense_RESOLUTION_15_BITS
*              capsense_RESOLUTION_16_BITS
*
* Global Variables:
*  capsense_widgetResolution[] - used to store scan resolution of every widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetScanResolution(uint32 widget)
{
    return(capsense_widgetResolution[widget]);
}


/*******************************************************************************
* Function Name: capsense_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all the sensors to the non-sampling state by sequentially disconnecting
*  all the sensors from Analog MUX Bus and putting them to an inactive state.
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
void capsense_ClearSensors(void)
{
    uint32 snsIndex;

    for (snsIndex = 0u; snsIndex < capsense_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        capsense_DisableScanSlot(snsIndex);
    }
}


#if (capsense_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: capsense_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement
    *  cycle. The corresponding pin/pins are set to Analog High-Z mode and
    *  connected to the Analog Mux Bus. This also enables the comparator function.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Constants:
    *  capsense_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  capsense_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  capsense_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  Bit 7 (msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_EnableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;
        /* Read sensor type: single or complex */
        uint8 snsType = capsense_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & capsense_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (single) */
            capsense_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~capsense_COMPLEX_SS_FLAG;
            index = &capsense_indexTable[snsType];
            snsNumber = capsense_maskTable[slot];

            for (j = 0u; j < snsNumber; j++)
            {
                capsense_EnableSensor(index[j]);
            }
        }
    }


    /*******************************************************************************
    * Function Name: capsense_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pins is/are disconnected
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  capsense_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  capsense_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  capsense_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  7bit(msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_DisableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;

        /* Read sensor type: single or complex */
        uint8 snsType = capsense_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & capsense_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (single) */
            capsense_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~capsense_COMPLEX_SS_FLAG;
            index = &capsense_indexTable[snsType];
            snsNumber = capsense_maskTable[slot];

            for (j=0; j < snsNumber; j++)
            {
                capsense_DisableSensor(index[j]);
            }
        }
    }
#endif  /* capsense_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: capsense_EnableSensor
********************************************************************************
*
* Summary:
*  Configures the selected sensor to measure during the next measurement cycle.
*  The corresponding pins are set to Analog High-Z mode and connected to the
*  Analog Mux Bus. This also enables the comparator function.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  capsense_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  capsense_pinShiftTbl[] - used to store position of pin that
*  configured as sensor in port.
*  capsense_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  capsense_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_EnableSensor(uint32 sensor)
{
    uint8  pinModeShift;
    uint8  pinHSIOMShift;
    uint8 interruptState;
    uint32 newRegisterValue;
    uint32 port;

    port = (uint32) capsense_portTable[sensor];
    pinModeShift = capsense_pinShiftTbl[sensor]  * capsense_PC_PIN_CFG_SIZE;
    pinHSIOMShift = capsense_pinShiftTbl[sensor] * capsense_HSIOM_PIN_CFG_SIZE;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = *capsense_prtSelTbl[port];
    newRegisterValue &= ~(capsense_CSD_HSIOM_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)capsense_CSD_SENSE_PORT_MODE << pinHSIOMShift);

    *capsense_prtCfgTbl[port] &= (uint32)~((uint32)capsense_CSD_PIN_MODE_MASK << pinModeShift);
    *capsense_prtSelTbl[port] = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: capsense_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z or Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  capsense_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  capsense_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*  capsense_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  capsense_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_DisableSensor(uint32 sensor)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    uint32 port = (uint32) capsense_portTable[sensor];
    uint8  pinHSIOMShift = capsense_pinShiftTbl[sensor] * capsense_HSIOM_PIN_CFG_SIZE;
    uint8  pinModeShift = capsense_pinShiftTbl[sensor]  * capsense_PC_PIN_CFG_SIZE;

    uint32 inactiveConnect = capsense_SNS_HIZANALOG_CONNECT;
    uint32 sensorState = capsense_unscannedSnsDriveMode[sensor];

    *capsense_prtSelTbl[port] &= ~(capsense_CSD_HSIOM_MASK << pinHSIOMShift);

    #if(capsense_IS_SHIELD_ENABLE != 0)
    if(sensorState != (uint32)capsense__SHIELD)
    {
    #else
        /* Connected to Ground if shield is disabled */
        if(sensorState == (uint32)capsense__SHIELD)
        {
            sensorState = (uint32)capsense__GROUND;
        }
    #endif /* (capsense_IS_SHIELD_ENABLE) */
        if(sensorState != (uint32)capsense__HIZ_ANALOG)
        {
            /* Connected to Ground */
            inactiveConnect = (uint32)capsense_SNS_GROUND_CONNECT;
        }

        interruptState = CyEnterCriticalSection();

        /* Set drive mode */
        newRegisterValue = *capsense_prtCfgTbl[port];
        newRegisterValue &= ~(capsense_CSD_PIN_MODE_MASK << pinModeShift);
        newRegisterValue |=  (uint32)(inactiveConnect << pinModeShift);
        *capsense_prtCfgTbl[port] =  newRegisterValue;

        CyExitCriticalSection(interruptState);

        *capsense_prtDRTbl[port]  &=  (uint32)~(uint32)((uint32)1u << capsense_pinShiftTbl[sensor]);
    #if(capsense_IS_SHIELD_ENABLE != 0)
    }
    else
    {
        /* Connect to Shield */
        *capsense_prtSelTbl[port] |= (capsense_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
    }
    #endif /* (capsense_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: capsense_SetDriveModeAllPins
********************************************************************************
*
* Summary:
* This API sets the drive mode of port pins used by the CapSense
* component (sensors, guard, shield, shield tank and Cmod) to drive the
* mode specified by the argument.
*
* Parameters:
*  driveMode:  Drive mode definition.
*
* Return:
*  None
*
* Global Variables:
*  capsense_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  capsense_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*
* Side Effects:
*  This API shall be called only after CapSense component is stopped.
*
*******************************************************************************/
void capsense_SetDriveModeAllPins(uint32 driveMode)
{
    uint8 curSensor;
    #if (capsense_IS_COMPLEX_SCANSLOTS)
        uint8 snsNumber;
        uint8 snsType;
    #endif  /* capsense_IS_COMPLEX_SCANSLOTS */
    uint32 prtNumberTmp;
    uint32 pinNumberTmp;

    for(curSensor = 0u; curSensor < capsense_TOTAL_SENSOR_COUNT; curSensor++)
    {
        #if (capsense_IS_COMPLEX_SCANSLOTS)
            /* Read sensor type: single or complex */
            snsType = capsense_portTable[curSensor];

            /* Check if sensor is complex */
            if ((snsType & capsense_COMPLEX_SS_FLAG) == 0u)
            {
                /* The sensor is not complex */
                snsNumber = curSensor;
            }
            else
            {
                /* Get dedicated sensor ID of the complex sensor */
                snsType &= ~capsense_COMPLEX_SS_FLAG;
                snsNumber = capsense_indexTable[snsType];
            }

            prtNumberTmp = capsense_portTable[snsNumber];
            pinNumberTmp = capsense_pinShiftTbl[snsNumber];
        #else
            prtNumberTmp = capsense_portTable[curSensor];
            pinNumberTmp = capsense_pinShiftTbl[curSensor];
        #endif  /* capsense_IS_COMPLEX_SCANSLOTS */

        capsense_SetPinDriveMode(driveMode, pinNumberTmp, prtNumberTmp);
    }

    capsense_SetPinDriveMode(driveMode, (uint32)capsense_CMOD_PIN_NUMBER, (uint32)capsense_CMOD_PRT_NUMBER);

    #if(0u != capsense_CSH_TANK_ENABLE)
        capsense_SetPinDriveMode(driveMode, (uint32)capsense_CTANK_PIN_NUMBER, (uint32)capsense_CTANK_PRT_NUMBER);
    #endif /* (0u != capsense_CSH_TANK_ENABLE) */

    #if(0u != capsense_IS_SHIELD_ENABLE)
        capsense_SetPinDriveMode(driveMode, (uint32)capsense_SHIELD_PIN_NUMBER, (uint32)capsense_SHIELD_PORT_NUMBER);
    #endif /* (0u != capsense_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: capsense_RestoreDriveModeAllPins
********************************************************************************
*
* Summary:
*  This API restores the drive for all the CapSense port pins to the original
*  state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*
* Side Effects:
*  This API is called only after the CapSense component is stopped.
*
*******************************************************************************/
void capsense_RestoreDriveModeAllPins(void)
{
    uint32 newRegisterValue;

    capsense_SetDriveModeAllPins(CY_SYS_PINS_DM_ALG_HIZ);

    newRegisterValue = capsense_CMOD_CONNECTION_REG;
    newRegisterValue &= ~(capsense_CSD_CMOD_CONNECTION_MASK);
    newRegisterValue |= capsense_CSD_CMOD_TO_AMUXBUS_A;
    capsense_CMOD_CONNECTION_REG = newRegisterValue;

    #if(0u != capsense_CSH_TANK_ENABLE)
        newRegisterValue = capsense_CTANK_CONNECTION_REG;
        newRegisterValue &= ~(capsense_CSD_CTANK_CONNECTION_MASK);
        newRegisterValue |= capsense_CSD_CTANK_TO_AMUXBUS_B;
        capsense_CTANK_CONNECTION_REG = newRegisterValue;
    #endif/* (0u != capsense_CSH_TANK_ENABLE) */

    #if(0u != capsense_IS_SHIELD_ENABLE)
        newRegisterValue = *capsense_prtSelTbl[capsense_SHIELD_PORT_NUMBER];
        newRegisterValue &= ~(capsense_CSD_HSIOM_MASK << ((uint32)capsense_SHIELD_PIN_NUMBER * capsense_HSIOM_PIN_CFG_SIZE));
        newRegisterValue |= (capsense_CSD_SHIELD_PORT_MODE << ((uint32)capsense_SHIELD_PIN_NUMBER * capsense_HSIOM_PIN_CFG_SIZE));
        *capsense_prtSelTbl[capsense_SHIELD_PORT_NUMBER] = newRegisterValue;
    #endif /* (0u != capsense_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: capsense_SetPinDriveMode
********************************************************************************
*
* Summary:
* This API sets the drive mode for the appropriate port/pin.
*
* Parameters:
*  driveMode:  Drive mode definition.
*  portNumber: contains port number (0, 1, 2).
*  pinNumber: contains pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  capsense_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  capsense_prtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  This API is called only after CapSense component is stopped.
*
*******************************************************************************/
void capsense_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber)
{
    uint32  pinModeShift;
    uint32 newRegisterValue;

    pinModeShift  = pinNumber * capsense_PC_PIN_CFG_SIZE;

    newRegisterValue = *capsense_prtCfgTbl[portNumber];
    newRegisterValue &= ~(capsense_CSD_PIN_MODE_MASK << pinModeShift);
    newRegisterValue |=  (uint32)((uint32)driveMode << pinModeShift);
    *capsense_prtCfgTbl[portNumber] =  newRegisterValue;
}


/*******************************************************************************
* Function Name: capsense_PreScan
********************************************************************************
*
* Summary:
*  Sets required settings, enables a sensor, removes Vref from AMUX and starts the
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
* capsense_widgetNumber[] - This array contains numbers of widgets for each sensor.
* capsense_widgetResolution[] - Contains the widget resolution.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_PreScan(uint32 sensor)
{
    uint8 widget;
    uint8 interruptState;
    uint32 newRegValue;
    uint32 counterResolution;

    #if(capsense_PRS_OPTIONS == capsense__PRS_AUTO)
        uint8 senseClkDivMath;
        uint8 sampleClkDivMath;
    #endif /* (capsense_PRS_OPTIONS == capsense__PRS_AUTO) */

    #if ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
         (0 != capsense_IS_OVERSAMPLING_EN))
        uint32 oversamplingFactor;
    #endif /* ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
               (0 != capsense_IS_OVERSAMPLING_EN)) */

    /* Define widget sensor belongs to */
    widget = capsense_widgetNumber[sensor];

    /* Recalculate Counter Resolution to MSB 16 bits */
    counterResolution = capsense_widgetResolution[widget];

    #if ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
         (0 != capsense_IS_OVERSAMPLING_EN))
        oversamplingFactor = capsense_GetBitValue(capsense_scanSpeedTbl, sensor);

        if(counterResolution < capsense_RESOLUTION_16_BITS)
        {
            counterResolution <<= oversamplingFactor;
            counterResolution |= (uint32)(capsense_RESOLUTION_8_BITS);
        }
    #endif /* ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
               (0 != capsense_IS_OVERSAMPLING_EN)) */

    #if (0u != capsense_IS_M0S8PERI_BLOCK)
        capsense_SenseClk_Stop();
        capsense_SampleClk_Stop();
    #endif /* (0u != capsense_IS_M0S8PERI_BLOCK) */

    #if (0u != capsense_MULTIPLE_FREQUENCY_SET)
        capsense_SampleClk_SetDividerValue((uint16)capsense_sampleClkDividerVal[sensor]);
        capsense_SenseClk_SetDividerValue((uint16)capsense_senseClkDividerVal[sensor]);
    #else
        capsense_SampleClk_SetDividerValue((uint16)capsense_sampleClkDividerVal);
        capsense_SenseClk_SetDividerValue((uint16)capsense_senseClkDividerVal);
    #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */

    #if (0u != capsense_IS_M0S8PERI_BLOCK)
        capsense_SampleClk_Start();
        capsense_SenseClk_StartEx(capsense_SampleClk__DIV_ID);

        #if(capsense_PRS_OPTIONS == capsense__PRS_NONE)
            CyIntDisable(capsense_ISR_NUMBER);
            capsense_CSD_CNT_REG = capsense_ONE_CYCLE;
            while(0u != (capsense_CSD_CNT_REG & capsense_RESOLUTION_16_BITS))
            {
            /* Wait until scanning is complete */
            }
            capsense_CSD_INTR_REG = 1u;
            CyIntClearPending(capsense_ISR_NUMBER);
            CyIntEnable(capsense_ISR_NUMBER);
        #endif /* capsense_PRS_OPTIONS == capsense__PRS_NONE */
    #endif /* (0u != capsense_IS_M0S8PERI_BLOCK) */

#if(capsense_PRS_OPTIONS != capsense__PRS_NONE)

    #if(capsense_TUNING_METHOD == capsense__TUNING_AUTO)
        if(capsense_prescalersTuningDone != 0u)
        {
    #endif /* (capsense_TUNING_METHOD == capsense__TUNING_AUTO) */

            CyIntDisable(capsense_ISR_NUMBER);

            newRegValue = capsense_CSD_CFG_REG;
            newRegValue |= capsense_CSD_CFG_PRS_SELECT;

            #if(capsense_PRS_OPTIONS == capsense__PRS_AUTO)

                newRegValue &= ~(capsense_PRS_MODE_MASK);

                #if (0u != capsense_MULTIPLE_FREQUENCY_SET)
                    senseClkDivMath = capsense_senseClkDividerVal[sensor];
                    sampleClkDivMath = capsense_sampleClkDividerVal[sensor];
                #else
                    senseClkDivMath = capsense_senseClkDividerVal;
                    sampleClkDivMath = capsense_sampleClkDividerVal;
                #endif /* ( capsense_MULTIPLE_FREQUENCY_SET) */

                #if(0u == capsense_IS_M0S8PERI_BLOCK)
                    senseClkDivMath *= sampleClkDivMath;
                #endif /* (0u == capsense_IS_M0S8PERI_BLOCK) */

                if((senseClkDivMath * capsense_RESOLUTION_12_BITS) <
                   (sampleClkDivMath * capsense_widgetResolution[widget]))
                {
                    newRegValue |= capsense_CSD_PRS_12_BIT;
                }
            #endif /* (capsense_PRS_OPTIONS == capsense__PRS_AUTO) */

            capsense_CSD_CFG_REG = newRegValue;

            CyIntEnable(capsense_ISR_NUMBER);

    #if(capsense_TUNING_METHOD == capsense__TUNING_AUTO)
        }
    #endif /* (capsense_PRS_OPTIONS != capsense__PRS_NONE) */

#endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */

    /* Set Idac Value */
    CyIntDisable(capsense_ISR_NUMBER);
    newRegValue = capsense_CSD_IDAC_REG;

#if (capsense_IDAC_CNT == 1u)
    newRegValue &= ~(capsense_CSD_IDAC1_DATA_MASK);
    newRegValue |= capsense_modulationIDAC[sensor];
#else
    newRegValue &= ~(capsense_CSD_IDAC1_DATA_MASK | capsense_CSD_IDAC2_DATA_MASK);
    newRegValue |= (capsense_modulationIDAC[sensor] |
                            (uint32)((uint32)capsense_compensationIDAC[sensor] <<
                            capsense_CSD_IDAC2_DATA_OFFSET));
#endif /* (capsense_IDAC_CNT == 1u) */

    capsense_CSD_IDAC_REG = newRegValue;

#if(capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRIOBUF)
    newRegValue = capsense_CMOD_CONNECTION_REG;
    newRegValue &= ~(capsense_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= capsense_CSD_CMOD_TO_AMUXBUS_A;
    capsense_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = capsense_CMOD_PORT_PC_REG;
    newRegValue &= ~(capsense_CSD_CMOD_PC_MASK);
    newRegValue |= capsense_CMOD_PC_HIGH_Z_MODE;
    capsense_CMOD_PORT_PC_REG = newRegValue;
#endif /* (capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRIOBUF) */

    /* Disconnect Vref Buffer from AMUX */
    newRegValue = capsense_CSD_CFG_REG;
    newRegValue &= ~(capsense_PRECHARGE_CONFIG_MASK);
    newRegValue |= capsense_CTANK_PRECHARGE_CONFIG;

    CyIntEnable(capsense_ISR_NUMBER);

    /* Enable Sensor */
    capsense_EnableScanSlot(sensor);

    interruptState = CyEnterCriticalSection();
    capsense_CSD_CFG_REG = newRegValue;

    /* `#START capsense_PreSettlingDelay_Debug` */

    /* `#END` */

#ifdef capsense_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK
    capsense_PreScan_Pre_SettlingDelay_Debug_Callback();
#endif /* capsense_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK */

    CyDelayCycles(capsense_GLITCH_ELIMINATION_CYCLES);

    /* `#START capsense_PreScan_Debug` */

    /* `#END` */

#ifdef capsense_PRE_SCAN_DEBUG_CALLBACK
    capsense_PreScan_Debug_Callback();
#endif /* capsense_PRE_SCAN_DEBUG_CALLBACK */

    capsense_CSD_CNT_REG = counterResolution;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: capsense_PostScan
********************************************************************************
*
* Summary:
*  Stores the results of measurement in the capsense_sensorRaw[] array,
*  sets the scanning sensor in the non-sampling state, turns off Idac(Current Source IDAC),
*  disconnects the IDAC(Sink mode), and applies Vref on AMUX.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  capsense_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_PostScan(uint32 sensor)
{
    uint32 newRegValue;
#if ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
     (0 != capsense_IS_OVERSAMPLING_EN))
    uint32 oversamplingFactor;
    uint32 widget;
#endif /* ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
           (0 != capsense_IS_OVERSAMPLING_EN)) */

    /* `#START capsense_PostScan_Debug` */

    /* `#END` */

#ifdef capsense_POST_SCAN_DEBUG_CALLBACK
    capsense_PostScan_Debug_Callback();
#endif /* capsense_POST_SCAN_DEBUG_Callback */

    /* Read SlotResult from Raw Counter */
    capsense_sensorRaw[sensor]  = (uint16)capsense_CSD_CNT_REG;

#if ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
     (0 != capsense_IS_OVERSAMPLING_EN))
    widget = capsense_widgetNumber[sensor];
    if(capsense_widgetResolution[widget] < capsense_RESOLUTION_16_BITS)
    {
        oversamplingFactor = capsense_GetBitValue(capsense_scanSpeedTbl, sensor);
        capsense_sensorRaw[sensor] >>= oversamplingFactor;
    }
#endif /* ((capsense_TUNING_METHOD == capsense__TUNING_AUTO) &&\
           (0 != capsense_IS_OVERSAMPLING_EN)) */

    /* Disable Sensor */
    capsense_DisableScanSlot(sensor);

    CyIntDisable(capsense_ISR_NUMBER);

#if(capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRIOBUF)
    newRegValue = capsense_CMOD_CONNECTION_REG;
    newRegValue &= ~(capsense_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= capsense_CSD_CMOD_TO_AMUXBUS_B;
    capsense_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = capsense_CMOD_PORT_PC_REG;
    newRegValue &= ~(capsense_CSD_CMOD_PC_MASK);
    newRegValue |= capsense_CMOD_PC_STRONG_MODE;
    capsense_CMOD_PORT_PC_REG = newRegValue;

    newRegValue = capsense_CMOD_PORT_DR_REG;
    newRegValue &= ~(capsense_CMOD_DR_MASK);
    newRegValue |= capsense_CMOD_DR_CONFIG;
    capsense_CMOD_PORT_DR_REG = newRegValue;
#endif /* (capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRIOBUF) */

    /* Connect Vref Buffer to AMUX bus  */
    newRegValue = capsense_CSD_CFG_REG;
    newRegValue &= ~(capsense_PRECHARGE_CONFIG_MASK);
    newRegValue |= capsense_CMOD_PRECHARGE_CONFIG;
    capsense_CSD_CFG_REG = newRegValue;

    /* Set Idac Value = 0 */
#if (capsense_IDAC_CNT == 1u)
    capsense_CSD_IDAC_REG &= ~(capsense_CSD_IDAC1_DATA_MASK);
#else
    capsense_CSD_IDAC_REG &= ~(capsense_CSD_IDAC1_DATA_MASK | capsense_CSD_IDAC2_DATA_MASK);
#endif /* (capsense_IDAC_CNT == 1u) */

    CyIntEnable(capsense_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: capsense_EnableShieldElectrode
********************************************************************************
*
* Summary:
*  This API enables or disables the shield electrode on a specified port pin.
*
* Parameters:
*  portNumber: contains the shield electrode port number (0, 1, 2).
*  pinNumber: contains the shield electrode pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  capsense_prtCfgTbl[] - Contains pointers to the port config registers for each port.
*  capsense_prtSelTbl[] - Contains pointers to the HSIOM registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber)
{
    uint32 newRegValue;

    *capsense_prtCfgTbl[portNumber] &= ~(capsense_CSD_PIN_MODE_MASK << (pinNumber * capsense_PC_PIN_CFG_SIZE));
    newRegValue = *capsense_prtSelTbl[portNumber];
    newRegValue &= ~(capsense_CSD_HSIOM_MASK << (pinNumber * capsense_HSIOM_PIN_CFG_SIZE));
    newRegValue |= (capsense_CSD_SHIELD_PORT_MODE << (pinNumber * capsense_HSIOM_PIN_CFG_SIZE));
    *capsense_prtSelTbl[portNumber] = newRegValue;
}


/*******************************************************************************
* Function Name: capsense_SetShieldDelay
********************************************************************************
*
* Summary:
*  This API sets a shield delay.
*
* Parameters:
*  delay:  shield delay value:
*                               0 - no delay
*                               1 - 1 cycle delay
*                               2 - 2 cycles delay
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
void capsense_SetShieldDelay(uint32 delay)
{
    uint32 newRegValue;

    delay &= 0x03u;

    newRegValue = capsense_CSD_CFG_REG;
    newRegValue &= (uint32)(~(uint32)capsense_SHIELD_DELAY);
    newRegValue |= (delay << capsense_CSD_CFG_SHIELD_DELAY_POS);
    capsense_CSD_CFG_REG = newRegValue;
}


/*******************************************************************************
* Function Name: capsense_ReadCurrentScanningSensor
********************************************************************************
*
* Summary:
*  This API returns scanning sensor number when sensor scan is in progress.
*  When sensor scan is completed the API returns
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) (when no sensor is scanned).
*
* Parameters:
*   None.
*
* Return:
*  Returns Sensor number if sensor is being scanned and
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) if scanning is complete.
*
* Global Variables:
*  capsense_sensorIndex - the sensor number is being scanned.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_ReadCurrentScanningSensor(void)
{
    return ((uint32)(( 0u != (capsense_csdStatusVar & capsense_SW_STS_BUSY)) ?
                     capsense_sensorIndex : capsense_NOT_SENSOR));
}


/*******************************************************************************
* Function Name: capsense_GetBitValue
********************************************************************************
*
* Summary:
*  The API returns a bit status of the bit in the table array which contains the masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*
* Return:
*  0 - bit is not set; 1 - bit is set.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetBitValue(const uint8 table[], uint32 position)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    return ((0u !=(table[offset] & enMask)) ? 1Lu : 0Lu);
}


/*******************************************************************************
* Function Name: capsense_SetBitValue
********************************************************************************
*
* Summary:
*  The API sets a bit status of the bit in the table array which contains masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*  value: 0 - bit is not set; 1 - bit is set.
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
void capsense_SetBitValue(uint8 table[], uint32 position, uint32 value)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    if(0u != value)
    {
        table[offset] |= enMask;
    }
    else
    {
        table[offset] &= (uint8)~(enMask);
    }
}



/*******************************************************************************
* Function Name: capsense_GetSenseClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the sense clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (capsense_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the sense clock divider of the sensor.
*
* Global Variables:
*  capsense_senseClkDividerVal[] - stores the sense clock divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetSenseClkDivider(uint32 sensor)
{
    #if(0u != capsense_MULTIPLE_FREQUENCY_SET)
        return((uint32)capsense_senseClkDividerVal[sensor]);
    #else
        return((uint32)capsense_senseClkDividerVal);
    #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
}

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    /*******************************************************************************
    * Function Name: capsense_SetSenseClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the sense clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  senseClk: represents the sense clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  capsense_senseClkDividerVal[] - stores the sense clock divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetSenseClkDivider(uint32 sensor, uint32 senseClk)
    {
        #if(0u != capsense_MULTIPLE_FREQUENCY_SET)
            capsense_senseClkDividerVal[sensor] = (uint8)senseClk;
        #else
            capsense_senseClkDividerVal = (uint8)senseClk;
        #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */


/*******************************************************************************
* Function Name: capsense_GetModulatorClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the modulator sample clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be
*  from 0 to (capsense_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulator sample clock divider for the  sensor.
*
* Global Variables:
*  capsense_sampleClkDividerVal[] - stores the modulator sample divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetModulatorClkDivider(uint32 sensor)
{
    #if(0u != capsense_MULTIPLE_FREQUENCY_SET)
        return((uint32)capsense_sampleClkDividerVal[sensor]);
    #else
        return((uint32)capsense_sampleClkDividerVal);
    #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
}

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    /*******************************************************************************
    * Function Name: capsense_SetModulatorClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulator sample clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  modulatorClk: represents the modulator sample clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  capsense_sampleClkDividerVal[] - stores the modulator sample divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk)
    {
        #if(0u != capsense_MULTIPLE_FREQUENCY_SET)
            capsense_sampleClkDividerVal[sensor] = (uint8)modulatorClk;
        #else
            capsense_sampleClkDividerVal = (uint8)modulatorClk;
        #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */

/*******************************************************************************
* Function Name: capsense_GetModulationIDAC
********************************************************************************
*
* Summary:
*  This API returns a value of the modulation IDAC for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (capsense_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulation IDAC of the sensor.
*
* Global Variables:
*  capsense_modulationIDAC[] - stores modulation IDAC values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetModulationIDAC(uint32 sensor)
{
        return((uint32)capsense_modulationIDAC[sensor]);
}

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    /*******************************************************************************
    * Function Name: capsense_SetModulationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the modulation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  capsense_modulationIDAC[] - array with modulation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetModulationIDAC(uint32 sensor, uint32 modIdacValue)
    {
        capsense_modulationIDAC[sensor] = (uint8)modIdacValue;
    }
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */


#if(capsense_IDAC_CNT > 1u)
    /*******************************************************************************
    * Function Name: capsense_GetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API returns a value of the compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor: sensor index. The index value can be
    *  from 0 to (capsense_TOTAL_SENSOR_COUNT-1).
    *
    * Return:
    *  This API returns the compensation IDAC of the sensor.
    *
    * Global Variables:
    *  capsense_compensationIDAC[] - stores the compensation IDAC values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint32 capsense_GetCompensationIDAC(uint32 sensor)
    {
        return((uint32)capsense_compensationIDAC[sensor]);
    }
#endif /* (capsense_IDAC_CNT > 1u) */


#if((capsense_TUNING_METHOD != capsense__TUNING_NONE) && (capsense_IDAC_CNT > 1u))
    /*******************************************************************************
    * Function Name: capsense_SetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the compensation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  capsense_compensationIDAC[] - an array with compensation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue)
    {
        capsense_compensationIDAC[sensor] = (uint8)compIdacValue;
    }
#endif /* ((capsense_TUNING_METHOD != capsense__TUNING_NONE) && (capsense_IDAC_CNT > 1u)) */

/*******************************************************************************
* Function Name: capsense_GetIDACRange
********************************************************************************
*
* Summary:
*  This API returns a value that indicates the IDAC range used by the
*  component to scan sensors. The IDAC range is common for all the sensors.
*
* Parameters:
*  None
*
* Return:
*  This API Returns a value that indicates the IDAC range:
*      0 - IDAC range set to 4x
*      1 - IDAC range set to 8x
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 capsense_GetIDACRange(void)
{
    return((0u != (capsense_CSD_IDAC_REG & capsense_CSD_IDAC1_RANGE_8X)) ? 1uL : 0uL);
}

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    /*******************************************************************************
    * Function Name: capsense_SetIDACRange
    ********************************************************************************
    *
    * Summary:
    *  This API sets the IDAC range to the 4x (1.2uA/bit) or 8x (2.4uA/bit) mode.
    *  The IDAC range is common for all the sensors and common for the modulation and
    *  compensation IDACs.
    *
    * Parameters:
    *  iDacRange:  represents value for IDAC range
    *  0 -  IDAC range set to 4x (1.2uA/bit)
    *  1 or >1 - IDAC range set to 8x (2.4uA/bit)
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void capsense_SetIDACRange(uint32 iDacRange)
    {
        if(iDacRange != 0u)
        {
            /*  IDAC range = 8x (2.4uA/bit) */
            capsense_CSD_IDAC_REG |= (capsense_CSD_IDAC1_RANGE_8X |\
                                              capsense_CSD_IDAC2_RANGE_8X);
        }
        else
        {
            /*  IDAC range = 4x (1.2uA/bit) */
            /*  IDAC range = 8x (2.4uA/bit) */
            capsense_CSD_IDAC_REG &= ~(capsense_CSD_IDAC1_RANGE_8X |\
                                               capsense_CSD_IDAC2_RANGE_8X);
        }
    }
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */


#if((0u != capsense_AUTOCALIBRATION_ENABLE) || (capsense_TUNING_METHOD == capsense__TUNING_AUTO))
    /*******************************************************************************
    * Function Name: capsense_GetSensorRaw
    ********************************************************************************
    *
    * Summary:
    *  The API updates and gets uprated raw data from the sensor.
    *
    * Parameters:
    *  sensor - Sensor number.
    *
    * Return:
    *  Returns the current raw data value for a defined sensor number.
    *
    * Global Variables:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint16  capsense_GetSensorRaw(uint32 sensor)
    {
        uint32 curSample;
        uint32 avgVal = 0u;

        for(curSample = 0u; curSample < capsense_AVG_SAMPLES_NUM; curSample++)
        {

            capsense_ScanSensor((uint32)sensor);
            while(capsense_IsBusy() == 1u)
            {
                /* Wait while sensor is busy */
            }
            avgVal += capsense_ReadSensorRaw((uint32)sensor);
        }

        return((uint16)(avgVal / capsense_AVG_SAMPLES_NUM));
    }
#endif /* ((0u != capsense_AUTOCALIBRATION_ENABLE) && (capsense_TUNING_METHOD == capsense__TUNING_AUTO)) */


#if((0u != capsense_AUTOCALIBRATION_ENABLE) && (capsense_TUNING_METHOD != capsense__TUNING_AUTO))
    /*******************************************************************************
    * Function Name: capsense_CalibrateSensor
    ********************************************************************************
    *
    * Summary:
    *  Computes the one sensor IDAC value, which provides the raw signal on
    *  a specified level, with a specified prescaler, speed, and resolution.
    *
    * Parameters:
    *  sensor - Sensor Number.
    *
    *  rawLevel -  Raw data level which should be reached during the calibration
    *              procedure.
    *
    *  idacLevelsTbl - Pointer to the modulatorIdac data register configuration table.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void capsense_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[])
    {
        uint8 mask;
        uint16 rawData;

        rawData = 0u;

        mask = 0x80u;
        /* Init IDAC for null Channel */
        idacLevelsTbl[sensor] = 0x00u;

        do
        {
            /* Set bit for null Channel */
            idacLevelsTbl[sensor] |= mask;

            /* Scan null Channel and get Rawdata */
            rawData = capsense_GetSensorRaw(sensor);

            /* Decrease IDAC until Rawdata reaches rawLevel */
            if(rawData < rawLevel)
            {
                /* Reset bit for null Channel  */
                idacLevelsTbl[sensor] &= (uint8)~mask;
            }

            mask >>= 1u;
        }
        while(mask > 0u);

    }
#endif /* ((0u != capsense_AUTOCALIBRATION_ENABLE) && (capsense_TUNING_METHOD != capsense__TUNING_AUTO)) */


/*******************************************************************************
* Function Name: capsense_SetUnscannedSensorState
********************************************************************************
*
* Summary:
*  This API sets a state for un-scanned sensors.
*  It is possible to set the state to Ground, High-Z, or the shield electrode.
*  The un-scanned sensor can be connected to a shield electrode only if the shield is
*  enabled. If the shield is disabled and this API is called with the parameter which
*  indicates the shield state, the un-scanned sensor will be connected to Ground.
*
* Parameters:
*  sensor - Sensor Number.
*  sensorState: This parameter indicates un-scanned sensor state:
*
*     capsense__GROUND 0
*     capsense__HIZ_ANALOG 1
*     capsense__SHIELD 2
*
* Return:
*  None.
*
* Global Variables:
*  capsense_unscannedSnsDriveMode[] - used to store the state for
*  un-scanned sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_SetUnscannedSensorState(uint32 sensor, uint32 sensorState)
{
    #if(capsense_IS_COMPLEX_SCANSLOTS)
        uint8 snsType;
        uint8 curSensor;
        uint16 snsNumber;

        /* Read sensor type: single or complex */
        snsType = capsense_portTable[sensor];

        /* Check if sensor is complex */
        if(0u != (snsType & capsense_COMPLEX_SS_FLAG))
        {
            snsType &= (uint8)~capsense_COMPLEX_SS_FLAG;
            snsNumber = (uint16)capsense_maskTable[sensor];

            for (curSensor=0u; curSensor < snsNumber; curSensor++)
            {
                sensor = capsense_indexTable[snsType + curSensor];
                capsense_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
            }
        }
        else
        {
            capsense_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
        }
    #else
        capsense_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
    #endif /* (capsense_IS_COMPLEX_SCANSLOTS) */
}

#if(0u != capsense_TOTAL_CENTROIDS_COUNT)
/*******************************************************************************
* Function Name: capsense_NormalizeWidgets
********************************************************************************
*
* Summary:
*  This API aligns all the parameters of the widget to the maximum parameter.
*
* Parameters:
*  uint32 widgetsNum: Number of widgets.
*  uint8 *dataPrt: pointer to array with widget parameters.
*
* Return:
*  None
*
* Global Variables:
*  capsense_numberOfSensors[] - Number of sensors in the widget.
*  capsense_rawDataIndex[currentWidget] - Contains the  1st sensor
*  position in the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[])
{
    uint32 currentWidget;
    uint32 currentSensor;
    uint32 lastSensor;
    uint32 sensorsPerWidget;
    uint32 maxPerWidget;

    for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
    {
        maxPerWidget = 0u;

        sensorsPerWidget = capsense_numberOfSensors[currentWidget];
        currentSensor = capsense_rawDataIndex[currentWidget];
        lastSensor = currentSensor + sensorsPerWidget;

        while(currentSensor < lastSensor)
        {
            if(maxPerWidget < dataPtr[currentSensor])
            {
                maxPerWidget = dataPtr[currentSensor];
            }
            currentSensor++;
        }

        currentSensor = capsense_rawDataIndex[currentWidget];

        while(currentSensor < lastSensor)
        {
            dataPtr[currentSensor] = (uint8)maxPerWidget;
            currentSensor++;
        }
    }
}
#endif /* (0u != capsense_TOTAL_CENTROIDS_COUNT) */

/* [] END OF FILE */
