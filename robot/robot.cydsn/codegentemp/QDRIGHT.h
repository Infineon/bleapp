/*******************************************************************************
* File Name: QDRIGHT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the QDRIGHT
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_QDRIGHT_H)
#define CY_TCPWM_QDRIGHT_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} QDRIGHT_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QDRIGHT_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define QDRIGHT_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define QDRIGHT_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define QDRIGHT_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QDRIGHT_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define QDRIGHT_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QDRIGHT_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QDRIGHT_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QDRIGHT_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QDRIGHT_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QDRIGHT_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QDRIGHT_QUAD_INTERRUPT_MASK            (0lu)

/* Timer/Counter Mode */
/* Parameters */
#define QDRIGHT_TC_RUN_MODE                    (0lu)
#define QDRIGHT_TC_COUNTER_MODE                (0lu)
#define QDRIGHT_TC_COMP_CAP_MODE               (2lu)
#define QDRIGHT_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QDRIGHT_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QDRIGHT_TC_COUNT_SIGNAL_MODE           (3lu)
#define QDRIGHT_TC_START_SIGNAL_MODE           (0lu)
#define QDRIGHT_TC_STOP_SIGNAL_MODE            (0lu)
#define QDRIGHT_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QDRIGHT_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QDRIGHT_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QDRIGHT_TC_START_SIGNAL_PRESENT        (0lu)
#define QDRIGHT_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QDRIGHT_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QDRIGHT_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QDRIGHT_PWM_KILL_EVENT                 (0lu)
#define QDRIGHT_PWM_STOP_EVENT                 (0lu)
#define QDRIGHT_PWM_MODE                       (4lu)
#define QDRIGHT_PWM_OUT_N_INVERT               (0lu)
#define QDRIGHT_PWM_OUT_INVERT                 (0lu)
#define QDRIGHT_PWM_ALIGN                      (0lu)
#define QDRIGHT_PWM_RUN_MODE                   (0lu)
#define QDRIGHT_PWM_DEAD_TIME_CYCLE            (0lu)
#define QDRIGHT_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QDRIGHT_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QDRIGHT_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QDRIGHT_PWM_START_SIGNAL_MODE          (0lu)
#define QDRIGHT_PWM_STOP_SIGNAL_MODE           (0lu)
#define QDRIGHT_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QDRIGHT_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QDRIGHT_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QDRIGHT_PWM_START_SIGNAL_PRESENT       (0lu)
#define QDRIGHT_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QDRIGHT_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QDRIGHT_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QDRIGHT_TC_PERIOD_VALUE                (65535lu)
#define QDRIGHT_TC_COMPARE_VALUE               (65535lu)
#define QDRIGHT_TC_COMPARE_BUF_VALUE           (65535lu)
#define QDRIGHT_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QDRIGHT_PWM_PERIOD_VALUE               (65535lu)
#define QDRIGHT_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QDRIGHT_PWM_PERIOD_SWAP                (0lu)
#define QDRIGHT_PWM_COMPARE_VALUE              (65535lu)
#define QDRIGHT_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QDRIGHT_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QDRIGHT__LEFT 0
#define QDRIGHT__RIGHT 1
#define QDRIGHT__CENTER 2
#define QDRIGHT__ASYMMETRIC 3

#define QDRIGHT__X1 0
#define QDRIGHT__X2 1
#define QDRIGHT__X4 2

#define QDRIGHT__PWM 4
#define QDRIGHT__PWM_DT 5
#define QDRIGHT__PWM_PR 6

#define QDRIGHT__INVERSE 1
#define QDRIGHT__DIRECT 0

#define QDRIGHT__CAPTURE 2
#define QDRIGHT__COMPARE 0

#define QDRIGHT__TRIG_LEVEL 3
#define QDRIGHT__TRIG_RISING 0
#define QDRIGHT__TRIG_FALLING 1
#define QDRIGHT__TRIG_BOTH 2

#define QDRIGHT__INTR_MASK_TC 1
#define QDRIGHT__INTR_MASK_CC_MATCH 2
#define QDRIGHT__INTR_MASK_NONE 0
#define QDRIGHT__INTR_MASK_TC_CC 3

#define QDRIGHT__UNCONFIG 8
#define QDRIGHT__TIMER 1
#define QDRIGHT__QUAD 3
#define QDRIGHT__PWM_SEL 7

#define QDRIGHT__COUNT_UP 0
#define QDRIGHT__COUNT_DOWN 1
#define QDRIGHT__COUNT_UPDOWN0 2
#define QDRIGHT__COUNT_UPDOWN1 3


/* Prescaler */
#define QDRIGHT_PRESCALE_DIVBY1                ((uint32)(0u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY2                ((uint32)(1u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY4                ((uint32)(2u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY8                ((uint32)(3u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY16               ((uint32)(4u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY32               ((uint32)(5u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY64               ((uint32)(6u << QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_PRESCALE_DIVBY128              ((uint32)(7u << QDRIGHT_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QDRIGHT_MODE_TIMER_COMPARE             ((uint32)(QDRIGHT__COMPARE         <<  \
                                                                  QDRIGHT_MODE_SHIFT))
#define QDRIGHT_MODE_TIMER_CAPTURE             ((uint32)(QDRIGHT__CAPTURE         <<  \
                                                                  QDRIGHT_MODE_SHIFT))
#define QDRIGHT_MODE_QUAD                      ((uint32)(QDRIGHT__QUAD            <<  \
                                                                  QDRIGHT_MODE_SHIFT))
#define QDRIGHT_MODE_PWM                       ((uint32)(QDRIGHT__PWM             <<  \
                                                                  QDRIGHT_MODE_SHIFT))
#define QDRIGHT_MODE_PWM_DT                    ((uint32)(QDRIGHT__PWM_DT          <<  \
                                                                  QDRIGHT_MODE_SHIFT))
#define QDRIGHT_MODE_PWM_PR                    ((uint32)(QDRIGHT__PWM_PR          <<  \
                                                                  QDRIGHT_MODE_SHIFT))

/* Quad Modes */
#define QDRIGHT_MODE_X1                        ((uint32)(QDRIGHT__X1              <<  \
                                                                  QDRIGHT_QUAD_MODE_SHIFT))
#define QDRIGHT_MODE_X2                        ((uint32)(QDRIGHT__X2              <<  \
                                                                  QDRIGHT_QUAD_MODE_SHIFT))
#define QDRIGHT_MODE_X4                        ((uint32)(QDRIGHT__X4              <<  \
                                                                  QDRIGHT_QUAD_MODE_SHIFT))

/* Counter modes */
#define QDRIGHT_COUNT_UP                       ((uint32)(QDRIGHT__COUNT_UP        <<  \
                                                                  QDRIGHT_UPDOWN_SHIFT))
#define QDRIGHT_COUNT_DOWN                     ((uint32)(QDRIGHT__COUNT_DOWN      <<  \
                                                                  QDRIGHT_UPDOWN_SHIFT))
#define QDRIGHT_COUNT_UPDOWN0                  ((uint32)(QDRIGHT__COUNT_UPDOWN0   <<  \
                                                                  QDRIGHT_UPDOWN_SHIFT))
#define QDRIGHT_COUNT_UPDOWN1                  ((uint32)(QDRIGHT__COUNT_UPDOWN1   <<  \
                                                                  QDRIGHT_UPDOWN_SHIFT))

/* PWM output invert */
#define QDRIGHT_INVERT_LINE                    ((uint32)(QDRIGHT__INVERSE         <<  \
                                                                  QDRIGHT_INV_OUT_SHIFT))
#define QDRIGHT_INVERT_LINE_N                  ((uint32)(QDRIGHT__INVERSE         <<  \
                                                                  QDRIGHT_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QDRIGHT_TRIG_RISING                    ((uint32)QDRIGHT__TRIG_RISING)
#define QDRIGHT_TRIG_FALLING                   ((uint32)QDRIGHT__TRIG_FALLING)
#define QDRIGHT_TRIG_BOTH                      ((uint32)QDRIGHT__TRIG_BOTH)
#define QDRIGHT_TRIG_LEVEL                     ((uint32)QDRIGHT__TRIG_LEVEL)

/* Interrupt mask */
#define QDRIGHT_INTR_MASK_TC                   ((uint32)QDRIGHT__INTR_MASK_TC)
#define QDRIGHT_INTR_MASK_CC_MATCH             ((uint32)QDRIGHT__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QDRIGHT_CC_MATCH_SET                   (0x00u)
#define QDRIGHT_CC_MATCH_CLEAR                 (0x01u)
#define QDRIGHT_CC_MATCH_INVERT                (0x02u)
#define QDRIGHT_CC_MATCH_NO_CHANGE             (0x03u)
#define QDRIGHT_OVERLOW_SET                    (0x00u)
#define QDRIGHT_OVERLOW_CLEAR                  (0x04u)
#define QDRIGHT_OVERLOW_INVERT                 (0x08u)
#define QDRIGHT_OVERLOW_NO_CHANGE              (0x0Cu)
#define QDRIGHT_UNDERFLOW_SET                  (0x00u)
#define QDRIGHT_UNDERFLOW_CLEAR                (0x10u)
#define QDRIGHT_UNDERFLOW_INVERT               (0x20u)
#define QDRIGHT_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QDRIGHT_PWM_MODE_LEFT                  (QDRIGHT_CC_MATCH_CLEAR        |   \
                                                         QDRIGHT_OVERLOW_SET           |   \
                                                         QDRIGHT_UNDERFLOW_NO_CHANGE)
#define QDRIGHT_PWM_MODE_RIGHT                 (QDRIGHT_CC_MATCH_SET          |   \
                                                         QDRIGHT_OVERLOW_NO_CHANGE     |   \
                                                         QDRIGHT_UNDERFLOW_CLEAR)
#define QDRIGHT_PWM_MODE_ASYM                  (QDRIGHT_CC_MATCH_INVERT       |   \
                                                         QDRIGHT_OVERLOW_SET           |   \
                                                         QDRIGHT_UNDERFLOW_CLEAR)

#if (QDRIGHT_CY_TCPWM_V2)
    #if(QDRIGHT_CY_TCPWM_4000)
        #define QDRIGHT_PWM_MODE_CENTER                (QDRIGHT_CC_MATCH_INVERT       |   \
                                                                 QDRIGHT_OVERLOW_NO_CHANGE     |   \
                                                                 QDRIGHT_UNDERFLOW_CLEAR)
    #else
        #define QDRIGHT_PWM_MODE_CENTER                (QDRIGHT_CC_MATCH_INVERT       |   \
                                                                 QDRIGHT_OVERLOW_SET           |   \
                                                                 QDRIGHT_UNDERFLOW_CLEAR)
    #endif /* (QDRIGHT_CY_TCPWM_4000) */
#else
    #define QDRIGHT_PWM_MODE_CENTER                (QDRIGHT_CC_MATCH_INVERT       |   \
                                                             QDRIGHT_OVERLOW_NO_CHANGE     |   \
                                                             QDRIGHT_UNDERFLOW_CLEAR)
#endif /* (QDRIGHT_CY_TCPWM_NEW) */

/* Command operations without condition */
#define QDRIGHT_CMD_CAPTURE                    (0u)
#define QDRIGHT_CMD_RELOAD                     (8u)
#define QDRIGHT_CMD_STOP                       (16u)
#define QDRIGHT_CMD_START                      (24u)

/* Status */
#define QDRIGHT_STATUS_DOWN                    (1u)
#define QDRIGHT_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QDRIGHT_Init(void);
void   QDRIGHT_Enable(void);
void   QDRIGHT_Start(void);
void   QDRIGHT_Stop(void);

void   QDRIGHT_SetMode(uint32 mode);
void   QDRIGHT_SetCounterMode(uint32 counterMode);
void   QDRIGHT_SetPWMMode(uint32 modeMask);
void   QDRIGHT_SetQDMode(uint32 qdMode);

void   QDRIGHT_SetPrescaler(uint32 prescaler);
void   QDRIGHT_TriggerCommand(uint32 mask, uint32 command);
void   QDRIGHT_SetOneShot(uint32 oneShotEnable);
uint32 QDRIGHT_ReadStatus(void);

void   QDRIGHT_SetPWMSyncKill(uint32 syncKillEnable);
void   QDRIGHT_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QDRIGHT_SetPWMDeadTime(uint32 deadTime);
void   QDRIGHT_SetPWMInvert(uint32 mask);

void   QDRIGHT_SetInterruptMode(uint32 interruptMask);
uint32 QDRIGHT_GetInterruptSourceMasked(void);
uint32 QDRIGHT_GetInterruptSource(void);
void   QDRIGHT_ClearInterrupt(uint32 interruptMask);
void   QDRIGHT_SetInterrupt(uint32 interruptMask);

void   QDRIGHT_WriteCounter(uint32 count);
uint32 QDRIGHT_ReadCounter(void);

uint32 QDRIGHT_ReadCapture(void);
uint32 QDRIGHT_ReadCaptureBuf(void);

void   QDRIGHT_WritePeriod(uint32 period);
uint32 QDRIGHT_ReadPeriod(void);
void   QDRIGHT_WritePeriodBuf(uint32 periodBuf);
uint32 QDRIGHT_ReadPeriodBuf(void);

void   QDRIGHT_WriteCompare(uint32 compare);
uint32 QDRIGHT_ReadCompare(void);
void   QDRIGHT_WriteCompareBuf(uint32 compareBuf);
uint32 QDRIGHT_ReadCompareBuf(void);

void   QDRIGHT_SetPeriodSwap(uint32 swapEnable);
void   QDRIGHT_SetCompareSwap(uint32 swapEnable);

void   QDRIGHT_SetCaptureMode(uint32 triggerMode);
void   QDRIGHT_SetReloadMode(uint32 triggerMode);
void   QDRIGHT_SetStartMode(uint32 triggerMode);
void   QDRIGHT_SetStopMode(uint32 triggerMode);
void   QDRIGHT_SetCountMode(uint32 triggerMode);

void   QDRIGHT_SaveConfig(void);
void   QDRIGHT_RestoreConfig(void);
void   QDRIGHT_Sleep(void);
void   QDRIGHT_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QDRIGHT_BLOCK_CONTROL_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QDRIGHT_BLOCK_CONTROL_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QDRIGHT_COMMAND_REG                    (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QDRIGHT_COMMAND_PTR                    ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QDRIGHT_INTRRUPT_CAUSE_REG             (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QDRIGHT_INTRRUPT_CAUSE_PTR             ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QDRIGHT_CONTROL_REG                    (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CTRL )
#define QDRIGHT_CONTROL_PTR                    ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CTRL )
#define QDRIGHT_STATUS_REG                     (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__STATUS )
#define QDRIGHT_STATUS_PTR                     ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__STATUS )
#define QDRIGHT_COUNTER_REG                    (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__COUNTER )
#define QDRIGHT_COUNTER_PTR                    ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__COUNTER )
#define QDRIGHT_COMP_CAP_REG                   (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CC )
#define QDRIGHT_COMP_CAP_PTR                   ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CC )
#define QDRIGHT_COMP_CAP_BUF_REG               (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CC_BUFF )
#define QDRIGHT_COMP_CAP_BUF_PTR               ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__CC_BUFF )
#define QDRIGHT_PERIOD_REG                     (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__PERIOD )
#define QDRIGHT_PERIOD_PTR                     ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__PERIOD )
#define QDRIGHT_PERIOD_BUF_REG                 (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QDRIGHT_PERIOD_BUF_PTR                 ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QDRIGHT_TRIG_CONTROL0_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QDRIGHT_TRIG_CONTROL0_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QDRIGHT_TRIG_CONTROL1_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QDRIGHT_TRIG_CONTROL1_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QDRIGHT_TRIG_CONTROL2_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QDRIGHT_TRIG_CONTROL2_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QDRIGHT_INTERRUPT_REQ_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR )
#define QDRIGHT_INTERRUPT_REQ_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR )
#define QDRIGHT_INTERRUPT_SET_REG              (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_SET )
#define QDRIGHT_INTERRUPT_SET_PTR              ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_SET )
#define QDRIGHT_INTERRUPT_MASK_REG             (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_MASK )
#define QDRIGHT_INTERRUPT_MASK_PTR             ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_MASK )
#define QDRIGHT_INTERRUPT_MASKED_REG           (*(reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QDRIGHT_INTERRUPT_MASKED_PTR           ( (reg32 *) QDRIGHT_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QDRIGHT_MASK                           ((uint32)QDRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QDRIGHT_RELOAD_CC_SHIFT                (0u)
#define QDRIGHT_RELOAD_PERIOD_SHIFT            (1u)
#define QDRIGHT_PWM_SYNC_KILL_SHIFT            (2u)
#define QDRIGHT_PWM_STOP_KILL_SHIFT            (3u)
#define QDRIGHT_PRESCALER_SHIFT                (8u)
#define QDRIGHT_UPDOWN_SHIFT                   (16u)
#define QDRIGHT_ONESHOT_SHIFT                  (18u)
#define QDRIGHT_QUAD_MODE_SHIFT                (20u)
#define QDRIGHT_INV_OUT_SHIFT                  (20u)
#define QDRIGHT_INV_COMPL_OUT_SHIFT            (21u)
#define QDRIGHT_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QDRIGHT_RELOAD_CC_MASK                 ((uint32)(QDRIGHT_1BIT_MASK        <<  \
                                                                            QDRIGHT_RELOAD_CC_SHIFT))
#define QDRIGHT_RELOAD_PERIOD_MASK             ((uint32)(QDRIGHT_1BIT_MASK        <<  \
                                                                            QDRIGHT_RELOAD_PERIOD_SHIFT))
#define QDRIGHT_PWM_SYNC_KILL_MASK             ((uint32)(QDRIGHT_1BIT_MASK        <<  \
                                                                            QDRIGHT_PWM_SYNC_KILL_SHIFT))
#define QDRIGHT_PWM_STOP_KILL_MASK             ((uint32)(QDRIGHT_1BIT_MASK        <<  \
                                                                            QDRIGHT_PWM_STOP_KILL_SHIFT))
#define QDRIGHT_PRESCALER_MASK                 ((uint32)(QDRIGHT_8BIT_MASK        <<  \
                                                                            QDRIGHT_PRESCALER_SHIFT))
#define QDRIGHT_UPDOWN_MASK                    ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                            QDRIGHT_UPDOWN_SHIFT))
#define QDRIGHT_ONESHOT_MASK                   ((uint32)(QDRIGHT_1BIT_MASK        <<  \
                                                                            QDRIGHT_ONESHOT_SHIFT))
#define QDRIGHT_QUAD_MODE_MASK                 ((uint32)(QDRIGHT_3BIT_MASK        <<  \
                                                                            QDRIGHT_QUAD_MODE_SHIFT))
#define QDRIGHT_INV_OUT_MASK                   ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                            QDRIGHT_INV_OUT_SHIFT))
#define QDRIGHT_MODE_MASK                      ((uint32)(QDRIGHT_3BIT_MASK        <<  \
                                                                            QDRIGHT_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QDRIGHT_CAPTURE_SHIFT                  (0u)
#define QDRIGHT_COUNT_SHIFT                    (2u)
#define QDRIGHT_RELOAD_SHIFT                   (4u)
#define QDRIGHT_STOP_SHIFT                     (6u)
#define QDRIGHT_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QDRIGHT_CAPTURE_MASK                   ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                  QDRIGHT_CAPTURE_SHIFT))
#define QDRIGHT_COUNT_MASK                     ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                  QDRIGHT_COUNT_SHIFT))
#define QDRIGHT_RELOAD_MASK                    ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                  QDRIGHT_RELOAD_SHIFT))
#define QDRIGHT_STOP_MASK                      ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                  QDRIGHT_STOP_SHIFT))
#define QDRIGHT_START_MASK                     ((uint32)(QDRIGHT_2BIT_MASK        <<  \
                                                                  QDRIGHT_START_SHIFT))

/* MASK */
#define QDRIGHT_1BIT_MASK                      ((uint32)0x01u)
#define QDRIGHT_2BIT_MASK                      ((uint32)0x03u)
#define QDRIGHT_3BIT_MASK                      ((uint32)0x07u)
#define QDRIGHT_6BIT_MASK                      ((uint32)0x3Fu)
#define QDRIGHT_8BIT_MASK                      ((uint32)0xFFu)
#define QDRIGHT_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QDRIGHT_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QDRIGHT_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(QDRIGHT_QUAD_ENCODING_MODES     << QDRIGHT_QUAD_MODE_SHIFT))       |\
         ((uint32)(QDRIGHT_CONFIG                  << QDRIGHT_MODE_SHIFT)))

#define QDRIGHT_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(QDRIGHT_PWM_STOP_EVENT          << QDRIGHT_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(QDRIGHT_PWM_OUT_INVERT          << QDRIGHT_INV_OUT_SHIFT))         |\
         ((uint32)(QDRIGHT_PWM_OUT_N_INVERT        << QDRIGHT_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(QDRIGHT_PWM_MODE                << QDRIGHT_MODE_SHIFT)))

#define QDRIGHT_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(QDRIGHT_PWM_RUN_MODE         << QDRIGHT_ONESHOT_SHIFT))
            
#define QDRIGHT_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(QDRIGHT_PWM_ALIGN            << QDRIGHT_UPDOWN_SHIFT))

#define QDRIGHT_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(QDRIGHT_PWM_KILL_EVENT      << QDRIGHT_PWM_SYNC_KILL_SHIFT))

#define QDRIGHT_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(QDRIGHT_PWM_DEAD_TIME_CYCLE  << QDRIGHT_PRESCALER_SHIFT))

#define QDRIGHT_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(QDRIGHT_PWM_PRESCALER        << QDRIGHT_PRESCALER_SHIFT))

#define QDRIGHT_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(QDRIGHT_TC_PRESCALER            << QDRIGHT_PRESCALER_SHIFT))       |\
         ((uint32)(QDRIGHT_TC_COUNTER_MODE         << QDRIGHT_UPDOWN_SHIFT))          |\
         ((uint32)(QDRIGHT_TC_RUN_MODE             << QDRIGHT_ONESHOT_SHIFT))         |\
         ((uint32)(QDRIGHT_TC_COMP_CAP_MODE        << QDRIGHT_MODE_SHIFT)))
        
#define QDRIGHT_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(QDRIGHT_QUAD_PHIA_SIGNAL_MODE   << QDRIGHT_COUNT_SHIFT))           |\
         ((uint32)(QDRIGHT_QUAD_INDEX_SIGNAL_MODE  << QDRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(QDRIGHT_QUAD_STOP_SIGNAL_MODE   << QDRIGHT_STOP_SHIFT))            |\
         ((uint32)(QDRIGHT_QUAD_PHIB_SIGNAL_MODE   << QDRIGHT_START_SHIFT)))

#define QDRIGHT_PWM_SIGNALS_MODES                                                              \
        (((uint32)(QDRIGHT_PWM_SWITCH_SIGNAL_MODE  << QDRIGHT_CAPTURE_SHIFT))         |\
         ((uint32)(QDRIGHT_PWM_COUNT_SIGNAL_MODE   << QDRIGHT_COUNT_SHIFT))           |\
         ((uint32)(QDRIGHT_PWM_RELOAD_SIGNAL_MODE  << QDRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(QDRIGHT_PWM_STOP_SIGNAL_MODE    << QDRIGHT_STOP_SHIFT))            |\
         ((uint32)(QDRIGHT_PWM_START_SIGNAL_MODE   << QDRIGHT_START_SHIFT)))

#define QDRIGHT_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(QDRIGHT_TC_CAPTURE_SIGNAL_MODE  << QDRIGHT_CAPTURE_SHIFT))         |\
         ((uint32)(QDRIGHT_TC_COUNT_SIGNAL_MODE    << QDRIGHT_COUNT_SHIFT))           |\
         ((uint32)(QDRIGHT_TC_RELOAD_SIGNAL_MODE   << QDRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(QDRIGHT_TC_STOP_SIGNAL_MODE     << QDRIGHT_STOP_SHIFT))            |\
         ((uint32)(QDRIGHT_TC_START_SIGNAL_MODE    << QDRIGHT_START_SHIFT)))
        
#define QDRIGHT_TIMER_UPDOWN_CNT_USED                                                          \
                ((QDRIGHT__COUNT_UPDOWN0 == QDRIGHT_TC_COUNTER_MODE)                  ||\
                 (QDRIGHT__COUNT_UPDOWN1 == QDRIGHT_TC_COUNTER_MODE))

#define QDRIGHT_PWM_UPDOWN_CNT_USED                                                            \
                ((QDRIGHT__CENTER == QDRIGHT_PWM_ALIGN)                               ||\
                 (QDRIGHT__ASYMMETRIC == QDRIGHT_PWM_ALIGN))               
        
#define QDRIGHT_PWM_PR_INIT_VALUE              (1u)
#define QDRIGHT_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_QDRIGHT_H */

/* [] END OF FILE */
