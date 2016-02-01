/*******************************************************************************
* File Name: GNDRIGHT.c  
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
#include "GNDRIGHT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        GNDRIGHT_PC =   (GNDRIGHT_PC & \
                                (uint32)(~(uint32)(GNDRIGHT_DRIVE_MODE_IND_MASK << (GNDRIGHT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (GNDRIGHT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: GNDRIGHT_Write
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
void GNDRIGHT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(GNDRIGHT_DR & (uint8)(~GNDRIGHT_MASK));
    drVal = (drVal | ((uint8)(value << GNDRIGHT_SHIFT) & GNDRIGHT_MASK));
    GNDRIGHT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: GNDRIGHT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  GNDRIGHT_DM_STRONG     Strong Drive 
*  GNDRIGHT_DM_OD_HI      Open Drain, Drives High 
*  GNDRIGHT_DM_OD_LO      Open Drain, Drives Low 
*  GNDRIGHT_DM_RES_UP     Resistive Pull Up 
*  GNDRIGHT_DM_RES_DWN    Resistive Pull Down 
*  GNDRIGHT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  GNDRIGHT_DM_DIG_HIZ    High Impedance Digital 
*  GNDRIGHT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void GNDRIGHT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(GNDRIGHT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: GNDRIGHT_Read
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
*  Macro GNDRIGHT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GNDRIGHT_Read(void) 
{
    return (uint8)((GNDRIGHT_PS & GNDRIGHT_MASK) >> GNDRIGHT_SHIFT);
}


/*******************************************************************************
* Function Name: GNDRIGHT_ReadDataReg
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
uint8 GNDRIGHT_ReadDataReg(void) 
{
    return (uint8)((GNDRIGHT_DR & GNDRIGHT_MASK) >> GNDRIGHT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GNDRIGHT_INTSTAT) 

    /*******************************************************************************
    * Function Name: GNDRIGHT_ClearInterrupt
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
    uint8 GNDRIGHT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(GNDRIGHT_INTSTAT & GNDRIGHT_MASK);
		GNDRIGHT_INTSTAT = maskedStatus;
        return maskedStatus >> GNDRIGHT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
