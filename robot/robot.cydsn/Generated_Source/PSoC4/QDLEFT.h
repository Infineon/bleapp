/*******************************************************************************
* File Name: QDLEFT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the QDLEFT
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

#if !defined(CY_TCPWM_QDLEFT_H)
#define CY_TCPWM_QDLEFT_H


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
} QDLEFT_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QDLEFT_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define QDLEFT_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define QDLEFT_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define QDLEFT_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QDLEFT_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define QDLEFT_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QDLEFT_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QDLEFT_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QDLEFT_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QDLEFT_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QDLEFT_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QDLEFT_QUAD_INTERRUPT_MASK            (0lu)

/* Timer/Counter Mode */
/* Parameters */
#define QDLEFT_TC_RUN_MODE                    (0lu)
#define QDLEFT_TC_COUNTER_MODE                (0lu)
#define QDLEFT_TC_COMP_CAP_MODE               (2lu)
#define QDLEFT_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QDLEFT_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QDLEFT_TC_COUNT_SIGNAL_MODE           (3lu)
#define QDLEFT_TC_START_SIGNAL_MODE           (0lu)
#define QDLEFT_TC_STOP_SIGNAL_MODE            (0lu)
#define QDLEFT_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QDLEFT_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QDLEFT_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QDLEFT_TC_START_SIGNAL_PRESENT        (0lu)
#define QDLEFT_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QDLEFT_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QDLEFT_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QDLEFT_PWM_KILL_EVENT                 (0lu)
#define QDLEFT_PWM_STOP_EVENT                 (0lu)
#define QDLEFT_PWM_MODE                       (4lu)
#define QDLEFT_PWM_OUT_N_INVERT               (0lu)
#define QDLEFT_PWM_OUT_INVERT                 (0lu)
#define QDLEFT_PWM_ALIGN                      (0lu)
#define QDLEFT_PWM_RUN_MODE                   (0lu)
#define QDLEFT_PWM_DEAD_TIME_CYCLE            (0lu)
#define QDLEFT_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QDLEFT_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QDLEFT_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QDLEFT_PWM_START_SIGNAL_MODE          (0lu)
#define QDLEFT_PWM_STOP_SIGNAL_MODE           (0lu)
#define QDLEFT_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QDLEFT_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QDLEFT_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QDLEFT_PWM_START_SIGNAL_PRESENT       (0lu)
#define QDLEFT_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QDLEFT_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QDLEFT_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QDLEFT_TC_PERIOD_VALUE                (65535lu)
#define QDLEFT_TC_COMPARE_VALUE               (65535lu)
#define QDLEFT_TC_COMPARE_BUF_VALUE           (65535lu)
#define QDLEFT_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QDLEFT_PWM_PERIOD_VALUE               (65535lu)
#define QDLEFT_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QDLEFT_PWM_PERIOD_SWAP                (0lu)
#define QDLEFT_PWM_COMPARE_VALUE              (65535lu)
#define QDLEFT_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QDLEFT_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QDLEFT__LEFT 0
#define QDLEFT__RIGHT 1
#define QDLEFT__CENTER 2
#define QDLEFT__ASYMMETRIC 3

#define QDLEFT__X1 0
#define QDLEFT__X2 1
#define QDLEFT__X4 2

#define QDLEFT__PWM 4
#define QDLEFT__PWM_DT 5
#define QDLEFT__PWM_PR 6

#define QDLEFT__INVERSE 1
#define QDLEFT__DIRECT 0

#define QDLEFT__CAPTURE 2
#define QDLEFT__COMPARE 0

#define QDLEFT__TRIG_LEVEL 3
#define QDLEFT__TRIG_RISING 0
#define QDLEFT__TRIG_FALLING 1
#define QDLEFT__TRIG_BOTH 2

#define QDLEFT__INTR_MASK_TC 1
#define QDLEFT__INTR_MASK_CC_MATCH 2
#define QDLEFT__INTR_MASK_NONE 0
#define QDLEFT__INTR_MASK_TC_CC 3

#define QDLEFT__UNCONFIG 8
#define QDLEFT__TIMER 1
#define QDLEFT__QUAD 3
#define QDLEFT__PWM_SEL 7

#define QDLEFT__COUNT_UP 0
#define QDLEFT__COUNT_DOWN 1
#define QDLEFT__COUNT_UPDOWN0 2
#define QDLEFT__COUNT_UPDOWN1 3


/* Prescaler */
#define QDLEFT_PRESCALE_DIVBY1                ((uint32)(0u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY2                ((uint32)(1u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY4                ((uint32)(2u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY8                ((uint32)(3u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY16               ((uint32)(4u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY32               ((uint32)(5u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY64               ((uint32)(6u << QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_PRESCALE_DIVBY128              ((uint32)(7u << QDLEFT_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QDLEFT_MODE_TIMER_COMPARE             ((uint32)(QDLEFT__COMPARE         <<  \
                                                                  QDLEFT_MODE_SHIFT))
#define QDLEFT_MODE_TIMER_CAPTURE             ((uint32)(QDLEFT__CAPTURE         <<  \
                                                                  QDLEFT_MODE_SHIFT))
#define QDLEFT_MODE_QUAD                      ((uint32)(QDLEFT__QUAD            <<  \
                                                                  QDLEFT_MODE_SHIFT))
#define QDLEFT_MODE_PWM                       ((uint32)(QDLEFT__PWM             <<  \
                                                                  QDLEFT_MODE_SHIFT))
#define QDLEFT_MODE_PWM_DT                    ((uint32)(QDLEFT__PWM_DT          <<  \
                                                                  QDLEFT_MODE_SHIFT))
#define QDLEFT_MODE_PWM_PR                    ((uint32)(QDLEFT__PWM_PR          <<  \
                                                                  QDLEFT_MODE_SHIFT))

/* Quad Modes */
#define QDLEFT_MODE_X1                        ((uint32)(QDLEFT__X1              <<  \
                                                                  QDLEFT_QUAD_MODE_SHIFT))
#define QDLEFT_MODE_X2                        ((uint32)(QDLEFT__X2              <<  \
                                                                  QDLEFT_QUAD_MODE_SHIFT))
#define QDLEFT_MODE_X4                        ((uint32)(QDLEFT__X4              <<  \
                                                                  QDLEFT_QUAD_MODE_SHIFT))

/* Counter modes */
#define QDLEFT_COUNT_UP                       ((uint32)(QDLEFT__COUNT_UP        <<  \
                                                                  QDLEFT_UPDOWN_SHIFT))
#define QDLEFT_COUNT_DOWN                     ((uint32)(QDLEFT__COUNT_DOWN      <<  \
                                                                  QDLEFT_UPDOWN_SHIFT))
#define QDLEFT_COUNT_UPDOWN0                  ((uint32)(QDLEFT__COUNT_UPDOWN0   <<  \
                                                                  QDLEFT_UPDOWN_SHIFT))
#define QDLEFT_COUNT_UPDOWN1                  ((uint32)(QDLEFT__COUNT_UPDOWN1   <<  \
                                                                  QDLEFT_UPDOWN_SHIFT))

/* PWM output invert */
#define QDLEFT_INVERT_LINE                    ((uint32)(QDLEFT__INVERSE         <<  \
                                                                  QDLEFT_INV_OUT_SHIFT))
#define QDLEFT_INVERT_LINE_N                  ((uint32)(QDLEFT__INVERSE         <<  \
                                                                  QDLEFT_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QDLEFT_TRIG_RISING                    ((uint32)QDLEFT__TRIG_RISING)
#define QDLEFT_TRIG_FALLING                   ((uint32)QDLEFT__TRIG_FALLING)
#define QDLEFT_TRIG_BOTH                      ((uint32)QDLEFT__TRIG_BOTH)
#define QDLEFT_TRIG_LEVEL                     ((uint32)QDLEFT__TRIG_LEVEL)

/* Interrupt mask */
#define QDLEFT_INTR_MASK_TC                   ((uint32)QDLEFT__INTR_MASK_TC)
#define QDLEFT_INTR_MASK_CC_MATCH             ((uint32)QDLEFT__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QDLEFT_CC_MATCH_SET                   (0x00u)
#define QDLEFT_CC_MATCH_CLEAR                 (0x01u)
#define QDLEFT_CC_MATCH_INVERT                (0x02u)
#define QDLEFT_CC_MATCH_NO_CHANGE             (0x03u)
#define QDLEFT_OVERLOW_SET                    (0x00u)
#define QDLEFT_OVERLOW_CLEAR                  (0x04u)
#define QDLEFT_OVERLOW_INVERT                 (0x08u)
#define QDLEFT_OVERLOW_NO_CHANGE              (0x0Cu)
#define QDLEFT_UNDERFLOW_SET                  (0x00u)
#define QDLEFT_UNDERFLOW_CLEAR                (0x10u)
#define QDLEFT_UNDERFLOW_INVERT               (0x20u)
#define QDLEFT_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QDLEFT_PWM_MODE_LEFT                  (QDLEFT_CC_MATCH_CLEAR        |   \
                                                         QDLEFT_OVERLOW_SET           |   \
                                                         QDLEFT_UNDERFLOW_NO_CHANGE)
#define QDLEFT_PWM_MODE_RIGHT                 (QDLEFT_CC_MATCH_SET          |   \
                                                         QDLEFT_OVERLOW_NO_CHANGE     |   \
                                                         QDLEFT_UNDERFLOW_CLEAR)
#define QDLEFT_PWM_MODE_ASYM                  (QDLEFT_CC_MATCH_INVERT       |   \
                                                         QDLEFT_OVERLOW_SET           |   \
                                                         QDLEFT_UNDERFLOW_CLEAR)

#if (QDLEFT_CY_TCPWM_V2)
    #if(QDLEFT_CY_TCPWM_4000)
        #define QDLEFT_PWM_MODE_CENTER                (QDLEFT_CC_MATCH_INVERT       |   \
                                                                 QDLEFT_OVERLOW_NO_CHANGE     |   \
                                                                 QDLEFT_UNDERFLOW_CLEAR)
    #else
        #define QDLEFT_PWM_MODE_CENTER                (QDLEFT_CC_MATCH_INVERT       |   \
                                                                 QDLEFT_OVERLOW_SET           |   \
                                                                 QDLEFT_UNDERFLOW_CLEAR)
    #endif /* (QDLEFT_CY_TCPWM_4000) */
#else
    #define QDLEFT_PWM_MODE_CENTER                (QDLEFT_CC_MATCH_INVERT       |   \
                                                             QDLEFT_OVERLOW_NO_CHANGE     |   \
                                                             QDLEFT_UNDERFLOW_CLEAR)
#endif /* (QDLEFT_CY_TCPWM_NEW) */

/* Command operations without condition */
#define QDLEFT_CMD_CAPTURE                    (0u)
#define QDLEFT_CMD_RELOAD                     (8u)
#define QDLEFT_CMD_STOP                       (16u)
#define QDLEFT_CMD_START                      (24u)

/* Status */
#define QDLEFT_STATUS_DOWN                    (1u)
#define QDLEFT_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QDLEFT_Init(void);
void   QDLEFT_Enable(void);
void   QDLEFT_Start(void);
void   QDLEFT_Stop(void);

void   QDLEFT_SetMode(uint32 mode);
void   QDLEFT_SetCounterMode(uint32 counterMode);
void   QDLEFT_SetPWMMode(uint32 modeMask);
void   QDLEFT_SetQDMode(uint32 qdMode);

void   QDLEFT_SetPrescaler(uint32 prescaler);
void   QDLEFT_TriggerCommand(uint32 mask, uint32 command);
void   QDLEFT_SetOneShot(uint32 oneShotEnable);
uint32 QDLEFT_ReadStatus(void);

void   QDLEFT_SetPWMSyncKill(uint32 syncKillEnable);
void   QDLEFT_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QDLEFT_SetPWMDeadTime(uint32 deadTime);
void   QDLEFT_SetPWMInvert(uint32 mask);

void   QDLEFT_SetInterruptMode(uint32 interruptMask);
uint32 QDLEFT_GetInterruptSourceMasked(void);
uint32 QDLEFT_GetInterruptSource(void);
void   QDLEFT_ClearInterrupt(uint32 interruptMask);
void   QDLEFT_SetInterrupt(uint32 interruptMask);

void   QDLEFT_WriteCounter(uint32 count);
uint32 QDLEFT_ReadCounter(void);

uint32 QDLEFT_ReadCapture(void);
uint32 QDLEFT_ReadCaptureBuf(void);

void   QDLEFT_WritePeriod(uint32 period);
uint32 QDLEFT_ReadPeriod(void);
void   QDLEFT_WritePeriodBuf(uint32 periodBuf);
uint32 QDLEFT_ReadPeriodBuf(void);

void   QDLEFT_WriteCompare(uint32 compare);
uint32 QDLEFT_ReadCompare(void);
void   QDLEFT_WriteCompareBuf(uint32 compareBuf);
uint32 QDLEFT_ReadCompareBuf(void);

void   QDLEFT_SetPeriodSwap(uint32 swapEnable);
void   QDLEFT_SetCompareSwap(uint32 swapEnable);

void   QDLEFT_SetCaptureMode(uint32 triggerMode);
void   QDLEFT_SetReloadMode(uint32 triggerMode);
void   QDLEFT_SetStartMode(uint32 triggerMode);
void   QDLEFT_SetStopMode(uint32 triggerMode);
void   QDLEFT_SetCountMode(uint32 triggerMode);

void   QDLEFT_SaveConfig(void);
void   QDLEFT_RestoreConfig(void);
void   QDLEFT_Sleep(void);
void   QDLEFT_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QDLEFT_BLOCK_CONTROL_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QDLEFT_BLOCK_CONTROL_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QDLEFT_COMMAND_REG                    (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QDLEFT_COMMAND_PTR                    ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QDLEFT_INTRRUPT_CAUSE_REG             (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QDLEFT_INTRRUPT_CAUSE_PTR             ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QDLEFT_CONTROL_REG                    (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CTRL )
#define QDLEFT_CONTROL_PTR                    ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CTRL )
#define QDLEFT_STATUS_REG                     (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__STATUS )
#define QDLEFT_STATUS_PTR                     ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__STATUS )
#define QDLEFT_COUNTER_REG                    (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__COUNTER )
#define QDLEFT_COUNTER_PTR                    ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__COUNTER )
#define QDLEFT_COMP_CAP_REG                   (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CC )
#define QDLEFT_COMP_CAP_PTR                   ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CC )
#define QDLEFT_COMP_CAP_BUF_REG               (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CC_BUFF )
#define QDLEFT_COMP_CAP_BUF_PTR               ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__CC_BUFF )
#define QDLEFT_PERIOD_REG                     (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__PERIOD )
#define QDLEFT_PERIOD_PTR                     ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__PERIOD )
#define QDLEFT_PERIOD_BUF_REG                 (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QDLEFT_PERIOD_BUF_PTR                 ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QDLEFT_TRIG_CONTROL0_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QDLEFT_TRIG_CONTROL0_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QDLEFT_TRIG_CONTROL1_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QDLEFT_TRIG_CONTROL1_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QDLEFT_TRIG_CONTROL2_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QDLEFT_TRIG_CONTROL2_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QDLEFT_INTERRUPT_REQ_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR )
#define QDLEFT_INTERRUPT_REQ_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR )
#define QDLEFT_INTERRUPT_SET_REG              (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_SET )
#define QDLEFT_INTERRUPT_SET_PTR              ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_SET )
#define QDLEFT_INTERRUPT_MASK_REG             (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_MASK )
#define QDLEFT_INTERRUPT_MASK_PTR             ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_MASK )
#define QDLEFT_INTERRUPT_MASKED_REG           (*(reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QDLEFT_INTERRUPT_MASKED_PTR           ( (reg32 *) QDLEFT_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QDLEFT_MASK                           ((uint32)QDLEFT_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QDLEFT_RELOAD_CC_SHIFT                (0u)
#define QDLEFT_RELOAD_PERIOD_SHIFT            (1u)
#define QDLEFT_PWM_SYNC_KILL_SHIFT            (2u)
#define QDLEFT_PWM_STOP_KILL_SHIFT            (3u)
#define QDLEFT_PRESCALER_SHIFT                (8u)
#define QDLEFT_UPDOWN_SHIFT                   (16u)
#define QDLEFT_ONESHOT_SHIFT                  (18u)
#define QDLEFT_QUAD_MODE_SHIFT                (20u)
#define QDLEFT_INV_OUT_SHIFT                  (20u)
#define QDLEFT_INV_COMPL_OUT_SHIFT            (21u)
#define QDLEFT_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QDLEFT_RELOAD_CC_MASK                 ((uint32)(QDLEFT_1BIT_MASK        <<  \
                                                                            QDLEFT_RELOAD_CC_SHIFT))
#define QDLEFT_RELOAD_PERIOD_MASK             ((uint32)(QDLEFT_1BIT_MASK        <<  \
                                                                            QDLEFT_RELOAD_PERIOD_SHIFT))
#define QDLEFT_PWM_SYNC_KILL_MASK             ((uint32)(QDLEFT_1BIT_MASK        <<  \
                                                                            QDLEFT_PWM_SYNC_KILL_SHIFT))
#define QDLEFT_PWM_STOP_KILL_MASK             ((uint32)(QDLEFT_1BIT_MASK        <<  \
                                                                            QDLEFT_PWM_STOP_KILL_SHIFT))
#define QDLEFT_PRESCALER_MASK                 ((uint32)(QDLEFT_8BIT_MASK        <<  \
                                                                            QDLEFT_PRESCALER_SHIFT))
#define QDLEFT_UPDOWN_MASK                    ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                            QDLEFT_UPDOWN_SHIFT))
#define QDLEFT_ONESHOT_MASK                   ((uint32)(QDLEFT_1BIT_MASK        <<  \
                                                                            QDLEFT_ONESHOT_SHIFT))
#define QDLEFT_QUAD_MODE_MASK                 ((uint32)(QDLEFT_3BIT_MASK        <<  \
                                                                            QDLEFT_QUAD_MODE_SHIFT))
#define QDLEFT_INV_OUT_MASK                   ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                            QDLEFT_INV_OUT_SHIFT))
#define QDLEFT_MODE_MASK                      ((uint32)(QDLEFT_3BIT_MASK        <<  \
                                                                            QDLEFT_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QDLEFT_CAPTURE_SHIFT                  (0u)
#define QDLEFT_COUNT_SHIFT                    (2u)
#define QDLEFT_RELOAD_SHIFT                   (4u)
#define QDLEFT_STOP_SHIFT                     (6u)
#define QDLEFT_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QDLEFT_CAPTURE_MASK                   ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                  QDLEFT_CAPTURE_SHIFT))
#define QDLEFT_COUNT_MASK                     ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                  QDLEFT_COUNT_SHIFT))
#define QDLEFT_RELOAD_MASK                    ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                  QDLEFT_RELOAD_SHIFT))
#define QDLEFT_STOP_MASK                      ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                  QDLEFT_STOP_SHIFT))
#define QDLEFT_START_MASK                     ((uint32)(QDLEFT_2BIT_MASK        <<  \
                                                                  QDLEFT_START_SHIFT))

/* MASK */
#define QDLEFT_1BIT_MASK                      ((uint32)0x01u)
#define QDLEFT_2BIT_MASK                      ((uint32)0x03u)
#define QDLEFT_3BIT_MASK                      ((uint32)0x07u)
#define QDLEFT_6BIT_MASK                      ((uint32)0x3Fu)
#define QDLEFT_8BIT_MASK                      ((uint32)0xFFu)
#define QDLEFT_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QDLEFT_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QDLEFT_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(QDLEFT_QUAD_ENCODING_MODES     << QDLEFT_QUAD_MODE_SHIFT))       |\
         ((uint32)(QDLEFT_CONFIG                  << QDLEFT_MODE_SHIFT)))

#define QDLEFT_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(QDLEFT_PWM_STOP_EVENT          << QDLEFT_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(QDLEFT_PWM_OUT_INVERT          << QDLEFT_INV_OUT_SHIFT))         |\
         ((uint32)(QDLEFT_PWM_OUT_N_INVERT        << QDLEFT_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(QDLEFT_PWM_MODE                << QDLEFT_MODE_SHIFT)))

#define QDLEFT_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(QDLEFT_PWM_RUN_MODE         << QDLEFT_ONESHOT_SHIFT))
            
#define QDLEFT_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(QDLEFT_PWM_ALIGN            << QDLEFT_UPDOWN_SHIFT))

#define QDLEFT_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(QDLEFT_PWM_KILL_EVENT      << QDLEFT_PWM_SYNC_KILL_SHIFT))

#define QDLEFT_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(QDLEFT_PWM_DEAD_TIME_CYCLE  << QDLEFT_PRESCALER_SHIFT))

#define QDLEFT_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(QDLEFT_PWM_PRESCALER        << QDLEFT_PRESCALER_SHIFT))

#define QDLEFT_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(QDLEFT_TC_PRESCALER            << QDLEFT_PRESCALER_SHIFT))       |\
         ((uint32)(QDLEFT_TC_COUNTER_MODE         << QDLEFT_UPDOWN_SHIFT))          |\
         ((uint32)(QDLEFT_TC_RUN_MODE             << QDLEFT_ONESHOT_SHIFT))         |\
         ((uint32)(QDLEFT_TC_COMP_CAP_MODE        << QDLEFT_MODE_SHIFT)))
        
#define QDLEFT_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(QDLEFT_QUAD_PHIA_SIGNAL_MODE   << QDLEFT_COUNT_SHIFT))           |\
         ((uint32)(QDLEFT_QUAD_INDEX_SIGNAL_MODE  << QDLEFT_RELOAD_SHIFT))          |\
         ((uint32)(QDLEFT_QUAD_STOP_SIGNAL_MODE   << QDLEFT_STOP_SHIFT))            |\
         ((uint32)(QDLEFT_QUAD_PHIB_SIGNAL_MODE   << QDLEFT_START_SHIFT)))

#define QDLEFT_PWM_SIGNALS_MODES                                                              \
        (((uint32)(QDLEFT_PWM_SWITCH_SIGNAL_MODE  << QDLEFT_CAPTURE_SHIFT))         |\
         ((uint32)(QDLEFT_PWM_COUNT_SIGNAL_MODE   << QDLEFT_COUNT_SHIFT))           |\
         ((uint32)(QDLEFT_PWM_RELOAD_SIGNAL_MODE  << QDLEFT_RELOAD_SHIFT))          |\
         ((uint32)(QDLEFT_PWM_STOP_SIGNAL_MODE    << QDLEFT_STOP_SHIFT))            |\
         ((uint32)(QDLEFT_PWM_START_SIGNAL_MODE   << QDLEFT_START_SHIFT)))

#define QDLEFT_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(QDLEFT_TC_CAPTURE_SIGNAL_MODE  << QDLEFT_CAPTURE_SHIFT))         |\
         ((uint32)(QDLEFT_TC_COUNT_SIGNAL_MODE    << QDLEFT_COUNT_SHIFT))           |\
         ((uint32)(QDLEFT_TC_RELOAD_SIGNAL_MODE   << QDLEFT_RELOAD_SHIFT))          |\
         ((uint32)(QDLEFT_TC_STOP_SIGNAL_MODE     << QDLEFT_STOP_SHIFT))            |\
         ((uint32)(QDLEFT_TC_START_SIGNAL_MODE    << QDLEFT_START_SHIFT)))
        
#define QDLEFT_TIMER_UPDOWN_CNT_USED                                                          \
                ((QDLEFT__COUNT_UPDOWN0 == QDLEFT_TC_COUNTER_MODE)                  ||\
                 (QDLEFT__COUNT_UPDOWN1 == QDLEFT_TC_COUNTER_MODE))

#define QDLEFT_PWM_UPDOWN_CNT_USED                                                            \
                ((QDLEFT__CENTER == QDLEFT_PWM_ALIGN)                               ||\
                 (QDLEFT__ASYMMETRIC == QDLEFT_PWM_ALIGN))               
        
#define QDLEFT_PWM_PR_INIT_VALUE              (1u)
#define QDLEFT_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_QDLEFT_H */

/* [] END OF FILE */
