/*******************************************************************************
* File Name: M2.c  
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
#include "M2.h"

static M2_BACKUP_STRUCT  M2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: M2_Sleep
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
*  \snippet M2_SUT.c usage_M2_Sleep_Wakeup
*******************************************************************************/
void M2_Sleep(void)
{
    #if defined(M2__PC)
        M2_backup.pcState = M2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            M2_backup.usbState = M2_CR1_REG;
            M2_USB_POWER_REG |= M2_USBIO_ENTER_SLEEP;
            M2_CR1_REG &= M2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M2__SIO)
        M2_backup.sioState = M2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        M2_SIO_REG &= (uint32)(~M2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: M2_Wakeup
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
*  Refer to M2_Sleep() for an example usage.
*******************************************************************************/
void M2_Wakeup(void)
{
    #if defined(M2__PC)
        M2_PC = M2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            M2_USB_POWER_REG &= M2_USBIO_EXIT_SLEEP_PH1;
            M2_CR1_REG = M2_backup.usbState;
            M2_USB_POWER_REG &= M2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M2__SIO)
        M2_SIO_REG = M2_backup.sioState;
    #endif
}


/* [] END OF FILE */
