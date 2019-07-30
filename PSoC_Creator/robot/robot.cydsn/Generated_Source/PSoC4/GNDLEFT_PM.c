/*******************************************************************************
* File Name: GNDLEFT.c  
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
#include "GNDLEFT.h"

static GNDLEFT_BACKUP_STRUCT  GNDLEFT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GNDLEFT_Sleep
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
*  \snippet GNDLEFT_SUT.c usage_GNDLEFT_Sleep_Wakeup
*******************************************************************************/
void GNDLEFT_Sleep(void)
{
    #if defined(GNDLEFT__PC)
        GNDLEFT_backup.pcState = GNDLEFT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GNDLEFT_backup.usbState = GNDLEFT_CR1_REG;
            GNDLEFT_USB_POWER_REG |= GNDLEFT_USBIO_ENTER_SLEEP;
            GNDLEFT_CR1_REG &= GNDLEFT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GNDLEFT__SIO)
        GNDLEFT_backup.sioState = GNDLEFT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GNDLEFT_SIO_REG &= (uint32)(~GNDLEFT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GNDLEFT_Wakeup
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
*  Refer to GNDLEFT_Sleep() for an example usage.
*******************************************************************************/
void GNDLEFT_Wakeup(void)
{
    #if defined(GNDLEFT__PC)
        GNDLEFT_PC = GNDLEFT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GNDLEFT_USB_POWER_REG &= GNDLEFT_USBIO_EXIT_SLEEP_PH1;
            GNDLEFT_CR1_REG = GNDLEFT_backup.usbState;
            GNDLEFT_USB_POWER_REG &= GNDLEFT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GNDLEFT__SIO)
        GNDLEFT_SIO_REG = GNDLEFT_backup.sioState;
    #endif
}


/* [] END OF FILE */
