/*******************************************************************************
* File Name: blue.c  
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
#include "blue.h"

static blue_BACKUP_STRUCT  blue_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: blue_Sleep
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
*  \snippet blue_SUT.c usage_blue_Sleep_Wakeup
*******************************************************************************/
void blue_Sleep(void)
{
    #if defined(blue__PC)
        blue_backup.pcState = blue_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            blue_backup.usbState = blue_CR1_REG;
            blue_USB_POWER_REG |= blue_USBIO_ENTER_SLEEP;
            blue_CR1_REG &= blue_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(blue__SIO)
        blue_backup.sioState = blue_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        blue_SIO_REG &= (uint32)(~blue_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: blue_Wakeup
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
*  Refer to blue_Sleep() for an example usage.
*******************************************************************************/
void blue_Wakeup(void)
{
    #if defined(blue__PC)
        blue_PC = blue_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            blue_USB_POWER_REG &= blue_USBIO_EXIT_SLEEP_PH1;
            blue_CR1_REG = blue_backup.usbState;
            blue_USB_POWER_REG &= blue_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(blue__SIO)
        blue_SIO_REG = blue_backup.sioState;
    #endif
}


/* [] END OF FILE */
