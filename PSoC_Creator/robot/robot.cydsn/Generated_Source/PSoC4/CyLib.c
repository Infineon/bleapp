/*******************************************************************************
* File Name: CyLib.c
* Version 5.20
*
*  Description:
*   Provides a system API for the clocking, interrupts, and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2010-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"

#if(CY_IP_SRSSV2 && CY_IP_FMLT)
    #include "CyFlash.h"
#endif /* (CY_IP_SRSSV2 && CY_IP_FMLT) */


/* Do not use these definitions directly in your application */
uint32 cydelayFreqHz  = CYDEV_BCLK__SYSCLK__HZ;
uint32 cydelayFreqKhz = (CYDEV_BCLK__SYSCLK__HZ + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;
uint8  cydelayFreqMhz = (uint8)((CYDEV_BCLK__SYSCLK__HZ + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
uint32 cydelay32kMs   = CY_DELAY_MS_OVERFLOW * ((CYDEV_BCLK__SYSCLK__HZ + CY_DELAY_1K_MINUS_1_THRESHOLD) /
                        CY_DELAY_1K_THRESHOLD);


static cySysTickCallback CySysTickCallbacks[CY_SYS_SYST_NUM_OF_CALLBACKS];
static void CySysTickServiceCallbacks(void);
#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    static uint32 CySysClkImoGetWcoLock(void);
#endif  /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */


/*******************************************************************************
* Indicates whether or not the SysTick has been initialized. The variable is
* initialized to 0 and set to 1 the first time CySysTickStart() is called.
*
* This allows the component to restart without reinitialization after the first
* call to the CySysTickStart() routine.
*
* If reinitialization of the SysTick is required, call CySysTickInit() before
* calling CySysTickStart(). Alternatively, the SysTick can be reinitialized by
* calling the CySysTickInit() and CySysTickEnable() functions.
*******************************************************************************/
uint32 CySysTickInitVar = 0u;


#if(CY_IP_SRSSV2)
        /* Conversion between CySysClkWriteImoFreq() parameter and register's value */
        const uint8 cyImoFreqMhz2Reg[CY_SYS_CLK_IMO_FREQ_TABLE_SIZE] = {
            /*  3 MHz */ 0x03u,  /*  4 MHz */ 0x04u,  /*  5 MHz */ 0x05u,  /*  6 MHz */ 0x06u,
            /*  7 MHz */ 0x07u,  /*  8 MHz */ 0x08u,  /*  9 MHz */ 0x09u,  /* 10 MHz */ 0x0Au,
            /* 11 MHz */ 0x0Bu,  /* 12 MHz */ 0x0Cu,  /* 13 MHz */ 0x0Eu,  /* 14 MHz */ 0x0Fu,
            /* 15 MHz */ 0x10u,  /* 16 MHz */ 0x11u,  /* 17 MHz */ 0x12u,  /* 18 MHz */ 0x13u,
            /* 19 MHz */ 0x14u,  /* 20 MHz */ 0x15u,  /* 21 MHz */ 0x16u,  /* 22 MHz */ 0x17u,
            /* 23 MHz */ 0x18u,  /* 24 MHz */ 0x19u,  /* 25 MHz */ 0x1Bu,  /* 26 MHz */ 0x1Cu,
            /* 27 MHz */ 0x1Du,  /* 28 MHz */ 0x1Eu,  /* 29 MHz */ 0x1Fu,  /* 30 MHz */ 0x20u,
            /* 31 MHz */ 0x21u,  /* 32 MHz */ 0x22u,  /* 33 MHz */ 0x23u,  /* 34 MHz */ 0x25u,
            /* 35 MHz */ 0x26u,  /* 36 MHz */ 0x27u,  /* 37 MHz */ 0x28u,  /* 38 MHz */ 0x29u,
            /* 39 MHz */ 0x2Au,  /* 40 MHz */ 0x2Bu,  /* 41 MHz */ 0x2Eu,  /* 42 MHz */ 0x2Fu,
            /* 43 MHz */ 0x30u,  /* 44 MHz */ 0x31u,  /* 45 MHz */ 0x32u,  /* 46 MHz */ 0x33u,
            /* 47 MHz */ 0x34u,  /* 48 MHz */ 0x35u };
#endif /* (CY_IP_SRSSV2) */


/*******************************************************************************
* Function Name: CySysClkImoStart
********************************************************************************
*
* Summary:
*  Enables the IMO.
*
*  For PSoC 4100M / PSoC 4200M devices, this function will also enable WCO lock
*  if selected in the Design Wide Resources tab.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkImoStart(void)
{
    CY_SYS_CLK_IMO_CONFIG_REG |= CY_SYS_CLK_IMO_CONFIG_ENABLE;

    #if (CY_PSOC4_4100M || CY_PSOC4_4200M)
        #if (CYDEV_IMO_TRIMMED_BY_WCO == 1u)
            CySysClkImoEnableWcoLock();
        #endif  /* (CYDEV_IMO_TRIMMED_BY_WCO == 1u) */
    #endif  /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */

}


/*******************************************************************************
* Function Name: CySysClkImoStop
********************************************************************************
*
* Summary:
*  Disables the IMO.
*
*  For PSoC 4100M/PSoC 4200M devices , this function will also disable WCO lock
*  if already enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysClkImoStop(void)
{
    #if (CY_PSOC4_4100M || CY_PSOC4_4200M)
        CySysClkImoDisableWcoLock();
    #endif  /* #if (CY_PSOC4_4100M || CY_PSOC4_4200M) */

    CY_SYS_CLK_IMO_CONFIG_REG &= ( uint32 ) ( ~( uint32 )CY_SYS_CLK_IMO_CONFIG_ENABLE);
}

#if (CY_PSOC4_4100M || CY_PSOC4_4200M)

    /*******************************************************************************
    * Function Name: CySysClkImoEnableWcoLock
    ********************************************************************************
    *
    * Summary:
    *  Enables the IMO to WCO lock feature. This function works only if the WCO is
    *  already enabled. If the WCO is not enabled then this function returns
    *  without enabling the lock feature.
    *
    *  This function is applicable for PSoC 4100M/PSoC 4200M devices only.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysClkImoEnableWcoLock(void)
    {
        uint32 i;
        uint32 freq = CY_SYS_CLK_IMO_MIN_FREQ_MHZ;
        uint8  interruptState;
        uint32 regTmp;
        volatile uint32 flashCtlReg;

        if (0u != CySysClkWcoEnabled())
        {
            interruptState = CyEnterCriticalSection();

            /* Get current IMO frequency based on the register value */
            for(i = 0u; i < CY_SYS_CLK_IMO_FREQ_TABLE_SIZE; i++)
            {
                if ((uint8) (CY_SYS_CLK_IMO_TRIM2_REG & CY_SYS_CLK_IMO_FREQ_BITS_MASK) == cyImoFreqMhz2Reg[i])
                {
                    freq = i + CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET;
                    break;
                }
            }

            if ((CY_SYS_CLK_IMO_TRIM4_REG & CY_SYS_CLK_IMO_TRIM4_GAIN_MASK) == 0u)
            {
			    CY_SYS_CLK_IMO_TRIM4_REG = (CY_SYS_CLK_IMO_TRIM4_REG & (uint32) ~CY_SYS_CLK_IMO_TRIM4_GAIN_MASK) |
			             				    CY_SYS_CLK_IMO_TRIM4_GAIN;
            }

            regTmp  = CY_SYS_CLK_WCO_DPLL_REG & ~(CY_SYS_CLK_WCO_DPLL_MULT_MASK |
                                                  CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN_MASK |
                                                  CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN_MASK);

            /* Set multiplier to determine IMO frequency in multiples of the WCO frequency */
            regTmp |= (CY_SYS_CLK_WCO_DPLL_MULT_VALUE(freq) & CY_SYS_CLK_WCO_DPLL_MULT_MASK);

            /* Set DPLL Loop Filter Integral and Proportional Gains Setting */
            regTmp |= (CY_SYS_CLK_WCO_CONFIG_DPLL_LF_IGAIN | CY_SYS_CLK_WCO_CONFIG_DPLL_LF_PGAIN);

            CY_SYS_CLK_WCO_DPLL_REG = regTmp;

            flashCtlReg = CY_FLASH_CTL_REG;
            CySysFlashSetWaitCycles(CY_SYS_CLK_IMO_MAX_FREQ_MHZ);
            CY_SYS_CLK_WCO_CONFIG_REG |= CY_SYS_CLK_WCO_CONFIG_DPLL_ENABLE;
            CyDelay(320u);
            CY_FLASH_CTL_REG = flashCtlReg;

            CyExitCriticalSection(interruptState);
        }
    }


    /*******************************************************************************
    * Function Name: CySysClkImoDisableWcoLock
    ********************************************************************************
    *
    * Summary:
    *  Disables the IMO to WCO lock feature.
    *
    *  This function is applicable for PSoC 4100M/PSoC 4200M devices only.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysClkImoDisableWcoLock(void)
    {
        CY_SYS_CLK_WCO_CONFIG_REG &= (uint32) ~CY_SYS_CLK_WCO_CONFIG_DPLL_ENABLE;
    }


    /*******************************************************************************
    * Function Name: CySysClkImoGetWcoLock
    ********************************************************************************
    *
    * Summary:
    *  Reports the IMO to WCO lock enable state.
    *
    *  This function is applicable for PSoC 4100M/PSoC 4200M devices only.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  1 if IMO to WCO lock is enabled, and 0 if IMO to WCO lock is disabled.
    *
    *******************************************************************************/
    static uint32 CySysClkImoGetWcoLock(void)
    {
        return ((0u != (CY_SYS_CLK_WCO_CONFIG_REG & CY_SYS_CLK_WCO_CONFIG_DPLL_ENABLE)) ?
                (uint32) 1u :
                (uint32) 0u);
    }

#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */


/*******************************************************************************
* Function Name: CySysClkWriteHfclkDirect
********************************************************************************
*
* Summary:
*  Selects the direct source for the HFCLK.
*
* Parameters:
*  clkSelect: One of the available HFCLK direct sources:
*   Define                    Source
*    CY_SYS_CLK_HFCLK_IMO     IMO
*    CY_SYS_CLK_HFCLK_EXTCLK  External clock pin
*    CY_SYS_CLK_HFCLK_ECO     External crystal oscillator
*                             (applicable only for PSoC 4100-BL / PSoC 4200-BL)
*
* Return:
*  None
*
* Side Effects:
*  The new source must be running and stable before calling this function.
*
*  PSoC 4000:
*  The SYSCLK has a maximum speed of 16 MHz, so HFCLK and SYSCLK dividers should
*  be selected in a way to not to exceed 16 MHz for the System clock.
*
*  If the SYSCLK clock frequency increases during device operation, call
*  CySysFlashSetWaitCycles() with the appropriate parameter to adjust the number
*  of clock cycles the cache will wait before sampling data comes back from
*  Flash. If the SYSCLK clock frequency decreases, you can call
*  CySysFlashSetWaitCycles() to improve the CPU performance. See
*  CySysFlashSetWaitCycles() description for more information.
*
*******************************************************************************/
void CySysClkWriteHfclkDirect(uint32 clkSelect)
{
    uint8  interruptState;

    interruptState = CyEnterCriticalSection();

    CY_SYS_CLK_SELECT_REG = ((CY_SYS_CLK_SELECT_REG & (( uint32 ) ~(( uint32 )CY_SYS_CLK_SELECT_DIRECT_SEL_MASK))) |
                        (( uint32 ) (clkSelect & ( uint32 )CY_SYS_CLK_SELECT_DIRECT_SEL_PARAM_MASK)));

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CySysClkWriteSysclkDiv
********************************************************************************
*
* Summary:
*  Selects the prescaler divide amount for SYSCLK from HFCLK.
*
* Parameters:
*  divider: Power of 2 prescaler selection
*
*   Define                        Description
*   CY_SYS_CLK_SYSCLK_DIV1        SYSCLK = HFCLK / 1
*   CY_SYS_CLK_SYSCLK_DIV2        SYSCLK = HFCLK / 2
*   CY_SYS_CLK_SYSCLK_DIV4        SYSCLK = HFCLK / 4
*   CY_SYS_CLK_SYSCLK_DIV8        SYSCLK = HFCLK / 8
*   CY_SYS_CLK_SYSCLK_DIV16       SYSCLK = HFCLK / 16  (N/A for 4000 Family)
*   CY_SYS_CLK_SYSCLK_DIV32       SYSCLK = HFCLK / 32  (N/A for 4000 Family)
*   CY_SYS_CLK_SYSCLK_DIV64       SYSCLK = HFCLK / 64  (N/A for 4000 Family)
*   CY_SYS_CLK_SYSCLK_DIV128      SYSCLK = HFCLK / 128 (N/A for 4000 Family)
*
* Return:
*  None
*
* Side Effects:
*  4000 Family:
*  The SYS_CLK has the speed of 16 MHz, so dividers HF_CLK and SYS_CLK
*  dividers should be selected in a way, not to exceed 16 MHz for SYS_CLK.
*
*  If the SYSCLK clock frequency increases during the device operation, call
*  CySysFlashSetWaitCycles() with the appropriate parameter to adjust the number
*  of clock cycles the cache will wait before sampling data comes back from
*  Flash. If the SYSCLK clock frequency decreases, you can call
*  CySysFlashSetWaitCycles() to improve the CPU performance. See
*  CySysFlashSetWaitCycles() description for more information.
*
*******************************************************************************/
void CySysClkWriteSysclkDiv(uint32 divider)
{
    uint8  interruptState;

    interruptState = CyEnterCriticalSection();

    CY_SYS_CLK_SELECT_REG = ((uint32)(((uint32)divider & CY_SYS_CLK_SELECT_SYSCLK_DIV_MASK) <<
                                    CY_SYS_CLK_SELECT_SYSCLK_DIV_SHIFT)) |
                            (CY_SYS_CLK_SELECT_REG & ((uint32)(~(uint32)(CY_SYS_CLK_SELECT_SYSCLK_DIV_MASK <<
                                    CY_SYS_CLK_SELECT_SYSCLK_DIV_SHIFT))));

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CySysClkWriteImoFreq
********************************************************************************
*
* Summary:
*  Sets the frequency of the IMO.
*
*  If IMO is currently driving the HFCLK, and if the HFCLK frequency decreases,
*  you can call CySysFlashSetWaitCycles () to improve CPU performance. See
*  CySysFlashSetWaitCycles () for more information.
*
*  For PSoC 4000 family of devices, maximum HFCLK frequency is 16 MHz. If IMO is
*  configured to frequencies above 16 MHz, ensure to set the appropriate HFCLK
*  predivider value first.
*
*  For PSoC 4100M/PSoC 4200M devices, if WCO lock feature is enabled then this
*  API will disable the lock, write the new IMO frequency and then re-enable the
*  lock.
*
* Parameters:
*  All PSoC 4 families excluding PSoC 4000: Valid range [3-48] with step size
*  equals 1.
*
*  PSoC 4000: Valid range [24-48] with step size equals 4.
*
*  Note: The CPU is halted if new frequency is invalid and project is
*  compiled in debug mode.
*
* Return:
*  None
*
* Side Effects:
*  If the SYSCLK clock frequency increases during the device operation, call
*  CySysFlashSetWaitCycles() with the appropriate parameter to adjust the number
*  of clock cycles the cache will wait before sampling data comes back from
*  Flash. If the SYSCLK clock frequency decreases, you can call
*  CySysFlashSetWaitCycles() to improve the CPU performance. See
*  CySysFlashSetWaitCycles() description for more information.
*
*  PSoC 4000: The System Clock (SYSCLK) has maximum speed of 16 MHz, so HFCLK
*  and SYSCLK dividers should be selected in a way, to not to exceed 16 MHz for
*  the System clock.
*
*******************************************************************************/
#if(CY_IP_SRSSV2)
    void CySysClkWriteImoFreq(uint32 freq)
    {
        #if (CY_IP_FMLT)
            volatile uint32   parameters[2u];
            volatile uint32   regValues[4u];
        #else
            uint8  bgTrim4;
            uint8  bgTrim5;
            uint8  newImoTrim2Value;
            uint8  currentImoTrim2Value;
        #endif /* (CY_IP_FM) */

        #if (CY_PSOC4_4100M || CY_PSOC4_4200M)
            uint32 wcoLock = 0u;
        #endif  /* #if (CY_PSOC4_4100M || CY_PSOC4_4200M) */

        uint8  interruptState;


        interruptState = CyEnterCriticalSection();

        #if (CY_PSOC4_4100M || CY_PSOC4_4200M)
            if(0u != CySysClkImoGetWcoLock())
            {
                wcoLock = 1u;
                CySysClkImoDisableWcoLock();
            }
        #endif  /* #if (CY_PSOC4_4100M || CY_PSOC4_4200M) */

        #if (CY_IP_FMLT)

            /* FM-Lite Clock Restore */
            regValues[0u] = CY_SYS_CLK_IMO_CONFIG_REG;
            regValues[1u] = CY_SYS_CLK_SELECT_REG;
            regValues[2u] = cyImoFreqMhz2Reg[freq - CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET];
            regValues[3u] = CY_FLASH_CTL_REG;

            parameters[0u] =
                (uint32) ((CY_FLASH_KEY_TWO(CY_FLASH_API_OPCODE_CLK_RESTORE) <<  CY_FLASH_PARAM_KEY_TWO_OFFSET) |
                            CY_FLASH_KEY_ONE);
            parameters[1u] = (uint32) &regValues[0u];

            CY_FLASH_CPUSS_SYSARG_REG = (uint32) &parameters[0u];
            CY_FLASH_CPUSS_SYSREQ_REG = CY_FLASH_CPUSS_REQ_START | CY_FLASH_API_OPCODE_CLK_RESTORE;
            (void) CY_FLASH_CPUSS_SYSARG_REG;

        #else /* (CY_IP_FM) */

        if ((freq >= CY_SYS_CLK_IMO_MIN_FREQ_MHZ) && (freq <= CY_SYS_CLK_IMO_MAX_FREQ_MHZ))
        {
            if(freq <= CY_SFLASH_IMO_MAXF0_REG)
            {
                bgTrim4 = CY_SFLASH_IMO_ABS0_REG;
                bgTrim5 = CY_SFLASH_IMO_TMPCO0_REG;
            }
            else if(freq <= CY_SFLASH_IMO_MAXF1_REG)
            {
                bgTrim4 = CY_SFLASH_IMO_ABS1_REG;
                bgTrim5 = CY_SFLASH_IMO_TMPCO1_REG;
            }
            else if(freq <= CY_SFLASH_IMO_MAXF2_REG)
            {
                bgTrim4 = CY_SFLASH_IMO_ABS2_REG;
                bgTrim5 = CY_SFLASH_IMO_TMPCO2_REG;
            }
            else if(freq <= CY_SFLASH_IMO_MAXF3_REG)
            {
                bgTrim4 = CY_SFLASH_IMO_ABS3_REG;
                bgTrim5 = CY_SFLASH_IMO_TMPCO3_REG;
            }
            else
            {
                bgTrim4 = CY_SFLASH_IMO_ABS4_REG;
                bgTrim5 = CY_SFLASH_IMO_TMPCO4_REG;
            }

            /* Get IMO_TRIM2 value for the new frequency */
            newImoTrim2Value = cyImoFreqMhz2Reg[freq - CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET];


            /**********************************************`*****************************
            * The IMO can have a different trim per frequency. To avoid possible corner
            * cases where a trim change can exceed the maximum frequency, the trim must
            * be applied at a frequency that is low enough.
            *
            * Comparing IMO_TRIM2 values for the current and new frequencies, since
            * IMO_TRIM2 value as a function of IMO frequency is a strictly increasing
            * function and is time-invariant.
            ***************************************************************************/
            if ((newImoTrim2Value >= CY_SYS_CLK_IMO_BOUNDARY_FREQ_TRIM2) && (freq >= CY_SYS_CLK_IMO_BOUNDARY_FREQ_MHZ))
            {
                /* Set boundary IMO frequency: safe for IMO above 48 MHZ trimming */
                CY_SYS_CLK_IMO_TRIM2_REG = (uint32) cyImoFreqMhz2Reg[CY_SYS_CLK_IMO_TEMP_FREQ_MHZ -
                                                                     CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET];

                CyDelayCycles(CY_SYS_CLK_IMO_FREQ_TIMEOUT_CYCLES);

                currentImoTrim2Value = CY_SYS_CLK_IMO_TEMP_FREQ_TRIM2;
            }
            else
            {
                currentImoTrim2Value = (uint8) (CY_SYS_CLK_IMO_TRIM2_REG & CY_SYS_CLK_IMO_FREQ_BITS_MASK);
            }


            /***************************************************************************
            * A trim change needs to be allowed to settle (within 5us) before the Freq
            * can be changed to a new frequency.
            *
            * Comparing IMO_TRIM2 values for the current and new frequencies, since
            * IMO_TRIM2 value as a function of IMO frequency is a strictly increasing
            * function and is time-invariant.
            ***************************************************************************/
            if (newImoTrim2Value < currentImoTrim2Value)
            {
                /* Set new IMO frequency */
                CY_SYS_CLK_IMO_TRIM2_REG = cyImoFreqMhz2Reg[freq - CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET];
                CyDelayCycles(CY_SYS_CLK_IMO_FREQ_TIMEOUT_CYCLES);
            }

            /* Set trims for the new IMO frequency */
            CY_SYS_CLK_IMO_TRIM1_REG = (uint32) CY_SFLASH_IMO_TRIM_REG(freq - CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET);
            CY_PWR_BG_TRIM4_REG  = bgTrim4;
            CY_PWR_BG_TRIM5_REG  = bgTrim5;
            CyDelayUs(CY_SYS_CLK_IMO_TRIM_TIMEOUT_US);

            if (newImoTrim2Value > currentImoTrim2Value)
            {
                /* Set new IMO frequency */
                CY_SYS_CLK_IMO_TRIM2_REG = cyImoFreqMhz2Reg[freq - CY_SYS_CLK_IMO_FREQ_TABLE_OFFSET];
                CyDelayCycles(CY_SYS_CLK_IMO_FREQ_TIMEOUT_CYCLES);
            }
        }
        else
        {
            /* Halt CPU in debug mode if new frequency is invalid */
            CYASSERT(0u != 0u);
        }

        #endif /* (CY_IP_FMLT) */

        #if (CY_PSOC4_4100M || CY_PSOC4_4200M)
            if (1u == wcoLock)
            {
                CySysClkImoEnableWcoLock();
            }
        #endif  /* #if (CY_PSOC4_4100M || CY_PSOC4_4200M) */

        CyExitCriticalSection(interruptState);
    }

#else

    void CySysClkWriteImoFreq(uint32 freq)
    {
        uint8  interruptState;

        if ((freq == 24u) || (freq == 32u) || (freq == 48u))
        {
            interruptState = CyEnterCriticalSection();

            /* Set IMO to 24 MHz - CLK_IMO_SELECT.FREQ = 0 */
            CY_SYS_CLK_IMO_SELECT_REG &= ((uint32) ~CY_SYS_CLK_IMO_SELECT_FREQ_MASK);

            /* Apply coarse trim */
            CY_SYS_CLK_IMO_TRIM1_REG = (CY_SYS_CLK_IMO_TRIM1_REG & ((uint32) ~CY_SYS_CLK_IMO_TRIM1_OFFSET_MASK)) |
                (CY_SFLASH_IMO_TRIM_REG(freq - CY_SYS_CLK_IMO_MIN_FREQ_MHZ) & CY_SYS_CLK_IMO_TRIM1_OFFSET_MASK);

            /* Zero out fine trim */
            CY_SYS_CLK_IMO_TRIM2_REG = CY_SYS_CLK_IMO_TRIM2_REG & ((uint32) ~CY_SYS_CLK_IMO_TRIM2_FSOFFSET_MASK);

            /* Apply TC trim */
            CY_SYS_CLK_IMO_TRIM3_REG = (CY_SYS_CLK_IMO_TRIM3_REG & ((uint32) ~CY_SYS_CLK_IMO_TRIM3_VALUES_MASK)) |
                (CY_SFLASH_IMO_TCTRIM_REG(freq - CY_SYS_CLK_IMO_MIN_FREQ_MHZ) & CY_SYS_CLK_IMO_TRIM3_VALUES_MASK);

            CyDelayCycles(CY_SYS_CLK_IMO_TRIM_DELAY_US);

            if (freq > CY_SYS_CLK_IMO_MIN_FREQ_MHZ)
            {
                /* Select nearby intermediate frequency */
                CY_SYS_CLK_IMO_SELECT_REG = (CY_SYS_CLK_IMO_SELECT_REG & ((uint32) ~CY_SYS_CLK_IMO_SELECT_FREQ_MASK)) |
                    (((freq - 4u - CY_SYS_CLK_IMO_MIN_FREQ_MHZ) >> 2u) & CY_SYS_CLK_IMO_SELECT_FREQ_MASK);

                CyDelayCycles(CY_SYS_CLK_IMO_TRIM_DELAY_US);

                /* Make small step to final frequency */
                /* Select nearby intermediate frequency */
                CY_SYS_CLK_IMO_SELECT_REG = (CY_SYS_CLK_IMO_SELECT_REG & ((uint32) ~CY_SYS_CLK_IMO_SELECT_FREQ_MASK)) |
                    (((freq - CY_SYS_CLK_IMO_MIN_FREQ_MHZ) >> 2u) & CY_SYS_CLK_IMO_SELECT_FREQ_MASK);
            }

            CyExitCriticalSection(interruptState);
        }
        else
        {
            /* Halt CPU in debug mode if new frequency is invalid */
            CYASSERT(0u != 0u);
        }
    }

#endif /* (CY_IP_SRSSV2) */


#if(CY_IP_SRSSLT)
    /*******************************************************************************
    * Function Name: CySysClkWriteHfclkDiv
    ********************************************************************************
    *
    * Summary:
    *  Selects the pre-scaler divider value for HFCLK from IMO.
    *
    *  The HFCLK predivider allows the device to divide the HFCLK selection mux
    *  input before use as HFCLK. The predivider is capable of dividing the HFCLK by
    *  powers of 2 between 1 and 8.
    *
    *  Note HFCLK's frequency cannot exceed 16 MHz. This API is applicable for
    *  PSoC 4000 family of devices only.
    *
    *
    * Parameters:
    *  divider: HF clock divider value
    *   Define                        Description
    *   CY_SYS_CLK_HFCLK_DIV_NODIV    Transparent mode (w/o dividing)
    *   CY_SYS_CLK_HFCLK_DIV_2        Divide selected clock source by 2
    *   CY_SYS_CLK_HFCLK_DIV_4        Divide selected clock source by 4
    *   CY_SYS_CLK_HFCLK_DIV_8        Divide selected clock source by 8
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  If the SYSCLK clock frequency increases during the device operation, call
    *  CySysFlashSetWaitCycles() with the appropriate parameter to adjust the number
    *  of clock cycles the cache will wait before sampling data comes back from
    *  Flash. If the SYSCLK clock frequency decreases, you can call
    *  CySysFlashSetWaitCycles() to improve the CPU performance. See
    *  CySysFlashSetWaitCycles() description for more information.
    *
    *******************************************************************************/
    void CySysClkWriteHfclkDiv(uint32 divider)
    {
        uint8  interruptState;

        interruptState = CyEnterCriticalSection();

        CY_SYS_CLK_SELECT_REG = ((CY_SYS_CLK_SELECT_REG & ((uint32) (~(CY_SYS_CLK_SELECT_HFCLK_DIV_MASK <<
                                        CY_SYS_CLK_SELECT_HFCLK_DIV_SHIFT)))) |
                    ((uint32)((divider & CY_SYS_CLK_SELECT_HFCLK_DIV_MASK) << CY_SYS_CLK_SELECT_HFCLK_DIV_SHIFT)));

        CyExitCriticalSection(interruptState);
    }
#endif /* (CY_IP_SRSSLT) */


#if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)

    /*******************************************************************************
    * Function Name: CySysClkEcoStart
    ********************************************************************************
    *
    * Summary:
    *  Starts the External Crystal Oscillator (ECO). Refer to the device datasheet
    *  for the ECO startup time.
    *
    *  The timeout interval is measured based on the system frequency defined by
    *  PSoC Creator at build time. If System clock frequency is changed in
    *  runtime, the CyDelayFreq() with the appropriate parameter should be called.
    *
    * Parameters:
    *  timeoutUs: Timeout in microseconds. If zero is specified, the function
    *             starts the crystal and returns CYRET_SUCCESS. If non-zero
    *             value is passed, the CYRET_SUCCESS is returned once crystal
    *             is oscillating and amplitude reached 60% and it does not mean
    *             24 MHz crystal is within 50 ppm. If it is not oscillating or
    *             amplitude didn't reach 60% after specified amount of time, the
    *             CYRET_TIMEOUT is returned.
    *
    * Return:
    *   CYRET_SUCCESS - Completed successfully. The ECO is oscillating and amplitude
    *                   reached 60% and it does not mean 24 MHz crystal is within
    *                   50 ppm.
    *   CYRET_TIMEOUT - Timeout occurred.
    *
    *******************************************************************************/
    cystatus CySysClkEcoStart(uint32 timeoutUs)
    {
        cystatus status = CYRET_SUCCESS;

        /* Enable the RF oscillator band gap */
        CY_SYS_XTAL_BLESS_RF_CONFIG_REG |= CY_SYS_XTAL_BLESS_RF_CONFIG_RF_ENABLE;

        /* Update trimming register */
        CY_SYS_XTAL_BLERD_BB_XO_REG = CY_SYS_XTAL_BLERD_BB_XO_TRIM;

        /* Enable the Crystal */
        CY_SYS_XTAL_BLERD_DBUS_REG |= CY_SYS_XTAL_BLERD_DBUS_XTAL_ENABLE;

        if(timeoutUs > 0u)
        {
            status = CYRET_TIMEOUT;

            for( ; timeoutUs > 0u; timeoutUs--)
            {
                CyDelayUs(1u);

                if(0u != CySysClkEcoReadStatus())
                {
                    status = CYRET_SUCCESS;
                    break;
                }
            }

        }

        return(status);
    }


    /*******************************************************************************
    * Function Name: CySysClkEcoStop
    ********************************************************************************
    *
    * Summary:
    *  Stops the megahertz crystal.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysClkEcoStop(void)
    {
        /* Disable the RF oscillator band gap */
        CY_SYS_XTAL_BLESS_RF_CONFIG_REG &= (uint32) ~CY_SYS_XTAL_BLESS_RF_CONFIG_RF_ENABLE;

        /* Disable the Crystal */
        CY_SYS_XTAL_BLERD_DBUS_REG &= (uint32) ~CY_SYS_XTAL_BLERD_DBUS_XTAL_ENABLE;
    }


    /*******************************************************************************
    * Function Name: CySysClkEcoReadStatus
    ********************************************************************************
    *
    * Summary:
    *  Read status bit (50 ppm reached) for the megahertz crystal.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Non-zero indicates that XTAL output reached 50 ppm.
    *
    *******************************************************************************/
    uint32 CySysClkEcoReadStatus(void)
    {
        return (CY_SYS_XTAL_BLERD_FSM_REG & CY_SYS_XTAL_BLERD_FSM_XO_AMP_DETECT);
    }


    /*******************************************************************************
    * Function Name: CySysClkWriteEcoDiv
    ********************************************************************************
    *
    * Summary:
    *  Selects value for the ECO divider.
    *
    *  The ECO must not be the HFCLK clock source when this function is called.
    *  The HFCLK source can be changed to the other clock source by call to the
    *  CySysClkWriteHfclkDirect() function. If the ECO sources the HFCLK this
    *  function will not have any effect if compiler in release mode, and halt the
    *  CPU when compiler in debug mode.
    *
    * Parameters:
    *  divider: Power of 2 divider selection.
    *
    *   Define                        Description
    *   CY_SYS_CLK_ECO_DIV1             HFCLK = ECO / 1
    *   CY_SYS_CLK_ECO_DIV2             HFCLK = ECO / 2
    *   CY_SYS_CLK_ECO_DIV4             HFCLK = ECO / 4
    *   CY_SYS_CLK_ECO_DIV8             HFCLK = ECO / 8
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  If the SYSCLK clock frequency increases during the device operation, call
    *  CySysFlashSetWaitCycles() with the appropriate parameter to adjust the number
    *  of clock cycles the cache will wait before sampling data comes back from
    *  Flash. If the SYSCLK clock frequency decreases, you can call
    *  CySysFlashSetWaitCycles() to improve the CPU performance. See
    *  CySysFlashSetWaitCycles() description for more information.
    *
    *******************************************************************************/
    void CySysClkWriteEcoDiv(uint32 divider)
    {
        uint8  interruptState;

        if (CY_SYS_CLK_HFCLK_ECO != (CY_SYS_CLK_SELECT_REG & CY_SYS_CLK_SELECT_DIRECT_SEL_MASK))
        {
            interruptState = CyEnterCriticalSection();

            CY_SYS_CLK_XTAL_CLK_DIV_CONFIG_REG =  (divider & CY_SYS_CLK_XTAL_CLK_DIV_MASK) |
                                                  (CY_SYS_CLK_XTAL_CLK_DIV_CONFIG_REG & ((uint32) ~CY_SYS_CLK_XTAL_CLK_DIV_MASK));

            CyExitCriticalSection(interruptState);
        }
        else
        {
            /* Halt CPU in debug mode if ECO sources HFCLK */
            CYASSERT(0u != 0u);
        }
    }
#endif /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */






#if(CY_IP_SRSSV2)

    /*******************************************************************************
    * Function Name: CySysLvdEnable
    ********************************************************************************
    *
    * Summary:
    *  Enables the output of the low-voltage monitor when Vddd is at or below the
    *  trip point, configures the device to generate an interrupt, and sets the
    *  voltage trip level.
    *
    * Parameters:
    *  threshold: Threshold selection for Low Voltage Detect circuit.
    *  Threshold variation is +/- 2.5% from these typical voltage choices.
    *         Define                     Voltage threshold
    *    CY_LVD_THRESHOLD_1_75_V       1.7500 V
    *    CY_LVD_THRESHOLD_1_80_V       1.8000 V
    *    CY_LVD_THRESHOLD_1_90_V       1.9000 V
    *    CY_LVD_THRESHOLD_2_00_V       2.0000 V
    *    CY_LVD_THRESHOLD_2_10_V       2.1000 V
    *    CY_LVD_THRESHOLD_2_20_V       2.2000 V
    *    CY_LVD_THRESHOLD_2_30_V       2.3000 V
    *    CY_LVD_THRESHOLD_2_40_V       2.4000 V
    *    CY_LVD_THRESHOLD_2_50_V       2.5000 V
    *    CY_LVD_THRESHOLD_2_60_V       2.6000 V
    *    CY_LVD_THRESHOLD_2_70_V       2.7000 V
    *    CY_LVD_THRESHOLD_2_80_V       2.8000 V
    *    CY_LVD_THRESHOLD_2_90_V       2.9000 V
    *    CY_LVD_THRESHOLD_3_00_V       3.0000 V
    *    CY_LVD_THRESHOLD_3_20_V       3.2000 V
    *    CY_LVD_THRESHOLD_4_50_V       4.5000 V
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysLvdEnable(uint32 threshold)
    {
        /* Prevent propagating a false interrupt */
        CY_LVD_PWR_INTR_MASK_REG   &= (uint32) ~CY_LVD_PROPAGATE_INT_TO_CPU;

        /* Set specified threshold */
        CY_LVD_PWR_VMON_CONFIG_REG = (CY_LVD_PWR_VMON_CONFIG_REG & ~CY_LVD_PWR_VMON_CONFIG_LVD_SEL_MASK) |
                ((threshold << CY_LVD_PWR_VMON_CONFIG_LVD_SEL_SHIFT) & CY_LVD_PWR_VMON_CONFIG_LVD_SEL_MASK);

        /* Enable the LVD. This may cause a false LVD event. */
        CY_LVD_PWR_VMON_CONFIG_REG |= CY_LVD_PWR_VMON_CONFIG_LVD_EN;

        /* Wait for the circuit to stabilize */
        CyDelayUs(CY_LVD_STABILIZE_TIMEOUT_US);

        /* Clear the false event */
        CySysLvdClearInterrupt();

        /* Unmask the interrupt */
        CY_LVD_PWR_INTR_MASK_REG   |= CY_LVD_PROPAGATE_INT_TO_CPU;
    }


    /*******************************************************************************
    * Function Name: CySysLvdDisable
    ********************************************************************************
    *
    * Summary:
    *  Disables the low voltage detection. A low voltage interrupt is disabled.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysLvdDisable(void)
    {
        CY_LVD_PWR_INTR_MASK_REG   &= ~CY_LVD_PROPAGATE_INT_TO_CPU;
        CY_LVD_PWR_VMON_CONFIG_REG &= ~CY_LVD_PWR_VMON_CONFIG_LVD_EN;
    }


    /*******************************************************************************
    * Function Name: CySysLvdGetInterruptSource
    ********************************************************************************
    *
    * Summary:
    *  Gets the low voltage detection interrupt status (without clearing).
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Interrupt request value:
    *    CY_SYS_LVD_INT - Indicates an Low Voltage Detect interrupt
    *
    *******************************************************************************/
    uint32 CySysLvdGetInterruptSource(void)
    {
        return (CY_LVD_PWR_INTR_REG & CY_SYS_LVD_INT);
    }


    /*******************************************************************************
    * Function Name: CySysLvdClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears the low voltage detection interrupt status.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CySysLvdClearInterrupt(void)
    {
        CY_LVD_PWR_INTR_REG = CY_SYS_LVD_INT;
    }

#endif /* (CY_IP_SRSSV2) */


/*******************************************************************************
* Function Name: CySysGetResetReason
********************************************************************************
*
* Summary:
*  Reports the cause for the latest reset(s) that occurred in the system. All
*  the bits in the RES_CAUSE register assert when the corresponding reset cause
*  occurs and must be cleared by the firmware. These bits are cleared by the
*  hardware only during XRES, POR, or a detected brown-out.
*
* Parameters:
*  reason: bits in the RES_CAUSE register to clear.
*   CY_SYS_RESET_WDT       - WDT caused a reset
*   CY_SYS_RESET_PROTFAULT - Occured protection violation that requires reset
*   CY_SYS_RESET_SW        - Cortex-M0 requested a system reset.
*
* Return:
*  Status. Same enumerated bit values as used for the reason parameter.
*
*******************************************************************************/
uint32 CySysGetResetReason(uint32 reason)
{
    uint32 status;

    reason &= (CY_SYS_RESET_WDT | CY_SYS_RESET_PROTFAULT | CY_SYS_RESET_SW);
    status = CY_SYS_RES_CAUSE_REG &
             (CY_SYS_RESET_WDT | CY_SYS_RESET_PROTFAULT | CY_SYS_RESET_SW);
    CY_SYS_RES_CAUSE_REG = reason;

    return (status);
}


/*******************************************************************************
* Function Name: CyDisableInts
********************************************************************************
*
* Summary:
*  Disables all interrupts.
*
* Parameters:
*  None
*
* Return:
*  32 bit mask of previously enabled interrupts.
*
*******************************************************************************/
uint32 CyDisableInts(void)
{
    uint32 intState;

    /* Get current interrupt state. */
    intState = CY_INT_CLEAR_REG;

    /* Disable all interrupts. */
    CY_INT_CLEAR_REG = CY_INT_CLEAR_DISABLE_ALL;

    return (intState);
}


/*******************************************************************************
* Function Name: CyEnableInts
********************************************************************************
*
* Summary:
*  Enables interrupts to a given state.
*
* Parameters:
*   mask, 32 bit mask of interrupts to enable.
*
* Return:
*  None
*
*******************************************************************************/
void CyEnableInts(uint32 mask)
{
    CY_INT_ENABLE_REG = mask;
}


/*******************************************************************************
* Function Name: CyIntSetSysVector
********************************************************************************
*
* Summary:
*  Sets the interrupt vector of the specified system interrupt number. These
*  interrupts are for SysTick, PendSV and others.
*
* Parameters:
*  number: System interrupt number:
*    CY_INT_NMI_IRQN        - Non Maskable Interrupt
*    CY_INT_HARD_FAULT_IRQN - Hard Fault Interrupt
*    CY_INT_SVCALL_IRQN     - SV Call Interrupt
*    CY_INT_PEND_SV_IRQN    - Pend SV Interrupt
*    CY_INT_SYSTICK_IRQN    - System Tick Interrupt
*
*  address: Pointer to an interrupt service routine.
*
* Return:
*  The old ISR vector at this location.
*
*******************************************************************************/
cyisraddress CyIntSetSysVector(uint8 number, cyisraddress address)
{
    cyisraddress oldIsr;
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_INT_IRQ_BASE);

    /* Save old Interrupt service routine. */
    oldIsr = ramVectorTable[number];

    /* Set new Interrupt service routine. */
    ramVectorTable[number] = address;

    return(oldIsr);
}


/*******************************************************************************
* Function Name: CyIntGetSysVector
********************************************************************************
*
* Summary:
*   Gets the interrupt vector of the specified system interrupt number. These
*   interrupts are for SysTick, PendSV and others.
*
* Parameters:
*  number: System interrupt number:
*    CY_INT_NMI_IRQN        - Non Maskable Interrupt
*    CY_INT_HARD_FAULT_IRQN - Hard Fault Interrupt
*    CY_INT_SVCALL_IRQN     - SV Call Interrupt
*    CY_INT_PEND_SV_IRQN    - Pend SV Interrupt
*    CY_INT_SYSTICK_IRQN    - System Tick Interrupt
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress CyIntGetSysVector(uint8 number)
{
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_INT_IRQ_BASE);

    return(ramVectorTable[number]);
}


/*******************************************************************************
* Function Name: CyIntSetVector
********************************************************************************
*
* Summary:
*  Sets the interrupt vector of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number
*  address: Pointer to an interrupt service routine
*
* Return:
*   Previous interrupt vector value.
*
*******************************************************************************/
cyisraddress CyIntSetVector(uint8 number, cyisraddress address)
{
    cyisraddress oldIsr;
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    /* Save old Interrupt service routine. */
    oldIsr = ramVectorTable[CY_INT_IRQ_BASE + number];

    /* Set new Interrupt service routine. */
    ramVectorTable[CY_INT_IRQ_BASE + number] = address;

    return(oldIsr);
}


/*******************************************************************************
* Function Name: CyIntGetVector
********************************************************************************
*
* Summary:
*  Gets the interrupt vector of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number
*
* Return:
*  Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress CyIntGetVector(uint8 number)
{
    cyisraddress *ramVectorTable = (cyisraddress *) CY_INT_VECT_TABLE;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    return (ramVectorTable[CY_INT_IRQ_BASE + number]);
}

/*******************************************************************************
* Function Name: CyIntSetPriority
********************************************************************************
*
* Summary:
*  Sets the priority of the interrupt.
*
* Parameters:
*  priority: Priority of the interrupt. 0 - 3, 0 being the highest.
*  number: The number of the interrupt, 0 - 31.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntSetPriority(uint8 number, uint8 priority)
{
    uint8 interruptState;
    uint32 shift;
    uint32 value;

    CYASSERT(priority <= CY_MIN_PRIORITY);
    CYASSERT(number < CY_NUM_INTERRUPTS);

    shift = CY_INT_PRIORITY_SHIFT(number);

    interruptState = CyEnterCriticalSection();

    value = CY_INT_PRIORITY_REG(number);
    value &= (uint32)(~((uint32)(CY_INT_PRIORITY_MASK << shift)));
    value |= ((uint32)priority << shift);
    CY_INT_PRIORITY_REG(number) = value;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CyIntGetPriority
********************************************************************************
*
* Summary:
*  Gets the priority of the interrupt.
*
* Parameters:
*  number: The number of the interrupt, 0 - 31.
*
* Return:
*  Priority of the interrupt. 0 - 3, 0 being the highest.
*
*******************************************************************************/
uint8 CyIntGetPriority(uint8 number)
{
    uint8 priority;

    CYASSERT(number < CY_NUM_INTERRUPTS);

    priority = (uint8) (CY_INT_PRIORITY_REG(number) >> CY_INT_PRIORITY_SHIFT(number));

    return (priority & (uint8) CY_INT_PRIORITY_MASK);
}


/*******************************************************************************
* Function Name: CyIntEnable
********************************************************************************
*
* Summary:
*  Enables the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number
*
* Return:
*  None
*
*******************************************************************************/
void CyIntEnable(uint8 number)
{
    CY_INT_ENABLE_REG = ((uint32) 0x01u << (CY_INT_ENABLE_RANGE_MASK & number));
}


/*******************************************************************************
* Function Name: CyIntGetState
********************************************************************************
*
* Summary:
*  Gets the enable state of the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number.
*
* Return:
*  Enable status: 1 if enabled, 0 if disabled
*
*******************************************************************************/
uint8 CyIntGetState(uint8 number)
{
    /* Get state of interrupt. */
    return ((0u != (CY_INT_ENABLE_REG & ((uint32) 0x01u << (CY_INT_ENABLE_RANGE_MASK & number)))) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: CyIntDisable
********************************************************************************
*
* Summary:
*   Disables the specified interrupt number.
*
* Parameters:
*   number: Valid range [0-31].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntDisable(uint8 number)
{
    CY_INT_CLEAR_REG = ((uint32) 0x01u << (CY_INT_ENABLE_RANGE_MASK & number));
}

/*******************************************************************************
* Function Name: CyIntSetPending
********************************************************************************
*
* Summary:
*  Forces the specified interrupt number to be pending.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntSetPending(uint8 number)
{
    CY_INT_SET_PEND_REG = ((uint32) 0x01u << (CY_INT_ENABLE_RANGE_MASK & number));
}


/*******************************************************************************
* Function Name: CyIntClearPending
********************************************************************************
*
* Summary:
*  Clears any pending interrupt for the specified interrupt number.
*
* Parameters:
*  number: Valid range [0-31].  Interrupt number.
*
* Return:
*  None
*
*******************************************************************************/
void CyIntClearPending(uint8 number)
{
    CY_INT_CLR_PEND_REG = ((uint32) 0x01u << (CY_INT_ENABLE_RANGE_MASK & number));
}


/*******************************************************************************
* Function Name: CyHalt
********************************************************************************
*
* Summary:
*  Halts the CPU.
*
* Parameters:
*  reason: Value to be used during debugging.
*
* Return:
*  None
*
*******************************************************************************/
void CyHalt(uint8 reason)
{
    if(0u != reason)
    {
        /* To remove unreferenced local variable warning */
    }

    #if defined (__ARMCC_VERSION)
        __breakpoint(0x0);
    #elif defined(__GNUC__) || defined (__ICCARM__)
        __asm("    bkpt    1");
    #elif defined(__C51__)
        CYDEV_HALT_CPU;
    #endif  /* (__ARMCC_VERSION) */
}


/*******************************************************************************
* Function Name: CySoftwareReset
********************************************************************************
*
* Summary:
*  Forces a software reset of the device.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySoftwareReset(void)
{
    /***************************************************************************
    * Setting the system reset request bit. The vector key value must be written
    * to the register, otherwise the register write is unpredictable.
    ***************************************************************************/
    CY_SYS_CM0_AIRCR_REG = (CY_SYS_CM0_AIRCR_REG & (uint32)(~CY_SYS_CM0_AIRCR_VECTKEY_MASK)) |
                            CY_SYS_CM0_AIRCR_VECTKEY | CY_SYS_CM0_AIRCR_SYSRESETREQ;
}


/*******************************************************************************
* Function Name: CyDelay
********************************************************************************
*
* Summary:
*  Blocks for milliseconds.
*
* Parameters:
*  milliseconds: number of milliseconds to delay.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelay(uint32 milliseconds)
{
    while (milliseconds > CY_DELAY_MS_OVERFLOW)
    {
        /* This loop prevents overflow.
         * At 100MHz, milliseconds * cydelayFreqKhz overflows at about 42 seconds
         */
        CyDelayCycles(cydelay32kMs);
        milliseconds -= CY_DELAY_MS_OVERFLOW;
    }

    CyDelayCycles(milliseconds * cydelayFreqKhz);
}


/*******************************************************************************
* Function Name: CyDelayUs
********************************************************************************
* Summary:
*  Blocks for microseconds.
*
* Parameters:
*  microseconds: number of microseconds to delay.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelayUs(uint16 microseconds)
{
    CyDelayCycles((uint32)microseconds * cydelayFreqMhz);
}


/*******************************************************************************
* Function Name: CyDelayFreq
********************************************************************************
* Summary:
*  Sets clock frequency for CyDelay.
*
* Parameters:
*  freq: Frequency of bus clock in Hertz.
*
* Return:
*  None
*
*******************************************************************************/
void CyDelayFreq(uint32 freq)
{
    if (freq != 0u)
    {
        cydelayFreqHz = freq;
    }
    else
    {
        cydelayFreqHz = CYDEV_BCLK__SYSCLK__HZ;
    }

    cydelayFreqMhz = (uint8)((cydelayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cydelayFreqKhz = (cydelayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;
    cydelay32kMs   = CY_DELAY_MS_OVERFLOW * cydelayFreqKhz;
}


/*******************************************************************************
* Function Name: CySysTick_Start
********************************************************************************
*
* Summary:
*  Starts the system timer (SysTick): configures SysTick to generate interrupt
*  every 1 ms and enables the interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set.
*
*******************************************************************************/
void CySysTickStart(void)
{
    if (0u == CySysTickInitVar)
    {
        CySysTickInit();
        CySysTickInitVar = 1u;
    }

    CySysTickEnable();
}


/*******************************************************************************
* Function Name: CySysTickInit
********************************************************************************
*
* Summary:
*  Sets CySysTickServiceCallbacks() as an ISR for the SysTick exception.
*  The clock source for the SysTick counter is set to the System Clock.
*  The SysTick reload value is configured for the timer to generate interrupt
*  every 1 ms. The System clock value is on the global variables cydelayFreqHz.
*  User is responsible for calling CyDelayFreq() function.
*  Initializes CySysTickCallbacks array.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set
*
*******************************************************************************/
void CySysTickInit(void)
{
    uint32 i;

    for (i = 0u; i<CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
    {
        CySysTickCallbacks[i] = (void *) 0;
    }

    (void) CyIntSetSysVector(CY_INT_SYSTICK_IRQN, &CySysTickServiceCallbacks);

    #if(!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200)
        CySysTickSetClockSource(CY_SYS_SYST_CSR_CLK_SRC_SYSCLK);
    #endif /* (!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200) */

    CySysTickSetReload(cydelayFreqHz/1000u);
    CySysTickClear();
    CyIntEnable(CY_INT_SYSTICK_IRQN);
}


/*******************************************************************************
* Function Name: CySysTickEnable
********************************************************************************
*
* Summary:
*  Enables the SysTick timer and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set
*
*******************************************************************************/
void CySysTickEnable(void)
{
    CySysTickEnableInterrupt();
    CY_SYS_SYST_CSR_REG |= CY_SYS_SYST_CSR_ENABLE;
}


/*******************************************************************************
* Function Name: CySysTickStop
********************************************************************************
*
* Summary:
*  Stops the system timer (SysTick).
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set
*
*******************************************************************************/
void CySysTickStop(void)
{
    CY_SYS_SYST_CSR_REG &= ((uint32) ~(CY_SYS_SYST_CSR_ENABLE));
}


/*******************************************************************************
* Function Name: CySysTickEnableInterrupt
********************************************************************************
*
* Summary:
*  Enables the SysTick interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set
*
*******************************************************************************/
void CySysTickEnableInterrupt(void)
{
    CY_SYS_SYST_CSR_REG |= CY_SYS_SYST_CSR_ENABLE_INT;
}


/*******************************************************************************
* Function Name: CySysTickDisableInterrupt
********************************************************************************
*
* Summary:
*  Disables the SysTick interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Clears SysTick count flag if it was set
*
*******************************************************************************/
void CySysTickDisableInterrupt(void)
{
    CY_SYS_SYST_CSR_REG &= ((uint32) ~(CY_SYS_SYST_CSR_ENABLE_INT));
}


/*******************************************************************************
* Function Name: CySysTickSetReload
********************************************************************************
*
* Summary:
*  Sets value the counter is set to on startup and after it reaches zero. This
*  function do not change or reset current sysTick counter value, so it should
*  be cleared using CySysTickClear() API.
*
* Parameters:
*  value: Valid range [0x0-0x00FFFFFF]. Counter reset value
*
* Return:
*  None
*
*******************************************************************************/
void CySysTickSetReload(uint32 value)
{
    CY_SYS_SYST_RVR_REG = (value & CY_SYS_SYST_RVR_CNT_MASK);
}


/*******************************************************************************
* Function Name: CySysTickGetReload
********************************************************************************
*
* Summary:
*  Sets value the counter is set to on startup and after it reaches zero.
*
* Parameters:
*  None
*
* Return:
*  Counter reset value.
*
*******************************************************************************/
uint32 CySysTickGetReload(void)
{
    return(CY_SYS_SYST_RVR_REG & CY_SYS_SYST_RVR_CNT_MASK);
}


/*******************************************************************************
* Function Name: CySysTickGetValue
********************************************************************************
*
* Summary:
*  Gets current SysTick counter value.
*
* Parameters:
*  None
*
* Return:
*  Current SysTick counter value
*
*******************************************************************************/
uint32 CySysTickGetValue(void)
{
    return(CY_SYS_SYST_CVR_REG & CY_SYS_SYST_CVR_CNT_MASK);
}


#if(!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200)
    /*******************************************************************************
    * Function Name: CySysTickSetClockSource
    ********************************************************************************
    *
    * Summary:
    *  Sets the clock source for the SysTick counter.
    *
    * Parameters:
    *  clockSource: Clock source for SysTick counter
    *         Define                     Clock Source
    *   CY_SYS_SYST_CSR_CLK_SRC_SYSCLK     SysTick is clocked by CPU clock.
    *   CY_SYS_SYST_CSR_CLK_SRC_LFCLK      SysTick is clocked by the low frequency
    *                                      clock. (ILO 100 KHz for PSoC 5LP, and
    *                                      LFCLK for PSoC 4).
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  Clears SysTick count flag if it was set. If clock source is not ready this
    *  function call will have no effect. After changing clock source to the low
    *  frequency clock the counter and reload register values will remain unchanged
    *  so time to the interrupt will be significantly bigger and vice versa.
    *
    *******************************************************************************/
    void CySysTickSetClockSource(uint32 clockSource)
    {
        if (clockSource == CY_SYS_SYST_CSR_CLK_SRC_SYSCLK)
        {
            CY_SYS_SYST_CSR_REG |= (uint32)(CY_SYS_SYST_CSR_CLK_SRC_SYSCLK << CY_SYS_SYST_CSR_CLK_SOURCE_SHIFT);
        }
        else
        {
            CY_SYS_SYST_CSR_REG &= ((uint32) ~((uint32)(CY_SYS_SYST_CSR_CLK_SRC_SYSCLK << CY_SYS_SYST_CSR_CLK_SOURCE_SHIFT)));
        }
    }
#endif /* (!CY_PSOC3 && !CY_PSOC4_4000 && !CY_PSOC4_4100 && !CY_PSOC4_4200) */


/*******************************************************************************
* Function Name: CySysTickGetCountFlag
********************************************************************************
*
* Summary:
*  The count flag is set once SysTick counter reaches zero.
*   The flag cleared on read.
*
* Parameters:
*  None
*
* Return:
    *  Returns non-zero value if flag is set, otherwise zero is returned.
*
*
* Side Effects:
*  Clears SysTick count flag if it was set.
*
*******************************************************************************/
uint32 CySysTickGetCountFlag(void)
{
    return ((CY_SYS_SYST_CSR_REG>>CY_SYS_SYST_CSR_COUNTFLAG_SHIFT) & 0x01u);
}


/*******************************************************************************
* Function Name: CySysTickClear
********************************************************************************
*
* Summary:
*  Clears the SysTick counter for well-defined startup.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CySysTickClear(void)
{
    CY_SYS_SYST_CVR_REG = 0u;
}


/*******************************************************************************
* Function Name: CySysTickSetCallback
********************************************************************************
*
* Summary:
*  This function allows up to five user-defined interrupt service routine
*  functions to be associated with the SysTick interrupt. These are specified
*  through the use of pointers to the function.
*
*  To set a custom callback function without the overhead of the system provided
*  one, use CyIntSetSysVector(CY_INT_SYSTICK_IRQN, cyisraddress <address>),
*  where <address> is address of the custom defined interrupt service routine.
*  Note: a custom callback function overrides the system defined callback
*  functions.
*
* Parameters:
*  number: The number of the callback function addresses to be set. The valid
*          range is from 0 to 4.
*
*  void(*CallbackFunction(void): A pointer to the function that will be
*                                associated with the SysTick ISR for the
*                                specified number.
*
* Return:
*  Returns the address of the previous callback function.
*  The NULL is returned if the specified address in not set.
*
* Side Effects:
*  The registered callback functions will be executed in the interrupt.
*
*******************************************************************************/
cySysTickCallback CySysTickSetCallback(uint32 number, cySysTickCallback function)
{
    cySysTickCallback retVal;

    retVal = CySysTickCallbacks[number];
    CySysTickCallbacks[number] = function;
    return (retVal);
}


/*******************************************************************************
* Function Name: CySysTickGetCallback
********************************************************************************
*
* Summary:
*  The function get the specified callback pointer.
*
* Parameters:
*  number: The number of callback function address to get. The valid
*          range is from 0 to 4.
*
* Return:
*  Returns the address of the specified callback function.
*  The NULL is returned if the specified address in not initialized.
*
*******************************************************************************/
cySysTickCallback CySysTickGetCallback(uint32 number)
{
    return ((cySysTickCallback) CySysTickCallbacks[number]);
}


/*******************************************************************************
* Function Name: CySysTickServiceCallbacks
********************************************************************************
*
* Summary:
*  System Tick timer interrupt routine
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void CySysTickServiceCallbacks(void)
{
    uint32 i;

    /* Verify that tick timer flag was set */
    if (1u == CySysTickGetCountFlag())
    {
        for (i=0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
        {
            if (CySysTickCallbacks[i] != (void *) 0)
            {
                (void)(CySysTickCallbacks[i])();
            }
        }
    }
}


/*******************************************************************************
* Function Name: CyGetUniqueId
********************************************************************************
*
* Summary:
*  Returns the 64-bit unique ID of the device. The uniqueness of the number is
*  guaranteed for 10 years due to the die lot number having a cycle life of 10
*  years and even after 10 years, the probability of getting two identical
*  numbers is very small.
*
* Parameters:
*  uniqueId: The pointer to a two element 32-bit unsigned integer array. Returns
*  the 64-bit unique ID of the device by loading them into the integer array
*  pointed to by uniqueId.
*
* Return:
*  None
*
*******************************************************************************/
void CyGetUniqueId(uint32* uniqueId)
{
#if(CY_PSOC4)
    uniqueId[0u]  =  (uint32)(* (reg8 *) CYREG_SFLASH_DIE_LOT0  );
    uniqueId[0u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_LOT1  ) <<  8u);
    uniqueId[0u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_LOT2  ) << 16u);
    uniqueId[0u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_WAFER ) << 24u);

    uniqueId[1u]  =  (uint32)(* (reg8 *) CYREG_SFLASH_DIE_X     );
    uniqueId[1u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_Y     ) <<  8u);
    uniqueId[1u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_SORT  ) << 16u);
    uniqueId[1u] |= ((uint32)(* (reg8 *) CYREG_SFLASH_DIE_MINOR ) << 24u);
#else
    uniqueId[0u]  =  (uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_LOT_LSB   ));
    uniqueId[0u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_LOT_MSB   )) <<  8u);
    uniqueId[0u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_MLOGIC_REV_ID                )) << 16u);
    uniqueId[0u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_WAFER_NUM )) << 24u);

    uniqueId[1u]  =  (uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_X_LOC     ));
    uniqueId[1u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_Y_LOC     )) <<  8u);
    uniqueId[1u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_WRK_WK    )) << 16u);
    uniqueId[1u] |= ((uint32) CY_GET_XTND_REG8((void CYFAR *) (CYREG_FLSHID_CUST_TABLES_FAB_YR    )) << 24u);
#endif  /* (CY_PSOC4) */
}


/* [] END OF FILE */
