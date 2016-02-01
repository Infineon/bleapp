/*******************************************************************************
* File Name: PWMRIGHT_PM.c
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

#include "PWMRIGHT.h"

static PWMRIGHT_BACKUP_STRUCT PWMRIGHT_backup;


/*******************************************************************************
* Function Name: PWMRIGHT_SaveConfig
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
void PWMRIGHT_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMRIGHT_Sleep
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
void PWMRIGHT_Sleep(void)
{
    if(0u != (PWMRIGHT_BLOCK_CONTROL_REG & PWMRIGHT_MASK))
    {
        PWMRIGHT_backup.enableState = 1u;
    }
    else
    {
        PWMRIGHT_backup.enableState = 0u;
    }

    PWMRIGHT_Stop();
    PWMRIGHT_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMRIGHT_RestoreConfig
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
void PWMRIGHT_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMRIGHT_Wakeup
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
void PWMRIGHT_Wakeup(void)
{
    PWMRIGHT_RestoreConfig();

    if(0u != PWMRIGHT_backup.enableState)
    {
        PWMRIGHT_Enable();
    }
}


/* [] END OF FILE */
