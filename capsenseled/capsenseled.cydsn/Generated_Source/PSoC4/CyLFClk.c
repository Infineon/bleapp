/*******************************************************************************
* File Name: .c
* Version 1.0
*
* Description:
*  This file provides the source code to API for the cy_lfclk Component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "CyLFClk.h"
#include "CyLib.h"


#if (CY_IP_WCO)
    static uint32 CySysClkGetLfclkSource(void);
#endif /* (CY_IP_WCO) */

#if(CY_IP_SRSSV2)
    /* CySysClkLfclkPosedgeCatch() / CySysClkLfclkPosedgeRestore() */
    static uint32 lfclkPosedgeWdtCounter0Enabled = 0u;
    static uint32 lfclkPosedgeWdtCounter0Mode    = CY_SYS_WDT_MODE_NONE;

    static volatile uint32 disableServicedIsr = 0uL;
    static volatile uint32 wdtIsrMask = CY_SYS_WDT_COUNTER0_INT |\
                                        CY_SYS_WDT_COUNTER1_INT |\
                                        CY_SYS_WDT_COUNTER2_INT;

    static const uint32 counterIntMaskTbl[CY_WDT_NUM_OF_WDT] = {CY_SYS_WDT_COUNTER0_INT,
                                                                CY_SYS_WDT_COUNTER1_INT,
                                                                CY_SYS_WDT_COUNTER2_INT};

    static void CySysClkLfclkPosedgeCatch(void);
    static void CySysClkLfclkPosedgeRestore(void);

    static uint32 CySysWdtLocked(void);
    static uint32 CySysClkIloEnabled(void);
#endif /* (CY_IP_SRSSV2) */

#if(CY_IP_SRSSV2)
    static cyWdtCallback cySysWdtCallback[CY_WDT_NUM_OF_WDT] = {(void *)0, (void *)0, (void *)0};
#else
    static cyWdtCallback cySysWdtCallback = (void *)0;
#endif /* (CY_IP_SRSSV2) */

/*******************************************************************************
* Function Name: CySysClkIloStart
********************************************************************************
*
* Summary:
*  Enables ILO. Refer to the device datasheet for the ILO startup time.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkIloStart(void)
{
    CY_SYS_CLK_ILO_CONFIG_REG |= CY_SYS_CLK_ILO_CONFIG_ENABLE;
}


/*******************************************************************************
* Function Name: CySysClkIloStop
********************************************************************************
*
* Summary:
*  Disables ILO.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function has no effect if WDT is locked (CySysWdtLock() is
*  called). Call CySysWdtUnlock() to unlock WDT and stop ILO.
*
*  PSoC 4100 / PSoC 4200: Note that ILO is required for WDT's operation.
*  ILO is required for WDT operation.
*
*  PSoC 4100-BL / PSoC 4200-BL and PSoC 4100M / PSoC 4200M:
*  Stopping ILO affects the peripheral clocked by LFCLK, if
*  LFCLK is configured to be sourced by ILO.
*
*******************************************************************************/
void CySysClkIloStop(void)
{
    #if(CY_IP_SRSSV2)
        uint8  interruptState;

        /* Do nothing if WDT is locked or ILO is disabled */
        if (0u == CySysWdtLocked())
        {
            if (0u != CySysClkIloEnabled())
            {

            #if (CY_IP_WCO)
                if (CY_SYS_CLK_LFCLK_SRC_ILO == CySysClkGetLfclkSource())
                {
            #endif /* (CY_IP_WCO) */

                interruptState = CyEnterCriticalSection();
                CySysClkLfclkPosedgeCatch();
                CY_SYS_CLK_ILO_CONFIG_REG &= ( uint32 ) ( ~( uint32 )CY_SYS_CLK_ILO_CONFIG_ENABLE);
                CySysClkLfclkPosedgeRestore();
                CyExitCriticalSection(interruptState);

            #if (CY_IP_WCO)
                }
                else /* Safe to disable - shortened pulse does not impact peripheral */
                {
                    CY_SYS_CLK_ILO_CONFIG_REG &= ( uint32 ) ( ~( uint32 )CY_SYS_CLK_ILO_CONFIG_ENABLE);
                }
            #endif /* (CY_IP_WCO) */

            }
        }
    #else
        CY_SYS_CLK_ILO_CONFIG_REG &= ( uint32 ) ( ~( uint32 )CY_SYS_CLK_ILO_CONFIG_ENABLE);
    #endif /* (CY_IP_SRSSV2) */
}

#if(CY_IP_SRSSV2)
    /*******************************************************************************
    * Function Name: CySysClkIloEnabled
    ********************************************************************************
    *
    * Summary:
    *  Reports the ILO enable state.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  1 if ILO is enabled, and 0 if ILO is disabled.
    *
    *******************************************************************************/
    static uint32 CySysClkIloEnabled(void)
    {
        /* Prohibits writing to WDT registers and ILO/WCO registers when not equal to 0 */
        return ((0u != (CY_SYS_CLK_ILO_CONFIG_REG & (uint32)(CY_SYS_CLK_ILO_CONFIG_ENABLE))) ?
            (uint32) 1u :
            (uint32) 0u);
    }
#endif /* (CY_IP_SRSSV2) */


/*******************************************************************************
* Function Name: CySysClkGetLfclkSource
********************************************************************************
*
* Summary:
*  Gets the clock source for the LFCLK clock.
*  The function is applicable only for PSoC 4100-BL and PSoC 4200-BL.
*
* Parameters:
*  None.
*
* Return:
*  The LFCLK source:
*   CY_SYS_CLK_LFCLK_SRC_ILO    Internal Low Frequency (32 kHz) Oscillator (ILO)
*   CY_SYS_CLK_LFCLK_SRC_WCO    Low Frequency Watch Crystal Oscillator (WCO)
*
*******************************************************************************/
#if (CY_IP_WCO)
    static uint32 CySysClkGetLfclkSource(void)
    {
        uint32 lfclkSource;
        lfclkSource = CY_SYS_WDT_CONFIG_REG & CY_SYS_CLK_LFCLK_SEL_MASK;
        return (lfclkSource);
    }
#endif /* (CY_IP_WCO) */


/*******************************************************************************
* Function Name: CySysClkSetLfclkSource
********************************************************************************
*
* Summary:
*  Sets the clock source for the LFCLK clock.
*
*  The switch between LFCLK sources must be done between the positive edges of
*  LFCLK, because the glitch risk is around the LFCLK positive edge. To ensure
*  that the switch can be done safely, the WDT counter value is read until it
*  changes.
*
*  That means that the positive edge just finished and the switch is performed.
*  The enabled WDT counter is used for that purpose. If no counters are enabled,
*  counter 0 is enabled. And after the LFCLK source is switched, counter 0
*  configuration is restored.
*
*  The function is applicable only for PSoC 4100-BL and PSoC 4200-BL.
*
* Parameters:
*  source: One of the available LFCLK sources.
*   CY_SYS_CLK_LFCLK_SRC_ILO    Internal Low Frequency (32 kHz) Oscillator (ILO)
*   CY_SYS_CLK_LFCLK_SRC_WCO    Low Frequency Watch Crystal Oscillator (WCO)
*
* Return:
*  None
*
* Side Effects:
*  This function has no effect if WDT is locked (CySysWdtLock() is
*  called). Call CySysWdtUnlock() to unlock WDT.
*
*  Both the current source and the new source must be running and stable before
*  calling this function.
*
*  Changing the LFCLK clock source may change the LFCLK clock frequency and
*  affect the functionality that uses this clock. For example, watchdog timer
*  "uses this clock" or "this clock uses" (WDT) is clocked by LFCLK.
*
*******************************************************************************/
#if (CY_IP_WCO)
    void CySysClkSetLfclkSource(uint32 source)
    {
        uint8  interruptState;

        if (CySysClkGetLfclkSource() != source)
        {
            interruptState = CyEnterCriticalSection();

            CySysClkLfclkPosedgeCatch();

            CY_SYS_WDT_CONFIG_REG = (CY_SYS_WDT_CONFIG_REG & (uint32)(~CY_SYS_CLK_LFCLK_SEL_MASK)) |
                                    (source & CY_SYS_CLK_LFCLK_SEL_MASK);

            CySysClkLfclkPosedgeRestore();

            CyExitCriticalSection(interruptState);
        }
    }
#endif /* (CY_IP_WCO) */


#if (CY_IP_WCO)
    /*******************************************************************************
    * Function Name: CySysClkWcoStart
    ********************************************************************************
    *
    * Summary:
    *  Enables Watch Crystal Oscillator (WCO). WCO is used as a source for
    *  LFCLK.  Similar to ILO, WCO is also available in all modes except Hibernate
    *  and Stop modes.
    *
    *  WCO is always enabled in High Power Mode (HPM). Refer to the device
    *  datasheet for the  WCO startup time. Once WCO becomes stable it can be
    *  switched to Low Power Mode (LPM). Note that oscillator can be unstable
    *  during a switch and hence its output should not be used at that moment.
    *
    *  The CySysClkWcoSetPowerMode() function configures the WCO power mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysClkWcoStart(void)
    {
        CySysClkWcoSetHighPowerMode();
        CY_SYS_CLK_WCO_CONFIG_REG |= CY_SYS_CLK_WCO_CONFIG_LPM_ENABLE;
    }


    /*******************************************************************************
    * Function Name: CySysClkWcoStop
    ********************************************************************************
    *
    * Summary:
    *  Disables the 32KHz Crystal Oscillator.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void  CySysClkWcoStop(void)
    {
        uint8  interruptState;

        if (0u != CySysClkWcoEnabled())
        {

            if (CY_SYS_CLK_LFCLK_SRC_WCO == CySysClkGetLfclkSource())
            {
                interruptState = CyEnterCriticalSection();
                CySysClkLfclkPosedgeCatch();
                CY_SYS_CLK_WCO_CONFIG_REG &= (uint32) ~CY_SYS_CLK_WCO_CONFIG_LPM_ENABLE;
                CySysClkLfclkPosedgeRestore();
                CyExitCriticalSection(interruptState);
            }
            else /* Safe to disable - shortened pulse does not impact peripheral */
            {
                CY_SYS_CLK_WCO_CONFIG_REG &= (uint32) ~CY_SYS_CLK_WCO_CONFIG_LPM_ENABLE;
            }
        } /* Otherwise do nothing. WCO configuration cannot be changed. */
    }


    /*******************************************************************************
    * Function Name: CySysClkWcoEnabled
    ********************************************************************************
    *
    * Summary:
    *  Reports the WCO enable state.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  1 if WCO is enabled, and 0 if WCO is disabled.
    *
    *******************************************************************************/
    uint32 CySysClkWcoEnabled(void)
    {
        return ((0u != (CY_SYS_CLK_WCO_CONFIG_REG & (uint32)(CY_SYS_CLK_WCO_CONFIG_LPM_ENABLE))) ?
                (uint32) 1u :
                (uint32) 0u);
    }


    /*******************************************************************************
    * Function Name: CySysClkWcoSetPowerMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the power mode for the 32 KHz WCO.
    *
    * Parameters:
    *  uint32 mode:
    *   CY_SYS_CLK_WCO_HPM  - The High Power mode
    *   CY_SYS_CLK_WCO_LPM  - The Low Power mode(not applicable for
    *                         PSoC 4100M / PSoC 4200M devices)
    *
    * Return:
    *  A previous power mode. The same as the parameters.
    *
    * Note:
    *  The WCO Low power mode is not applicable for the PSoC 4100M/PSoC 4200M
    *  devices.
    *
    *******************************************************************************/
    uint32 CySysClkWcoSetPowerMode(uint32 mode)
    {
        uint32 status;

        status = CY_SYS_CLK_WCO_CONFIG_REG & CY_SYS_CLK_WCO_CONFIG_LPM_EN;

        switch(mode)
        {
        case CY_SYS_CLK_WCO_HPM:
                CySysClkWcoSetHighPowerMode();
            break;

        #if(!CY_PSOC4_4100M && !CY_PSOC4_4200M)
            case CY_SYS_CLK_WCO_LPM:
                    CySysClkWcoSetLowPowerMode();
                break;
        #endif /* (!CY_PSOC4_4100M && !CY_PSOC4_4200M) */

        default:
            CYASSERT(0u != 0u);
            break;
        }

        return (status);
    }

#endif  /* (CY_IP_WCO) */


#if(CY_IP_SRSSV2)


    /*******************************************************************************
    * Function Name: CySysWdtLock
    ********************************************************************************
    *
    * Summary:
    *  Locks out configuration changes to the Watchdog timer registers and ILO
    *  configuration register.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side effects:
    *  After this function is called, ILO clock can't be disabled until
    *  CySysWdtUnlock() is called.
    *
    *******************************************************************************/
    void CySysWdtLock(void)
    {
        uint8 interruptState;
        interruptState = CyEnterCriticalSection();

        CY_SYS_CLK_SELECT_REG = (CY_SYS_CLK_SELECT_REG & (uint32)(~CY_SYS_WDT_CLK_LOCK_BITS_MASK)) |
                 CY_SYS_WDT_CLK_LOCK_BITS_MASK;

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysWdtLocked
    ********************************************************************************
    *
    * Summary:
    *  Reports the WDT lock state.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  1 - WDT is locked, and 0 - WDT is unlocked.
    *
    *******************************************************************************/
    static uint32 CySysWdtLocked(void)
    {
        /* Prohibits writing to WDT registers and ILO/WCO registers when not equal 0 */
        return ((0u != (CY_SYS_CLK_SELECT_REG & (uint32)(CY_SYS_WDT_CLK_LOCK_BITS_MASK))) ? (uint32) 1u : (uint32) 0u);
    }


    /*******************************************************************************
    * Function Name: CySysWdtUnlock
    ********************************************************************************
    *
    * Summary:
    *  Unlocks the Watchdog Timer configuration register.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysWdtUnlock(void)
    {
        uint8 interruptState;
        interruptState = CyEnterCriticalSection();

        /* Removing WDT lock requires two writes */
        CY_SYS_CLK_SELECT_REG = ((CY_SYS_CLK_SELECT_REG & (uint32)(~CY_SYS_WDT_CLK_LOCK_BITS_MASK)) |
                CY_SYS_WDT_CLK_LOCK_BIT0);

        CY_SYS_CLK_SELECT_REG = ((CY_SYS_CLK_SELECT_REG & (uint32)(~CY_SYS_WDT_CLK_LOCK_BITS_MASK)) |
                CY_SYS_WDT_CLK_LOCK_BIT1);

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetEnabledStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the enabled status of one of the three WDT counters.
    *
    * Parameters:
    *  counterNum: Valid range [0-2].  the number of the WDT counter.
    *
    * Return:
    *  The status of the WDT counter:
    *   0 - The counter is disabled.
    *   1 - The counter is enabled.
    *
    * Side Effects:
    *  This function returns an actual WDT counter status from the status register. It may
    *  take up to 3 LFCLK cycles for the WDT status register to contain actual data
    *  after the WDT counter is enabled.
    *
    *
    *******************************************************************************/
    uint32 CySysWdtGetEnabledStatus(uint32 counterNum)
    {
        CYASSERT(counterNum < CY_SYS_WDT_COUNTERS_MAX);
        return ((CY_SYS_WDT_CONTROL_REG >> ((CY_SYS_WDT_CNT_SHIFT * counterNum) + CY_SYS_WDT_CNT_STTS_SHIFT)) & 0x01u);
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetMode
    ********************************************************************************
    *
    * Summary:
    *   Writes the mode of one of the three WDT counters.
    *
    * Parameters:
    *   counterNum: Valid range [0-2].  The number of the WDT counter.
    *   mode:       Mode of operation for the counter.
    *       Define                     Mode
    *        CY_SYS_WDT_MODE_NONE       Free running
    *        CY_SYS_WDT_MODE_INT        The interrupt generated on match for counter 0
    *                                   and 1, and on bit toggle for counter 2.
    *        CY_SYS_WDT_MODE_RESET      Reset on match (valid for counter 0 and 1
    *                                   only)
    *        CY_SYS_WDT_MODE_INT_RESET  Generate an interrupt.  Generate a reset on
    *                                   the 3rd non-handled interrupt.
    *                                   (valid for counter 0 and 1 only)
    * Return:
    *   None.
    *
    * Side Effects:
    *   WDT counter counterNum should be disabled to set a mode. Otherwise, this
    *   function call has no effect. If the specified counter is enabled,
    *   call the CySysWdtDisable() function with the corresponding parameter to
    *   disable the specified counter and wait for it to stop.
    *
    *******************************************************************************/
    void CySysWdtSetMode(uint32 counterNum, uint32 mode)
    {
        uint32 configRegValue;

        CYASSERT(counterNum < CY_SYS_WDT_COUNTERS_MAX);

        if(0u == CySysWdtGetEnabledStatus(counterNum))
        {
            configRegValue = CY_SYS_WDT_CONFIG_REG &
                                (uint32)~((uint32)(CY_SYS_WDT_MODE_MASK << (counterNum * CY_SYS_WDT_CNT_SHIFT)));
            configRegValue |= (uint32)((mode & CY_SYS_WDT_MODE_MASK) << (counterNum * CY_SYS_WDT_CNT_SHIFT));
            CY_SYS_WDT_CONFIG_REG = configRegValue;
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetMode
    ********************************************************************************
    *
    * Summary:
    *  Reads the mode of one of the three WDT counters.
    *
    * Parameters:
    *  counterNum: Valid range [0-2].  The number of the WDT counter.
    *
    * Return:
    *  The mode of the counter.  The same enumerated values as the mode parameter used in
    *  CySysWdtSetMode().
    *
    *******************************************************************************/
    uint32 CySysWdtGetMode(uint32 counterNum)
    {
        return ((CY_SYS_WDT_CONFIG_REG >> (counterNum * CY_SYS_WDT_CNT_SHIFT)) & CY_SYS_WDT_MODE_MASK);
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetClearOnMatch
    ********************************************************************************
    *
    * Summary:
    *  Configures the WDT counter "clear on match" setting.  If configured to "clear
    *  on match", the counter counts from 0 to MatchValue giving it a
    *  period of (MatchValue + 1).
    *
    * Parameters:
    *  counterNum:
    *   Valid range [0-1].  The number of the WDT counter.  The match values are not
    *   supported by counter 2.
    *
    * enable:
    *   0 to disable, 1 to enable
    *
    * Return:
    *   None.
    *
    * Side Effects:
    *   WDT counter counterNum should be disabled. Otherwise this function call
    *   has no effect. If the specified counter is enabled, call the CySysWdtDisable()
    *   function with the corresponding parameter to disable the specified counter and
    *   wait for it to stop. This may take up to three LFCLK cycles.
    *
    *******************************************************************************/
    void CySysWdtSetClearOnMatch(uint32 counterNum, uint32 enable)
    {
        uint32 configRegValue;

        CYASSERT((counterNum == CY_SYS_WDT_COUNTER0) ||
                 (counterNum == CY_SYS_WDT_COUNTER1));

        if(0u == CySysWdtGetEnabledStatus(counterNum))
        {
            configRegValue = CY_SYS_WDT_CONFIG_REG &
                (uint32)~((uint32)((uint32)1u << ((counterNum * CY_SYS_WDT_CNT_SHIFT) + CY_SYS_WDT_CNT_MATCH_CLR_SHIFT)));

            configRegValue
                |= (uint32)(enable << ((counterNum * CY_SYS_WDT_CNT_SHIFT) + CY_SYS_WDT_CNT_MATCH_CLR_SHIFT));

            CY_SYS_WDT_CONFIG_REG = configRegValue;
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetClearOnMatch
    ********************************************************************************
    *
    * Summary:
    *  Reads the "clear on match" setting for the specified counter.
    *
    * Parameters:
    *   counterNum: Valid range [0-1].  The number of the WDT counter.  The match values are
    *               not supported by counter 2.
    *
    * Return:
    *   The "clear on match" status: 1 if enabled, 0 if disabled
    *
    *******************************************************************************/
    uint32 CySysWdtGetClearOnMatch(uint32 counterNum)
    {
        CYASSERT((counterNum == CY_SYS_WDT_COUNTER0) ||
                 (counterNum == CY_SYS_WDT_COUNTER1));

        return (uint32)((CY_SYS_WDT_CONFIG_REG >>
                        ((counterNum * CY_SYS_WDT_CNT_SHIFT) + CY_SYS_WDT_CNT_MATCH_CLR_SHIFT)) & 0x01u);
    }


    /*******************************************************************************
    * Function Name: CySysWdtEnable
    ********************************************************************************
    *
    * Summary:
    *  Enables the specified WDT counters.  All the counters specified in the mask
    *  are enabled.
    *
    * Parameters:
    *  counterMask: The mask of all counters to enable.
    *       Define                       Counter
    *      CY_SYS_WDT_COUNTER0_MASK      0
    *      CY_SYS_WDT_COUNTER1_MASK      1
    *      CY_SYS_WDT_COUNTER2_MASK      2
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  Enabling or disabling WDT requires 3 LFCLK cycles to come into effect.
    *  Therefore, the WDT enable state must not be changed more than once in
    *  that period.
    *
    *  After WDT is enabled, it is illegal to write WDT configuration (WDT_CONFIG)
    *  and control (WDT_CONTROL) registers. This means that all WDT functions that
    *  contain 'write' in the name (with the exception of CySysWdtSetMatch()
    *  function) are illegal to call once WDT enabled.
    *
    *  PSoC 4100 / PSoC 4200:
    *  This function enables ILO.
    *
    *  PSoC 4100-BL / PSoC 4200-BL and PSoC 4100M / PSoC 4200M:
    *  LFLCK should be configured before calling this function. The desired
    *  source should be enabled and configured to be the source for LFCLK.
    *
    *******************************************************************************/
    void CySysWdtEnable(uint32 counterMask)
    {
        #if (!CY_IP_WCO)
            CySysClkIloStart();
        #endif /* (!CY_IP_WCO) */

        CY_SYS_WDT_CONTROL_REG |= counterMask;

        if(0u != (counterMask & CY_SYS_WDT_COUNTER0_MASK))
        {
            while (0u == CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER0))
            {
                /* Wait for changes to come into effect */
            }
        }

        if(0u != (counterMask & CY_SYS_WDT_COUNTER1_MASK))
        {
            while (0u == CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER1))
            {
                /* Wait for changes to come into effect */
            }
        }

        if(0u != (counterMask & CY_SYS_WDT_COUNTER2_MASK))
        {
            while (0u == CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER2))
            {
                /* Wait for changes to come into effect */
            }
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtDisable
    ********************************************************************************
    *
    * Summary:
    *  Disables the specified WDT counters. All the counters specified in the mask
    *  are disabled. The function waits for the changes to come into effect.
    *
    * Parameters:
    *  uint32 counterMask: The mask of all counters to disable
    *    Define                       Counter
    *   CY_SYS_WDT_COUNTER0_MASK      0
    *   CY_SYS_WDT_COUNTER1_MASK      1
    *   CY_SYS_WDT_COUNTER2_MASK      2
    *
    * Return:
    *   None.
    *
    *******************************************************************************/
    void CySysWdtDisable(uint32 counterMask)
    {
        if (0uL == CySysWdtLocked())
        {
            CY_SYS_WDT_CONTROL_REG &= ~counterMask;

            if(0u != (counterMask & CY_SYS_WDT_COUNTER0_MASK))
            {
                while (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER0))
                {
                    /* Wait for changes to come into effect */
                }
            }

            if(0u != (counterMask & CY_SYS_WDT_COUNTER1_MASK))
            {
                while (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER1))
                {
                    /* Wait for changes to come into effect */
                }
            }

            if(0u != (counterMask & CY_SYS_WDT_COUNTER2_MASK))
            {
                while (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER2))
                {
                    /* Wait for changes to come into effect */
                }
            }
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetCascade
    ********************************************************************************
    *
    * Summary:
    *   Writes the two WDT cascade values based on the combination of mask values
    *   specified.
    *
    * Parameters:
    *   cascadeMask: The mask value used to set or clear the cascade values.
    *   Define                     Cascade
    *   CY_SYS_WDT_CASCADE_NONE    Neither
    *   CY_SYS_WDT_CASCADE_01      Cascade 01
    *   CY_SYS_WDT_CASCADE_12      Cascade 12
    *
    *   To set both cascade modes, two defines should be ORed:
    *   (CY_SYS_WDT_CASCADE_01 | CY_SYS_WDT_CASCADE_12)
    *
    * Return:
    *   None.
    *
    * Side effects:
    *   If only one cascade mask is specified, the second cascade is disabled.
    *   To set both cascade modes, two defines should be ORed:
    *    (CY_SYS_WDT_CASCADE_01 | CY_SYS_WDT_CASCADE_12).
    *
    *   WDT counters that are part of the specified cascade should be disabled.
    *   Otherwise this function call has no effect. If the specified
    *   counter is enabled, call CySysWdtDisable() function with the corresponding
    *   parameter to disable the specified counter and wait for it to stop. This may
    *   take up to 3 LFCLK cycles.
    *
    *******************************************************************************/
    void CySysWdtSetCascade(uint32 cascadeMask)
    {
        uint32 configRegValue;
        uint32 countersEnableStatus;

        countersEnableStatus = CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER0) |
                            CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER1) |
                            CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER2);

        if (0u == countersEnableStatus)
        {
            configRegValue = CY_SYS_WDT_CONFIG_REG;
            configRegValue &= ((uint32)(~(CY_SYS_WDT_CASCADE_01|CY_SYS_WDT_CASCADE_12)));
            configRegValue |= cascadeMask;
            CY_SYS_WDT_CONFIG_REG = configRegValue;
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetCascade
    ********************************************************************************
    *
    * Summary:
    *   Reads the two WDT cascade values returning a mask of the bits set.
    *
    * Parameters:
    *   None.
    *
    * Return:
    *   The mask of the cascade values set.
    *   Define                     Cascade
    *   CY_SYS_WDT_CASCADE_NONE    Neither
    *   CY_SYS_WDT_CASCADE_01      Cascade 01
    *   CY_SYS_WDT_CASCADE_12      Cascade 12
    *
    *******************************************************************************/
    uint32 CySysWdtGetCascade(void)
    {
        return (CY_SYS_WDT_CONFIG_REG & (CY_SYS_WDT_CASCADE_01 | CY_SYS_WDT_CASCADE_12));
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetMatch
    ********************************************************************************
    *
    * Summary:
    *  Configures the WDT counter match comparison value.
    *
    * Parameters:
    *  counterNum:
    *   Valid range [0-1]. The number of the WDT counter. The match values are not
    *   supported by counter 2.
    *
    *  match:
    *   Valid range [0-65535]. The value to be used to match against the counter.
    *
    * Return:
    *   None.
    *
    *******************************************************************************/
    void CySysWdtSetMatch(uint32 counterNum, uint32 match)
    {
        uint32 regValue;

        CYASSERT((counterNum == CY_SYS_WDT_COUNTER0) ||
                 (counterNum == CY_SYS_WDT_COUNTER1));

        /* Wait for previous changes to come into effect */
        CyDelayUs(CY_SYS_WDT_3LFCLK_DELAY_US);

        regValue = CY_SYS_WDT_MATCH_REG;
        regValue &= (uint32)~((uint32)(CY_SYS_WDT_LOWER_16BITS_MASK << (counterNum * CY_SYS_WDT_CNT_MATCH_SHIFT)));
        CY_SYS_WDT_MATCH_REG = (regValue | (match << (counterNum * CY_SYS_WDT_CNT_MATCH_SHIFT)));

        /* Make sure match synchronization has started */
        CyDelayUs(CY_SYS_WDT_1LFCLK_DELAY_US);
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetToggleBit
    ********************************************************************************
    *
    * Summary:
    *  Configures which bit in WDT counter 2 to monitor for a toggle. When that
    *  bit toggles, an interrupt is generated if the mode for counter 2 has
    *  enabled interrupts.
    *
    * Parameters:
    *  bit:
    *   Valid range [0-31].  Counter 2 bit to monitor for a toggle.
    *
    * Return:
    *   None.
    *
    * Side effects:
    *   WDT Counter 2 should be disabled. Otherwise this function call has no
    *   effect.
    *
    *   If the specified counter is enabled, call the CySysWdtDisable() function with
    *   the corresponding parameter to disable the specified counter and wait for it to
    *   stop. This may take up to 3 LFCLK cycles.
    *
    *******************************************************************************/
    void CySysWdtSetToggleBit(uint32 bits)
    {
        uint32 configRegValue;

        if (0u == CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER2))
        {
            configRegValue = CY_SYS_WDT_CONFIG_REG;
            configRegValue &= (uint32)(~((uint32)(CY_SYS_WDT_CONFIG_BITS2_MASK << CY_SYS_WDT_CONFIG_BITS2_POS)));
            configRegValue |= ((bits & CY_SYS_WDT_CONFIG_BITS2_MASK) << CY_SYS_WDT_CONFIG_BITS2_POS);
            CY_SYS_WDT_CONFIG_REG = configRegValue;
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetToggleBit
    ********************************************************************************
    *
    * Summary:
    *  Reads which bit in WDT counter 2 is monitored for a toggle.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  The bit that is monitored (range of 0 to 31)
    *
    *******************************************************************************/
    uint32 CySysWdtGetToggleBit(void)
    {
        return ((CY_SYS_WDT_CONFIG_REG >> CY_SYS_WDT_CONFIG_BITS2_POS) & CY_SYS_WDT_CONFIG_BITS2_MASK);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetMatch
    ********************************************************************************
    *
    * Summary:
    *  Reads the WDT counter match comparison value.
    *
    * Parameters:
    *  counterNum: Valid range [0-1].  The number of the WDT counter.  The match values
    *               are not supported by counter 2.
    *
    * Return:
    *  A 16-bit match value.
    *
    *******************************************************************************/
    uint32 CySysWdtGetMatch(uint32 counterNum)
    {
        CYASSERT((counterNum == CY_SYS_WDT_COUNTER0) ||
                 (counterNum == CY_SYS_WDT_COUNTER1));

        return ((uint32)(CY_SYS_WDT_MATCH_REG >> (counterNum * CY_SYS_WDT_CNT_MATCH_SHIFT)) & CY_SYS_WDT_LOWER_16BITS_MASK);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetCount
    ********************************************************************************
    *
    * Summary:
    *  Reads the current WDT counter value.
    *
    * Parameters:
    *  counterNum: Valid range [0-2].  The number of the WDT counter.
    *
    * Return:
    *  A live counter value.  Counter 0 and 1 are 16 bit counters and counter
    *  2 is a 32 bit counter.
    *
    *******************************************************************************/
    uint32 CySysWdtGetCount(uint32 counterNum)
    {
        uint32 regValue = 0u;

        switch(counterNum)
        {
            /* WDT Counter 0 */
            case 0u:
                regValue = CY_SYS_WDT_CTRLOW_REG & CY_SYS_WDT_LOWER_16BITS_MASK;
            break;

            /* WDT Counter 1 */
            case 1u:
                regValue = (CY_SYS_WDT_CTRLOW_REG >> CY_SYS_WDT_CNT_MATCH_SHIFT) & CY_SYS_WDT_LOWER_16BITS_MASK;
            break;

            /* WDT Counter 2 */
            case 2u:
                regValue = CY_SYS_WDT_CTRHIGH_REG;
            break;

            default:
                CYASSERT(0u != 0u);
            break;
        }

        return (regValue);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetInterruptSource
    ********************************************************************************
    *
    * Summary:
    *   Reads a mask containing all the WDT counters interrupts that are currently
    *   set by the hardware, if a corresponding mode is selected.
    *
    * Parameters:
    *   None.
    *
    * Return:
    *   The mask of interrupts set.
    *   Define                    Counter
    *   CY_SYS_WDT_COUNTER0_INT    0
    *   CY_SYS_WDT_COUNTER1_INT    1
    *   CY_SYS_WDT_COUNTER2_INT    2
    *
    *******************************************************************************/
    uint32 CySysWdtGetInterruptSource(void)
    {
        return (CY_SYS_WDT_CONTROL_REG & (CY_SYS_WDT_COUNTER0_INT | CY_SYS_WDT_COUNTER1_INT | CY_SYS_WDT_COUNTER2_INT));
    }


    /*******************************************************************************
    * Function Name: CySysWdtClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *   Clears all the WDT counter interrupts set in the mask. Calling this function
    *   also prevents from Reset when the counter mode is set to generate
    *   3 interrupts and then the device resets.
    *
    *   All the WDT interrupts are to be cleared by the firmware, otherwise
    *   interrupts are generated continuously.
    *
    * Parameters:
    *   counterMask: The mask of all the counters to enable.
    *   Define                    Counter
    *   CY_SYS_WDT_COUNTER0_INT    0
    *   CY_SYS_WDT_COUNTER1_INT    1
    *   CY_SYS_WDT_COUNTER2_INT    2
    *
    * Return:
    *   None
    *
    * Side effects:
    *   This function temporary removes the watchdog lock, if it was set, and
    *   restores the lock state after cleaning the WDT interrupts that are set in
    *   a mask.
    *
    *******************************************************************************/
    void CySysWdtClearInterrupt(uint32 counterMask)
    {
        uint8 interruptState;
        uint32 wdtLockState;

        interruptState = CyEnterCriticalSection();

        if (0u != CySysWdtLocked())
        {
            wdtLockState = 1u;
            CySysWdtUnlock();
        }
        else
        {
            wdtLockState = 0u;
        }

        /* Set new WDT control register value */
        counterMask &= (CY_SYS_WDT_COUNTER0_INT |
                        CY_SYS_WDT_COUNTER1_INT |
                        CY_SYS_WDT_COUNTER2_INT);

        CY_SYS_WDT_CONTROL_REG = counterMask | (CY_SYS_WDT_CONTROL_REG & ~(CY_SYS_WDT_COUNTER0_INT |
                                                                           CY_SYS_WDT_COUNTER1_INT |
                                                                           CY_SYS_WDT_COUNTER2_INT));

        /* Read the CY_SYS_WDT_CONTROL_REG to clear the interrupt request.
         * Cypress ID #207093, #206231
        */
        (void)CY_SYS_WDT_CONTROL_REG;

        if (1u == wdtLockState)
        {
            CySysWdtLock();
        }

        CyExitCriticalSection(interruptState);
    }


    /*******************************************************************************
    * Function Name: CySysWdtResetCounters
    ********************************************************************************
    *
    * Summary:
    *  Resets all the WDT counters set in the mask.
    *
    * Parameters:
    *  counterMask: The mask of all the counters to reset.
    *   Define                       Counter
    *   CY_SYS_WDT_COUNTER0_RESET    0
    *   CY_SYS_WDT_COUNTER1_RESET    1
    *   CY_SYS_WDT_COUNTER2_RESET    2
    *
    * Return:
    *   None
    *
    * Side effects:
    *   This function does not reset counter values if the Watchdog is locked.
    *   This function waits while corresponding counters will be reset. This may
    *   take up to 3 LFCLK cycles.
    *   The LFCLK source must be enabled. Otherwise, the function will never exit.
    *
    *******************************************************************************/
    void CySysWdtResetCounters(uint32 countersMask)
    {
        /* Set new WDT reset value */
        CY_SYS_WDT_CONTROL_REG |= (countersMask & CY_SYS_WDT_COUNTERS_RESET);

        while (0uL != (CY_SYS_WDT_CONTROL_REG & CY_SYS_WDT_COUNTERS_RESET))
        {
            /* Wait for reset to come into effect */
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetInterruptCallback
    ********************************************************************************
    *
    * Summary:
    *  Sets the ISR callback function for the particular WDT counter.
    *  These functions are called on the WDT interrupt.
    *
    * Parameters:
    *  counterNum : The number of the WDT counter.
    *  function   : The pointer to the callback function.
    *
    * Return:
    *  The pointer to the previous callback function.
    *  NULL is returned if the specified address is not set.
    *
    *******************************************************************************/
    cyWdtCallback CySysWdtSetInterruptCallback(uint32 counterNum, cyWdtCallback function)
    {
        cyWdtCallback prevCallback = (void *)0;

        if(counterNum < CY_WDT_NUM_OF_WDT)
        {
            prevCallback = cySysWdtCallback[counterNum];
            cySysWdtCallback[counterNum] = function;
        }
        else
        {
            CYASSERT(0u != 0u);
        }

        return((cyWdtCallback)prevCallback);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetInterruptCallback
    ********************************************************************************
    *
    * Summary:
    *  Gets the ISR callback function for the particular WDT counter.
    *
    * Parameters:
    *  counterNum : The number of the WDT counter.
    *
    * Return:
    *  The pointer to the callback function registered for a particular WDT by
    *  a particular address that are passed through arguments.
    *
    *******************************************************************************/
    cyWdtCallback CySysWdtGetInterruptCallback(uint32 counterNum)
    {
        cyWdtCallback retCallback = (void *)0;

        if(counterNum < CY_WDT_NUM_OF_WDT)
        {
            retCallback = (cyWdtCallback)cySysWdtCallback[counterNum];
        }
        else
        {
            CYASSERT(0u != 0u);
        }

        return(retCallback);
    }


    /*******************************************************************************
    * Function Name: CySysWdtEnableCounterIsr
    ********************************************************************************
    *
    * Summary:
    *  Enables the ISR callback servicing for the particular WDT counter
    *
    * Parameters:
    *  counterNum: Valid range [0-2].  The number of the WDT counter.
    *
    *******************************************************************************/
    void CySysWdtEnableCounterIsr(uint32 counterNum)
    {
        if(counterNum <= CY_SYS_WDT_COUNTER2)
        {
            disableServicedIsr &= ~counterIntMaskTbl[counterNum];
            wdtIsrMask |= counterIntMaskTbl[counterNum];
        }
        else
        {
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtDisableCounterIsr
    ********************************************************************************
    *
    * Summary:
    *  Disables the ISR callback servicing for the particular WDT counter
    *
    * Parameters:
    *  counterNum: Valid range [0-2].  The number of the WDT counter.
    *
    *******************************************************************************/
    void CySysWdtDisableCounterIsr(uint32 counterNum)
    {
        if(counterNum <= CY_SYS_WDT_COUNTER2)
        {
            wdtIsrMask &= ~counterIntMaskTbl[counterNum];
        }
        else
        {
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: CySysWdtIsr
    ********************************************************************************
    *
    * Summary:
    *  This is the handler of the WDT interrupt in CPU NVIC. The handler checks
    *  which WDT triggered in the interrupt and calls the respective callback
    *  functions configured by the user by using CySysWdtSetIsrCallback() API.
    *
    *  The order of the callback execution is incremental. Callback-0 is
    *  run as the first one and callback-2 is called as the last one.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function clears the WDT interrupt every time when it is called.
    *  Reset after the 3rd interrupt does not happen if this function is registered
    *  as the interrupt handler even if the "Watchdog with Interrupt" mode is
    *  selected on the "Low Frequency Clocks" tab.
    *
    *******************************************************************************/
    void CySysWdtIsr(void)
    {
        if(0u != (CY_SYS_WDT_COUNTER0_INT & CY_SYS_WDT_CONTROL_REG))
        {
            if(0u != (CY_SYS_WDT_COUNTER0_INT & wdtIsrMask))
            {
                wdtIsrMask &= ~(disableServicedIsr & CY_SYS_WDT_COUNTER0_INT);
                disableServicedIsr  &= ~CY_SYS_WDT_COUNTER0_INT;
                if(cySysWdtCallback[CY_SYS_WDT_COUNTER0] != (void *) 0)
                {
                    (void)(cySysWdtCallback[CY_SYS_WDT_COUNTER0])();
                }
            }
            CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
        }

        if(0u != (CY_SYS_WDT_COUNTER1_INT & CY_SYS_WDT_CONTROL_REG))
        {
            if(0u != (CY_SYS_WDT_COUNTER1_INT & wdtIsrMask))
            {
                wdtIsrMask &= ~(disableServicedIsr & CY_SYS_WDT_COUNTER1_INT);
                disableServicedIsr  &= ~CY_SYS_WDT_COUNTER1_INT;
                if(cySysWdtCallback[CY_SYS_WDT_COUNTER1] != (void *) 0)
                {
                    (void)(cySysWdtCallback[CY_SYS_WDT_COUNTER1])();
                }
            }
            CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);
        }

        if(0u != (CY_SYS_WDT_COUNTER2_INT & CY_SYS_WDT_CONTROL_REG))
        {
            if(0u != (CY_SYS_WDT_COUNTER2_INT & wdtIsrMask))
            {
                if(cySysWdtCallback[CY_SYS_WDT_COUNTER2] != (void *) 0)
                {
                    (void)(cySysWdtCallback[CY_SYS_WDT_COUNTER2])();
                }
            }
            CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER2_INT);
        }
    }


    /*******************************************************************************
    * Function Name: CySysTimerDelay
    ********************************************************************************
    *
    * Summary:
    *  The function implements the delay specified in the LFCLK clock ticks. The
    *  specified WDT counter should be configured as described below and started.
    *
    *  This function can operate in two modes: the "WAIT" and "INTERRUPT" modes. In
    *  the "WAIT" mode, the function waits for the specified number of ticks. In the
    *  "INTERRUPT" mode, the interrupt is generated after the specified number of
    *  ticks.
    *
    *  For the correct function operation, the "Clear On Match" option should be
    *  disabled for the specified WDT counter. Use CySysWdtSetClearOnMatch()
    *  function with the "enable" parameter equal to zero for the used WDT counter.
    *
    *  The corresponding WDT counter should be configured to match the selected
    *  mode: "Free running Timer" for the "WAIT" mode, and
    *  "Periodic Timer" / "Watchdog (w/Interrupt)" for the "INTERRUPT" mode.
    *
    *  This can be configured in two ways:
    *  - Through the DWR page. Open the "Clocks" tab, click the "Edit Clocks..."
    *    button, in the "Configure System Clocks" window click on the
    *    "Low Frequency Clocks" tab and choose the appropriate option for the used
    *    WDT counter.
    *
    *  - Through the CySysWdtSetMode() function. Call it with the appropriate “mode”
    *    parameter for the used WDT counter.
    *
    *  For the "INTERRUPT" mode, the recommended sequence is the following:
    *  - Call the CySysWdtDisableCounterIsr() function to disable servicing
    *    interrupts of the specified WDT counter.
    *
    *  - Call the CySysWdtSetInterruptCallback() function to register the callback
    *    function for the corresponding WDT counter.
    *
    *  - Call the CySysTimerDelay() function.
    *
    * Parameters:
    *  counterNum: Valid range [0-1]. The number of the WDT counter (WDT0 or WDT1).
    *  delayType : Defines the operation mode.
    *               CY_SYS_TIMER_WAIT       "WAIT" mode.
    *               CY_SYS_TIMER_INTERRUPT  "INTERRUPT" mode.
    *  delay:  The delay value in the LFCLK ticks (allowable range - 16-bit value).
    *
    * Return:
    *  None
    *
    * Side effects:
    *  In the "INTERRUPT" mode, this function enables ISR callback servicing
    *  from the corresponding WDT counter. Servicing of this ISR callback will be
    *  disabled after the expiration of the delay time.
    *
    *******************************************************************************/
    void CySysTimerDelay(uint32 counterNum, cy_sys_timer_delaytype_enum delayType, uint32 delay)
    {
        uint32 regValue;
        uint32 matchValue;

        if((counterNum < CY_SYS_WDT_COUNTER2) && (0uL == CySysWdtGetClearOnMatch(counterNum)) && (delay <= UINT16_MAX_VAL))
        {
            regValue   = CySysWdtGetCount(counterNum);
            matchValue = (regValue + delay) & (uint32)UINT16_MAX_VAL;

            CySysTimerDelayUntilMatch(counterNum, delayType, matchValue);
        }
        else
        {
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: CySysTimerDelayUntilMatch
    ********************************************************************************
    *
    * Summary:
    *  The function implements the delay specified as the number of LFCLK ticks
    *  between the specified WDT counter's current value and the "match" passed as
    *  the parameter to this function. The current WDT counter value can be obtained
    *  using the CySysWdtGetCount() function.
    *
    *  This function can operate in two modes: the "WAIT" and "INTERRUPT" mode. In
    *  the "WAIT" mode, the function waits while the used WDT counter value becomes
    *  equal to the match value. In the "INTERRUPT" mode, the interrupt is generated
    *  when the used WDT counter became equal to the "match" value.
    *
    *  For the correct function operation, the "Clear On Match" option should be
    *  disabled for the specified WDT counter. Use CySysWdtSetClearOnMatch()
    *  function with the "enable" parameter equal to zero for the used WDT counter.
    *
    *  The corresponding WDT counter should be configured to match the selected mode:
    *  "Free running Timer" for the "WAIT" mode, and "Periodic Timer" / "Watchdog
    *  (w/Interrupt)" for the "INTERRUPT" mode.
    *
    *  This can be configured in two ways:
    *  - Through the DWR page. Open the "Clocks" tab, click the "Edit Clocks..."
    *    button, in the "Configure System Clocks" window click on the
    *    "Low Frequency Clocks" tab and choose the appropriate option for the used
    *    WDT counter.
    *
    *  - Through the CySysWdtSetMode() function. Call it with the appropriate "mode"
    *    parameter for the used WDT counter.
    *
    *  For the "INTERRUPT" mode, the recommended sequence is the following:
    *  - Call the CySysWdtDisableCounterIsr() function to disable servicing
    *    interrupts of the specified WDT counter.
    *
    *  - Call the CySysWdtSetInterruptCallback() function to register the callback
    *    function for the corresponding WDT counter.
    *
    *  - Call the CySysTimerDelay() function.
    *
    * Parameters:
    *  counterNum: Valid range [0-1]. The number of the WDT counter (WDT0 or WDT1).
    *  delayType : Defines the operation mode.
    *               CY_SYS_TIMER_WAIT       "WAIT" mode.
    *               CY_SYS_TIMER_INTERRUPT  "INTERRUPT" mode.
    *  delay:  The delay value in the LFCLK ticks (allowable range - 16-bit value).
    *
    * Return:
    *  None
    *
    * Side effects:
    *  In the "INTERRUPT" mode, this function enables ISR callback servicing
    *  from the corresponding WDT counter. Servicing of this ISR callback will be
    *  disabled after the expiration of the delay time.
    *
    *******************************************************************************/
    void CySysTimerDelayUntilMatch(uint32 counterNum, cy_sys_timer_delaytype_enum delayType, uint32 match)
    {
        uint32 tmpValue;

        if((counterNum < CY_SYS_WDT_COUNTER2) && (0uL == CySysWdtGetClearOnMatch(counterNum)) && (match <= UINT16_MAX_VAL))
        {
            if(delayType == CY_SYS_TIMER_WAIT)
            {
                do
                {
                    tmpValue = CySysWdtGetCount(counterNum);
                }while(tmpValue > match);

                do
                {
                    tmpValue = CySysWdtGetCount(counterNum);
                }while(tmpValue < match);
            }
            else
            {
                tmpValue = counterIntMaskTbl[counterNum];
                CySysWdtSetMatch(counterNum, match);

                disableServicedIsr  |= tmpValue;
                wdtIsrMask |= tmpValue;
            }
        }
        else
        {
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: CySysWatchdogFeed
    ********************************************************************************
    *
    * Summary:
    *  Feeds the watchdog counter before it causes the device reset. Supported only
    *  for WDT0 and WDT1 in the "Watchdog" or "Watchdog w/ Interrupts" modes.
    *
    * Parameters:
    *  counterNum:    The number of the WDT counter.
    *
    * Return:
    *  None.
    *
    * Side effects:
    *  Clears the WDT counter in the "Watchdog" mode or clears the WDT interrupt in
    *  "Watchdog w/ Interrupts" mode. Does nothing in other modes.
    *
    *******************************************************************************/
    void CySysWatchdogFeed(uint32 counterNum)
    {
        if(counterNum == CY_SYS_WDT_COUNTER0)
        {
            if(CY_SYS_WDT_MODE_INT_RESET == CySysWdtGetMode(counterNum))
            {
                CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_MASK);
            }
            else if(CY_SYS_WDT_MODE_RESET == CySysWdtGetMode(counterNum))
            {
                CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
                CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_MASK);
            }
            else
            {
                /* Do nothing. */
            }
        }
        else if(counterNum == CY_SYS_WDT_COUNTER1)
        {
            if(CY_SYS_WDT_MODE_INT_RESET == CySysWdtGetMode(counterNum))
            {
                CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_MASK);
            }
            else if(CY_SYS_WDT_MODE_RESET == CySysWdtGetMode(counterNum))
            {
                CySysWdtResetCounters(CY_SYS_WDT_COUNTER1_RESET);
                CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_MASK);
            }
            else
            {
                /* Do nothing. */
            }
        }
        else
        {
            /* Do nothing. */
        }
    }


    /*******************************************************************************
    * Function Name: CySysClkLfclkPosedgeCatch
    ********************************************************************************
    *
    * Summary:
    *  Returns once the LFCLK positive edge occurred.
    *
    *  CySysClkLfclkPosedgeRestore() should be called after this function
    *  to restore the WDT configuration.
    *
    *  A pair of the CySysClkLfclkPosedgeCatch() and CySysClkLfclkPosedgeRestore()
    *  functions is expected to be called inside a critical section.
    *
    *  To ensure that the WDT counter value is read until it changes, the enabled
    *  WDT counter is used. If no counter is enabled, counter 0 is enabled.
    *  And after the LFCLK source is switched, the counter 0 configuration
    *  is restored.
    *
    *  Not applicable for the PSoC 4000 devices.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function has no effect if WDT is locked (CySysWdtLock() is
    *  called). Call CySysWdtUnlock() to unlock WDT.
    *
    *******************************************************************************/
    static void CySysClkLfclkPosedgeCatch(void)
    {
        uint32 firstCount;
        static uint32 lfclkPosedgeEnabledWdtCounter = 0u;

        if (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER0))
        {
            lfclkPosedgeEnabledWdtCounter = CY_SYS_WDT_COUNTER0;
        }
        else if (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER1))
        {
            lfclkPosedgeEnabledWdtCounter = CY_SYS_WDT_COUNTER1;
        }
        else if (0u != CySysWdtGetEnabledStatus(CY_SYS_WDT_COUNTER2))
        {
            lfclkPosedgeEnabledWdtCounter = CY_SYS_WDT_COUNTER2;
        }
        else /* All WDT counters are disabled */
        {
            /* Configure WDT counter # 0 */
            lfclkPosedgeWdtCounter0Enabled = 1u;
            lfclkPosedgeEnabledWdtCounter = CY_SYS_WDT_COUNTER0;

            lfclkPosedgeWdtCounter0Mode = CySysWdtGetMode(CY_SYS_WDT_COUNTER0);
            CySysWdtSetMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_NONE);
            CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
        }

        firstCount = CySysWdtGetCount(lfclkPosedgeEnabledWdtCounter);
        while (CySysWdtGetCount(lfclkPosedgeEnabledWdtCounter) == firstCount)
        {
            /* Wait for counter to increment */
        }
    }


    /*******************************************************************************
    * Function Name: CySysClkLfclkPosedgeRestore
    ********************************************************************************
    *
    * Summary:
    *  Restores the WDT configuration after a CySysClkLfclkPosedgeCatch() call.
    *
    *  A pair of the CySysClkLfclkPosedgeCatch() and CySysClkLfclkPosedgeRestore()
    *  functions is expected to be called inside a critical section.
    *
    *  Not applicable for the PSoC 4000 devices.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function has no effect if WDT is locked (CySysWdtLock() is
    *  called). Call CySysWdtUnlock() to unlock WDT.
    *
    *******************************************************************************/
    static void CySysClkLfclkPosedgeRestore(void)
    {
        if (lfclkPosedgeWdtCounter0Enabled != 0u)
        {
            /* Restore counter # 0 configuration and force its shutdown */
            CY_SYS_WDT_CONTROL_REG &= (uint32)(~CY_SYS_WDT_COUNTER0_MASK);
            CySysWdtSetMode(CY_SYS_WDT_COUNTER0, lfclkPosedgeWdtCounter0Mode);
            lfclkPosedgeWdtCounter0Enabled = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: CySysWdtGetEnabledStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the enabled status of the WDT counter.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  The status of the WDT counter:
    *   0 - counter is disabled
    *   1 - counter is enabled
    *
    *******************************************************************************/
    uint32 CySysWdtGetEnabledStatus(void)
    {
        return ((CY_SYS_WDT_DISABLE_KEY_REG == CY_SYS_WDT_KEY) ? (uint32) 0u : (uint32) 1u);
    }


    /*******************************************************************************
    * Function Name: CySysWdtEnable
    ********************************************************************************
    *
    * Summary:
    *  Enables watchdog timer reset generation. CySysWdtClearInterrupt()
    *  feeds the watchdog. Two unserviced interrupts lead to a system reset
    *  (i.e. at the third match).
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  ILO is enabled by the hardware once WDT is started.
    *
    *******************************************************************************/
    void CySysWdtEnable(void)
    {
        CY_SYS_WDT_DISABLE_KEY_REG = 0u;
    }


    /*******************************************************************************
    * Function Name: CySysWdtDisable
    ********************************************************************************
    *
    * Summary:
    *  Disables the WDT reset generation.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function unlocks the ENABLE bit in the CLK_ILO_CONFIG registers and
    *  enables the user to disable ILO.
    *
    *******************************************************************************/
    void CySysWdtDisable(void)
    {
        CY_SYS_WDT_DISABLE_KEY_REG = CY_SYS_WDT_KEY;
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetMatch
    ********************************************************************************
    *
    * Summary:
    *  Configures the WDT counter match comparison value.
    *
    * Parameters:
    *  match:
    *   Valid range [0-65535]. The value to be used to match against the counter.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysWdtSetMatch(uint32 match)
    {
        CY_SYS_WDT_MATCH_REG = (CY_SYS_WDT_MATCH_REG & (uint32)(~ (uint32)CY_SYS_WDT_MATCH_MASK)) | match;
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetMatch
    ********************************************************************************
    *
    * Summary:
    *  Reads the WDT counter match comparison value.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  The counter match value.
    *
    *******************************************************************************/
    uint32 CySysWdtGetMatch(void)
    {
        return (CY_SYS_WDT_MATCH_REG & CY_SYS_WDT_MATCH_MASK);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetCount
    ********************************************************************************
    *
    * Summary:
    *  Reads the current WDT counter value.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  A live counter value.
    *
    *******************************************************************************/
    uint32 CySysWdtGetCount(void)
    {
        return ((uint32)CY_SYS_WDT_COUNTER_REG);
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetIgnoreBits
    ********************************************************************************
    *
    * Summary:
    *  Configures the number of the MSB bits of the watchdog timer that are not
    *  checked against the match.
    *
    * Parameters:
    *  bitsNum:
    *   Valid range [0-15]. The umber of the MSB bits.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  The value of bitsNum controls the time-to-reset of the watchdog
    *  (which happens after 3 successive matches).
    *
    *******************************************************************************/
    void CySysWdtSetIgnoreBits(uint32 bitsNum)
    {
        bitsNum = ((uint32)(bitsNum << CY_SYS_WDT_IGNORE_BITS_SHIFT) & CY_SYS_WDT_IGNORE_BITS_MASK);
        CY_SYS_WDT_MATCH_REG = (CY_SYS_WDT_MATCH_REG & (uint32)(~CY_SYS_WDT_IGNORE_BITS_MASK)) | bitsNum;
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetIgnoreBits
    ********************************************************************************
    *
    * Summary:
    *  Reads the number of the  MSB bits of the watchdog timer that are not
    *  checked against the match.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  The number of the MSB bits.
    *
    *******************************************************************************/
    uint32 CySysWdtGetIgnoreBits(void)
    {
        return((uint32)((CY_SYS_WDT_MATCH_REG & CY_SYS_WDT_IGNORE_BITS_MASK) >> CY_SYS_WDT_IGNORE_BITS_SHIFT));
    }


    /*******************************************************************************
    * Function Name: CySysWdtClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Feeds the watchdog. Cleans the WDT match flag which is set every time the
    *  WDT counter reaches a WDT match value. Two unserviced interrupts lead
    *  to a system reset (i.e. at the third match).
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysWdtClearInterrupt(void)
    {
        CY_SYS_SRSS_INTR_REG |= CY_SYS_WDT_LOWER_BIT_MASK;
    }


    /*******************************************************************************
    * Function Name: CySysWdtMaskInterrupt
    ********************************************************************************
    *
    * Summary:
    *  After masking interrupts from WDT, they are not passed to CPU.
    *  This function does not disable WDT reset generation.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysWdtMaskInterrupt(void)
    {
        CY_SYS_SRSS_INTR_MASK_REG &= (uint32)(~ (uint32)CY_SYS_WDT_LOWER_BIT_MASK);
    }


    /*******************************************************************************
    * Function Name: CySysWdtUnmaskInterrupt
    ********************************************************************************
    *
    * Summary:
    *  After unmasking interrupts from WDT, they are passed to CPU.
    *  This function does not impact the reset generation.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CySysWdtUnmaskInterrupt(void)
    {
        CY_SYS_SRSS_INTR_MASK_REG |= CY_SYS_WDT_LOWER_BIT_MASK;
    }


    /*******************************************************************************
    * Function Name: CySysWdtSetIsrCallback
    ********************************************************************************
    *
    * Summary:
    *  Sets the ISR callback function for the particular WDT counter;
    *
    * Parameters:
    *  function  : The pointer to the callback function.
    *
    * Return:
    *  The pointer to a previous callback function.
    *
    *******************************************************************************/
    cyWdtCallback CySysWdtSetInterruptCallback(cyWdtCallback function)
    {
        cyWdtCallback prevCallback = (void *)0;

        prevCallback = cySysWdtCallback;
        cySysWdtCallback = function;

        return(prevCallback);
    }


    /*******************************************************************************
    * Function Name: CySysWdtGetIsrCallback
    ********************************************************************************
    *
    * Summary:
    *  Gets the ISR callback function for the particular WDT counter;
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  The pointer to the callback function registered for WDT.
    *
    *******************************************************************************/
    cyWdtCallback CySysWdtGetInterruptCallback(void)
    {
        return(cySysWdtCallback);
    }


    /*******************************************************************************
    * Function Name: CySysWdtIsr
    ********************************************************************************
    *
    * Summary:
    *  This is the handler of the WDT interrupt in CPU NVIC. The handler checks
    *  which WDT triggered in the interrupt and calls the respective callback
    *  functions configured by the user by using CySysWdtSetIsrCallback() API.
    *
    *  The order of the callback execution is incremental. Callback-0 is
    *  run as the first one and callback-2 is called as the last one.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function clears the WDT interrupt every time when it is called.
    *  Reset after the 3rd interrupt does not happen if this function is registered
    *  as the interrupt handler even if the "Watchdog with Interrupt" mode is
    *  selected on the "Low Frequency Clocks" tab.
    *
    *******************************************************************************/
    void CySysWdtIsr(void)
    {
        if(cySysWdtCallback != (void *) 0)
        {
            (void)(cySysWdtCallback)();
        }

        CySysWdtClearInterrupt();
    }

#endif /* (CY_IP_SRSSV2) */


/* [] END OF FILE */
