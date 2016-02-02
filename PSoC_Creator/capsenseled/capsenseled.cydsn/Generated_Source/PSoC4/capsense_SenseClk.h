/*******************************************************************************
* File Name: capsense_SenseClk.h
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

#if !defined(CY_CLOCK_capsense_SenseClk_H)
#define CY_CLOCK_capsense_SenseClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void capsense_SenseClk_StartEx(uint32 alignClkDiv);
#define capsense_SenseClk_Start() \
    capsense_SenseClk_StartEx(capsense_SenseClk__PA_DIV_ID)

#else

void capsense_SenseClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void capsense_SenseClk_Stop(void);

void capsense_SenseClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 capsense_SenseClk_GetDividerRegister(void);
uint8  capsense_SenseClk_GetFractionalDividerRegister(void);

#define capsense_SenseClk_Enable()                         capsense_SenseClk_Start()
#define capsense_SenseClk_Disable()                        capsense_SenseClk_Stop()
#define capsense_SenseClk_SetDividerRegister(clkDivider, reset)  \
    capsense_SenseClk_SetFractionalDividerRegister((clkDivider), 0u)
#define capsense_SenseClk_SetDivider(clkDivider)           capsense_SenseClk_SetDividerRegister((clkDivider), 1u)
#define capsense_SenseClk_SetDividerValue(clkDivider)      capsense_SenseClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define capsense_SenseClk_DIV_ID     capsense_SenseClk__DIV_ID

#define capsense_SenseClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define capsense_SenseClk_CTRL_REG   (*(reg32 *)capsense_SenseClk__CTRL_REGISTER)
#define capsense_SenseClk_DIV_REG    (*(reg32 *)capsense_SenseClk__DIV_REGISTER)

#define capsense_SenseClk_CMD_DIV_SHIFT          (0u)
#define capsense_SenseClk_CMD_PA_DIV_SHIFT       (8u)
#define capsense_SenseClk_CMD_DISABLE_SHIFT      (30u)
#define capsense_SenseClk_CMD_ENABLE_SHIFT       (31u)

#define capsense_SenseClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << capsense_SenseClk_CMD_DISABLE_SHIFT))
#define capsense_SenseClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << capsense_SenseClk_CMD_ENABLE_SHIFT))

#define capsense_SenseClk_DIV_FRAC_MASK  (0x000000F8u)
#define capsense_SenseClk_DIV_FRAC_SHIFT (3u)
#define capsense_SenseClk_DIV_INT_MASK   (0xFFFFFF00u)
#define capsense_SenseClk_DIV_INT_SHIFT  (8u)

#else 

#define capsense_SenseClk_DIV_REG        (*(reg32 *)capsense_SenseClk__REGISTER)
#define capsense_SenseClk_ENABLE_REG     capsense_SenseClk_DIV_REG
#define capsense_SenseClk_DIV_FRAC_MASK  capsense_SenseClk__FRAC_MASK
#define capsense_SenseClk_DIV_FRAC_SHIFT (16u)
#define capsense_SenseClk_DIV_INT_MASK   capsense_SenseClk__DIVIDER_MASK
#define capsense_SenseClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_capsense_SenseClk_H) */

/* [] END OF FILE */
