/*******************************************************************************
* File Name: POWERRIGHT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "POWERRIGHT.h"

static POWERRIGHT_BACKUP_STRUCT  POWERRIGHT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: POWERRIGHT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet POWERRIGHT_SUT.c usage_POWERRIGHT_Sleep_Wakeup
*******************************************************************************/
void POWERRIGHT_Sleep(void)
{
    #if defined(POWERRIGHT__PC)
        POWERRIGHT_backup.pcState = POWERRIGHT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            POWERRIGHT_backup.usbState = POWERRIGHT_CR1_REG;
            POWERRIGHT_USB_POWER_REG |= POWERRIGHT_USBIO_ENTER_SLEEP;
            POWERRIGHT_CR1_REG &= POWERRIGHT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(POWERRIGHT__SIO)
        POWERRIGHT_backup.sioState = POWERRIGHT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        POWERRIGHT_SIO_REG &= (uint32)(~POWERRIGHT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: POWERRIGHT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to POWERRIGHT_Sleep() for an example usage.
*******************************************************************************/
void POWERRIGHT_Wakeup(void)
{
    #if defined(POWERRIGHT__PC)
        POWERRIGHT_PC = POWERRIGHT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            POWERRIGHT_USB_POWER_REG &= POWERRIGHT_USBIO_EXIT_SLEEP_PH1;
            POWERRIGHT_CR1_REG = POWERRIGHT_backup.usbState;
            POWERRIGHT_USB_POWER_REG &= POWERRIGHT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(POWERRIGHT__SIO)
        POWERRIGHT_SIO_REG = POWERRIGHT_backup.sioState;
    #endif
}


/* [] END OF FILE */
