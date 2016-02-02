/*******************************************************************************
* File Name: PWMLEFT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the PWMLEFT
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

#if !defined(CY_TCPWM_PWMLEFT_H)
#define CY_TCPWM_PWMLEFT_H


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
} PWMLEFT_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWMLEFT_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWMLEFT_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWMLEFT_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWMLEFT_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWMLEFT_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define PWMLEFT_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWMLEFT_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWMLEFT_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWMLEFT_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWMLEFT_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWMLEFT_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWMLEFT_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWMLEFT_TC_RUN_MODE                    (0lu)
#define PWMLEFT_TC_COUNTER_MODE                (0lu)
#define PWMLEFT_TC_COMP_CAP_MODE               (2lu)
#define PWMLEFT_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWMLEFT_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWMLEFT_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWMLEFT_TC_START_SIGNAL_MODE           (0lu)
#define PWMLEFT_TC_STOP_SIGNAL_MODE            (0lu)
#define PWMLEFT_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMLEFT_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWMLEFT_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWMLEFT_TC_START_SIGNAL_PRESENT        (0lu)
#define PWMLEFT_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWMLEFT_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMLEFT_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWMLEFT_PWM_KILL_EVENT                 (0lu)
#define PWMLEFT_PWM_STOP_EVENT                 (0lu)
#define PWMLEFT_PWM_MODE                       (4lu)
#define PWMLEFT_PWM_OUT_N_INVERT               (0lu)
#define PWMLEFT_PWM_OUT_INVERT                 (0lu)
#define PWMLEFT_PWM_ALIGN                      (0lu)
#define PWMLEFT_PWM_RUN_MODE                   (0lu)
#define PWMLEFT_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWMLEFT_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWMLEFT_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWMLEFT_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWMLEFT_PWM_START_SIGNAL_MODE          (0lu)
#define PWMLEFT_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWMLEFT_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMLEFT_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWMLEFT_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWMLEFT_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWMLEFT_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWMLEFT_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMLEFT_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWMLEFT_TC_PERIOD_VALUE                (65535lu)
#define PWMLEFT_TC_COMPARE_VALUE               (65535lu)
#define PWMLEFT_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWMLEFT_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWMLEFT_PWM_PERIOD_VALUE               (100lu)
#define PWMLEFT_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWMLEFT_PWM_PERIOD_SWAP                (0lu)
#define PWMLEFT_PWM_COMPARE_VALUE              (50lu)
#define PWMLEFT_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWMLEFT_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWMLEFT__LEFT 0
#define PWMLEFT__RIGHT 1
#define PWMLEFT__CENTER 2
#define PWMLEFT__ASYMMETRIC 3

#define PWMLEFT__X1 0
#define PWMLEFT__X2 1
#define PWMLEFT__X4 2

#define PWMLEFT__PWM 4
#define PWMLEFT__PWM_DT 5
#define PWMLEFT__PWM_PR 6

#define PWMLEFT__INVERSE 1
#define PWMLEFT__DIRECT 0

#define PWMLEFT__CAPTURE 2
#define PWMLEFT__COMPARE 0

#define PWMLEFT__TRIG_LEVEL 3
#define PWMLEFT__TRIG_RISING 0
#define PWMLEFT__TRIG_FALLING 1
#define PWMLEFT__TRIG_BOTH 2

#define PWMLEFT__INTR_MASK_TC 1
#define PWMLEFT__INTR_MASK_CC_MATCH 2
#define PWMLEFT__INTR_MASK_NONE 0
#define PWMLEFT__INTR_MASK_TC_CC 3

#define PWMLEFT__UNCONFIG 8
#define PWMLEFT__TIMER 1
#define PWMLEFT__QUAD 3
#define PWMLEFT__PWM_SEL 7

#define PWMLEFT__COUNT_UP 0
#define PWMLEFT__COUNT_DOWN 1
#define PWMLEFT__COUNT_UPDOWN0 2
#define PWMLEFT__COUNT_UPDOWN1 3


/* Prescaler */
#define PWMLEFT_PRESCALE_DIVBY1                ((uint32)(0u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY2                ((uint32)(1u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY4                ((uint32)(2u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY8                ((uint32)(3u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY16               ((uint32)(4u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY32               ((uint32)(5u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY64               ((uint32)(6u << PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_PRESCALE_DIVBY128              ((uint32)(7u << PWMLEFT_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWMLEFT_MODE_TIMER_COMPARE             ((uint32)(PWMLEFT__COMPARE         <<  \
                                                                  PWMLEFT_MODE_SHIFT))
#define PWMLEFT_MODE_TIMER_CAPTURE             ((uint32)(PWMLEFT__CAPTURE         <<  \
                                                                  PWMLEFT_MODE_SHIFT))
#define PWMLEFT_MODE_QUAD                      ((uint32)(PWMLEFT__QUAD            <<  \
                                                                  PWMLEFT_MODE_SHIFT))
#define PWMLEFT_MODE_PWM                       ((uint32)(PWMLEFT__PWM             <<  \
                                                                  PWMLEFT_MODE_SHIFT))
#define PWMLEFT_MODE_PWM_DT                    ((uint32)(PWMLEFT__PWM_DT          <<  \
                                                                  PWMLEFT_MODE_SHIFT))
#define PWMLEFT_MODE_PWM_PR                    ((uint32)(PWMLEFT__PWM_PR          <<  \
                                                                  PWMLEFT_MODE_SHIFT))

/* Quad Modes */
#define PWMLEFT_MODE_X1                        ((uint32)(PWMLEFT__X1              <<  \
                                                                  PWMLEFT_QUAD_MODE_SHIFT))
#define PWMLEFT_MODE_X2                        ((uint32)(PWMLEFT__X2              <<  \
                                                                  PWMLEFT_QUAD_MODE_SHIFT))
#define PWMLEFT_MODE_X4                        ((uint32)(PWMLEFT__X4              <<  \
                                                                  PWMLEFT_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWMLEFT_COUNT_UP                       ((uint32)(PWMLEFT__COUNT_UP        <<  \
                                                                  PWMLEFT_UPDOWN_SHIFT))
#define PWMLEFT_COUNT_DOWN                     ((uint32)(PWMLEFT__COUNT_DOWN      <<  \
                                                                  PWMLEFT_UPDOWN_SHIFT))
#define PWMLEFT_COUNT_UPDOWN0                  ((uint32)(PWMLEFT__COUNT_UPDOWN0   <<  \
                                                                  PWMLEFT_UPDOWN_SHIFT))
#define PWMLEFT_COUNT_UPDOWN1                  ((uint32)(PWMLEFT__COUNT_UPDOWN1   <<  \
                                                                  PWMLEFT_UPDOWN_SHIFT))

/* PWM output invert */
#define PWMLEFT_INVERT_LINE                    ((uint32)(PWMLEFT__INVERSE         <<  \
                                                                  PWMLEFT_INV_OUT_SHIFT))
#define PWMLEFT_INVERT_LINE_N                  ((uint32)(PWMLEFT__INVERSE         <<  \
                                                                  PWMLEFT_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWMLEFT_TRIG_RISING                    ((uint32)PWMLEFT__TRIG_RISING)
#define PWMLEFT_TRIG_FALLING                   ((uint32)PWMLEFT__TRIG_FALLING)
#define PWMLEFT_TRIG_BOTH                      ((uint32)PWMLEFT__TRIG_BOTH)
#define PWMLEFT_TRIG_LEVEL                     ((uint32)PWMLEFT__TRIG_LEVEL)

/* Interrupt mask */
#define PWMLEFT_INTR_MASK_TC                   ((uint32)PWMLEFT__INTR_MASK_TC)
#define PWMLEFT_INTR_MASK_CC_MATCH             ((uint32)PWMLEFT__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWMLEFT_CC_MATCH_SET                   (0x00u)
#define PWMLEFT_CC_MATCH_CLEAR                 (0x01u)
#define PWMLEFT_CC_MATCH_INVERT                (0x02u)
#define PWMLEFT_CC_MATCH_NO_CHANGE             (0x03u)
#define PWMLEFT_OVERLOW_SET                    (0x00u)
#define PWMLEFT_OVERLOW_CLEAR                  (0x04u)
#define PWMLEFT_OVERLOW_INVERT                 (0x08u)
#define PWMLEFT_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWMLEFT_UNDERFLOW_SET                  (0x00u)
#define PWMLEFT_UNDERFLOW_CLEAR                (0x10u)
#define PWMLEFT_UNDERFLOW_INVERT               (0x20u)
#define PWMLEFT_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWMLEFT_PWM_MODE_LEFT                  (PWMLEFT_CC_MATCH_CLEAR        |   \
                                                         PWMLEFT_OVERLOW_SET           |   \
                                                         PWMLEFT_UNDERFLOW_NO_CHANGE)
#define PWMLEFT_PWM_MODE_RIGHT                 (PWMLEFT_CC_MATCH_SET          |   \
                                                         PWMLEFT_OVERLOW_NO_CHANGE     |   \
                                                         PWMLEFT_UNDERFLOW_CLEAR)
#define PWMLEFT_PWM_MODE_ASYM                  (PWMLEFT_CC_MATCH_INVERT       |   \
                                                         PWMLEFT_OVERLOW_SET           |   \
                                                         PWMLEFT_UNDERFLOW_CLEAR)

#if (PWMLEFT_CY_TCPWM_V2)
    #if(PWMLEFT_CY_TCPWM_4000)
        #define PWMLEFT_PWM_MODE_CENTER                (PWMLEFT_CC_MATCH_INVERT       |   \
                                                                 PWMLEFT_OVERLOW_NO_CHANGE     |   \
                                                                 PWMLEFT_UNDERFLOW_CLEAR)
    #else
        #define PWMLEFT_PWM_MODE_CENTER                (PWMLEFT_CC_MATCH_INVERT       |   \
                                                                 PWMLEFT_OVERLOW_SET           |   \
                                                                 PWMLEFT_UNDERFLOW_CLEAR)
    #endif /* (PWMLEFT_CY_TCPWM_4000) */
#else
    #define PWMLEFT_PWM_MODE_CENTER                (PWMLEFT_CC_MATCH_INVERT       |   \
                                                             PWMLEFT_OVERLOW_NO_CHANGE     |   \
                                                             PWMLEFT_UNDERFLOW_CLEAR)
#endif /* (PWMLEFT_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWMLEFT_CMD_CAPTURE                    (0u)
#define PWMLEFT_CMD_RELOAD                     (8u)
#define PWMLEFT_CMD_STOP                       (16u)
#define PWMLEFT_CMD_START                      (24u)

/* Status */
#define PWMLEFT_STATUS_DOWN                    (1u)
#define PWMLEFT_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWMLEFT_Init(void);
void   PWMLEFT_Enable(void);
void   PWMLEFT_Start(void);
void   PWMLEFT_Stop(void);

void   PWMLEFT_SetMode(uint32 mode);
void   PWMLEFT_SetCounterMode(uint32 counterMode);
void   PWMLEFT_SetPWMMode(uint32 modeMask);
void   PWMLEFT_SetQDMode(uint32 qdMode);

void   PWMLEFT_SetPrescaler(uint32 prescaler);
void   PWMLEFT_TriggerCommand(uint32 mask, uint32 command);
void   PWMLEFT_SetOneShot(uint32 oneShotEnable);
uint32 PWMLEFT_ReadStatus(void);

void   PWMLEFT_SetPWMSyncKill(uint32 syncKillEnable);
void   PWMLEFT_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWMLEFT_SetPWMDeadTime(uint32 deadTime);
void   PWMLEFT_SetPWMInvert(uint32 mask);

void   PWMLEFT_SetInterruptMode(uint32 interruptMask);
uint32 PWMLEFT_GetInterruptSourceMasked(void);
uint32 PWMLEFT_GetInterruptSource(void);
void   PWMLEFT_ClearInterrupt(uint32 interruptMask);
void   PWMLEFT_SetInterrupt(uint32 interruptMask);

void   PWMLEFT_WriteCounter(uint32 count);
uint32 PWMLEFT_ReadCounter(void);

uint32 PWMLEFT_ReadCapture(void);
uint32 PWMLEFT_ReadCaptureBuf(void);

void   PWMLEFT_WritePeriod(uint32 period);
uint32 PWMLEFT_ReadPeriod(void);
void   PWMLEFT_WritePeriodBuf(uint32 periodBuf);
uint32 PWMLEFT_ReadPeriodBuf(void);

void   PWMLEFT_WriteCompare(uint32 compare);
uint32 PWMLEFT_ReadCompare(void);
void   PWMLEFT_WriteCompareBuf(uint32 compareBuf);
uint32 PWMLEFT_ReadCompareBuf(void);

void   PWMLEFT_SetPeriodSwap(uint32 swapEnable);
void   PWMLEFT_SetCompareSwap(uint32 swapEnable);

void   PWMLEFT_SetCaptureMode(uint32 triggerMode);
void   PWMLEFT_SetReloadMode(uint32 triggerMode);
void   PWMLEFT_SetStartMode(uint32 triggerMode);
void   PWMLEFT_SetStopMode(uint32 triggerMode);
void   PWMLEFT_SetCountMode(uint32 triggerMode);

void   PWMLEFT_SaveConfig(void);
void   PWMLEFT_RestoreConfig(void);
void   PWMLEFT_Sleep(void);
void   PWMLEFT_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWMLEFT_BLOCK_CONTROL_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMLEFT_BLOCK_CONTROL_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMLEFT_COMMAND_REG                    (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMLEFT_COMMAND_PTR                    ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMLEFT_INTRRUPT_CAUSE_REG             (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMLEFT_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMLEFT_CONTROL_REG                    (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CTRL )
#define PWMLEFT_CONTROL_PTR                    ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CTRL )
#define PWMLEFT_STATUS_REG                     (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__STATUS )
#define PWMLEFT_STATUS_PTR                     ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__STATUS )
#define PWMLEFT_COUNTER_REG                    (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__COUNTER )
#define PWMLEFT_COUNTER_PTR                    ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__COUNTER )
#define PWMLEFT_COMP_CAP_REG                   (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CC )
#define PWMLEFT_COMP_CAP_PTR                   ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CC )
#define PWMLEFT_COMP_CAP_BUF_REG               (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMLEFT_COMP_CAP_BUF_PTR               ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMLEFT_PERIOD_REG                     (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__PERIOD )
#define PWMLEFT_PERIOD_PTR                     ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__PERIOD )
#define PWMLEFT_PERIOD_BUF_REG                 (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMLEFT_PERIOD_BUF_PTR                 ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMLEFT_TRIG_CONTROL0_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMLEFT_TRIG_CONTROL0_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMLEFT_TRIG_CONTROL1_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMLEFT_TRIG_CONTROL1_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMLEFT_TRIG_CONTROL2_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMLEFT_TRIG_CONTROL2_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMLEFT_INTERRUPT_REQ_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR )
#define PWMLEFT_INTERRUPT_REQ_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR )
#define PWMLEFT_INTERRUPT_SET_REG              (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMLEFT_INTERRUPT_SET_PTR              ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMLEFT_INTERRUPT_MASK_REG             (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMLEFT_INTERRUPT_MASK_PTR             ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMLEFT_INTERRUPT_MASKED_REG           (*(reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWMLEFT_INTERRUPT_MASKED_PTR           ( (reg32 *) PWMLEFT_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWMLEFT_MASK                           ((uint32)PWMLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWMLEFT_RELOAD_CC_SHIFT                (0u)
#define PWMLEFT_RELOAD_PERIOD_SHIFT            (1u)
#define PWMLEFT_PWM_SYNC_KILL_SHIFT            (2u)
#define PWMLEFT_PWM_STOP_KILL_SHIFT            (3u)
#define PWMLEFT_PRESCALER_SHIFT                (8u)
#define PWMLEFT_UPDOWN_SHIFT                   (16u)
#define PWMLEFT_ONESHOT_SHIFT                  (18u)
#define PWMLEFT_QUAD_MODE_SHIFT                (20u)
#define PWMLEFT_INV_OUT_SHIFT                  (20u)
#define PWMLEFT_INV_COMPL_OUT_SHIFT            (21u)
#define PWMLEFT_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWMLEFT_RELOAD_CC_MASK                 ((uint32)(PWMLEFT_1BIT_MASK        <<  \
                                                                            PWMLEFT_RELOAD_CC_SHIFT))
#define PWMLEFT_RELOAD_PERIOD_MASK             ((uint32)(PWMLEFT_1BIT_MASK        <<  \
                                                                            PWMLEFT_RELOAD_PERIOD_SHIFT))
#define PWMLEFT_PWM_SYNC_KILL_MASK             ((uint32)(PWMLEFT_1BIT_MASK        <<  \
                                                                            PWMLEFT_PWM_SYNC_KILL_SHIFT))
#define PWMLEFT_PWM_STOP_KILL_MASK             ((uint32)(PWMLEFT_1BIT_MASK        <<  \
                                                                            PWMLEFT_PWM_STOP_KILL_SHIFT))
#define PWMLEFT_PRESCALER_MASK                 ((uint32)(PWMLEFT_8BIT_MASK        <<  \
                                                                            PWMLEFT_PRESCALER_SHIFT))
#define PWMLEFT_UPDOWN_MASK                    ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                            PWMLEFT_UPDOWN_SHIFT))
#define PWMLEFT_ONESHOT_MASK                   ((uint32)(PWMLEFT_1BIT_MASK        <<  \
                                                                            PWMLEFT_ONESHOT_SHIFT))
#define PWMLEFT_QUAD_MODE_MASK                 ((uint32)(PWMLEFT_3BIT_MASK        <<  \
                                                                            PWMLEFT_QUAD_MODE_SHIFT))
#define PWMLEFT_INV_OUT_MASK                   ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                            PWMLEFT_INV_OUT_SHIFT))
#define PWMLEFT_MODE_MASK                      ((uint32)(PWMLEFT_3BIT_MASK        <<  \
                                                                            PWMLEFT_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWMLEFT_CAPTURE_SHIFT                  (0u)
#define PWMLEFT_COUNT_SHIFT                    (2u)
#define PWMLEFT_RELOAD_SHIFT                   (4u)
#define PWMLEFT_STOP_SHIFT                     (6u)
#define PWMLEFT_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWMLEFT_CAPTURE_MASK                   ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                  PWMLEFT_CAPTURE_SHIFT))
#define PWMLEFT_COUNT_MASK                     ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                  PWMLEFT_COUNT_SHIFT))
#define PWMLEFT_RELOAD_MASK                    ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                  PWMLEFT_RELOAD_SHIFT))
#define PWMLEFT_STOP_MASK                      ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                  PWMLEFT_STOP_SHIFT))
#define PWMLEFT_START_MASK                     ((uint32)(PWMLEFT_2BIT_MASK        <<  \
                                                                  PWMLEFT_START_SHIFT))

/* MASK */
#define PWMLEFT_1BIT_MASK                      ((uint32)0x01u)
#define PWMLEFT_2BIT_MASK                      ((uint32)0x03u)
#define PWMLEFT_3BIT_MASK                      ((uint32)0x07u)
#define PWMLEFT_6BIT_MASK                      ((uint32)0x3Fu)
#define PWMLEFT_8BIT_MASK                      ((uint32)0xFFu)
#define PWMLEFT_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWMLEFT_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWMLEFT_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWMLEFT_QUAD_ENCODING_MODES     << PWMLEFT_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWMLEFT_CONFIG                  << PWMLEFT_MODE_SHIFT)))

#define PWMLEFT_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWMLEFT_PWM_STOP_EVENT          << PWMLEFT_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWMLEFT_PWM_OUT_INVERT          << PWMLEFT_INV_OUT_SHIFT))         |\
         ((uint32)(PWMLEFT_PWM_OUT_N_INVERT        << PWMLEFT_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWMLEFT_PWM_MODE                << PWMLEFT_MODE_SHIFT)))

#define PWMLEFT_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWMLEFT_PWM_RUN_MODE         << PWMLEFT_ONESHOT_SHIFT))
            
#define PWMLEFT_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWMLEFT_PWM_ALIGN            << PWMLEFT_UPDOWN_SHIFT))

#define PWMLEFT_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWMLEFT_PWM_KILL_EVENT      << PWMLEFT_PWM_SYNC_KILL_SHIFT))

#define PWMLEFT_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWMLEFT_PWM_DEAD_TIME_CYCLE  << PWMLEFT_PRESCALER_SHIFT))

#define PWMLEFT_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWMLEFT_PWM_PRESCALER        << PWMLEFT_PRESCALER_SHIFT))

#define PWMLEFT_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWMLEFT_TC_PRESCALER            << PWMLEFT_PRESCALER_SHIFT))       |\
         ((uint32)(PWMLEFT_TC_COUNTER_MODE         << PWMLEFT_UPDOWN_SHIFT))          |\
         ((uint32)(PWMLEFT_TC_RUN_MODE             << PWMLEFT_ONESHOT_SHIFT))         |\
         ((uint32)(PWMLEFT_TC_COMP_CAP_MODE        << PWMLEFT_MODE_SHIFT)))
        
#define PWMLEFT_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWMLEFT_QUAD_PHIA_SIGNAL_MODE   << PWMLEFT_COUNT_SHIFT))           |\
         ((uint32)(PWMLEFT_QUAD_INDEX_SIGNAL_MODE  << PWMLEFT_RELOAD_SHIFT))          |\
         ((uint32)(PWMLEFT_QUAD_STOP_SIGNAL_MODE   << PWMLEFT_STOP_SHIFT))            |\
         ((uint32)(PWMLEFT_QUAD_PHIB_SIGNAL_MODE   << PWMLEFT_START_SHIFT)))

#define PWMLEFT_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWMLEFT_PWM_SWITCH_SIGNAL_MODE  << PWMLEFT_CAPTURE_SHIFT))         |\
         ((uint32)(PWMLEFT_PWM_COUNT_SIGNAL_MODE   << PWMLEFT_COUNT_SHIFT))           |\
         ((uint32)(PWMLEFT_PWM_RELOAD_SIGNAL_MODE  << PWMLEFT_RELOAD_SHIFT))          |\
         ((uint32)(PWMLEFT_PWM_STOP_SIGNAL_MODE    << PWMLEFT_STOP_SHIFT))            |\
         ((uint32)(PWMLEFT_PWM_START_SIGNAL_MODE   << PWMLEFT_START_SHIFT)))

#define PWMLEFT_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWMLEFT_TC_CAPTURE_SIGNAL_MODE  << PWMLEFT_CAPTURE_SHIFT))         |\
         ((uint32)(PWMLEFT_TC_COUNT_SIGNAL_MODE    << PWMLEFT_COUNT_SHIFT))           |\
         ((uint32)(PWMLEFT_TC_RELOAD_SIGNAL_MODE   << PWMLEFT_RELOAD_SHIFT))          |\
         ((uint32)(PWMLEFT_TC_STOP_SIGNAL_MODE     << PWMLEFT_STOP_SHIFT))            |\
         ((uint32)(PWMLEFT_TC_START_SIGNAL_MODE    << PWMLEFT_START_SHIFT)))
        
#define PWMLEFT_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWMLEFT__COUNT_UPDOWN0 == PWMLEFT_TC_COUNTER_MODE)                  ||\
                 (PWMLEFT__COUNT_UPDOWN1 == PWMLEFT_TC_COUNTER_MODE))

#define PWMLEFT_PWM_UPDOWN_CNT_USED                                                            \
                ((PWMLEFT__CENTER == PWMLEFT_PWM_ALIGN)                               ||\
                 (PWMLEFT__ASYMMETRIC == PWMLEFT_PWM_ALIGN))               
        
#define PWMLEFT_PWM_PR_INIT_VALUE              (1u)
#define PWMLEFT_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWMLEFT_H */

/* [] END OF FILE */
