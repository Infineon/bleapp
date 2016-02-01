/*******************************************************************************
* File Name: DIRLEFT.c  
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
#include "DIRLEFT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DIRLEFT_PC =   (DIRLEFT_PC & \
                                (uint32)(~(uint32)(DIRLEFT_DRIVE_MODE_IND_MASK << (DIRLEFT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DIRLEFT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DIRLEFT_Write
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
void DIRLEFT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DIRLEFT_DR & (uint8)(~DIRLEFT_MASK));
    drVal = (drVal | ((uint8)(value << DIRLEFT_SHIFT) & DIRLEFT_MASK));
    DIRLEFT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DIRLEFT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DIRLEFT_DM_STRONG     Strong Drive 
*  DIRLEFT_DM_OD_HI      Open Drain, Drives High 
*  DIRLEFT_DM_OD_LO      Open Drain, Drives Low 
*  DIRLEFT_DM_RES_UP     Resistive Pull Up 
*  DIRLEFT_DM_RES_DWN    Resistive Pull Down 
*  DIRLEFT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DIRLEFT_DM_DIG_HIZ    High Impedance Digital 
*  DIRLEFT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DIRLEFT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DIRLEFT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DIRLEFT_Read
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
*  Macro DIRLEFT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DIRLEFT_Read(void) 
{
    return (uint8)((DIRLEFT_PS & DIRLEFT_MASK) >> DIRLEFT_SHIFT);
}


/*******************************************************************************
* Function Name: DIRLEFT_ReadDataReg
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
uint8 DIRLEFT_ReadDataReg(void) 
{
    return (uint8)((DIRLEFT_DR & DIRLEFT_MASK) >> DIRLEFT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DIRLEFT_INTSTAT) 

    /*******************************************************************************
    * Function Name: DIRLEFT_ClearInterrupt
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
    uint8 DIRLEFT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DIRLEFT_INTSTAT & DIRLEFT_MASK);
		DIRLEFT_INTSTAT = maskedStatus;
        return maskedStatus >> DIRLEFT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
