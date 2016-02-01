/*******************************************************************************
* File Name: capsense_SampleClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_capsense_SampleClk_H)
#define CY_CLOCK_capsense_SampleClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void capsense_SampleClk_StartEx(uint32 alignClkDiv);
#define capsense_SampleClk_Start() \
    capsense_SampleClk_StartEx(capsense_SampleClk__PA_DIV_ID)

#else

void capsense_SampleClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void capsense_SampleClk_Stop(void);

void capsense_SampleClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 capsense_SampleClk_GetDividerRegister(void);
uint8  capsense_SampleClk_GetFractionalDividerRegister(void);

#define capsense_SampleClk_Enable()                         capsense_SampleClk_Start()
#define capsense_SampleClk_Disable()                        capsense_SampleClk_Stop()
#define capsense_SampleClk_SetDividerRegister(clkDivider, reset)  \
    capsense_SampleClk_SetFractionalDividerRegister((clkDivider), 0u)
#define capsense_SampleClk_SetDivider(clkDivider)           capsense_SampleClk_SetDividerRegister((clkDivider), 1u)
#define capsense_SampleClk_SetDividerValue(clkDivider)      capsense_SampleClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define capsense_SampleClk_DIV_ID     capsense_SampleClk__DIV_ID

#define capsense_SampleClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define capsense_SampleClk_CTRL_REG   (*(reg32 *)capsense_SampleClk__CTRL_REGISTER)
#define capsense_SampleClk_DIV_REG    (*(reg32 *)capsense_SampleClk__DIV_REGISTER)

#define capsense_SampleClk_CMD_DIV_SHIFT          (0u)
#define capsense_SampleClk_CMD_PA_DIV_SHIFT       (8u)
#define capsense_SampleClk_CMD_DISABLE_SHIFT      (30u)
#define capsense_SampleClk_CMD_ENABLE_SHIFT       (31u)

#define capsense_SampleClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << capsense_SampleClk_CMD_DISABLE_SHIFT))
#define capsense_SampleClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << capsense_SampleClk_CMD_ENABLE_SHIFT))

#define capsense_SampleClk_DIV_FRAC_MASK  (0x000000F8u)
#define capsense_SampleClk_DIV_FRAC_SHIFT (3u)
#define capsense_SampleClk_DIV_INT_MASK   (0xFFFFFF00u)
#define capsense_SampleClk_DIV_INT_SHIFT  (8u)

#else 

#define capsense_SampleClk_DIV_REG        (*(reg32 *)capsense_SampleClk__REGISTER)
#define capsense_SampleClk_ENABLE_REG     capsense_SampleClk_DIV_REG
#define capsense_SampleClk_DIV_FRAC_MASK  capsense_SampleClk__FRAC_MASK
#define capsense_SampleClk_DIV_FRAC_SHIFT (16u)
#define capsense_SampleClk_DIV_INT_MASK   capsense_SampleClk__DIVIDER_MASK
#define capsense_SampleClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_capsense_SampleClk_H) */

/* [] END OF FILE */
