/*******************************************************************************
* File Name: GNDLEFT.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "GNDLEFT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        GNDLEFT_PC =   (GNDLEFT_PC & \
                                (uint32)(~(uint32)(GNDLEFT_DRIVE_MODE_IND_MASK << (GNDLEFT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (GNDLEFT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: GNDLEFT_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GNDLEFT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(GNDLEFT_DR & (uint8)(~GNDLEFT_MASK));
    drVal = (drVal | ((uint8)(value << GNDLEFT_SHIFT) & GNDLEFT_MASK));
    GNDLEFT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: GNDLEFT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  GNDLEFT_DM_STRONG     Strong Drive 
*  GNDLEFT_DM_OD_HI      Open Drain, Drives High 
*  GNDLEFT_DM_OD_LO      Open Drain, Drives Low 
*  GNDLEFT_DM_RES_UP     Resistive Pull Up 
*  GNDLEFT_DM_RES_DWN    Resistive Pull Down 
*  GNDLEFT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  GNDLEFT_DM_DIG_HIZ    High Impedance Digital 
*  GNDLEFT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void GNDLEFT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(GNDLEFT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: GNDLEFT_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro GNDLEFT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GNDLEFT_Read(void) 
{
    return (uint8)((GNDLEFT_PS & GNDLEFT_MASK) >> GNDLEFT_SHIFT);
}


/*******************************************************************************
* Function Name: GNDLEFT_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 GNDLEFT_ReadDataReg(void) 
{
    return (uint8)((GNDLEFT_DR & GNDLEFT_MASK) >> GNDLEFT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GNDLEFT_INTSTAT) 

    /*******************************************************************************
    * Function Name: GNDLEFT_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 GNDLEFT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(GNDLEFT_INTSTAT & GNDLEFT_MASK);
		GNDLEFT_INTSTAT = maskedStatus;
        return maskedStatus >> GNDLEFT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
