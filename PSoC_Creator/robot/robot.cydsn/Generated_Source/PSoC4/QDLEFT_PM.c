/*******************************************************************************
* File Name: QDLEFT_PM.c
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

#include "QDLEFT.h"

static QDLEFT_BACKUP_STRUCT QDLEFT_backup;


/*******************************************************************************
* Function Name: QDLEFT_SaveConfig
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
void QDLEFT_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: QDLEFT_Sleep
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
void QDLEFT_Sleep(void)
{
    if(0u != (QDLEFT_BLOCK_CONTROL_REG & QDLEFT_MASK))
    {
        QDLEFT_backup.enableState = 1u;
    }
    else
    {
        QDLEFT_backup.enableState = 0u;
    }

    QDLEFT_Stop();
    QDLEFT_SaveConfig();
}


/*******************************************************************************
* Function Name: QDLEFT_RestoreConfig
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
void QDLEFT_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: QDLEFT_Wakeup
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
void QDLEFT_Wakeup(void)
{
    QDLEFT_RestoreConfig();

    if(0u != QDLEFT_backup.enableState)
    {
        QDLEFT_Enable();
    }
}


/* [] END OF FILE */
