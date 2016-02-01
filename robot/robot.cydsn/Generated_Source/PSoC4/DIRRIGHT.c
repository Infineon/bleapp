/*******************************************************************************
* File Name: DIRRIGHT.c  
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
#include "DIRRIGHT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DIRRIGHT_PC =   (DIRRIGHT_PC & \
                                (uint32)(~(uint32)(DIRRIGHT_DRIVE_MODE_IND_MASK << (DIRRIGHT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DIRRIGHT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DIRRIGHT_Write
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
void DIRRIGHT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DIRRIGHT_DR & (uint8)(~DIRRIGHT_MASK));
    drVal = (drVal | ((uint8)(value << DIRRIGHT_SHIFT) & DIRRIGHT_MASK));
    DIRRIGHT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DIRRIGHT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DIRRIGHT_DM_STRONG     Strong Drive 
*  DIRRIGHT_DM_OD_HI      Open Drain, Drives High 
*  DIRRIGHT_DM_OD_LO      Open Drain, Drives Low 
*  DIRRIGHT_DM_RES_UP     Resistive Pull Up 
*  DIRRIGHT_DM_RES_DWN    Resistive Pull Down 
*  DIRRIGHT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DIRRIGHT_DM_DIG_HIZ    High Impedance Digital 
*  DIRRIGHT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DIRRIGHT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DIRRIGHT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DIRRIGHT_Read
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
*  Macro DIRRIGHT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DIRRIGHT_Read(void) 
{
    return (uint8)((DIRRIGHT_PS & DIRRIGHT_MASK) >> DIRRIGHT_SHIFT);
}


/*******************************************************************************
* Function Name: DIRRIGHT_ReadDataReg
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
uint8 DIRRIGHT_ReadDataReg(void) 
{
    return (uint8)((DIRRIGHT_DR & DIRRIGHT_MASK) >> DIRRIGHT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DIRRIGHT_INTSTAT) 

    /*******************************************************************************
    * Function Name: DIRRIGHT_ClearInterrupt
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
    uint8 DIRRIGHT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DIRRIGHT_INTSTAT & DIRRIGHT_MASK);
		DIRRIGHT_INTSTAT = maskedStatus;
        return maskedStatus >> DIRRIGHT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
