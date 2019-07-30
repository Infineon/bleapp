/*******************************************************************************
* File Name: capsense_PM.c
* Version 2.60
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "capsense.h"

static capsense_BACKUP_STRUCT capsense_backup =
{
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: capsense_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_backup - used to save the component state before entering the  sleep
*  mode and none-retention registers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void capsense_SaveConfig(void)
{
    if ((capsense_CSD_CFG_REG & capsense_CSD_CFG_ENABLE) != 0u)
    {
        capsense_backup.enableState = 1u;
    }
}


/*******************************************************************************
* Function Name: capsense_Sleep
********************************************************************************
*
* Summary:
*  Disables the Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_backup - used to save the component state before entering the sleep
*  mode.
*
*******************************************************************************/
void capsense_Sleep(void)
{
    capsense_SaveConfig();

    /* Disable interrupt */
    CyIntDisable(capsense_ISR_NUMBER);

    capsense_CSD_CFG_REG &= ~(capsense_CSD_CFG_SENSE_COMP_EN | capsense_CSD_CFG_SENSE_EN);

    #if(capsense_IDAC_CNT == 2u)
        capsense_CSD_CFG_REG &= ~(capsense_CSD_CFG_ENABLE);
    #endif /* (capsense_IDAC_CNT == 2u) */

    /* Disable Clocks */
    capsense_SenseClk_Stop();
    capsense_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: capsense_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after capsense_SaveConfig() routine. Otherwise
*  the component configuration will be overwritten with its initial setting.
*
* Global Variables:
*  capsense_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void capsense_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: capsense_Wakeup
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration and non-retention register values.
*  Restores the enabled state of the component by setting the Active mode power template
*  bits for a number of components used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void capsense_Wakeup(void)
{
    /* Enable the Clocks */
    capsense_SenseClk_Start();
    capsense_SampleClk_Start();

    /* Restore CapSense Enable state */
    if (capsense_backup.enableState != 0u)
    {
        capsense_Enable();
    }
}


/* [] END OF FILE */
