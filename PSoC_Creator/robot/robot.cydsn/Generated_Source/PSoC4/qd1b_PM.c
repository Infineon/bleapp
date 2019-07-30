/*******************************************************************************
* File Name: qd1b.c  
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
#include "qd1b.h"

static qd1b_BACKUP_STRUCT  qd1b_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: qd1b_Sleep
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
*  \snippet qd1b_SUT.c usage_qd1b_Sleep_Wakeup
*******************************************************************************/
void qd1b_Sleep(void)
{
    #if defined(qd1b__PC)
        qd1b_backup.pcState = qd1b_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            qd1b_backup.usbState = qd1b_CR1_REG;
            qd1b_USB_POWER_REG |= qd1b_USBIO_ENTER_SLEEP;
            qd1b_CR1_REG &= qd1b_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(qd1b__SIO)
        qd1b_backup.sioState = qd1b_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        qd1b_SIO_REG &= (uint32)(~qd1b_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: qd1b_Wakeup
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
*  Refer to qd1b_Sleep() for an example usage.
*******************************************************************************/
void qd1b_Wakeup(void)
{
    #if defined(qd1b__PC)
        qd1b_PC = qd1b_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            qd1b_USB_POWER_REG &= qd1b_USBIO_EXIT_SLEEP_PH1;
            qd1b_CR1_REG = qd1b_backup.usbState;
            qd1b_USB_POWER_REG &= qd1b_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(qd1b__SIO)
        qd1b_SIO_REG = qd1b_backup.sioState;
    #endif
}


/* [] END OF FILE */
