/*******************************************************************************
* File Name: tachPwm.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_tachPwm_H)
#define CY_PWM_tachPwm_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 tachPwm_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define tachPwm_Resolution                     (8u)
#define tachPwm_UsingFixedFunction             (0u)
#define tachPwm_DeadBandMode                   (0u)
#define tachPwm_KillModeMinTime                (0u)
#define tachPwm_KillMode                       (0u)
#define tachPwm_PWMMode                        (0u)
#define tachPwm_PWMModeIsCenterAligned         (0u)
#define tachPwm_DeadBandUsed                   (0u)
#define tachPwm_DeadBand2_4                    (0u)

#if !defined(tachPwm_PWMUDB_genblk8_stsreg__REMOVED)
    #define tachPwm_UseStatus                  (1u)
#else
    #define tachPwm_UseStatus                  (0u)
#endif /* !defined(tachPwm_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(tachPwm_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define tachPwm_UseControl                 (1u)
#else
    #define tachPwm_UseControl                 (0u)
#endif /* !defined(tachPwm_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define tachPwm_UseOneCompareMode              (1u)
#define tachPwm_MinimumKillTime                (1u)
#define tachPwm_EnableMode                     (0u)

#define tachPwm_CompareMode1SW                 (0u)
#define tachPwm_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define tachPwm__B_PWM__DISABLED 0
#define tachPwm__B_PWM__ASYNCHRONOUS 1
#define tachPwm__B_PWM__SINGLECYCLE 2
#define tachPwm__B_PWM__LATCHED 3
#define tachPwm__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define tachPwm__B_PWM__DBMDISABLED 0
#define tachPwm__B_PWM__DBM_2_4_CLOCKS 1
#define tachPwm__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define tachPwm__B_PWM__ONE_OUTPUT 0
#define tachPwm__B_PWM__TWO_OUTPUTS 1
#define tachPwm__B_PWM__DUAL_EDGE 2
#define tachPwm__B_PWM__CENTER_ALIGN 3
#define tachPwm__B_PWM__DITHER 5
#define tachPwm__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define tachPwm__B_PWM__LESS_THAN 1
#define tachPwm__B_PWM__LESS_THAN_OR_EQUAL 2
#define tachPwm__B_PWM__GREATER_THAN 3
#define tachPwm__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define tachPwm__B_PWM__EQUAL 0
#define tachPwm__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!tachPwm_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!tachPwm_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!tachPwm_PWMModeIsCenterAligned) */
        #if (tachPwm_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (tachPwm_UseStatus) */

        /* Backup for Deadband parameters */
        #if(tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_256_CLOCKS || \
            tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(tachPwm_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (tachPwm_KillModeMinTime) */

        /* Backup control register */
        #if(tachPwm_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (tachPwm_UseControl) */

    #endif /* (!tachPwm_UsingFixedFunction) */

}tachPwm_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    tachPwm_Start(void) ;
void    tachPwm_Stop(void) ;

#if (tachPwm_UseStatus || tachPwm_UsingFixedFunction)
    void  tachPwm_SetInterruptMode(uint8 interruptMode) ;
    uint8 tachPwm_ReadStatusRegister(void) ;
#endif /* (tachPwm_UseStatus || tachPwm_UsingFixedFunction) */

#define tachPwm_GetInterruptSource() tachPwm_ReadStatusRegister()

#if (tachPwm_UseControl)
    uint8 tachPwm_ReadControlRegister(void) ;
    void  tachPwm_WriteControlRegister(uint8 control)
          ;
#endif /* (tachPwm_UseControl) */

#if (tachPwm_UseOneCompareMode)
   #if (tachPwm_CompareMode1SW)
       void    tachPwm_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (tachPwm_CompareMode1SW) */
#else
    #if (tachPwm_CompareMode1SW)
        void    tachPwm_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (tachPwm_CompareMode1SW) */
    #if (tachPwm_CompareMode2SW)
        void    tachPwm_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (tachPwm_CompareMode2SW) */
#endif /* (tachPwm_UseOneCompareMode) */

#if (!tachPwm_UsingFixedFunction)
    uint8   tachPwm_ReadCounter(void) ;
    uint8 tachPwm_ReadCapture(void) ;

    #if (tachPwm_UseStatus)
            void tachPwm_ClearFIFO(void) ;
    #endif /* (tachPwm_UseStatus) */

    void    tachPwm_WriteCounter(uint8 counter)
            ;
#endif /* (!tachPwm_UsingFixedFunction) */

void    tachPwm_WritePeriod(uint8 period)
        ;
uint8 tachPwm_ReadPeriod(void) ;

#if (tachPwm_UseOneCompareMode)
    void    tachPwm_WriteCompare(uint8 compare)
            ;
    uint8 tachPwm_ReadCompare(void) ;
#else
    void    tachPwm_WriteCompare1(uint8 compare)
            ;
    uint8 tachPwm_ReadCompare1(void) ;
    void    tachPwm_WriteCompare2(uint8 compare)
            ;
    uint8 tachPwm_ReadCompare2(void) ;
#endif /* (tachPwm_UseOneCompareMode) */


#if (tachPwm_DeadBandUsed)
    void    tachPwm_WriteDeadTime(uint8 deadtime) ;
    uint8   tachPwm_ReadDeadTime(void) ;
#endif /* (tachPwm_DeadBandUsed) */

#if ( tachPwm_KillModeMinTime)
    void tachPwm_WriteKillTime(uint8 killtime) ;
    uint8 tachPwm_ReadKillTime(void) ;
#endif /* ( tachPwm_KillModeMinTime) */

void tachPwm_Init(void) ;
void tachPwm_Enable(void) ;
void tachPwm_Sleep(void) ;
void tachPwm_Wakeup(void) ;
void tachPwm_SaveConfig(void) ;
void tachPwm_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define tachPwm_INIT_PERIOD_VALUE          (199u)
#define tachPwm_INIT_COMPARE_VALUE1        (100u)
#define tachPwm_INIT_COMPARE_VALUE2        (63u)
#define tachPwm_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(1u <<   \
                                                    tachPwm_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    tachPwm_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    tachPwm_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    tachPwm_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define tachPwm_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  tachPwm_CTRL_CMPMODE2_SHIFT)
#define tachPwm_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  tachPwm_CTRL_CMPMODE1_SHIFT)
#define tachPwm_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (tachPwm_UsingFixedFunction)
   #define tachPwm_PERIOD_LSB              (*(reg16 *) tachPwm_PWMHW__PER0)
   #define tachPwm_PERIOD_LSB_PTR          ( (reg16 *) tachPwm_PWMHW__PER0)
   #define tachPwm_COMPARE1_LSB            (*(reg16 *) tachPwm_PWMHW__CNT_CMP0)
   #define tachPwm_COMPARE1_LSB_PTR        ( (reg16 *) tachPwm_PWMHW__CNT_CMP0)
   #define tachPwm_COMPARE2_LSB            (0x00u)
   #define tachPwm_COMPARE2_LSB_PTR        (0x00u)
   #define tachPwm_COUNTER_LSB             (*(reg16 *) tachPwm_PWMHW__CNT_CMP0)
   #define tachPwm_COUNTER_LSB_PTR         ( (reg16 *) tachPwm_PWMHW__CNT_CMP0)
   #define tachPwm_CAPTURE_LSB             (*(reg16 *) tachPwm_PWMHW__CAP0)
   #define tachPwm_CAPTURE_LSB_PTR         ( (reg16 *) tachPwm_PWMHW__CAP0)
   #define tachPwm_RT1                     (*(reg8 *)  tachPwm_PWMHW__RT1)
   #define tachPwm_RT1_PTR                 ( (reg8 *)  tachPwm_PWMHW__RT1)

#else
   #if (tachPwm_Resolution == 8u) /* 8bit - PWM */

       #if(tachPwm_PWMModeIsCenterAligned)
           #define tachPwm_PERIOD_LSB      (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define tachPwm_PERIOD_LSB_PTR  ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define tachPwm_PERIOD_LSB      (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define tachPwm_PERIOD_LSB_PTR  ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (tachPwm_PWMModeIsCenterAligned) */

       #define tachPwm_COMPARE1_LSB        (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define tachPwm_COMPARE1_LSB_PTR    ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define tachPwm_COMPARE2_LSB        (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define tachPwm_COMPARE2_LSB_PTR    ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define tachPwm_COUNTERCAP_LSB      (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define tachPwm_COUNTERCAP_LSB_PTR  ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define tachPwm_COUNTER_LSB         (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define tachPwm_COUNTER_LSB_PTR     ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define tachPwm_CAPTURE_LSB         (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define tachPwm_CAPTURE_LSB_PTR     ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(tachPwm_PWMModeIsCenterAligned)
               #define tachPwm_PERIOD_LSB      (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define tachPwm_PERIOD_LSB_PTR  ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define tachPwm_PERIOD_LSB      (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define tachPwm_PERIOD_LSB_PTR  ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (tachPwm_PWMModeIsCenterAligned) */

            #define tachPwm_COMPARE1_LSB       (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define tachPwm_COMPARE1_LSB_PTR   ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define tachPwm_COMPARE2_LSB       (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define tachPwm_COMPARE2_LSB_PTR   ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define tachPwm_COUNTERCAP_LSB     (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define tachPwm_COUNTERCAP_LSB_PTR ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define tachPwm_COUNTER_LSB        (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define tachPwm_COUNTER_LSB_PTR    ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define tachPwm_CAPTURE_LSB        (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define tachPwm_CAPTURE_LSB_PTR    ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(tachPwm_PWMModeIsCenterAligned)
               #define tachPwm_PERIOD_LSB      (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define tachPwm_PERIOD_LSB_PTR  ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define tachPwm_PERIOD_LSB      (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define tachPwm_PERIOD_LSB_PTR  ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (tachPwm_PWMModeIsCenterAligned) */

            #define tachPwm_COMPARE1_LSB       (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define tachPwm_COMPARE1_LSB_PTR   ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define tachPwm_COMPARE2_LSB       (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define tachPwm_COMPARE2_LSB_PTR   ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define tachPwm_COUNTERCAP_LSB     (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define tachPwm_COUNTERCAP_LSB_PTR ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define tachPwm_COUNTER_LSB        (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define tachPwm_COUNTER_LSB_PTR    ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define tachPwm_CAPTURE_LSB        (*(reg16 *) tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define tachPwm_CAPTURE_LSB_PTR    ((reg16 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define tachPwm_AUX_CONTROLDP1          (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define tachPwm_AUX_CONTROLDP1_PTR      ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (tachPwm_Resolution == 8) */

   #define tachPwm_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define tachPwm_AUX_CONTROLDP0          (*(reg8 *)  tachPwm_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define tachPwm_AUX_CONTROLDP0_PTR      ((reg8 *)   tachPwm_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (tachPwm_UsingFixedFunction) */

#if(tachPwm_KillModeMinTime )
    #define tachPwm_KILLMODEMINTIME        (*(reg8 *)  tachPwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define tachPwm_KILLMODEMINTIME_PTR    ((reg8 *)   tachPwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (tachPwm_KillModeMinTime ) */

#if(tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_256_CLOCKS)
    #define tachPwm_DEADBAND_COUNT         (*(reg8 *)  tachPwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define tachPwm_DEADBAND_COUNT_PTR     ((reg8 *)   tachPwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define tachPwm_DEADBAND_LSB_PTR       ((reg8 *)   tachPwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define tachPwm_DEADBAND_LSB           (*(reg8 *)  tachPwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (tachPwm_UsingFixedFunction)
        #define tachPwm_DEADBAND_COUNT         (*(reg8 *)  tachPwm_PWMHW__CFG0)
        #define tachPwm_DEADBAND_COUNT_PTR     ((reg8 *)   tachPwm_PWMHW__CFG0)
        #define tachPwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << tachPwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define tachPwm_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define tachPwm_DEADBAND_COUNT         (*(reg8 *)  tachPwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define tachPwm_DEADBAND_COUNT_PTR     ((reg8 *)   tachPwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define tachPwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << tachPwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define tachPwm_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (tachPwm_UsingFixedFunction) */
#endif /* (tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_256_CLOCKS) */



#if (tachPwm_UsingFixedFunction)
    #define tachPwm_STATUS                 (*(reg8 *) tachPwm_PWMHW__SR0)
    #define tachPwm_STATUS_PTR             ((reg8 *) tachPwm_PWMHW__SR0)
    #define tachPwm_STATUS_MASK            (*(reg8 *) tachPwm_PWMHW__SR0)
    #define tachPwm_STATUS_MASK_PTR        ((reg8 *) tachPwm_PWMHW__SR0)
    #define tachPwm_CONTROL                (*(reg8 *) tachPwm_PWMHW__CFG0)
    #define tachPwm_CONTROL_PTR            ((reg8 *) tachPwm_PWMHW__CFG0)
    #define tachPwm_CONTROL2               (*(reg8 *) tachPwm_PWMHW__CFG1)
    #define tachPwm_CONTROL3               (*(reg8 *) tachPwm_PWMHW__CFG2)
    #define tachPwm_GLOBAL_ENABLE          (*(reg8 *) tachPwm_PWMHW__PM_ACT_CFG)
    #define tachPwm_GLOBAL_ENABLE_PTR      ( (reg8 *) tachPwm_PWMHW__PM_ACT_CFG)
    #define tachPwm_GLOBAL_STBY_ENABLE     (*(reg8 *) tachPwm_PWMHW__PM_STBY_CFG)
    #define tachPwm_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) tachPwm_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define tachPwm_BLOCK_EN_MASK          (tachPwm_PWMHW__PM_ACT_MSK)
    #define tachPwm_BLOCK_STBY_EN_MASK     (tachPwm_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define tachPwm_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define tachPwm_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define tachPwm_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define tachPwm_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define tachPwm_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define tachPwm_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define tachPwm_CTRL_ENABLE            (uint8)((uint8)0x01u << tachPwm_CTRL_ENABLE_SHIFT)
    #define tachPwm_CTRL_RESET             (uint8)((uint8)0x01u << tachPwm_CTRL_RESET_SHIFT)
    #define tachPwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << tachPwm_CTRL_CMPMODE2_SHIFT)
    #define tachPwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << tachPwm_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define tachPwm_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define tachPwm_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << tachPwm_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define tachPwm_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define tachPwm_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define tachPwm_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define tachPwm_STATUS_TC_INT_EN_MASK_SHIFT            (tachPwm_STATUS_TC_SHIFT - 4u)
    #define tachPwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define tachPwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (tachPwm_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define tachPwm_STATUS_TC              (uint8)((uint8)0x01u << tachPwm_STATUS_TC_SHIFT)
    #define tachPwm_STATUS_CMP1            (uint8)((uint8)0x01u << tachPwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define tachPwm_STATUS_TC_INT_EN_MASK              (uint8)((uint8)tachPwm_STATUS_TC >> 4u)
    #define tachPwm_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)tachPwm_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define tachPwm_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define tachPwm_RT1_MASK              (uint8)((uint8)0x03u << tachPwm_RT1_SHIFT)
    #define tachPwm_SYNC                  (uint8)((uint8)0x03u << tachPwm_RT1_SHIFT)
    #define tachPwm_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define tachPwm_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << tachPwm_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define tachPwm_SYNCDSI_EN            (uint8)((uint8)0x0Fu << tachPwm_SYNCDSI_SHIFT)


#else
    #define tachPwm_STATUS                (*(reg8 *)   tachPwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define tachPwm_STATUS_PTR            ((reg8 *)    tachPwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define tachPwm_STATUS_MASK           (*(reg8 *)   tachPwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define tachPwm_STATUS_MASK_PTR       ((reg8 *)    tachPwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define tachPwm_STATUS_AUX_CTRL       (*(reg8 *)   tachPwm_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define tachPwm_CONTROL               (*(reg8 *)   tachPwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define tachPwm_CONTROL_PTR           ((reg8 *)    tachPwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define tachPwm_CTRL_ENABLE_SHIFT      (0x07u)
    #define tachPwm_CTRL_RESET_SHIFT       (0x06u)
    #define tachPwm_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define tachPwm_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define tachPwm_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define tachPwm_CTRL_ENABLE            (uint8)((uint8)0x01u << tachPwm_CTRL_ENABLE_SHIFT)
    #define tachPwm_CTRL_RESET             (uint8)((uint8)0x01u << tachPwm_CTRL_RESET_SHIFT)
    #define tachPwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << tachPwm_CTRL_CMPMODE2_SHIFT)
    #define tachPwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << tachPwm_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define tachPwm_STATUS_KILL_SHIFT          (0x05u)
    #define tachPwm_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define tachPwm_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define tachPwm_STATUS_TC_SHIFT            (0x02u)
    #define tachPwm_STATUS_CMP2_SHIFT          (0x01u)
    #define tachPwm_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define tachPwm_STATUS_KILL_INT_EN_MASK_SHIFT          (tachPwm_STATUS_KILL_SHIFT)
    #define tachPwm_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (tachPwm_STATUS_FIFONEMPTY_SHIFT)
    #define tachPwm_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (tachPwm_STATUS_FIFOFULL_SHIFT)
    #define tachPwm_STATUS_TC_INT_EN_MASK_SHIFT            (tachPwm_STATUS_TC_SHIFT)
    #define tachPwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (tachPwm_STATUS_CMP2_SHIFT)
    #define tachPwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (tachPwm_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define tachPwm_STATUS_KILL            (uint8)((uint8)0x00u << tachPwm_STATUS_KILL_SHIFT )
    #define tachPwm_STATUS_FIFOFULL        (uint8)((uint8)0x01u << tachPwm_STATUS_FIFOFULL_SHIFT)
    #define tachPwm_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << tachPwm_STATUS_FIFONEMPTY_SHIFT)
    #define tachPwm_STATUS_TC              (uint8)((uint8)0x01u << tachPwm_STATUS_TC_SHIFT)
    #define tachPwm_STATUS_CMP2            (uint8)((uint8)0x01u << tachPwm_STATUS_CMP2_SHIFT)
    #define tachPwm_STATUS_CMP1            (uint8)((uint8)0x01u << tachPwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define tachPwm_STATUS_KILL_INT_EN_MASK            (tachPwm_STATUS_KILL)
    #define tachPwm_STATUS_FIFOFULL_INT_EN_MASK        (tachPwm_STATUS_FIFOFULL)
    #define tachPwm_STATUS_FIFONEMPTY_INT_EN_MASK      (tachPwm_STATUS_FIFONEMPTY)
    #define tachPwm_STATUS_TC_INT_EN_MASK              (tachPwm_STATUS_TC)
    #define tachPwm_STATUS_CMP2_INT_EN_MASK            (tachPwm_STATUS_CMP2)
    #define tachPwm_STATUS_CMP1_INT_EN_MASK            (tachPwm_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define tachPwm_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define tachPwm_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define tachPwm_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define tachPwm_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define tachPwm_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* tachPwm_UsingFixedFunction */

#endif  /* CY_PWM_tachPwm_H */


/* [] END OF FILE */
