/*******************************************************************************
* File Name: Control.c  
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
#include "Control.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Control_PC =   (Control_PC & \
                                (uint32)(~(uint32)(Control_DRIVE_MODE_IND_MASK << (Control_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Control_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Control_Write
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
void Control_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Control_DR & (uint8)(~Control_MASK));
    drVal = (drVal | ((uint8)(value << Control_SHIFT) & Control_MASK));
    Control_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Control_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Control_DM_STRONG     Strong Drive 
*  Control_DM_OD_HI      Open Drain, Drives High 
*  Control_DM_OD_LO      Open Drain, Drives Low 
*  Control_DM_RES_UP     Resistive Pull Up 
*  Control_DM_RES_DWN    Resistive Pull Down 
*  Control_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Control_DM_DIG_HIZ    High Impedance Digital 
*  Control_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Control_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Control__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Control_Read
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
*  Macro Control_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Control_Read(void) 
{
    return (uint8)((Control_PS & Control_MASK) >> Control_SHIFT);
}


/*******************************************************************************
* Function Name: Control_ReadDataReg
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
uint8 Control_ReadDataReg(void) 
{
    return (uint8)((Control_DR & Control_MASK) >> Control_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Control_INTSTAT) 

    /*******************************************************************************
    * Function Name: Control_ClearInterrupt
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
    uint8 Control_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Control_INTSTAT & Control_MASK);
		Control_INTSTAT = maskedStatus;
        return maskedStatus >> Control_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
