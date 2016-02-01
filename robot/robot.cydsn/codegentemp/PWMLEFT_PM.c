/*******************************************************************************
* File Name: PWMLEFT_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "PWMLEFT.h"

static PWMLEFT_BACKUP_STRUCT PWMLEFT_backup;


/*******************************************************************************
* Function Name: PWMLEFT_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMLEFT_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_Sleep(void)
{
    if(0u != (PWMLEFT_BLOCK_CONTROL_REG & PWMLEFT_MASK))
    {
        PWMLEFT_backup.enableState = 1u;
    }
    else
    {
        PWMLEFT_backup.enableState = 0u;
    }

    PWMLEFT_Stop();
    PWMLEFT_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMLEFT_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMLEFT_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_Wakeup(void)
{
    PWMLEFT_RestoreConfig();

    if(0u != PWMLEFT_backup.enableState)
    {
        PWMLEFT_Enable();
    }
}


/* [] END OF FILE */
