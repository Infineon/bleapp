/*******************************************************************************
* File Name: PWMRIGHT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the PWMRIGHT
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

#if !defined(CY_TCPWM_PWMRIGHT_H)
#define CY_TCPWM_PWMRIGHT_H


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
} PWMRIGHT_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWMRIGHT_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWMRIGHT_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWMRIGHT_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWMRIGHT_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWMRIGHT_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define PWMRIGHT_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWMRIGHT_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWMRIGHT_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWMRIGHT_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWMRIGHT_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWMRIGHT_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWMRIGHT_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWMRIGHT_TC_RUN_MODE                    (0lu)
#define PWMRIGHT_TC_COUNTER_MODE                (0lu)
#define PWMRIGHT_TC_COMP_CAP_MODE               (2lu)
#define PWMRIGHT_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWMRIGHT_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWMRIGHT_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWMRIGHT_TC_START_SIGNAL_MODE           (0lu)
#define PWMRIGHT_TC_STOP_SIGNAL_MODE            (0lu)
#define PWMRIGHT_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMRIGHT_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWMRIGHT_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWMRIGHT_TC_START_SIGNAL_PRESENT        (0lu)
#define PWMRIGHT_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWMRIGHT_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMRIGHT_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWMRIGHT_PWM_KILL_EVENT                 (0lu)
#define PWMRIGHT_PWM_STOP_EVENT                 (0lu)
#define PWMRIGHT_PWM_MODE                       (4lu)
#define PWMRIGHT_PWM_OUT_N_INVERT               (0lu)
#define PWMRIGHT_PWM_OUT_INVERT                 (0lu)
#define PWMRIGHT_PWM_ALIGN                      (0lu)
#define PWMRIGHT_PWM_RUN_MODE                   (0lu)
#define PWMRIGHT_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWMRIGHT_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWMRIGHT_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWMRIGHT_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWMRIGHT_PWM_START_SIGNAL_MODE          (0lu)
#define PWMRIGHT_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWMRIGHT_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMRIGHT_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWMRIGHT_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWMRIGHT_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWMRIGHT_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWMRIGHT_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMRIGHT_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWMRIGHT_TC_PERIOD_VALUE                (65535lu)
#define PWMRIGHT_TC_COMPARE_VALUE               (65535lu)
#define PWMRIGHT_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWMRIGHT_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWMRIGHT_PWM_PERIOD_VALUE               (100lu)
#define PWMRIGHT_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWMRIGHT_PWM_PERIOD_SWAP                (0lu)
#define PWMRIGHT_PWM_COMPARE_VALUE              (50lu)
#define PWMRIGHT_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWMRIGHT_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWMRIGHT__LEFT 0
#define PWMRIGHT__RIGHT 1
#define PWMRIGHT__CENTER 2
#define PWMRIGHT__ASYMMETRIC 3

#define PWMRIGHT__X1 0
#define PWMRIGHT__X2 1
#define PWMRIGHT__X4 2

#define PWMRIGHT__PWM 4
#define PWMRIGHT__PWM_DT 5
#define PWMRIGHT__PWM_PR 6

#define PWMRIGHT__INVERSE 1
#define PWMRIGHT__DIRECT 0

#define PWMRIGHT__CAPTURE 2
#define PWMRIGHT__COMPARE 0

#define PWMRIGHT__TRIG_LEVEL 3
#define PWMRIGHT__TRIG_RISING 0
#define PWMRIGHT__TRIG_FALLING 1
#define PWMRIGHT__TRIG_BOTH 2

#define PWMRIGHT__INTR_MASK_TC 1
#define PWMRIGHT__INTR_MASK_CC_MATCH 2
#define PWMRIGHT__INTR_MASK_NONE 0
#define PWMRIGHT__INTR_MASK_TC_CC 3

#define PWMRIGHT__UNCONFIG 8
#define PWMRIGHT__TIMER 1
#define PWMRIGHT__QUAD 3
#define PWMRIGHT__PWM_SEL 7

#define PWMRIGHT__COUNT_UP 0
#define PWMRIGHT__COUNT_DOWN 1
#define PWMRIGHT__COUNT_UPDOWN0 2
#define PWMRIGHT__COUNT_UPDOWN1 3


/* Prescaler */
#define PWMRIGHT_PRESCALE_DIVBY1                ((uint32)(0u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY2                ((uint32)(1u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY4                ((uint32)(2u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY8                ((uint32)(3u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY16               ((uint32)(4u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY32               ((uint32)(5u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY64               ((uint32)(6u << PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_PRESCALE_DIVBY128              ((uint32)(7u << PWMRIGHT_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWMRIGHT_MODE_TIMER_COMPARE             ((uint32)(PWMRIGHT__COMPARE         <<  \
                                                                  PWMRIGHT_MODE_SHIFT))
#define PWMRIGHT_MODE_TIMER_CAPTURE             ((uint32)(PWMRIGHT__CAPTURE         <<  \
                                                                  PWMRIGHT_MODE_SHIFT))
#define PWMRIGHT_MODE_QUAD                      ((uint32)(PWMRIGHT__QUAD            <<  \
                                                                  PWMRIGHT_MODE_SHIFT))
#define PWMRIGHT_MODE_PWM                       ((uint32)(PWMRIGHT__PWM             <<  \
                                                                  PWMRIGHT_MODE_SHIFT))
#define PWMRIGHT_MODE_PWM_DT                    ((uint32)(PWMRIGHT__PWM_DT          <<  \
                                                                  PWMRIGHT_MODE_SHIFT))
#define PWMRIGHT_MODE_PWM_PR                    ((uint32)(PWMRIGHT__PWM_PR          <<  \
                                                                  PWMRIGHT_MODE_SHIFT))

/* Quad Modes */
#define PWMRIGHT_MODE_X1                        ((uint32)(PWMRIGHT__X1              <<  \
                                                                  PWMRIGHT_QUAD_MODE_SHIFT))
#define PWMRIGHT_MODE_X2                        ((uint32)(PWMRIGHT__X2              <<  \
                                                                  PWMRIGHT_QUAD_MODE_SHIFT))
#define PWMRIGHT_MODE_X4                        ((uint32)(PWMRIGHT__X4              <<  \
                                                                  PWMRIGHT_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWMRIGHT_COUNT_UP                       ((uint32)(PWMRIGHT__COUNT_UP        <<  \
                                                                  PWMRIGHT_UPDOWN_SHIFT))
#define PWMRIGHT_COUNT_DOWN                     ((uint32)(PWMRIGHT__COUNT_DOWN      <<  \
                                                                  PWMRIGHT_UPDOWN_SHIFT))
#define PWMRIGHT_COUNT_UPDOWN0                  ((uint32)(PWMRIGHT__COUNT_UPDOWN0   <<  \
                                                                  PWMRIGHT_UPDOWN_SHIFT))
#define PWMRIGHT_COUNT_UPDOWN1                  ((uint32)(PWMRIGHT__COUNT_UPDOWN1   <<  \
                                                                  PWMRIGHT_UPDOWN_SHIFT))

/* PWM output invert */
#define PWMRIGHT_INVERT_LINE                    ((uint32)(PWMRIGHT__INVERSE         <<  \
                                                                  PWMRIGHT_INV_OUT_SHIFT))
#define PWMRIGHT_INVERT_LINE_N                  ((uint32)(PWMRIGHT__INVERSE         <<  \
                                                                  PWMRIGHT_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWMRIGHT_TRIG_RISING                    ((uint32)PWMRIGHT__TRIG_RISING)
#define PWMRIGHT_TRIG_FALLING                   ((uint32)PWMRIGHT__TRIG_FALLING)
#define PWMRIGHT_TRIG_BOTH                      ((uint32)PWMRIGHT__TRIG_BOTH)
#define PWMRIGHT_TRIG_LEVEL                     ((uint32)PWMRIGHT__TRIG_LEVEL)

/* Interrupt mask */
#define PWMRIGHT_INTR_MASK_TC                   ((uint32)PWMRIGHT__INTR_MASK_TC)
#define PWMRIGHT_INTR_MASK_CC_MATCH             ((uint32)PWMRIGHT__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWMRIGHT_CC_MATCH_SET                   (0x00u)
#define PWMRIGHT_CC_MATCH_CLEAR                 (0x01u)
#define PWMRIGHT_CC_MATCH_INVERT                (0x02u)
#define PWMRIGHT_CC_MATCH_NO_CHANGE             (0x03u)
#define PWMRIGHT_OVERLOW_SET                    (0x00u)
#define PWMRIGHT_OVERLOW_CLEAR                  (0x04u)
#define PWMRIGHT_OVERLOW_INVERT                 (0x08u)
#define PWMRIGHT_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWMRIGHT_UNDERFLOW_SET                  (0x00u)
#define PWMRIGHT_UNDERFLOW_CLEAR                (0x10u)
#define PWMRIGHT_UNDERFLOW_INVERT               (0x20u)
#define PWMRIGHT_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWMRIGHT_PWM_MODE_LEFT                  (PWMRIGHT_CC_MATCH_CLEAR        |   \
                                                         PWMRIGHT_OVERLOW_SET           |   \
                                                         PWMRIGHT_UNDERFLOW_NO_CHANGE)
#define PWMRIGHT_PWM_MODE_RIGHT                 (PWMRIGHT_CC_MATCH_SET          |   \
                                                         PWMRIGHT_OVERLOW_NO_CHANGE     |   \
                                                         PWMRIGHT_UNDERFLOW_CLEAR)
#define PWMRIGHT_PWM_MODE_ASYM                  (PWMRIGHT_CC_MATCH_INVERT       |   \
                                                         PWMRIGHT_OVERLOW_SET           |   \
                                                         PWMRIGHT_UNDERFLOW_CLEAR)

#if (PWMRIGHT_CY_TCPWM_V2)
    #if(PWMRIGHT_CY_TCPWM_4000)
        #define PWMRIGHT_PWM_MODE_CENTER                (PWMRIGHT_CC_MATCH_INVERT       |   \
                                                                 PWMRIGHT_OVERLOW_NO_CHANGE     |   \
                                                                 PWMRIGHT_UNDERFLOW_CLEAR)
    #else
        #define PWMRIGHT_PWM_MODE_CENTER                (PWMRIGHT_CC_MATCH_INVERT       |   \
                                                                 PWMRIGHT_OVERLOW_SET           |   \
                                                                 PWMRIGHT_UNDERFLOW_CLEAR)
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */
#else
    #define PWMRIGHT_PWM_MODE_CENTER                (PWMRIGHT_CC_MATCH_INVERT       |   \
                                                             PWMRIGHT_OVERLOW_NO_CHANGE     |   \
                                                             PWMRIGHT_UNDERFLOW_CLEAR)
#endif /* (PWMRIGHT_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWMRIGHT_CMD_CAPTURE                    (0u)
#define PWMRIGHT_CMD_RELOAD                     (8u)
#define PWMRIGHT_CMD_STOP                       (16u)
#define PWMRIGHT_CMD_START                      (24u)

/* Status */
#define PWMRIGHT_STATUS_DOWN                    (1u)
#define PWMRIGHT_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWMRIGHT_Init(void);
void   PWMRIGHT_Enable(void);
void   PWMRIGHT_Start(void);
void   PWMRIGHT_Stop(void);

void   PWMRIGHT_SetMode(uint32 mode);
void   PWMRIGHT_SetCounterMode(uint32 counterMode);
void   PWMRIGHT_SetPWMMode(uint32 modeMask);
void   PWMRIGHT_SetQDMode(uint32 qdMode);

void   PWMRIGHT_SetPrescaler(uint32 prescaler);
void   PWMRIGHT_TriggerCommand(uint32 mask, uint32 command);
void   PWMRIGHT_SetOneShot(uint32 oneShotEnable);
uint32 PWMRIGHT_ReadStatus(void);

void   PWMRIGHT_SetPWMSyncKill(uint32 syncKillEnable);
void   PWMRIGHT_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWMRIGHT_SetPWMDeadTime(uint32 deadTime);
void   PWMRIGHT_SetPWMInvert(uint32 mask);

void   PWMRIGHT_SetInterruptMode(uint32 interruptMask);
uint32 PWMRIGHT_GetInterruptSourceMasked(void);
uint32 PWMRIGHT_GetInterruptSource(void);
void   PWMRIGHT_ClearInterrupt(uint32 interruptMask);
void   PWMRIGHT_SetInterrupt(uint32 interruptMask);

void   PWMRIGHT_WriteCounter(uint32 count);
uint32 PWMRIGHT_ReadCounter(void);

uint32 PWMRIGHT_ReadCapture(void);
uint32 PWMRIGHT_ReadCaptureBuf(void);

void   PWMRIGHT_WritePeriod(uint32 period);
uint32 PWMRIGHT_ReadPeriod(void);
void   PWMRIGHT_WritePeriodBuf(uint32 periodBuf);
uint32 PWMRIGHT_ReadPeriodBuf(void);

void   PWMRIGHT_WriteCompare(uint32 compare);
uint32 PWMRIGHT_ReadCompare(void);
void   PWMRIGHT_WriteCompareBuf(uint32 compareBuf);
uint32 PWMRIGHT_ReadCompareBuf(void);

void   PWMRIGHT_SetPeriodSwap(uint32 swapEnable);
void   PWMRIGHT_SetCompareSwap(uint32 swapEnable);

void   PWMRIGHT_SetCaptureMode(uint32 triggerMode);
void   PWMRIGHT_SetReloadMode(uint32 triggerMode);
void   PWMRIGHT_SetStartMode(uint32 triggerMode);
void   PWMRIGHT_SetStopMode(uint32 triggerMode);
void   PWMRIGHT_SetCountMode(uint32 triggerMode);

void   PWMRIGHT_SaveConfig(void);
void   PWMRIGHT_RestoreConfig(void);
void   PWMRIGHT_Sleep(void);
void   PWMRIGHT_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWMRIGHT_BLOCK_CONTROL_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMRIGHT_BLOCK_CONTROL_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMRIGHT_COMMAND_REG                    (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMRIGHT_COMMAND_PTR                    ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMRIGHT_INTRRUPT_CAUSE_REG             (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMRIGHT_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMRIGHT_CONTROL_REG                    (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CTRL )
#define PWMRIGHT_CONTROL_PTR                    ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CTRL )
#define PWMRIGHT_STATUS_REG                     (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__STATUS )
#define PWMRIGHT_STATUS_PTR                     ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__STATUS )
#define PWMRIGHT_COUNTER_REG                    (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__COUNTER )
#define PWMRIGHT_COUNTER_PTR                    ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__COUNTER )
#define PWMRIGHT_COMP_CAP_REG                   (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CC )
#define PWMRIGHT_COMP_CAP_PTR                   ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CC )
#define PWMRIGHT_COMP_CAP_BUF_REG               (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMRIGHT_COMP_CAP_BUF_PTR               ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMRIGHT_PERIOD_REG                     (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__PERIOD )
#define PWMRIGHT_PERIOD_PTR                     ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__PERIOD )
#define PWMRIGHT_PERIOD_BUF_REG                 (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMRIGHT_PERIOD_BUF_PTR                 ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMRIGHT_TRIG_CONTROL0_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMRIGHT_TRIG_CONTROL0_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMRIGHT_TRIG_CONTROL1_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMRIGHT_TRIG_CONTROL1_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMRIGHT_TRIG_CONTROL2_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMRIGHT_TRIG_CONTROL2_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMRIGHT_INTERRUPT_REQ_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR )
#define PWMRIGHT_INTERRUPT_REQ_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR )
#define PWMRIGHT_INTERRUPT_SET_REG              (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMRIGHT_INTERRUPT_SET_PTR              ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMRIGHT_INTERRUPT_MASK_REG             (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMRIGHT_INTERRUPT_MASK_PTR             ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMRIGHT_INTERRUPT_MASKED_REG           (*(reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWMRIGHT_INTERRUPT_MASKED_PTR           ( (reg32 *) PWMRIGHT_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWMRIGHT_MASK                           ((uint32)PWMRIGHT_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWMRIGHT_RELOAD_CC_SHIFT                (0u)
#define PWMRIGHT_RELOAD_PERIOD_SHIFT            (1u)
#define PWMRIGHT_PWM_SYNC_KILL_SHIFT            (2u)
#define PWMRIGHT_PWM_STOP_KILL_SHIFT            (3u)
#define PWMRIGHT_PRESCALER_SHIFT                (8u)
#define PWMRIGHT_UPDOWN_SHIFT                   (16u)
#define PWMRIGHT_ONESHOT_SHIFT                  (18u)
#define PWMRIGHT_QUAD_MODE_SHIFT                (20u)
#define PWMRIGHT_INV_OUT_SHIFT                  (20u)
#define PWMRIGHT_INV_COMPL_OUT_SHIFT            (21u)
#define PWMRIGHT_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWMRIGHT_RELOAD_CC_MASK                 ((uint32)(PWMRIGHT_1BIT_MASK        <<  \
                                                                            PWMRIGHT_RELOAD_CC_SHIFT))
#define PWMRIGHT_RELOAD_PERIOD_MASK             ((uint32)(PWMRIGHT_1BIT_MASK        <<  \
                                                                            PWMRIGHT_RELOAD_PERIOD_SHIFT))
#define PWMRIGHT_PWM_SYNC_KILL_MASK             ((uint32)(PWMRIGHT_1BIT_MASK        <<  \
                                                                            PWMRIGHT_PWM_SYNC_KILL_SHIFT))
#define PWMRIGHT_PWM_STOP_KILL_MASK             ((uint32)(PWMRIGHT_1BIT_MASK        <<  \
                                                                            PWMRIGHT_PWM_STOP_KILL_SHIFT))
#define PWMRIGHT_PRESCALER_MASK                 ((uint32)(PWMRIGHT_8BIT_MASK        <<  \
                                                                            PWMRIGHT_PRESCALER_SHIFT))
#define PWMRIGHT_UPDOWN_MASK                    ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                            PWMRIGHT_UPDOWN_SHIFT))
#define PWMRIGHT_ONESHOT_MASK                   ((uint32)(PWMRIGHT_1BIT_MASK        <<  \
                                                                            PWMRIGHT_ONESHOT_SHIFT))
#define PWMRIGHT_QUAD_MODE_MASK                 ((uint32)(PWMRIGHT_3BIT_MASK        <<  \
                                                                            PWMRIGHT_QUAD_MODE_SHIFT))
#define PWMRIGHT_INV_OUT_MASK                   ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                            PWMRIGHT_INV_OUT_SHIFT))
#define PWMRIGHT_MODE_MASK                      ((uint32)(PWMRIGHT_3BIT_MASK        <<  \
                                                                            PWMRIGHT_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWMRIGHT_CAPTURE_SHIFT                  (0u)
#define PWMRIGHT_COUNT_SHIFT                    (2u)
#define PWMRIGHT_RELOAD_SHIFT                   (4u)
#define PWMRIGHT_STOP_SHIFT                     (6u)
#define PWMRIGHT_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWMRIGHT_CAPTURE_MASK                   ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                  PWMRIGHT_CAPTURE_SHIFT))
#define PWMRIGHT_COUNT_MASK                     ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                  PWMRIGHT_COUNT_SHIFT))
#define PWMRIGHT_RELOAD_MASK                    ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                  PWMRIGHT_RELOAD_SHIFT))
#define PWMRIGHT_STOP_MASK                      ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                  PWMRIGHT_STOP_SHIFT))
#define PWMRIGHT_START_MASK                     ((uint32)(PWMRIGHT_2BIT_MASK        <<  \
                                                                  PWMRIGHT_START_SHIFT))

/* MASK */
#define PWMRIGHT_1BIT_MASK                      ((uint32)0x01u)
#define PWMRIGHT_2BIT_MASK                      ((uint32)0x03u)
#define PWMRIGHT_3BIT_MASK                      ((uint32)0x07u)
#define PWMRIGHT_6BIT_MASK                      ((uint32)0x3Fu)
#define PWMRIGHT_8BIT_MASK                      ((uint32)0xFFu)
#define PWMRIGHT_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWMRIGHT_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWMRIGHT_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWMRIGHT_QUAD_ENCODING_MODES     << PWMRIGHT_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWMRIGHT_CONFIG                  << PWMRIGHT_MODE_SHIFT)))

#define PWMRIGHT_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWMRIGHT_PWM_STOP_EVENT          << PWMRIGHT_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWMRIGHT_PWM_OUT_INVERT          << PWMRIGHT_INV_OUT_SHIFT))         |\
         ((uint32)(PWMRIGHT_PWM_OUT_N_INVERT        << PWMRIGHT_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWMRIGHT_PWM_MODE                << PWMRIGHT_MODE_SHIFT)))

#define PWMRIGHT_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWMRIGHT_PWM_RUN_MODE         << PWMRIGHT_ONESHOT_SHIFT))
            
#define PWMRIGHT_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWMRIGHT_PWM_ALIGN            << PWMRIGHT_UPDOWN_SHIFT))

#define PWMRIGHT_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWMRIGHT_PWM_KILL_EVENT      << PWMRIGHT_PWM_SYNC_KILL_SHIFT))

#define PWMRIGHT_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWMRIGHT_PWM_DEAD_TIME_CYCLE  << PWMRIGHT_PRESCALER_SHIFT))

#define PWMRIGHT_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWMRIGHT_PWM_PRESCALER        << PWMRIGHT_PRESCALER_SHIFT))

#define PWMRIGHT_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWMRIGHT_TC_PRESCALER            << PWMRIGHT_PRESCALER_SHIFT))       |\
         ((uint32)(PWMRIGHT_TC_COUNTER_MODE         << PWMRIGHT_UPDOWN_SHIFT))          |\
         ((uint32)(PWMRIGHT_TC_RUN_MODE             << PWMRIGHT_ONESHOT_SHIFT))         |\
         ((uint32)(PWMRIGHT_TC_COMP_CAP_MODE        << PWMRIGHT_MODE_SHIFT)))
        
#define PWMRIGHT_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWMRIGHT_QUAD_PHIA_SIGNAL_MODE   << PWMRIGHT_COUNT_SHIFT))           |\
         ((uint32)(PWMRIGHT_QUAD_INDEX_SIGNAL_MODE  << PWMRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(PWMRIGHT_QUAD_STOP_SIGNAL_MODE   << PWMRIGHT_STOP_SHIFT))            |\
         ((uint32)(PWMRIGHT_QUAD_PHIB_SIGNAL_MODE   << PWMRIGHT_START_SHIFT)))

#define PWMRIGHT_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWMRIGHT_PWM_SWITCH_SIGNAL_MODE  << PWMRIGHT_CAPTURE_SHIFT))         |\
         ((uint32)(PWMRIGHT_PWM_COUNT_SIGNAL_MODE   << PWMRIGHT_COUNT_SHIFT))           |\
         ((uint32)(PWMRIGHT_PWM_RELOAD_SIGNAL_MODE  << PWMRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(PWMRIGHT_PWM_STOP_SIGNAL_MODE    << PWMRIGHT_STOP_SHIFT))            |\
         ((uint32)(PWMRIGHT_PWM_START_SIGNAL_MODE   << PWMRIGHT_START_SHIFT)))

#define PWMRIGHT_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWMRIGHT_TC_CAPTURE_SIGNAL_MODE  << PWMRIGHT_CAPTURE_SHIFT))         |\
         ((uint32)(PWMRIGHT_TC_COUNT_SIGNAL_MODE    << PWMRIGHT_COUNT_SHIFT))           |\
         ((uint32)(PWMRIGHT_TC_RELOAD_SIGNAL_MODE   << PWMRIGHT_RELOAD_SHIFT))          |\
         ((uint32)(PWMRIGHT_TC_STOP_SIGNAL_MODE     << PWMRIGHT_STOP_SHIFT))            |\
         ((uint32)(PWMRIGHT_TC_START_SIGNAL_MODE    << PWMRIGHT_START_SHIFT)))
        
#define PWMRIGHT_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWMRIGHT__COUNT_UPDOWN0 == PWMRIGHT_TC_COUNTER_MODE)                  ||\
                 (PWMRIGHT__COUNT_UPDOWN1 == PWMRIGHT_TC_COUNTER_MODE))

#define PWMRIGHT_PWM_UPDOWN_CNT_USED                                                            \
                ((PWMRIGHT__CENTER == PWMRIGHT_PWM_ALIGN)                               ||\
                 (PWMRIGHT__ASYMMETRIC == PWMRIGHT_PWM_ALIGN))               
        
#define PWMRIGHT_PWM_PR_INIT_VALUE              (1u)
#define PWMRIGHT_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWMRIGHT_H */

/* [] END OF FILE */
