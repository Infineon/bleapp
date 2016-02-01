/*******************************************************************************
* File Name: qd1b.c  
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
#include "qd1b.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        qd1b_PC =   (qd1b_PC & \
                                (uint32)(~(uint32)(qd1b_DRIVE_MODE_IND_MASK << (qd1b_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (qd1b_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: qd1b_Write
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
void qd1b_Write(uint8 value) 
{
    uint8 drVal = (uint8)(qd1b_DR & (uint8)(~qd1b_MASK));
    drVal = (drVal | ((uint8)(value << qd1b_SHIFT) & qd1b_MASK));
    qd1b_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: qd1b_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  qd1b_DM_STRONG     Strong Drive 
*  qd1b_DM_OD_HI      Open Drain, Drives High 
*  qd1b_DM_OD_LO      Open Drain, Drives Low 
*  qd1b_DM_RES_UP     Resistive Pull Up 
*  qd1b_DM_RES_DWN    Resistive Pull Down 
*  qd1b_DM_RES_UPDWN  Resistive Pull Up/Down 
*  qd1b_DM_DIG_HIZ    High Impedance Digital 
*  qd1b_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void qd1b_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(qd1b__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: qd1b_Read
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
*  Macro qd1b_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 qd1b_Read(void) 
{
    return (uint8)((qd1b_PS & qd1b_MASK) >> qd1b_SHIFT);
}


/*******************************************************************************
* Function Name: qd1b_ReadDataReg
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
uint8 qd1b_ReadDataReg(void) 
{
    return (uint8)((qd1b_DR & qd1b_MASK) >> qd1b_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(qd1b_INTSTAT) 

    /*******************************************************************************
    * Function Name: qd1b_ClearInterrupt
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
    uint8 qd1b_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(qd1b_INTSTAT & qd1b_MASK);
		qd1b_INTSTAT = maskedStatus;
        return maskedStatus >> qd1b_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
