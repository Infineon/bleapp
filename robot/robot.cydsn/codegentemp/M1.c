/*******************************************************************************
* File Name: M1.c  
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
#include "M1.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        M1_PC =   (M1_PC & \
                                (uint32)(~(uint32)(M1_DRIVE_MODE_IND_MASK << (M1_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (M1_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: M1_Write
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
void M1_Write(uint8 value) 
{
    uint8 drVal = (uint8)(M1_DR & (uint8)(~M1_MASK));
    drVal = (drVal | ((uint8)(value << M1_SHIFT) & M1_MASK));
    M1_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: M1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  M1_DM_STRONG     Strong Drive 
*  M1_DM_OD_HI      Open Drain, Drives High 
*  M1_DM_OD_LO      Open Drain, Drives Low 
*  M1_DM_RES_UP     Resistive Pull Up 
*  M1_DM_RES_DWN    Resistive Pull Down 
*  M1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  M1_DM_DIG_HIZ    High Impedance Digital 
*  M1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void M1_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(M1__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: M1_Read
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
*  Macro M1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 M1_Read(void) 
{
    return (uint8)((M1_PS & M1_MASK) >> M1_SHIFT);
}


/*******************************************************************************
* Function Name: M1_ReadDataReg
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
uint8 M1_ReadDataReg(void) 
{
    return (uint8)((M1_DR & M1_MASK) >> M1_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(M1_INTSTAT) 

    /*******************************************************************************
    * Function Name: M1_ClearInterrupt
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
    uint8 M1_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(M1_INTSTAT & M1_MASK);
		M1_INTSTAT = maskedStatus;
        return maskedStatus >> M1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
