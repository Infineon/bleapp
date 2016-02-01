/*******************************************************************************
* File Name: ledpwm.h
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

#if !defined(CY_PWM_ledpwm_H)
#define CY_PWM_ledpwm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ledpwm_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ledpwm_Resolution                     (8u)
#define ledpwm_UsingFixedFunction             (0u)
#define ledpwm_DeadBandMode                   (0u)
#define ledpwm_KillModeMinTime                (0u)
#define ledpwm_KillMode                       (0u)
#define ledpwm_PWMMode                        (0u)
#define ledpwm_PWMModeIsCenterAligned         (0u)
#define ledpwm_DeadBandUsed                   (0u)
#define ledpwm_DeadBand2_4                    (0u)

#if !defined(ledpwm_PWMUDB_genblk8_stsreg__REMOVED)
    #define ledpwm_UseStatus                  (1u)
#else
    #define ledpwm_UseStatus                  (0u)
#endif /* !defined(ledpwm_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(ledpwm_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define ledpwm_UseControl                 (1u)
#else
    #define ledpwm_UseControl                 (0u)
#endif /* !defined(ledpwm_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define ledpwm_UseOneCompareMode              (1u)
#define ledpwm_MinimumKillTime                (1u)
#define ledpwm_EnableMode                     (0u)

#define ledpwm_CompareMode1SW                 (0u)
#define ledpwm_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ledpwm__B_PWM__DISABLED 0
#define ledpwm__B_PWM__ASYNCHRONOUS 1
#define ledpwm__B_PWM__SINGLECYCLE 2
#define ledpwm__B_PWM__LATCHED 3
#define ledpwm__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ledpwm__B_PWM__DBMDISABLED 0
#define ledpwm__B_PWM__DBM_2_4_CLOCKS 1
#define ledpwm__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ledpwm__B_PWM__ONE_OUTPUT 0
#define ledpwm__B_PWM__TWO_OUTPUTS 1
#define ledpwm__B_PWM__DUAL_EDGE 2
#define ledpwm__B_PWM__CENTER_ALIGN 3
#define ledpwm__B_PWM__DITHER 5
#define ledpwm__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ledpwm__B_PWM__LESS_THAN 1
#define ledpwm__B_PWM__LESS_THAN_OR_EQUAL 2
#define ledpwm__B_PWM__GREATER_THAN 3
#define ledpwm__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ledpwm__B_PWM__EQUAL 0
#define ledpwm__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!ledpwm_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!ledpwm_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!ledpwm_PWMModeIsCenterAligned) */
        #if (ledpwm_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (ledpwm_UseStatus) */

        /* Backup for Deadband parameters */
        #if(ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_256_CLOCKS || \
            ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(ledpwm_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (ledpwm_KillModeMinTime) */

        /* Backup control register */
        #if(ledpwm_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (ledpwm_UseControl) */

    #endif /* (!ledpwm_UsingFixedFunction) */

}ledpwm_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    ledpwm_Start(void) ;
void    ledpwm_Stop(void) ;

#if (ledpwm_UseStatus || ledpwm_UsingFixedFunction)
    void  ledpwm_SetInterruptMode(uint8 interruptMode) ;
    uint8 ledpwm_ReadStatusRegister(void) ;
#endif /* (ledpwm_UseStatus || ledpwm_UsingFixedFunction) */

#define ledpwm_GetInterruptSource() ledpwm_ReadStatusRegister()

#if (ledpwm_UseControl)
    uint8 ledpwm_ReadControlRegister(void) ;
    void  ledpwm_WriteControlRegister(uint8 control)
          ;
#endif /* (ledpwm_UseControl) */

#if (ledpwm_UseOneCompareMode)
   #if (ledpwm_CompareMode1SW)
       void    ledpwm_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (ledpwm_CompareMode1SW) */
#else
    #if (ledpwm_CompareMode1SW)
        void    ledpwm_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (ledpwm_CompareMode1SW) */
    #if (ledpwm_CompareMode2SW)
        void    ledpwm_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (ledpwm_CompareMode2SW) */
#endif /* (ledpwm_UseOneCompareMode) */

#if (!ledpwm_UsingFixedFunction)
    uint8   ledpwm_ReadCounter(void) ;
    uint8 ledpwm_ReadCapture(void) ;

    #if (ledpwm_UseStatus)
            void ledpwm_ClearFIFO(void) ;
    #endif /* (ledpwm_UseStatus) */

    void    ledpwm_WriteCounter(uint8 counter)
            ;
#endif /* (!ledpwm_UsingFixedFunction) */

void    ledpwm_WritePeriod(uint8 period)
        ;
uint8 ledpwm_ReadPeriod(void) ;

#if (ledpwm_UseOneCompareMode)
    void    ledpwm_WriteCompare(uint8 compare)
            ;
    uint8 ledpwm_ReadCompare(void) ;
#else
    void    ledpwm_WriteCompare1(uint8 compare)
            ;
    uint8 ledpwm_ReadCompare1(void) ;
    void    ledpwm_WriteCompare2(uint8 compare)
            ;
    uint8 ledpwm_ReadCompare2(void) ;
#endif /* (ledpwm_UseOneCompareMode) */


#if (ledpwm_DeadBandUsed)
    void    ledpwm_WriteDeadTime(uint8 deadtime) ;
    uint8   ledpwm_ReadDeadTime(void) ;
#endif /* (ledpwm_DeadBandUsed) */

#if ( ledpwm_KillModeMinTime)
    void ledpwm_WriteKillTime(uint8 killtime) ;
    uint8 ledpwm_ReadKillTime(void) ;
#endif /* ( ledpwm_KillModeMinTime) */

void ledpwm_Init(void) ;
void ledpwm_Enable(void) ;
void ledpwm_Sleep(void) ;
void ledpwm_Wakeup(void) ;
void ledpwm_SaveConfig(void) ;
void ledpwm_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ledpwm_INIT_PERIOD_VALUE          (255u)
#define ledpwm_INIT_COMPARE_VALUE1        (127u)
#define ledpwm_INIT_COMPARE_VALUE2        (63u)
#define ledpwm_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    ledpwm_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ledpwm_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ledpwm_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ledpwm_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define ledpwm_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  ledpwm_CTRL_CMPMODE2_SHIFT)
#define ledpwm_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  ledpwm_CTRL_CMPMODE1_SHIFT)
#define ledpwm_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (ledpwm_UsingFixedFunction)
   #define ledpwm_PERIOD_LSB              (*(reg16 *) ledpwm_PWMHW__PER0)
   #define ledpwm_PERIOD_LSB_PTR          ( (reg16 *) ledpwm_PWMHW__PER0)
   #define ledpwm_COMPARE1_LSB            (*(reg16 *) ledpwm_PWMHW__CNT_CMP0)
   #define ledpwm_COMPARE1_LSB_PTR        ( (reg16 *) ledpwm_PWMHW__CNT_CMP0)
   #define ledpwm_COMPARE2_LSB            (0x00u)
   #define ledpwm_COMPARE2_LSB_PTR        (0x00u)
   #define ledpwm_COUNTER_LSB             (*(reg16 *) ledpwm_PWMHW__CNT_CMP0)
   #define ledpwm_COUNTER_LSB_PTR         ( (reg16 *) ledpwm_PWMHW__CNT_CMP0)
   #define ledpwm_CAPTURE_LSB             (*(reg16 *) ledpwm_PWMHW__CAP0)
   #define ledpwm_CAPTURE_LSB_PTR         ( (reg16 *) ledpwm_PWMHW__CAP0)
   #define ledpwm_RT1                     (*(reg8 *)  ledpwm_PWMHW__RT1)
   #define ledpwm_RT1_PTR                 ( (reg8 *)  ledpwm_PWMHW__RT1)

#else
   #if (ledpwm_Resolution == 8u) /* 8bit - PWM */

       #if(ledpwm_PWMModeIsCenterAligned)
           #define ledpwm_PERIOD_LSB      (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define ledpwm_PERIOD_LSB_PTR  ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define ledpwm_PERIOD_LSB      (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define ledpwm_PERIOD_LSB_PTR  ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (ledpwm_PWMModeIsCenterAligned) */

       #define ledpwm_COMPARE1_LSB        (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define ledpwm_COMPARE1_LSB_PTR    ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define ledpwm_COMPARE2_LSB        (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define ledpwm_COMPARE2_LSB_PTR    ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define ledpwm_COUNTERCAP_LSB      (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define ledpwm_COUNTERCAP_LSB_PTR  ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define ledpwm_COUNTER_LSB         (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define ledpwm_COUNTER_LSB_PTR     ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define ledpwm_CAPTURE_LSB         (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define ledpwm_CAPTURE_LSB_PTR     ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(ledpwm_PWMModeIsCenterAligned)
               #define ledpwm_PERIOD_LSB      (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define ledpwm_PERIOD_LSB_PTR  ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define ledpwm_PERIOD_LSB      (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define ledpwm_PERIOD_LSB_PTR  ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (ledpwm_PWMModeIsCenterAligned) */

            #define ledpwm_COMPARE1_LSB       (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define ledpwm_COMPARE1_LSB_PTR   ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define ledpwm_COMPARE2_LSB       (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define ledpwm_COMPARE2_LSB_PTR   ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define ledpwm_COUNTERCAP_LSB     (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define ledpwm_COUNTERCAP_LSB_PTR ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define ledpwm_COUNTER_LSB        (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define ledpwm_COUNTER_LSB_PTR    ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define ledpwm_CAPTURE_LSB        (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define ledpwm_CAPTURE_LSB_PTR    ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(ledpwm_PWMModeIsCenterAligned)
               #define ledpwm_PERIOD_LSB      (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define ledpwm_PERIOD_LSB_PTR  ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define ledpwm_PERIOD_LSB      (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define ledpwm_PERIOD_LSB_PTR  ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (ledpwm_PWMModeIsCenterAligned) */

            #define ledpwm_COMPARE1_LSB       (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define ledpwm_COMPARE1_LSB_PTR   ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define ledpwm_COMPARE2_LSB       (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define ledpwm_COMPARE2_LSB_PTR   ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define ledpwm_COUNTERCAP_LSB     (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define ledpwm_COUNTERCAP_LSB_PTR ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define ledpwm_COUNTER_LSB        (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define ledpwm_COUNTER_LSB_PTR    ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define ledpwm_CAPTURE_LSB        (*(reg16 *) ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define ledpwm_CAPTURE_LSB_PTR    ((reg16 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define ledpwm_AUX_CONTROLDP1          (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define ledpwm_AUX_CONTROLDP1_PTR      ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (ledpwm_Resolution == 8) */

   #define ledpwm_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define ledpwm_AUX_CONTROLDP0          (*(reg8 *)  ledpwm_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define ledpwm_AUX_CONTROLDP0_PTR      ((reg8 *)   ledpwm_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (ledpwm_UsingFixedFunction) */

#if(ledpwm_KillModeMinTime )
    #define ledpwm_KILLMODEMINTIME        (*(reg8 *)  ledpwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ledpwm_KILLMODEMINTIME_PTR    ((reg8 *)   ledpwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (ledpwm_KillModeMinTime ) */

#if(ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_256_CLOCKS)
    #define ledpwm_DEADBAND_COUNT         (*(reg8 *)  ledpwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ledpwm_DEADBAND_COUNT_PTR     ((reg8 *)   ledpwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ledpwm_DEADBAND_LSB_PTR       ((reg8 *)   ledpwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ledpwm_DEADBAND_LSB           (*(reg8 *)  ledpwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (ledpwm_UsingFixedFunction)
        #define ledpwm_DEADBAND_COUNT         (*(reg8 *)  ledpwm_PWMHW__CFG0)
        #define ledpwm_DEADBAND_COUNT_PTR     ((reg8 *)   ledpwm_PWMHW__CFG0)
        #define ledpwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ledpwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ledpwm_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ledpwm_DEADBAND_COUNT         (*(reg8 *)  ledpwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ledpwm_DEADBAND_COUNT_PTR     ((reg8 *)   ledpwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ledpwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ledpwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define ledpwm_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (ledpwm_UsingFixedFunction) */
#endif /* (ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_256_CLOCKS) */



#if (ledpwm_UsingFixedFunction)
    #define ledpwm_STATUS                 (*(reg8 *) ledpwm_PWMHW__SR0)
    #define ledpwm_STATUS_PTR             ((reg8 *) ledpwm_PWMHW__SR0)
    #define ledpwm_STATUS_MASK            (*(reg8 *) ledpwm_PWMHW__SR0)
    #define ledpwm_STATUS_MASK_PTR        ((reg8 *) ledpwm_PWMHW__SR0)
    #define ledpwm_CONTROL                (*(reg8 *) ledpwm_PWMHW__CFG0)
    #define ledpwm_CONTROL_PTR            ((reg8 *) ledpwm_PWMHW__CFG0)
    #define ledpwm_CONTROL2               (*(reg8 *) ledpwm_PWMHW__CFG1)
    #define ledpwm_CONTROL3               (*(reg8 *) ledpwm_PWMHW__CFG2)
    #define ledpwm_GLOBAL_ENABLE          (*(reg8 *) ledpwm_PWMHW__PM_ACT_CFG)
    #define ledpwm_GLOBAL_ENABLE_PTR      ( (reg8 *) ledpwm_PWMHW__PM_ACT_CFG)
    #define ledpwm_GLOBAL_STBY_ENABLE     (*(reg8 *) ledpwm_PWMHW__PM_STBY_CFG)
    #define ledpwm_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) ledpwm_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ledpwm_BLOCK_EN_MASK          (ledpwm_PWMHW__PM_ACT_MSK)
    #define ledpwm_BLOCK_STBY_EN_MASK     (ledpwm_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define ledpwm_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define ledpwm_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define ledpwm_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define ledpwm_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define ledpwm_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define ledpwm_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define ledpwm_CTRL_ENABLE            (uint8)((uint8)0x01u << ledpwm_CTRL_ENABLE_SHIFT)
    #define ledpwm_CTRL_RESET             (uint8)((uint8)0x01u << ledpwm_CTRL_RESET_SHIFT)
    #define ledpwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ledpwm_CTRL_CMPMODE2_SHIFT)
    #define ledpwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ledpwm_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ledpwm_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define ledpwm_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << ledpwm_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define ledpwm_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define ledpwm_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define ledpwm_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define ledpwm_STATUS_TC_INT_EN_MASK_SHIFT            (ledpwm_STATUS_TC_SHIFT - 4u)
    #define ledpwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define ledpwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (ledpwm_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define ledpwm_STATUS_TC              (uint8)((uint8)0x01u << ledpwm_STATUS_TC_SHIFT)
    #define ledpwm_STATUS_CMP1            (uint8)((uint8)0x01u << ledpwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define ledpwm_STATUS_TC_INT_EN_MASK              (uint8)((uint8)ledpwm_STATUS_TC >> 4u)
    #define ledpwm_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)ledpwm_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define ledpwm_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define ledpwm_RT1_MASK              (uint8)((uint8)0x03u << ledpwm_RT1_SHIFT)
    #define ledpwm_SYNC                  (uint8)((uint8)0x03u << ledpwm_RT1_SHIFT)
    #define ledpwm_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define ledpwm_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << ledpwm_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define ledpwm_SYNCDSI_EN            (uint8)((uint8)0x0Fu << ledpwm_SYNCDSI_SHIFT)


#else
    #define ledpwm_STATUS                (*(reg8 *)   ledpwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ledpwm_STATUS_PTR            ((reg8 *)    ledpwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ledpwm_STATUS_MASK           (*(reg8 *)   ledpwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ledpwm_STATUS_MASK_PTR       ((reg8 *)    ledpwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ledpwm_STATUS_AUX_CTRL       (*(reg8 *)   ledpwm_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define ledpwm_CONTROL               (*(reg8 *)   ledpwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define ledpwm_CONTROL_PTR           ((reg8 *)    ledpwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define ledpwm_CTRL_ENABLE_SHIFT      (0x07u)
    #define ledpwm_CTRL_RESET_SHIFT       (0x06u)
    #define ledpwm_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define ledpwm_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define ledpwm_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define ledpwm_CTRL_ENABLE            (uint8)((uint8)0x01u << ledpwm_CTRL_ENABLE_SHIFT)
    #define ledpwm_CTRL_RESET             (uint8)((uint8)0x01u << ledpwm_CTRL_RESET_SHIFT)
    #define ledpwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ledpwm_CTRL_CMPMODE2_SHIFT)
    #define ledpwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ledpwm_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define ledpwm_STATUS_KILL_SHIFT          (0x05u)
    #define ledpwm_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define ledpwm_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define ledpwm_STATUS_TC_SHIFT            (0x02u)
    #define ledpwm_STATUS_CMP2_SHIFT          (0x01u)
    #define ledpwm_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ledpwm_STATUS_KILL_INT_EN_MASK_SHIFT          (ledpwm_STATUS_KILL_SHIFT)
    #define ledpwm_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (ledpwm_STATUS_FIFONEMPTY_SHIFT)
    #define ledpwm_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (ledpwm_STATUS_FIFOFULL_SHIFT)
    #define ledpwm_STATUS_TC_INT_EN_MASK_SHIFT            (ledpwm_STATUS_TC_SHIFT)
    #define ledpwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (ledpwm_STATUS_CMP2_SHIFT)
    #define ledpwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (ledpwm_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define ledpwm_STATUS_KILL            (uint8)((uint8)0x00u << ledpwm_STATUS_KILL_SHIFT )
    #define ledpwm_STATUS_FIFOFULL        (uint8)((uint8)0x01u << ledpwm_STATUS_FIFOFULL_SHIFT)
    #define ledpwm_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << ledpwm_STATUS_FIFONEMPTY_SHIFT)
    #define ledpwm_STATUS_TC              (uint8)((uint8)0x01u << ledpwm_STATUS_TC_SHIFT)
    #define ledpwm_STATUS_CMP2            (uint8)((uint8)0x01u << ledpwm_STATUS_CMP2_SHIFT)
    #define ledpwm_STATUS_CMP1            (uint8)((uint8)0x01u << ledpwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ledpwm_STATUS_KILL_INT_EN_MASK            (ledpwm_STATUS_KILL)
    #define ledpwm_STATUS_FIFOFULL_INT_EN_MASK        (ledpwm_STATUS_FIFOFULL)
    #define ledpwm_STATUS_FIFONEMPTY_INT_EN_MASK      (ledpwm_STATUS_FIFONEMPTY)
    #define ledpwm_STATUS_TC_INT_EN_MASK              (ledpwm_STATUS_TC)
    #define ledpwm_STATUS_CMP2_INT_EN_MASK            (ledpwm_STATUS_CMP2)
    #define ledpwm_STATUS_CMP1_INT_EN_MASK            (ledpwm_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define ledpwm_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define ledpwm_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define ledpwm_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define ledpwm_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define ledpwm_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* ledpwm_UsingFixedFunction */

#endif  /* CY_PWM_ledpwm_H */


/* [] END OF FILE */
