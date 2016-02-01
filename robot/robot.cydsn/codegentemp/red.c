/*******************************************************************************
* File Name: red.c  
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
#include "red.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        red_PC =   (red_PC & \
                                (uint32)(~(uint32)(red_DRIVE_MODE_IND_MASK << (red_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (red_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: red_Write
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
void red_Write(uint8 value) 
{
    uint8 drVal = (uint8)(red_DR & (uint8)(~red_MASK));
    drVal = (drVal | ((uint8)(value << red_SHIFT) & red_MASK));
    red_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: red_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  red_DM_STRONG     Strong Drive 
*  red_DM_OD_HI      Open Drain, Drives High 
*  red_DM_OD_LO      Open Drain, Drives Low 
*  red_DM_RES_UP     Resistive Pull Up 
*  red_DM_RES_DWN    Resistive Pull Down 
*  red_DM_RES_UPDWN  Resistive Pull Up/Down 
*  red_DM_DIG_HIZ    High Impedance Digital 
*  red_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void red_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(red__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: red_Read
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
*  Macro red_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 red_Read(void) 
{
    return (uint8)((red_PS & red_MASK) >> red_SHIFT);
}


/*******************************************************************************
* Function Name: red_ReadDataReg
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
uint8 red_ReadDataReg(void) 
{
    return (uint8)((red_DR & red_MASK) >> red_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(red_INTSTAT) 

    /*******************************************************************************
    * Function Name: red_ClearInterrupt
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
    uint8 red_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(red_INTSTAT & red_MASK);
		red_INTSTAT = maskedStatus;
        return maskedStatus >> red_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
