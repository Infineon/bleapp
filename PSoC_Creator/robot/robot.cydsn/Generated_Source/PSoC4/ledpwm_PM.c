/*******************************************************************************
* File Name: ledpwm_PM.c
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

#include "ledpwm.h"

static ledpwm_backupStruct ledpwm_backup;


/*******************************************************************************
* Function Name: ledpwm_SaveConfig
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
*  ledpwm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ledpwm_SaveConfig(void) 
{

    #if(!ledpwm_UsingFixedFunction)
        #if(!ledpwm_PWMModeIsCenterAligned)
            ledpwm_backup.PWMPeriod = ledpwm_ReadPeriod();
        #endif /* (!ledpwm_PWMModeIsCenterAligned) */
        ledpwm_backup.PWMUdb = ledpwm_ReadCounter();
        #if (ledpwm_UseStatus)
            ledpwm_backup.InterruptMaskValue = ledpwm_STATUS_MASK;
        #endif /* (ledpwm_UseStatus) */

        #if(ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_256_CLOCKS || \
            ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_2_4_CLOCKS)
            ledpwm_backup.PWMdeadBandValue = ledpwm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ledpwm_KillModeMinTime)
             ledpwm_backup.PWMKillCounterPeriod = ledpwm_ReadKillTime();
        #endif /* (ledpwm_KillModeMinTime) */

        #if(ledpwm_UseControl)
            ledpwm_backup.PWMControlRegister = ledpwm_ReadControlRegister();
        #endif /* (ledpwm_UseControl) */
    #endif  /* (!ledpwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledpwm_RestoreConfig
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
*  ledpwm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ledpwm_RestoreConfig(void) 
{
        #if(!ledpwm_UsingFixedFunction)
            #if(!ledpwm_PWMModeIsCenterAligned)
                ledpwm_WritePeriod(ledpwm_backup.PWMPeriod);
            #endif /* (!ledpwm_PWMModeIsCenterAligned) */

            ledpwm_WriteCounter(ledpwm_backup.PWMUdb);

            #if (ledpwm_UseStatus)
                ledpwm_STATUS_MASK = ledpwm_backup.InterruptMaskValue;
            #endif /* (ledpwm_UseStatus) */

            #if(ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_256_CLOCKS || \
                ledpwm_DeadBandMode == ledpwm__B_PWM__DBM_2_4_CLOCKS)
                ledpwm_WriteDeadTime(ledpwm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ledpwm_KillModeMinTime)
                ledpwm_WriteKillTime(ledpwm_backup.PWMKillCounterPeriod);
            #endif /* (ledpwm_KillModeMinTime) */

            #if(ledpwm_UseControl)
                ledpwm_WriteControlRegister(ledpwm_backup.PWMControlRegister);
            #endif /* (ledpwm_UseControl) */
        #endif  /* (!ledpwm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ledpwm_Sleep
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
*  ledpwm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ledpwm_Sleep(void) 
{
    #if(ledpwm_UseControl)
        if(ledpwm_CTRL_ENABLE == (ledpwm_CONTROL & ledpwm_CTRL_ENABLE))
        {
            /*Component is enabled */
            ledpwm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ledpwm_backup.PWMEnableState = 0u;
        }
    #endif /* (ledpwm_UseControl) */

    /* Stop component */
    ledpwm_Stop();

    /* Save registers configuration */
    ledpwm_SaveConfig();
}


/*******************************************************************************
* Function Name: ledpwm_Wakeup
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
*  ledpwm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ledpwm_Wakeup(void) 
{
     /* Restore registers values */
    ledpwm_RestoreConfig();

    if(ledpwm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ledpwm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
