/*******************************************************************************
* File Name: tachPwm.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "tachPwm.h"

/* Error message for removed <resource> through optimization */
#ifdef tachPwm_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* tachPwm_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 tachPwm_initVar = 0u;


/*******************************************************************************
* Function Name: tachPwm_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  tachPwm_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void tachPwm_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(tachPwm_initVar == 0u)
    {
        tachPwm_Init();
        tachPwm_initVar = 1u;
    }
    tachPwm_Enable();

}


/*******************************************************************************
* Function Name: tachPwm_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  tachPwm_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void tachPwm_Init(void) 
{
    #if (tachPwm_UsingFixedFunction || tachPwm_UseControl)
        uint8 ctrl;
    #endif /* (tachPwm_UsingFixedFunction || tachPwm_UseControl) */

    #if(!tachPwm_UsingFixedFunction)
        #if(tachPwm_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 tachPwm_interruptState;
        #endif /* (tachPwm_UseStatus) */
    #endif /* (!tachPwm_UsingFixedFunction) */

    #if (tachPwm_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        tachPwm_CONTROL |= tachPwm_CFG0_MODE;
        #if (tachPwm_DeadBand2_4)
            tachPwm_CONTROL |= tachPwm_CFG0_DB;
        #endif /* (tachPwm_DeadBand2_4) */

        ctrl = tachPwm_CONTROL3 & ((uint8 )(~tachPwm_CTRL_CMPMODE1_MASK));
        tachPwm_CONTROL3 = ctrl | tachPwm_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        tachPwm_RT1 &= ((uint8)(~tachPwm_RT1_MASK));
        tachPwm_RT1 |= tachPwm_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        tachPwm_RT1 &= ((uint8)(~tachPwm_SYNCDSI_MASK));
        tachPwm_RT1 |= tachPwm_SYNCDSI_EN;

    #elif (tachPwm_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = tachPwm_CONTROL & ((uint8)(~tachPwm_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~tachPwm_CTRL_CMPMODE1_MASK));
        tachPwm_CONTROL = ctrl | tachPwm_DEFAULT_COMPARE2_MODE |
                                   tachPwm_DEFAULT_COMPARE1_MODE;
    #endif /* (tachPwm_UsingFixedFunction) */

    #if (!tachPwm_UsingFixedFunction)
        #if (tachPwm_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            tachPwm_AUX_CONTROLDP0 |= (tachPwm_AUX_CTRL_FIFO0_CLR);
        #else /* (tachPwm_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            tachPwm_AUX_CONTROLDP0 |= (tachPwm_AUX_CTRL_FIFO0_CLR);
            tachPwm_AUX_CONTROLDP1 |= (tachPwm_AUX_CTRL_FIFO0_CLR);
        #endif /* (tachPwm_Resolution == 8) */

        tachPwm_WriteCounter(tachPwm_INIT_PERIOD_VALUE);
    #endif /* (!tachPwm_UsingFixedFunction) */

    tachPwm_WritePeriod(tachPwm_INIT_PERIOD_VALUE);

        #if (tachPwm_UseOneCompareMode)
            tachPwm_WriteCompare(tachPwm_INIT_COMPARE_VALUE1);
        #else
            tachPwm_WriteCompare1(tachPwm_INIT_COMPARE_VALUE1);
            tachPwm_WriteCompare2(tachPwm_INIT_COMPARE_VALUE2);
        #endif /* (tachPwm_UseOneCompareMode) */

        #if (tachPwm_KillModeMinTime)
            tachPwm_WriteKillTime(tachPwm_MinimumKillTime);
        #endif /* (tachPwm_KillModeMinTime) */

        #if (tachPwm_DeadBandUsed)
            tachPwm_WriteDeadTime(tachPwm_INIT_DEAD_TIME);
        #endif /* (tachPwm_DeadBandUsed) */

    #if (tachPwm_UseStatus || tachPwm_UsingFixedFunction)
        tachPwm_SetInterruptMode(tachPwm_INIT_INTERRUPTS_MODE);
    #endif /* (tachPwm_UseStatus || tachPwm_UsingFixedFunction) */

    #if (tachPwm_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        tachPwm_GLOBAL_ENABLE |= tachPwm_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        tachPwm_CONTROL2 |= tachPwm_CTRL2_IRQ_SEL;
    #else
        #if(tachPwm_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            tachPwm_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            tachPwm_STATUS_AUX_CTRL |= tachPwm_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(tachPwm_interruptState);

            /* Clear the FIFO to enable the tachPwm_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            tachPwm_ClearFIFO();
        #endif /* (tachPwm_UseStatus) */
    #endif /* (tachPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: tachPwm_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void tachPwm_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (tachPwm_UsingFixedFunction)
        tachPwm_GLOBAL_ENABLE |= tachPwm_BLOCK_EN_MASK;
        tachPwm_GLOBAL_STBY_ENABLE |= tachPwm_BLOCK_STBY_EN_MASK;
    #endif /* (tachPwm_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (tachPwm_UseControl || tachPwm_UsingFixedFunction)
        tachPwm_CONTROL |= tachPwm_CTRL_ENABLE;
    #endif /* (tachPwm_UseControl || tachPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: tachPwm_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void tachPwm_Stop(void) 
{
    #if (tachPwm_UseControl || tachPwm_UsingFixedFunction)
        tachPwm_CONTROL &= ((uint8)(~tachPwm_CTRL_ENABLE));
    #endif /* (tachPwm_UseControl || tachPwm_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (tachPwm_UsingFixedFunction)
        tachPwm_GLOBAL_ENABLE &= ((uint8)(~tachPwm_BLOCK_EN_MASK));
        tachPwm_GLOBAL_STBY_ENABLE &= ((uint8)(~tachPwm_BLOCK_STBY_EN_MASK));
    #endif /* (tachPwm_UsingFixedFunction) */
}

#if (tachPwm_UseOneCompareMode)
    #if (tachPwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: tachPwm_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void tachPwm_SetCompareMode(uint8 comparemode) 
        {
            #if(tachPwm_UsingFixedFunction)

                #if(0 != tachPwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << tachPwm_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != tachPwm_CTRL_CMPMODE1_SHIFT) */

                tachPwm_CONTROL3 &= ((uint8)(~tachPwm_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                tachPwm_CONTROL3 |= comparemodemasked;

            #elif (tachPwm_UseControl)

                #if(0 != tachPwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << tachPwm_CTRL_CMPMODE1_SHIFT)) &
                                                tachPwm_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & tachPwm_CTRL_CMPMODE1_MASK;
                #endif /* (0 != tachPwm_CTRL_CMPMODE1_SHIFT) */

                #if(0 != tachPwm_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << tachPwm_CTRL_CMPMODE2_SHIFT)) &
                                               tachPwm_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & tachPwm_CTRL_CMPMODE2_MASK;
                #endif /* (0 != tachPwm_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                tachPwm_CONTROL &= ((uint8)(~(tachPwm_CTRL_CMPMODE1_MASK |
                                            tachPwm_CTRL_CMPMODE2_MASK)));
                tachPwm_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (tachPwm_UsingFixedFunction) */
        }
    #endif /* tachPwm_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (tachPwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: tachPwm_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void tachPwm_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != tachPwm_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << tachPwm_CTRL_CMPMODE1_SHIFT)) &
                                           tachPwm_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & tachPwm_CTRL_CMPMODE1_MASK;
            #endif /* (0 != tachPwm_CTRL_CMPMODE1_SHIFT) */

            #if (tachPwm_UseControl)
                tachPwm_CONTROL &= ((uint8)(~tachPwm_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                tachPwm_CONTROL |= comparemodemasked;
            #endif /* (tachPwm_UseControl) */
        }
    #endif /* tachPwm_CompareMode1SW */

#if (tachPwm_CompareMode2SW)


    /*******************************************************************************
    * Function Name: tachPwm_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != tachPwm_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << tachPwm_CTRL_CMPMODE2_SHIFT)) &
                                                 tachPwm_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & tachPwm_CTRL_CMPMODE2_MASK;
        #endif /* (0 != tachPwm_CTRL_CMPMODE2_SHIFT) */

        #if (tachPwm_UseControl)
            tachPwm_CONTROL &= ((uint8)(~tachPwm_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            tachPwm_CONTROL |= comparemodemasked;
        #endif /* (tachPwm_UseControl) */
    }
    #endif /*tachPwm_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!tachPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: tachPwm_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void tachPwm_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(tachPwm_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: tachPwm_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 tachPwm_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(tachPwm_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(tachPwm_CAPTURE_LSB_PTR));
    }

    #if (tachPwm_UseStatus)


        /*******************************************************************************
        * Function Name: tachPwm_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void tachPwm_ClearFIFO(void) 
        {
            while(0u != (tachPwm_ReadStatusRegister() & tachPwm_STATUS_FIFONEMPTY))
            {
                (void)tachPwm_ReadCapture();
            }
        }

    #endif /* tachPwm_UseStatus */

#endif /* !tachPwm_UsingFixedFunction */


/*******************************************************************************
* Function Name: tachPwm_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void tachPwm_WritePeriod(uint8 period) 
{
    #if(tachPwm_UsingFixedFunction)
        CY_SET_REG16(tachPwm_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(tachPwm_PERIOD_LSB_PTR, period);
    #endif /* (tachPwm_UsingFixedFunction) */
}

#if (tachPwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: tachPwm_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void tachPwm_WriteCompare(uint8 compare) \
                                       
    {
        #if(tachPwm_UsingFixedFunction)
            CY_SET_REG16(tachPwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(tachPwm_COMPARE1_LSB_PTR, compare);
        #endif /* (tachPwm_UsingFixedFunction) */

        #if (tachPwm_PWMMode == tachPwm__B_PWM__DITHER)
            #if(tachPwm_UsingFixedFunction)
                CY_SET_REG16(tachPwm_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(tachPwm_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (tachPwm_UsingFixedFunction) */
        #endif /* (tachPwm_PWMMode == tachPwm__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: tachPwm_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_WriteCompare1(uint8 compare) \
                                        
    {
        #if(tachPwm_UsingFixedFunction)
            CY_SET_REG16(tachPwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(tachPwm_COMPARE1_LSB_PTR, compare);
        #endif /* (tachPwm_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: tachPwm_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_WriteCompare2(uint8 compare) \
                                        
    {
        #if(tachPwm_UsingFixedFunction)
            CY_SET_REG16(tachPwm_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(tachPwm_COMPARE2_LSB_PTR, compare);
        #endif /* (tachPwm_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (tachPwm_DeadBandUsed)


    /*******************************************************************************
    * Function Name: tachPwm_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!tachPwm_DeadBand2_4)
            CY_SET_REG8(tachPwm_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            tachPwm_DEADBAND_COUNT &= ((uint8)(~tachPwm_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(tachPwm_DEADBAND_COUNT_SHIFT)
                tachPwm_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << tachPwm_DEADBAND_COUNT_SHIFT)) &
                                                    tachPwm_DEADBAND_COUNT_MASK;
            #else
                tachPwm_DEADBAND_COUNT |= deadtime & tachPwm_DEADBAND_COUNT_MASK;
            #endif /* (tachPwm_DEADBAND_COUNT_SHIFT) */

        #endif /* (!tachPwm_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: tachPwm_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 tachPwm_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!tachPwm_DeadBand2_4)
            return (CY_GET_REG8(tachPwm_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(tachPwm_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(tachPwm_DEADBAND_COUNT & tachPwm_DEADBAND_COUNT_MASK)) >>
                                                                           tachPwm_DEADBAND_COUNT_SHIFT));
            #else
                return (tachPwm_DEADBAND_COUNT & tachPwm_DEADBAND_COUNT_MASK);
            #endif /* (tachPwm_DEADBAND_COUNT_SHIFT) */
        #endif /* (!tachPwm_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (tachPwm_UseStatus || tachPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: tachPwm_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(tachPwm_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: tachPwm_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 tachPwm_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(tachPwm_STATUS_PTR));
    }

#endif /* (tachPwm_UseStatus || tachPwm_UsingFixedFunction) */


#if (tachPwm_UseControl)


    /*******************************************************************************
    * Function Name: tachPwm_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 tachPwm_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(tachPwm_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: tachPwm_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(tachPwm_CONTROL_PTR, control);
    }

#endif /* (tachPwm_UseControl) */


#if (!tachPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: tachPwm_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 tachPwm_ReadCapture(void) 
    {
        return (CY_GET_REG8(tachPwm_CAPTURE_LSB_PTR));
    }

#endif /* (!tachPwm_UsingFixedFunction) */


#if (tachPwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: tachPwm_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 tachPwm_ReadCompare(void) 
    {
        #if(tachPwm_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(tachPwm_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(tachPwm_COMPARE1_LSB_PTR));
        #endif /* (tachPwm_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: tachPwm_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 tachPwm_ReadCompare1(void) 
    {
        return (CY_GET_REG8(tachPwm_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: tachPwm_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 tachPwm_ReadCompare2(void) 
    {
        return (CY_GET_REG8(tachPwm_COMPARE2_LSB_PTR));
    }

#endif /* (tachPwm_UseOneCompareMode) */


/*******************************************************************************
* Function Name: tachPwm_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 tachPwm_ReadPeriod(void) 
{
    #if(tachPwm_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(tachPwm_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(tachPwm_PERIOD_LSB_PTR));
    #endif /* (tachPwm_UsingFixedFunction) */
}

#if ( tachPwm_KillModeMinTime)


    /*******************************************************************************
    * Function Name: tachPwm_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void tachPwm_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(tachPwm_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: tachPwm_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 tachPwm_ReadKillTime(void) 
    {
        return (CY_GET_REG8(tachPwm_KILLMODEMINTIME_PTR));
    }

#endif /* ( tachPwm_KillModeMinTime) */

/* [] END OF FILE */
