/*******************************************************************************
* File Name: QDRIGHT_PM.c
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

#include "QDRIGHT.h"

static QDRIGHT_BACKUP_STRUCT QDRIGHT_backup;


/*******************************************************************************
* Function Name: QDRIGHT_SaveConfig
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
void QDRIGHT_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: QDRIGHT_Sleep
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
void QDRIGHT_Sleep(void)
{
    if(0u != (QDRIGHT_BLOCK_CONTROL_REG & QDRIGHT_MASK))
    {
        QDRIGHT_backup.enableState = 1u;
    }
    else
    {
        QDRIGHT_backup.enableState = 0u;
    }

    QDRIGHT_Stop();
    QDRIGHT_SaveConfig();
}


/*******************************************************************************
* Function Name: QDRIGHT_RestoreConfig
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
void QDRIGHT_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: QDRIGHT_Wakeup
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
void QDRIGHT_Wakeup(void)
{
    QDRIGHT_RestoreConfig();

    if(0u != QDRIGHT_backup.enableState)
    {
        QDRIGHT_Enable();
    }
}


/* [] END OF FILE */
