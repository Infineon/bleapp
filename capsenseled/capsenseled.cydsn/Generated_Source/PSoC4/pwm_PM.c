/*******************************************************************************
* File Name: pwm_PM.c
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

#include "pwm.h"

static pwm_backupStruct pwm_backup;


/*******************************************************************************
* Function Name: pwm_SaveConfig
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
*  pwm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwm_SaveConfig(void) 
{

    #if(!pwm_UsingFixedFunction)
        #if(!pwm_PWMModeIsCenterAligned)
            pwm_backup.PWMPeriod = pwm_ReadPeriod();
        #endif /* (!pwm_PWMModeIsCenterAligned) */
        pwm_backup.PWMUdb = pwm_ReadCounter();
        #if (pwm_UseStatus)
            pwm_backup.InterruptMaskValue = pwm_STATUS_MASK;
        #endif /* (pwm_UseStatus) */

        #if(pwm_DeadBandMode == pwm__B_PWM__DBM_256_CLOCKS || \
            pwm_DeadBandMode == pwm__B_PWM__DBM_2_4_CLOCKS)
            pwm_backup.PWMdeadBandValue = pwm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwm_KillModeMinTime)
             pwm_backup.PWMKillCounterPeriod = pwm_ReadKillTime();
        #endif /* (pwm_KillModeMinTime) */

        #if(pwm_UseControl)
            pwm_backup.PWMControlRegister = pwm_ReadControlRegister();
        #endif /* (pwm_UseControl) */
    #endif  /* (!pwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwm_RestoreConfig
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
*  pwm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwm_RestoreConfig(void) 
{
        #if(!pwm_UsingFixedFunction)
            #if(!pwm_PWMModeIsCenterAligned)
                pwm_WritePeriod(pwm_backup.PWMPeriod);
            #endif /* (!pwm_PWMModeIsCenterAligned) */

            pwm_WriteCounter(pwm_backup.PWMUdb);

            #if (pwm_UseStatus)
                pwm_STATUS_MASK = pwm_backup.InterruptMaskValue;
            #endif /* (pwm_UseStatus) */

            #if(pwm_DeadBandMode == pwm__B_PWM__DBM_256_CLOCKS || \
                pwm_DeadBandMode == pwm__B_PWM__DBM_2_4_CLOCKS)
                pwm_WriteDeadTime(pwm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwm_KillModeMinTime)
                pwm_WriteKillTime(pwm_backup.PWMKillCounterPeriod);
            #endif /* (pwm_KillModeMinTime) */

            #if(pwm_UseControl)
                pwm_WriteControlRegister(pwm_backup.PWMControlRegister);
            #endif /* (pwm_UseControl) */
        #endif  /* (!pwm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwm_Sleep
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
*  pwm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwm_Sleep(void) 
{
    #if(pwm_UseControl)
        if(pwm_CTRL_ENABLE == (pwm_CONTROL & pwm_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwm_backup.PWMEnableState = 0u;
        }
    #endif /* (pwm_UseControl) */

    /* Stop component */
    pwm_Stop();

    /* Save registers configuration */
    pwm_SaveConfig();
}


/*******************************************************************************
* Function Name: pwm_Wakeup
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
*  pwm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwm_Wakeup(void) 
{
     /* Restore registers values */
    pwm_RestoreConfig();

    if(pwm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
