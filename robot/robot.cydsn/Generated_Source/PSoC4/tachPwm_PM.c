/*******************************************************************************
* File Name: tachPwm_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "tachPwm.h"

static tachPwm_backupStruct tachPwm_backup;


/*******************************************************************************
* Function Name: tachPwm_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  tachPwm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void tachPwm_SaveConfig(void) 
{

    #if(!tachPwm_UsingFixedFunction)
        #if(!tachPwm_PWMModeIsCenterAligned)
            tachPwm_backup.PWMPeriod = tachPwm_ReadPeriod();
        #endif /* (!tachPwm_PWMModeIsCenterAligned) */
        tachPwm_backup.PWMUdb = tachPwm_ReadCounter();
        #if (tachPwm_UseStatus)
            tachPwm_backup.InterruptMaskValue = tachPwm_STATUS_MASK;
        #endif /* (tachPwm_UseStatus) */

        #if(tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_256_CLOCKS || \
            tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_2_4_CLOCKS)
            tachPwm_backup.PWMdeadBandValue = tachPwm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(tachPwm_KillModeMinTime)
             tachPwm_backup.PWMKillCounterPeriod = tachPwm_ReadKillTime();
        #endif /* (tachPwm_KillModeMinTime) */

        #if(tachPwm_UseControl)
            tachPwm_backup.PWMControlRegister = tachPwm_ReadControlRegister();
        #endif /* (tachPwm_UseControl) */
    #endif  /* (!tachPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: tachPwm_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  tachPwm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void tachPwm_RestoreConfig(void) 
{
        #if(!tachPwm_UsingFixedFunction)
            #if(!tachPwm_PWMModeIsCenterAligned)
                tachPwm_WritePeriod(tachPwm_backup.PWMPeriod);
            #endif /* (!tachPwm_PWMModeIsCenterAligned) */

            tachPwm_WriteCounter(tachPwm_backup.PWMUdb);

            #if (tachPwm_UseStatus)
                tachPwm_STATUS_MASK = tachPwm_backup.InterruptMaskValue;
            #endif /* (tachPwm_UseStatus) */

            #if(tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_256_CLOCKS || \
                tachPwm_DeadBandMode == tachPwm__B_PWM__DBM_2_4_CLOCKS)
                tachPwm_WriteDeadTime(tachPwm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(tachPwm_KillModeMinTime)
                tachPwm_WriteKillTime(tachPwm_backup.PWMKillCounterPeriod);
            #endif /* (tachPwm_KillModeMinTime) */

            #if(tachPwm_UseControl)
                tachPwm_WriteControlRegister(tachPwm_backup.PWMControlRegister);
            #endif /* (tachPwm_UseControl) */
        #endif  /* (!tachPwm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: tachPwm_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  tachPwm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void tachPwm_Sleep(void) 
{
    #if(tachPwm_UseControl)
        if(tachPwm_CTRL_ENABLE == (tachPwm_CONTROL & tachPwm_CTRL_ENABLE))
        {
            /*Component is enabled */
            tachPwm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            tachPwm_backup.PWMEnableState = 0u;
        }
    #endif /* (tachPwm_UseControl) */

    /* Stop component */
    tachPwm_Stop();

    /* Save registers configuration */
    tachPwm_SaveConfig();
}


/*******************************************************************************
* Function Name: tachPwm_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  tachPwm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void tachPwm_Wakeup(void) 
{
     /* Restore registers values */
    tachPwm_RestoreConfig();

    if(tachPwm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        tachPwm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
