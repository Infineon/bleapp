/*******************************************************************************
* File Name: capsense.h
* Version 2.60
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
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

#if !defined(CY_CAPSENSE_CSD_capsense_H)
#define CY_CAPSENSE_CSD_capsense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "capsense_IP.h"
#include "capsense_SenseClk.h"
#include "capsense_SampleClk.h"

/* Constants set by Customizer */
#define capsense_TOTAL_SENSOR_COUNT            (5u)
#define capsense_TOTAL_SCANSLOT_COUNT          (5u)
#define capsense_INDEX_TABLE_SIZE              (0u)

/* Define Sensors */
#define capsense_SENSOR_LINEARSLIDER0_E0__LS    (0u)
#define capsense_SENSOR_LINEARSLIDER0_E1__LS    (1u)
#define capsense_SENSOR_LINEARSLIDER0_E2__LS    (2u)
#define capsense_SENSOR_LINEARSLIDER0_E3__LS    (3u)
#define capsense_SENSOR_LINEARSLIDER0_E4__LS    (4u)

#define capsense_TOTAL_SENSOR_MASK (((capsense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

/* Interrupt handler */
CY_ISR_PROTO(capsense_ISR);

/* ISR Number and Priority to work with CyLib functions */
#define capsense_ISR_NUMBER        (capsense_ISR__INTC_NUMBER)
#define capsense_ISR_PRIORITY      (capsense_ISR__INTC_PRIOR_NUM)

/***************************************
*   Condition compilation parameters
***************************************/

#define capsense_CONNECT_INACTIVE_SNS       (0u)
#define capsense_IS_COMPLEX_SCANSLOTS       (0u)
#define capsense_COMPLEX_SCANSLOTS_NUM      (0u)
#define capsense_DEDICATED_SENSORS_NUM      (0u)
#define capsense_PORT_PIN_CONFIG_TBL_ZISE   (5u)

#define capsense_IDAC_CNT                   (2u)
#define capsense_IDAC1_POLARITY             (0u)
#define capsense_IDAC1_RANGE_VALUE          (0u)
#define capsense_IDAC2_RANGE_VALUE          (0u)

#define capsense_MULTIPLE_FREQUENCY_SET     (1u)
#define capsense_FILTER_ENABLE              (0u)
#define capsense_PRS_OPTIONS                (0u)

#define capsense_WATER_PROOF                (0u)

#define capsense_TUNING_METHOD              (2u)
#define capsense_TUNER_API_GENERATE         (0u)

#define capsense_CSHL_API_GENERATE          (1u)

#define capsense_CMOD_PREGARGE_OPTION       (1u)
#define capsense_CSH_TANK_PREGARGE_OPTION   (0u)
#define capsense_IS_SHIELD_ENABLE           (0u)
#define capsense_CSH_TANK_ENABLE            (0u)

#define capsense_SHIELD_DELAY               (0u)
#define capsense_AUTOCALIBRATION_ENABLE     (0u)

#define capsense_IS_OVERSAMPLING_EN         (1u)

#define capsense_CSD_4B_PWM_MODE            (0u)
#define capsense_CSD_4B_PWM_COUNT           (0u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
#define capsense__IDAC_SOURCE 0
#define capsense__IDAC_SINK 1

#define capsense__IDAC_4X 0
#define capsense__IDAC_8X 1

#define capsense__PRS_NONE 0
#define capsense__PRS_8BITS 1
#define capsense__PRS_12BITS 2
#define capsense__PRS_AUTO 3

/* Connection of inactive sensors definitions */
#define capsense__GROUND 0
#define capsense__HIZ_ANALOG 1
#define capsense__SHIELD 2

/* Precharge options definitions */
#define capsense__CAPPRIOBUF 0
#define capsense__CAPPRVREF 1

/* Method of tuning */
#define capsense__TUNING_NONE 0
#define capsense__TUNING_MANUAL 1
#define capsense__TUNING_AUTO 2

/* Dead band PWM modulator options */
#define capsense__PWM_OFF 0
#define capsense__PWM_HIGH 2
#define capsense__PWM_LOW 3


#define capsense_DELAY_EXTRACYCLES_NUM          (9u)
#define capsense_GLITCH_ELIMINATION_TIMEOUT     (0u)
#define capsense_GLITCH_ELIMINATION_CYCLES_CALC (capsense_GLITCH_ELIMINATION_TIMEOUT * CYDEV_BCLK__SYSCLK__MHZ)

#if(capsense_GLITCH_ELIMINATION_CYCLES_CALC >= capsense_DELAY_EXTRACYCLES_NUM)
    #define capsense_GLITCH_ELIMINATION_CYCLES (capsense_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                        capsense_DELAY_EXTRACYCLES_NUM)
#else
    #define capsense_GLITCH_ELIMINATION_CYCLES (capsense_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (capsense_GLITCH_ELIMINATION_CYCLES_CALC >= capsense_DELAY_EXTRACYCLES_NUM) */

#define capsense_INITIAL_CLK_DIVIDER            (CYDEV_BCLK__HFCLK__KHZ / CYDEV_BCLK__SYSCLK__KHZ)


/* Structure to save registers before going to sleep */
typedef struct
{
    uint8 enableState;
} capsense_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/
void capsense_Init(void);
void capsense_CsdHwBlockInit(void);
void capsense_Enable(void);
void capsense_Start(void);
void capsense_Stop(void);
void capsense_SaveConfig(void);
void capsense_Sleep(void);
void capsense_RestoreConfig(void);
void capsense_Wakeup(void);
uint32 capsense_IsBusy(void);
void capsense_ScanSensor(uint32 sensor);
void capsense_ScanWidget(uint32 widget);
void capsense_ScanEnabledWidgets(void);
uint16 capsense_ReadSensorRaw(uint32 sensor);
void capsense_WriteSensorRaw(uint32 sensor, uint16 value);
void capsense_ClearSensors(void);
void capsense_SetShieldDelay(uint32 delay);
uint32 capsense_ReadCurrentScanningSensor(void);

uint32 capsense_GetScanResolution(uint32 widget);
uint32 capsense_GetSenseClkDivider(uint32 sensor);
uint32 capsense_GetModulatorClkDivider(uint32 sensor);
uint32 capsense_GetModulationIDAC(uint32 sensor);
uint32 capsense_GetCompensationIDAC(uint32 sensor);
uint32 capsense_GetIDACRange(void);

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    void capsense_SetScanResolution(uint32 widget, uint32 resolution);
    void capsense_SetSenseClkDivider(uint32 sensor, uint32 senseClk);
    void capsense_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk);
    void capsense_SetModulationIDAC(uint32 sensor, uint32 modIdacValue);
    void capsense_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue);
    void capsense_SetIDACRange(uint32 iDacRange);
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */


void capsense_SetDriveModeAllPins(uint32 driveMode);
void capsense_RestoreDriveModeAllPins(void);
void capsense_SetUnscannedSensorState(uint32 sensor, uint32 sensorState);
void capsense_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[]);

/***************************************
*           API Constants
***************************************/

/* PWM Resolution */
#define capsense_CNT_MSB_RESOLUTION_8_BITS  (0x00u)
#define capsense_CNT_MSB_RESOLUTION_9_BITS  (0x01u)
#define capsense_CNT_MSB_RESOLUTION_10_BITS (0x03u)
#define capsense_CNT_MSB_RESOLUTION_11_BITS (0x07u)
#define capsense_CNT_MSB_RESOLUTION_12_BITS (0x0Fu)
#define capsense_CNT_MSB_RESOLUTION_13_BITS (0x1Fu)
#define capsense_CNT_MSB_RESOLUTION_14_BITS (0x3Fu)
#define capsense_CNT_MSB_RESOLUTION_15_BITS (0x7Fu)
#define capsense_CNT_MSB_RESOLUTION_16_BITS (0xFFu)

#define capsense_ONE_CYCLE                  (0x00010000Lu)

#define capsense_WINDOW_APPEND              (0xFFFF0000Lu)
#define capsense_RESOLUTION_6_BITS          (0x003F0000Lu)
#define capsense_RESOLUTION_7_BITS          (0x007F0000Lu)
#define capsense_RESOLUTION_8_BITS          (0x00FF0000Lu)
#define capsense_RESOLUTION_9_BITS          (0x01FF0000Lu)
#define capsense_RESOLUTION_10_BITS         (0x03FF0000Lu)
#define capsense_RESOLUTION_11_BITS         (0x07FF0000Lu)
#define capsense_RESOLUTION_12_BITS         (0x0FFF0000Lu)
#define capsense_RESOLUTION_13_BITS         (0x1FFF0000Lu)
#define capsense_RESOLUTION_14_BITS         (0x3FFF0000Lu)
#define capsense_RESOLUTION_15_BITS         (0x7FFF0000Lu)
#define capsense_RESOLUTION_16_BITS         (0xFFFF0000Lu)

#define capsense_RESOLUTION_OFFSET          (16u)
#define capsense_MSB_RESOLUTION_OFFSET      (22u)
#define capsense_RESOLUTIONS_TBL_SIZE       (1u)

/* Software Status Register Bit Masks */
#define capsense_SW_STS_BUSY                (0x01u)
/* Software Control Register Bit Masks */
#define capsense_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Software Control Register Bit Masks for scanning one widget */
#define capsense_SW_CTRL_WIDGET_SCAN        (0x40u)

/* Flag for complex scan slot */
#define capsense_COMPLEX_SS_FLAG            (0x80u)

/* Flag for scanning is complete */
#define capsense_NOT_SENSOR                 (0xFFFFFFFFLu)

/* Number of bits for each pin in PC register. */
#define capsense_PC_PIN_CFG_SIZE            (0x03u)

/* Number of bits for each pin in HSIOM register. */
#define capsense_HSIOM_PIN_CFG_SIZE         (0x04u)

#define capsense_CFG_REG_TBL_SIZE           (7u)

/***************************************
*             Registers
***************************************/

#define capsense_CSD_ID_REG             (*(reg32 *)  capsense_CSD_FFB__CSD_ID)
#define capsense_CSD_ID_PTR             ( (reg32 *)  capsense_CSD_FFB__CSD_ID)

#define capsense_CSD_CFG_REG            (*(reg32 *)  capsense_CSD_FFB__CSD_CONFIG)
#define capsense_CSD_CFG_PTR            ( (reg32 *)  capsense_CSD_FFB__CSD_CONFIG)

#define capsense_CSD_IDAC_REG           (*(reg32 *)  capsense_IDAC1_cy_psoc4_idac__CSD_IDAC)
#define capsense_CSD_IDAC_PTR           ( (reg32 *)  capsense_IDAC1_cy_psoc4_idac__CSD_IDAC)

#define capsense_CSD_CNT_REG            (*(reg32 *) capsense_CSD_FFB__CSD_COUNTER)
#define capsense_CSD_CNT_PTR            ( (reg32 *) capsense_CSD_FFB__CSD_COUNTER)

#define capsense_CSD_STAT_REG           (*(reg32 *) capsense_CSD_FFB__CSD_STATUS)
#define capsense_CSD_STAT_PTR           ( (reg32 *) capsense_CSD_FFB__CSD_STATUS)

#define capsense_CSD_INTR_REG           (*(reg32 *) capsense_CSD_FFB__CSD_INTR)
#define capsense_CSD_INTR_PTR           ( (reg32 *) capsense_CSD_FFB__CSD_INTR)

#define capsense_CSD_INTR_SET_REG       (*(reg32 *) capsense_CSD_FFB__CSD_INTR_SET)
#define capsense_CSD_INTR_SET_PTR       ( (reg32 *) capsense_CSD_FFB__CSD_INTR_SET)

#define capsense_CSD_4B_PWM_REG         (*(reg32 *) capsense_CSD_FFB__CSD_PWM)
#define capsense_CSD_4B_PWM_PTR         ( (reg32 *) capsense_CSD_FFB__CSD_PWM)

#define capsense_CSD_TRIM1_REG          (*(reg32 *) capsense_IDAC1_cy_psoc4_idac__CSD_TRIM1)
#define capsense_CSD_TRIM1_PTR          ( (reg32 *) capsense_IDAC1_cy_psoc4_idac__CSD_TRIM1)

#define capsense_CSD_TRIM2_REG          (*(reg32 *) capsense_IDAC1_cy_psoc4_idac__CSD_TRIM2)
#define capsense_CSD_TRIM2_PTR          ( (reg32 *) capsense_IDAC1_cy_psoc4_idac__CSD_TRIM2)

#if (2u == capsense_M0S8CSD_BLOCK_CNT)
    #if (capsense_CSD_FFB__CSD_NUMBER != 1u)
        #define capsense_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
        #define capsense_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

        #define capsense_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #define capsense_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #else
        #define capsense_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
        #define capsense_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

        #define capsense_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
        #define capsense_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
    #endif /* (capsense_CSD_FFB__CSD_NUMBER != 1u) */
#else
    #define capsense_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
    #define capsense_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

    #define capsense_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #define capsense_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#endif /* (2u == capsense_M0S8CSD_BLOCK_CNT) */

/* Port function select */
#define capsense_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define capsense_PORT_SEL0_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define capsense_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define capsense_PORT_SEL1_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define capsense_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define capsense_PORT_SEL2_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define capsense_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define capsense_PORT_SEL3_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define capsense_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define capsense_PORT_SEL4_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )

#define capsense_PORT_SEL5_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL5 )
#define capsense_PORT_SEL5_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL5 )

#define capsense_PORT_SEL6_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL6 )
#define capsense_PORT_SEL6_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL6 )


#define capsense_PORT0_PC_REG          (*(reg32 *) CYREG_GPIO_PRT0_PC )
#define capsense_PORT0_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT0_PC )

#define capsense_PORT1_PC_REG          (*(reg32 *) CYREG_GPIO_PRT1_PC )
#define capsense_PORT1_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT1_PC )

#define capsense_PORT2_PC_REG          (*(reg32 *) CYREG_GPIO_PRT2_PC )
#define capsense_PORT2_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT2_PC )

#define capsense_PORT3_PC_REG          (*(reg32 *) CYREG_GPIO_PRT3_PC )
#define capsense_PORT3_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT3_PC )

#define capsense_PORT4_PC_REG          (*(reg32 *) CYREG_GPIO_PRT4_PC )
#define capsense_PORT4_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT4_PC )

#define capsense_PORT5_PC_REG          (*(reg32 *) CYREG_GPIO_PRT5_PC )
#define capsense_PORT5_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT5_PC )

#define capsense_PORT6_PC_REG          (*(reg32 *) CYREG_GPIO_PRT6_PC )
#define capsense_PORT6_PC_PTR          (*(reg32 *) CYREG_GPIO_PRT6_PC )


#define capsense_PORT0_DR_REG          (*(reg32 *) CYREG_GPIO_PRT0_DR )
#define capsense_PORT0_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT0_DR )

#define capsense_PORT1_DR_REG          (*(reg32 *) CYREG_GPIO_PRT1_DR )
#define capsense_PORT1_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT1_DR )

#define capsense_PORT2_DR_REG          (*(reg32 *) CYREG_GPIO_PRT2_DR )
#define capsense_PORT2_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT2_DR )

#define capsense_PORT3_DR_REG          (*(reg32 *) CYREG_GPIO_PRT3_DR )
#define capsense_PORT3_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT3_DR )

#define capsense_PORT4_DR_REG          (*(reg32 *) CYREG_GPIO_PRT4_DR )
#define capsense_PORT4_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT4_DR )

#define capsense_PORT5_DR_REG          (*(reg32 *) CYREG_GPIO_PRT5_DR )
#define capsense_PORT5_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT5_DR )

#define capsense_PORT6_DR_REG          (*(reg32 *) CYREG_GPIO_PRT6_DR )
#define capsense_PORT6_DR_PTR          (*(reg32 *) CYREG_GPIO_PRT6_DR )



#define capsense_CMOD_CONNECTION_REG        (*(reg32 *) capsense_Cmod__0__HSIOM)
#define capsense_CMOD_PORT_PC_REG           (*(reg32 *) capsense_Cmod__0__PC)
#define capsense_CMOD_PORT_DR_REG           (*(reg32 *) capsense_Cmod__0__DR)

#define capsense_CTANK_CONNECTION_REG       (*(reg32 *) capsense_Csh_tank__0__HSIOM)
#define capsense_CTANK_PORT_PC_REG          (*(reg32 *) capsense_Csh_tank__0__PC)
#define capsense_CTANK_PORT_DR_REG          (*(reg32 *) capsense_Csh_tank__0__DR)

/***************************************
*       Register Constants
***************************************/

/* Port configuration defines */
#define capsense_CSD_HSIOM_MASK                 (0x0000000FLu)

#define capsense_CSD_SENSE_PORT_MODE            (0x00000004Lu)
#define capsense_CSD_SHIELD_PORT_MODE           (0x00000005Lu)

#define capsense_AMUXA_CONNECTION_MODE          (0x00000006Lu)
#define capsense_AMUXB_CONNECTION_MODE          (0x00000007Lu)

#define capsense_CSD_PIN_MODE_MASK              (0x00000007Lu)
#define capsense_CSD_PIN_DRIVE_MASK             (0x00000001Lu)

#define capsense_CSD_PIN_DM_STRONG              (0x00000006Lu)
#define capsense_CSD_PIN_DM_HIGH_Z              (0x00000000Lu)

#define capsense_CSD_CMOD_CONNECTION_MASK   (uint32)(capsense_Cmod__0__HSIOM_MASK)
#define capsense_CSD_CMOD_TO_AMUXBUS_A      (uint32)(capsense_AMUXA_CONNECTION_MODE << capsense_Cmod__0__HSIOM_SHIFT)
#define capsense_CSD_CMOD_TO_AMUXBUS_B      (uint32)(capsense_AMUXB_CONNECTION_MODE << capsense_Cmod__0__HSIOM_SHIFT)

#if(0u != capsense_CSH_TANK_ENABLE)
    #define capsense_CSD_CTANK_CONNECTION_MASK  (uint32)(capsense_Csh_tank__0__HSIOM_MASK)
    #define capsense_CSD_CTANK_TO_AMUXBUS_A     (uint32)(capsense_AMUXA_CONNECTION_MODE << capsense_Csh_tank__0__HSIOM_SHIFT)
    #define capsense_CSD_CTANK_TO_AMUXBUS_B     (uint32)(capsense_AMUXB_CONNECTION_MODE << capsense_Csh_tank__0__HSIOM_SHIFT)
#endif /* (0u != capsense_CSH_TANK_ENABLE) */

#define  capsense_CSD_CMOD_PC_MASK          (uint32)(capsense_CSD_PIN_MODE_MASK <<\
                                                            ((uint32)capsense_Cmod__0__SHIFT * capsense_PC_PIN_CFG_SIZE))
#define  capsense_CMOD_PC_STRONG_MODE       (uint32)(capsense_CSD_PIN_DM_STRONG <<\
                                                            ((uint32)capsense_Cmod__0__SHIFT * capsense_PC_PIN_CFG_SIZE))
#define  capsense_CMOD_PC_HIGH_Z_MODE       (uint32)(capsense_CSD_PIN_DM_HIGH_Z <<\
                                                            ((uint32)capsense_Cmod__0__SHIFT * capsense_PC_PIN_CFG_SIZE))

#if(0u != capsense_CSH_TANK_ENABLE)
    #define  capsense_CSD_CTANK_PC_MASK         (uint32)(capsense_CSD_PIN_MODE_MASK <<\
                                                                ((uint32)capsense_Csh_tank__0__SHIFT * capsense_PC_PIN_CFG_SIZE))
    #define  capsense_CTANK_PC_STRONG_MODE      (uint32)(capsense_CSD_PIN_DM_STRONG <<\
                                                                ((uint32)capsense_Csh_tank__0__SHIFT * capsense_PC_PIN_CFG_SIZE))
    #define  capsense_CTANK_PC_HIGH_Z_MODE      (uint32)(capsense_CSD_PIN_DM_HIGH_Z <<\
                                                                ((uint32)capsense_Csh_tank__0__SHIFT * capsense_PC_PIN_CFG_SIZE))
#endif /* (0u != capsense_CSH_TANK_ENABLE) */

#define  capsense_CMOD_DR_VSSIO             (uint32)(capsense_Cmod__0__MASK)
#define  capsense_CMOD_DR_VDDIO             (0x00000000Lu)
#define  capsense_CMOD_DR_MASK              (uint32)(capsense_Cmod__0__MASK)

#if(0u != capsense_CSH_TANK_ENABLE)
    #define  capsense_CTANK_DR_VSSIO            (uint32)(capsense_Csh_tank__0__MASK)
    #define  capsense_CTANK_DR_VDDIO            (0x00000000Lu)
    #define  capsense_CTANK_DR_MASK             (uint32)(capsense_Csh_tank__0__MASK)
#endif /* (0u != capsense_CSH_TANK_ENABLE) */

#define  capsense_CMOD_PIN_NUMBER               (capsense_Cmod__0__SHIFT)
#define  capsense_CMOD_PRT_NUMBER               (capsense_Cmod__0__PORT)

#if(0u != capsense_CSH_TANK_ENABLE)
    #define  capsense_CTANK_PIN_NUMBER          (capsense_Csh_tank__0__SHIFT)
    #define  capsense_CTANK_PRT_NUMBER          (capsense_Csh_tank__0__PORT)
#endif /* (0u != capsense_CSH_TANK_ENABLE) */

/* ID register fields position */
#define capsense_CSD_ID_ID__POS                 (0x00u)
#define capsense_CSD_ID_REV__POS                (0x10u)

#define capsense_CSD_ID_ID                      (0xFFLu << capsense_CSD_ID_ID__POS)
#define capsense_CSD_ID_REV                     (0xFFLu << capsense_CSD_ID_REV__POS)

/* CSD_CONFIG register fields position */
#define capsense_CSD_CFG_DSI_SAMPLE_EN_POS      (0x00u)
#define capsense_CSD_CFG_SAMPLE_SYNC_POS        (0x01u)
#define capsense_CSD_CFG_FILTER_EN_POS          (0x03u)
#define capsense_CSD_CFG_PRS_CLEAR_POS          (0x05u)
#define capsense_CSD_CFG_PRS_SELECT_POS         (0x06u)
#define capsense_CSD_CFG_PRS_12_8_POS           (0x07u)
#define capsense_CSD_CFG_DSI_SENSE_EN_POS       (0x08u)
#define capsense_CSD_CFG_SHIELD_DELAY_POS       (0x09u)
#define capsense_CSD_CFG_SENSE_COMP_BW_POS      (0x0Bu)
#define capsense_CSD_CFG_SENSE_EN_POS           (0x0Cu)
#define capsense_CSD_CFG_REFBUF_EN_POS          (0x0Du)
#define capsense_CSD_CFG_CHARGE_IO_POS          (0x0Eu)
#define capsense_CSD_CFG_COMP_PIN_POS           (0x0Fu)
#define capsense_CSD_CFG_POLARITY_POS           (0x10u)
#define capsense_CSD_CFG_MUTUAL_CAP_POS         (0x12u)
#define capsense_CSD_CFG_SENSE_COMP_EN_POS      (0x13u)
#define capsense_CSD_CFG_REFBUF_OUTSEL_POS      (0x15u)
#define capsense_CSD_CFG_SENSE_INSEL_POS        (0x16u)
#define capsense_CSD_REFBUF_DRV_POS             (0x17u)
#define capsense_CSD_CFG_DDFTSEL_POS            (0x1Au)
#define capsense_CSD_CFG_ADFTEN_POS             (0x1Du)
#define capsense_CSD_CFG_DDFTCOMP_POS           (0x1Eu)
#define capsense_CSD_CFG_ENABLE_POS             (0x1Fu)

/* CSD_STATUS register fields position */
#define capsense_CSD_STAT_CSD_CHARGE_POS        (0x00u)
#define capsense_CSD_STAT_CSD_SENSE_POS         (0x01u)
#define capsense_CSD_STAT_COMP_OUT_POS          (0x02u)
#define capsense_CSD_STAT_SAMPLE_POS            (0x03u)

/* CSD_IDAC control register fields position */
#define capsense_CSD_IDAC1_MODE_MASK_POS        (0x08u)
#define capsense_CSD_IDAC1_MODE_FIXED_POS       (0x08u)
#define capsense_CSD_IDAC1_MODE_VARIABLE_POS    (0x08u)
#define capsense_CSD_IDAC1_MODE_DSI_POS         (0x08u)
#define capsense_CSD_IDAC1_RANGE_8X_POS         (0x0Au)
#define capsense_CSD_IDAC1_DATA_MASK_POS        (0x00u)

#define capsense_CSD_IDAC2_MODE_MASK_POS        (0x18u)
#define capsense_CSD_IDAC2_MODE_FIXED_POS       (0x18u)
#define capsense_CSD_IDAC2_MODE_VARIABLE_POS    (0x18u)
#define capsense_CSD_IDAC2_MODE_DSI_POS         (0x18u)
#define capsense_CSD_IDAC2_RANGE_8X_POS         (0x1Au)
#define capsense_CSD_IDAC2_DATA_MASK_POS        (0x10u)

/* CSD_COUNTER register fields position */
#define capsense_CSD_CNT_COUNTER_POS            (0x00u)
#define capsense_CSD_CNT_PERIOD_POS             (0x10u)

/* CSD_CONFIRG register definitions */
#define capsense_CSD_CFG_DSI_SAMPLE_EN          (0x01Lu << capsense_CSD_CFG_DSI_SAMPLE_EN_POS)
#define capsense_CSD_CFG_SAMPLE_SYNC            (0x01Lu << capsense_CSD_CFG_SAMPLE_SYNC_POS)
#define capsense_CSD_CFG_FILTER_EN              (0x01Lu << capsense_CSD_CFG_FILTER_EN_POS)
#define capsense_CSD_CFG_PRS_CLEAR              (0x01Lu << capsense_CSD_CFG_PRS_CLEAR_POS)
#define capsense_CSD_CFG_PRS_SELECT             (0x01Lu << capsense_CSD_CFG_PRS_SELECT_POS)
#define capsense_CSD_CFG_PRS_12_8               (0x01Lu << capsense_CSD_CFG_PRS_12_8_POS)
#define capsense_CSD_CFG_DSI_SENSE_EN           (0x01Lu << capsense_CSD_CFG_DSI_SENSE_EN_POS)
#define capsense_CSD_CFG_SHIELD_DELAY_MASK      (0x03Lu << capsense_CSD_CFG_SHIELD_DELAY_POS)
#define capsense_CSD_CFG_SENSE_COMP_BW          (0x01Lu << capsense_CSD_CFG_SENSE_COMP_BW_POS)
#define capsense_CSD_CFG_SENSE_EN               (0x01Lu << capsense_CSD_CFG_SENSE_EN_POS)
#define capsense_CSD_CFG_REFBUF_EN              (0x01Lu << capsense_CSD_CFG_REFBUF_EN_POS)
#define capsense_CSD_CFG_CHARGE_IO              (0x01Lu << capsense_CSD_CFG_CHARGE_IO_POS)
#define capsense_CSD_CFG_COMP_PIN_CH2           (0x01Lu << capsense_CSD_CFG_COMP_PIN_POS)
#define capsense_CSD_CFG_POLARITY_VDDIO         (0x01Lu << capsense_CSD_CFG_POLARITY_POS)
#define capsense_CSD_CFG_MUTUAL_CAP             (0x01Lu << capsense_CSD_CFG_MUTUAL_CAP_POS)
#define capsense_CSD_CFG_SENSE_COMP_EN          (0x01Lu << capsense_CSD_CFG_SENSE_COMP_EN_POS)
#define capsense_CSD_CFG_REFBUF_OUTSEL          (0x01Lu << capsense_CSD_CFG_REFBUF_OUTSEL_POS)
#define capsense_CSD_CFG_SENSE_INSEL            (0x01Lu << capsense_CSD_CFG_SENSE_INSEL_POS)
#define capsense_CSD_REFBUF_DRV_MASK            (0x03Lu << capsense_CSD_REFBUF_DRV_POS)
#define capsense_CSD_REFBUF_DRV_LOW             (0x01Lu << capsense_CSD_REFBUF_DRV_POS)
#define capsense_CSD_REFBUF_DRV_MEDIUM          (0x02Lu << capsense_CSD_REFBUF_DRV_POS)
#define capsense_CSD_REFBUF_DRV_HIGH            (0x03Lu << capsense_CSD_REFBUF_DRV_POS)
#define capsense_CSD_CFG_DDFTSEL_MASK           (0x07Lu << capsense_CSD_CFG_DDFTSEL_POS)
#define capsense_CSD_CFG_ADFTEN                 (0x01Lu << capsense_CSD_CFG_ADFTEN_POS)
#define capsense_CSD_CFG_DDFTCOMP_MASK          (0x03Lu << capsense_CSD_CFG_DDFTCOMP_POS)
#define capsense_CSD_CFG_DDFTCOMP_REFCOMP       (0x01Lu << capsense_CSD_CFG_DDFTCOMP_POS)
#define capsense_CSD_CFG_DDFTCOMP_SENSECOMP     (0x02Lu << capsense_CSD_CFG_DDFTCOMP_POS)
#define capsense_CSD_CFG_ENABLE                 (0x01Lu << capsense_CSD_CFG_ENABLE_POS)

/* CSD_STATUS register definitions */
#define capsense_CSD_STAT_CSD_CHARGE            (0x01Lu << capsense_CSD_STAT_CSD_CHARGE_POS)
#define capsense_CSD_STAT_CSD_SENSE             (0x01Lu << capsense_CSD_STAT_CSD_SENSE_POS)
#define capsense_CSD_STAT_COMP_OUT              (0x01Lu << capsense_CSD_STAT_COMP_OUT_POS)
#define capsense_CSD_STAT_SAMPLE                (0x01Lu << capsense_CSD_STAT_SAMPLE_POS)

/* CSD_IDAC control register definitions */
#define capsense_CSD_IDAC1_MODE_MASK            (0x03Lu << capsense_CSD_IDAC1_MODE_MASK_POS)
#define capsense_CSD_IDAC1_MODE_FIXED           (0x01Lu << capsense_CSD_IDAC1_MODE_FIXED_POS)
#define capsense_CSD_IDAC1_MODE_VARIABLE        (0x02Lu << capsense_CSD_IDAC1_MODE_VARIABLE_POS)
#define capsense_CSD_IDAC1_MODE_DSI             (0x03Lu << capsense_CSD_IDAC1_MODE_DSI_POS)
#define capsense_CSD_IDAC1_RANGE_8X             (0x01Lu << capsense_CSD_IDAC1_RANGE_8X_POS)
#define capsense_CSD_IDAC1_DATA_MASK            (0xFFLu << capsense_CSD_IDAC1_DATA_MASK_POS)

#define capsense_CSD_IDAC2_MODE_MASK            (0x03Lu << capsense_CSD_IDAC2_MODE_MASK_POS)
#define capsense_CSD_IDAC2_MODE_FIXED           (0x01Lu << capsense_CSD_IDAC2_MODE_FIXED_POS)
#define capsense_CSD_IDAC2_MODE_VARIABLE        (0x02Lu << capsense_CSD_IDAC2_MODE_VARIABLE_POS)
#define capsense_CSD_IDAC2_MODE_DSI             (0x03Lu << capsense_CSD_IDAC2_MODE_DSI_POS)
#define capsense_CSD_IDAC2_RANGE_8X             (0x01Lu << capsense_CSD_IDAC2_RANGE_8X_POS)
#define capsense_CSD_IDAC2_DATA_MASK            (0x7FLu << capsense_CSD_IDAC2_DATA_MASK_POS)

#define capsense_CSD_IDAC2_DATA_OFFSET          (16u)

#define capsense_CSD_IDAC1_TRIM_MASK            (0xFFFFFFF0u)
#define capsense_CSD_IDAC2_TRIM_MASK            (0xFFFFFF0Fu)

#define capsense_CSFLASH_TRIM_IDAC1_MASK        (0x0Fu)
#define capsense_CSFLASH_TRIM_IDAC2_MASK        (0xF0)

#define capsense_CSD_4B_PWM_MODE_OFFSET         (4u)
#define capsense_CSD_4B_PWM_MODE_DEFAULT        (capsense_CSD_4B_PWM_MODE << capsense_CSD_4B_PWM_MODE_OFFSET)

#define capsense_CSD_4B_PWM_COUNT_MASK          (0x0000000Fu)
#define capsense_CSD_4B_PWM_MODE_MASK           (0x00000030u)

#define capsense_CSD_IDAC_PRECHARGE_CONFIG      (capsense_CSD_IDAC1_MODE_FIXED |\
                                                        capsense_PRECHARGE_IDAC1_VAL)

/* CSD_COUNTER register definitions */
#define capsense_CSD_CNT_COUNTER                (0xFFLu << capsense_CSD_CNT_COUNTER_POS )
#define capsense_CSD_CNT_PERIOD                 (0xFFLu << capsense_CSD_CNT_PERIOD_POS)

#define capsense_CSD_PRS_8_BIT                  (0x00000000u)
#define capsense_CSD_PRS_12_BIT                 (capsense_CSD_CFG_PRS_12_8)
#define capsense_PRS_MODE_MASK                  (capsense_CSD_CFG_PRS_12_8)

/***************************************
*    Initial Parameter Constants
***************************************/

#if (0u != capsense_FILTER_ENABLE)
    #define capsense_DEFAULT_FILTER_STATE       (capsense_CSD_CFG_FILTER_EN)

#else
    #define capsense_DEFAULT_FILTER_STATE       (0u)

#endif /* (capsense_PRS_OPTIONS == capsense_PRS_8BITS) */

#define capsense_DEFAULT_CSD_4B_PWM_CONFIG      (capsense_CSD_4B_PWM_MODE_DEFAULT | capsense_CSD_4B_PWM_COUNT)

/* Set PRS */
#if (capsense_PRS_OPTIONS == capsense__PRS_8BITS)
    #define capsense_DEFAULT_MODULATION_MODE    capsense_CSD_CFG_PRS_SELECT

#elif (capsense_PRS_OPTIONS == capsense__PRS_12BITS)
    #define capsense_DEFAULT_MODULATION_MODE    (capsense_CSD_CFG_PRS_12_8 |\
                                                        capsense_CSD_CFG_PRS_SELECT)
#else
    #define capsense_DEFAULT_MODULATION_MODE    (0u)
#endif /* (capsense_PRS_OPTIONS == capsense_PRS_8BITS) */

/* Set IDAC ranges */
#if (capsense_IDAC1_RANGE_VALUE == capsense__IDAC_8X)
    #define capsense_DEFAULT_IDAC1_RANGE        capsense_CSD_IDAC1_RANGE_8X
    #define capsense_DEFAULT_IDAC2_RANGE        capsense_CSD_IDAC2_RANGE_8X
#else
    #define capsense_DEFAULT_IDAC1_RANGE        (0u)
    #define capsense_DEFAULT_IDAC2_RANGE        (0u)
#endif /* (capsense_IDAC1_RANGE_VALUE == capsense_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(capsense_IDAC1_POLARITY == capsense__IDAC_SINK)

    #define capsense_DEFAULT_IDAC_POLARITY      capsense_CSD_CFG_POLARITY_VDDIO
    #define capsense_CMOD_DR_CONFIG             capsense_CMOD_DR_VDDIO
    #define capsense_CTANK_DR_CONFIG            capsense_CTANK_DR_VDDIO
#else

    #define capsense_DEFAULT_IDAC_POLARITY      (0u)
    #define capsense_CMOD_DR_CONFIG             capsense_CMOD_DR_VSSIO
    #define capsense_CTANK_DR_CONFIG            capsense_CTANK_DR_VSSIO
#endif /* (capsense_IDAC_OPTIONS == capsense_IDAC_SINK) */

#define capsense_SNS_GROUND_CONNECT             (6u)
#define capsense_SNS_HIZANALOG_CONNECT          (0u)

/* Inactive sensors connection configuration */
#if (capsense_CONNECT_INACTIVE_SNS == capsense__GROUND)
    #define capsense_CSD_INACTIVE_CONNECT       (capsense_SNS_GROUND_CONNECT)
#else
    #define capsense_CSD_INACTIVE_CONNECT       (capsense_SNS_HIZANALOG_CONNECT)
#endif /* capsense_CONNECT_INACTIVE_SNS == capsense__GROUND */

#if(capsense_IS_SHIELD_ENABLE)
    #define capsense_SHIELD_PORT_NUMBER capsense_Shield__PORT
    #define capsense_SHIELD_PIN_NUMBER  capsense_Shield__SHIFT
#endif /* (capsense_IS_SHIELD_ENABLE) */

/* Defining default CSD configuration according to settings in customizer. */
#define capsense_DEFAULT_CSD_CONFIG             (capsense_DEFAULT_FILTER_STATE |\
                                                         capsense_DEFAULT_MODULATION_MODE |\
                                                         capsense_CSD_CFG_SENSE_COMP_BW |\
                                                         capsense_DEFAULT_IDAC_POLARITY |\
                                                         capsense_CSD_CFG_REFBUF_OUTSEL |\
                                                         capsense_CSD_REFBUF_DRV_HIGH)

#define capsense_CSD_CONFIG_MASK                (capsense_CSD_CFG_FILTER_EN |\
                                                         capsense_CSD_CFG_PRS_SELECT |\
                                                         capsense_CSD_CFG_PRS_12_8 |\
                                                         capsense_CSD_CFG_SENSE_COMP_BW |\
                                                         capsense_CSD_CFG_REFBUF_EN |\
                                                         capsense_CSD_CFG_REFBUF_OUTSEL |\
                                                         capsense_CSD_CFG_POLARITY_VDDIO |\
                                                         capsense_CSD_CFG_REFBUF_OUTSEL  |\
                                                         capsense_CSD_REFBUF_DRV_MASK)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (capsense_IDAC_CNT == 1u)
    #define capsense_DEFAULT_CSD_IDAC_CONFIG    (capsense_CSD_IDAC1_MODE_VARIABLE |\
                                                             capsense_DEFAULT_IDAC1_RANGE)
#else
    #define capsense_DEFAULT_CSD_IDAC_CONFIG    (capsense_CSD_IDAC1_MODE_VARIABLE |\
                                                             capsense_CSD_IDAC2_MODE_FIXED |\
                                                             capsense_DEFAULT_IDAC1_RANGE |\
                                                             capsense_DEFAULT_IDAC2_RANGE)
#endif /* (capsense_IDAC_CNT == 1u) */

/* Defining mask intended for clearing bits related to pre-charging options. */
#define capsense_PRECHARGE_CONFIG_MASK          (capsense_CSD_CFG_REFBUF_EN |\
                                                         capsense_CSD_CFG_CHARGE_IO |\
                                                         capsense_CSD_CFG_COMP_PIN_CH2  |\
                                                         capsense_CSD_CFG_REFBUF_OUTSEL)

/* Cmod the precharge mode configuration */
#if(capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRVREF)

    #define capsense_CMOD_PRECHARGE_CONFIG      (capsense_CSD_CFG_REFBUF_EN |\
                                                         capsense_CSD_CFG_COMP_PIN_CH2)

#else

    #define capsense_CMOD_PRECHARGE_CONFIG      (capsense_CSD_CFG_REFBUF_OUTSEL |\
                                                         capsense_CSD_CFG_REFBUF_EN |\
                                                         capsense_CSD_CFG_CHARGE_IO)

#endif /* (capsense_CMOD_PREGARGE_OPTION == capsense__CAPPRVREF) */

/* Ctank the precharge mode configuration */
#if(capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRVREF)

    #if(0u != capsense_IS_SHIELD_ENABLE)
        #define  capsense_CTANK_PRECHARGE_CONFIG    (capsense_CSD_CFG_REFBUF_EN |\
                                                             capsense_CSD_CFG_PRS_CLEAR |\
                                                             capsense_CSD_CFG_REFBUF_OUTSEL)
    #else
        #define  capsense_CTANK_PRECHARGE_CONFIG    (capsense_CSD_CFG_REFBUF_OUTSEL |\
                                                             capsense_CSD_CFG_PRS_CLEAR)
    #endif /* (0u != capsense_IS_SHIELD_ENABLE) */

#else

    #define  capsense_CTANK_PRECHARGE_CONFIG    (capsense_CSD_CFG_REFBUF_OUTSEL |\
                                                         capsense_CSD_CFG_REFBUF_EN |\
                                                         capsense_CSD_CFG_CHARGE_IO |\
                                                         capsense_CSD_CFG_PRS_CLEAR |\
                                                         capsense_CSD_CFG_COMP_PIN_CH2)
#endif /* (capsense_CSH_TANK_PREGARGE_OPTION == capsense__CAPPRIOBUF) */

#define capsense_MAX_UINT_8                     (0xFFu)
#define capsense_MAX_UINT_16                    (0xFFFFu)
#define capsense_MAX_UINT_32                    (0xFFFFFFFFLu)

/***************************************
*     Vars with External Linkage
***************************************/
/* SmartSense functions */
#if (capsense_TUNING_METHOD == capsense__TUNING_AUTO)
    extern uint8 capsense_lowLevelTuningDone;
    extern uint8 capsense_scanSpeedTbl[((capsense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
    extern void capsense_AutoTune(void);
#endif /* (capsense_TUNING_METHOD == capsense__TUNING_AUTO) */

#if(capsense_PRS_OPTIONS != capsense__PRS_NONE)
    extern uint8 capsense_prescalersTuningDone;
#endif /* (capsense_PRS_OPTIONS == capsense__PRS_NONE) */

/* Global software variables */
extern volatile uint8 capsense_csdStatusVar;
extern volatile uint8 capsense_sensorIndex;
extern uint16 capsense_sensorRaw[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_unscannedSnsDriveMode[capsense_PORT_PIN_CONFIG_TBL_ZISE];
extern uint8 capsense_sensorEnableMaskBackup[capsense_TOTAL_SENSOR_MASK];
extern uint8 capsense_sensorEnableMask[capsense_TOTAL_SENSOR_MASK];

#if ((capsense_TUNING_METHOD != capsense__TUNING_NONE) || (0u != capsense_AUTOCALIBRATION_ENABLE))
    extern uint8 capsense_modulationIDAC[capsense_TOTAL_SENSOR_COUNT];
    extern uint8 capsense_compensationIDAC[capsense_TOTAL_SENSOR_COUNT];
#else
    extern const uint8 capsense_modulationIDAC[capsense_TOTAL_SENSOR_COUNT];
    extern const uint8 capsense_compensationIDAC[capsense_TOTAL_SENSOR_COUNT];
#endif /* ((capsense_TUNING_METHOD != capsense__TUNING_NONE) || (0u != capsense_AUTOCALIBRATION_ENABLE)) */

#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    extern uint32 capsense_widgetResolution[capsense_RESOLUTIONS_TBL_SIZE];
    #if (0u != capsense_MULTIPLE_FREQUENCY_SET)
        extern uint8 capsense_senseClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];
        extern uint8 capsense_sampleClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];
    #else
        extern uint8 capsense_senseClkDividerVal;
        extern uint8 capsense_sampleClkDividerVal;
    #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
#else
    extern const uint32 capsense_widgetResolution[capsense_RESOLUTIONS_TBL_SIZE];
    #if (0u != capsense_MULTIPLE_FREQUENCY_SET)
        extern const uint8 capsense_senseClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];
        extern const uint8 capsense_sampleClkDividerVal[capsense_TOTAL_SCANSLOT_COUNT];
    #else
        extern const uint8 capsense_senseClkDividerVal;
        extern const uint8 capsense_sampleClkDividerVal;
    #endif /* (0u != capsense_MULTIPLE_FREQUENCY_SET) */
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE)  */

extern const uint8 capsense_widgetNumber[capsense_TOTAL_SENSOR_COUNT];

extern reg32* const capsense_prtSelTbl[capsense_CFG_REG_TBL_SIZE];
extern reg32* const capsense_prtCfgTbl[capsense_CFG_REG_TBL_SIZE];
extern reg32* const capsense_prtDRTbl[capsense_CFG_REG_TBL_SIZE];
extern reg32 * capsense_pcTable[capsense_PORT_PIN_CONFIG_TBL_ZISE];

extern const uint8  capsense_portTable[capsense_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint32 capsense_maskTable[capsense_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint8  capsense_pinShiftTbl[capsense_PORT_PIN_CONFIG_TBL_ZISE];

#if (0u != capsense_INDEX_TABLE_SIZE)
extern const uint8 CYCODE capsense_indexTable[capsense_INDEX_TABLE_SIZE];
#endif /* (0u != capsense_INDEX_TABLE_SIZE)) */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  capsense_PrescalersTuningDone         capsense_prescalersTuningDone
#define  capsense_SensorRaw                    capsense_sensorRaw
#define  capsense_PRSResolutionTbl             capsense_prsResolutionTbl
#define  capsense_SensorEnableMask             capsense_sensorEnableMask
#define  capsense_Clk1DividerVal               capsense_senseClkDividerVal
#define  capsense_Clk2DividerVal               capsense_sampleClkDividerVal
#define  capsense_PrtSelTbl                    capsense_prtSelTbl
#define  capsense_PrtCfgTbl                    capsense_prtCfgTbl
#define  capsense_PrtDRTbl                     capsense_prtDRTbl
#define  capsense_idac1Settings                capsense_modulationIDAC
#define  capsense_idac2Settings                capsense_compensationIDAC

#endif /* CY_CAPSENSE_CSD_capsense_H */


 /* [] END OF FILE */
