/*******************************************************************************
* File Name: qd1a.c  
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
#include "qd1a.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        qd1a_PC =   (qd1a_PC & \
                                (uint32)(~(uint32)(qd1a_DRIVE_MODE_IND_MASK << (qd1a_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (qd1a_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: qd1a_Write
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
void qd1a_Write(uint8 value) 
{
    uint8 drVal = (uint8)(qd1a_DR & (uint8)(~qd1a_MASK));
    drVal = (drVal | ((uint8)(value << qd1a_SHIFT) & qd1a_MASK));
    qd1a_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: qd1a_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  qd1a_DM_STRONG     Strong Drive 
*  qd1a_DM_OD_HI      Open Drain, Drives High 
*  qd1a_DM_OD_LO      Open Drain, Drives Low 
*  qd1a_DM_RES_UP     Resistive Pull Up 
*  qd1a_DM_RES_DWN    Resistive Pull Down 
*  qd1a_DM_RES_UPDWN  Resistive Pull Up/Down 
*  qd1a_DM_DIG_HIZ    High Impedance Digital 
*  qd1a_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void qd1a_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(qd1a__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: qd1a_Read
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
*  Macro qd1a_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 qd1a_Read(void) 
{
    return (uint8)((qd1a_PS & qd1a_MASK) >> qd1a_SHIFT);
}


/*******************************************************************************
* Function Name: qd1a_ReadDataReg
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
uint8 qd1a_ReadDataReg(void) 
{
    return (uint8)((qd1a_DR & qd1a_MASK) >> qd1a_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(qd1a_INTSTAT) 

    /*******************************************************************************
    * Function Name: qd1a_ClearInterrupt
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
    uint8 qd1a_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(qd1a_INTSTAT & qd1a_MASK);
		qd1a_INTSTAT = maskedStatus;
        return maskedStatus >> qd1a_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
