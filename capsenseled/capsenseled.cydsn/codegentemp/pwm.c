/*******************************************************************************
* File Name: pwm.c
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

#include "pwm.h"

/* Error message for removed <resource> through optimization */
#ifdef pwm_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* pwm_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 pwm_initVar = 0u;


/*******************************************************************************
* Function Name: pwm_Start
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
*  pwm_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void pwm_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(pwm_initVar == 0u)
    {
        pwm_Init();
        pwm_initVar = 1u;
    }
    pwm_Enable();

}


/*******************************************************************************
* Function Name: pwm_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  pwm_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void pwm_Init(void) 
{
    #if (pwm_UsingFixedFunction || pwm_UseControl)
        uint8 ctrl;
    #endif /* (pwm_UsingFixedFunction || pwm_UseControl) */

    #if(!pwm_UsingFixedFunction)
        #if(pwm_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 pwm_interruptState;
        #endif /* (pwm_UseStatus) */
    #endif /* (!pwm_UsingFixedFunction) */

    #if (pwm_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        pwm_CONTROL |= pwm_CFG0_MODE;
        #if (pwm_DeadBand2_4)
            pwm_CONTROL |= pwm_CFG0_DB;
        #endif /* (pwm_DeadBand2_4) */

        ctrl = pwm_CONTROL3 & ((uint8 )(~pwm_CTRL_CMPMODE1_MASK));
        pwm_CONTROL3 = ctrl | pwm_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        pwm_RT1 &= ((uint8)(~pwm_RT1_MASK));
        pwm_RT1 |= pwm_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        pwm_RT1 &= ((uint8)(~pwm_SYNCDSI_MASK));
        pwm_RT1 |= pwm_SYNCDSI_EN;

    #elif (pwm_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = pwm_CONTROL & ((uint8)(~pwm_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~pwm_CTRL_CMPMODE1_MASK));
        pwm_CONTROL = ctrl | pwm_DEFAULT_COMPARE2_MODE |
                                   pwm_DEFAULT_COMPARE1_MODE;
    #endif /* (pwm_UsingFixedFunction) */

    #if (!pwm_UsingFixedFunction)
        #if (pwm_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            pwm_AUX_CONTROLDP0 |= (pwm_AUX_CTRL_FIFO0_CLR);
        #else /* (pwm_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            pwm_AUX_CONTROLDP0 |= (pwm_AUX_CTRL_FIFO0_CLR);
            pwm_AUX_CONTROLDP1 |= (pwm_AUX_CTRL_FIFO0_CLR);
        #endif /* (pwm_Resolution == 8) */

        pwm_WriteCounter(pwm_INIT_PERIOD_VALUE);
    #endif /* (!pwm_UsingFixedFunction) */

    pwm_WritePeriod(pwm_INIT_PERIOD_VALUE);

        #if (pwm_UseOneCompareMode)
            pwm_WriteCompare(pwm_INIT_COMPARE_VALUE1);
        #else
            pwm_WriteCompare1(pwm_INIT_COMPARE_VALUE1);
            pwm_WriteCompare2(pwm_INIT_COMPARE_VALUE2);
        #endif /* (pwm_UseOneCompareMode) */

        #if (pwm_KillModeMinTime)
            pwm_WriteKillTime(pwm_MinimumKillTime);
        #endif /* (pwm_KillModeMinTime) */

        #if (pwm_DeadBandUsed)
            pwm_WriteDeadTime(pwm_INIT_DEAD_TIME);
        #endif /* (pwm_DeadBandUsed) */

    #if (pwm_UseStatus || pwm_UsingFixedFunction)
        pwm_SetInterruptMode(pwm_INIT_INTERRUPTS_MODE);
    #endif /* (pwm_UseStatus || pwm_UsingFixedFunction) */

    #if (pwm_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        pwm_GLOBAL_ENABLE |= pwm_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        pwm_CONTROL2 |= pwm_CTRL2_IRQ_SEL;
    #else
        #if(pwm_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            pwm_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            pwm_STATUS_AUX_CTRL |= pwm_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(pwm_interruptState);

            /* Clear the FIFO to enable the pwm_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            pwm_ClearFIFO();
        #endif /* (pwm_UseStatus) */
    #endif /* (pwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwm_Enable
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
void pwm_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (pwm_UsingFixedFunction)
        pwm_GLOBAL_ENABLE |= pwm_BLOCK_EN_MASK;
        pwm_GLOBAL_STBY_ENABLE |= pwm_BLOCK_STBY_EN_MASK;
    #endif /* (pwm_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (pwm_UseControl || pwm_UsingFixedFunction)
        pwm_CONTROL |= pwm_CTRL_ENABLE;
    #endif /* (pwm_UseControl || pwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwm_Stop
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
void pwm_Stop(void) 
{
    #if (pwm_UseControl || pwm_UsingFixedFunction)
        pwm_CONTROL &= ((uint8)(~pwm_CTRL_ENABLE));
    #endif /* (pwm_UseControl || pwm_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (pwm_UsingFixedFunction)
        pwm_GLOBAL_ENABLE &= ((uint8)(~pwm_BLOCK_EN_MASK));
        pwm_GLOBAL_STBY_ENABLE &= ((uint8)(~pwm_BLOCK_STBY_EN_MASK));
    #endif /* (pwm_UsingFixedFunction) */
}

#if (pwm_UseOneCompareMode)
    #if (pwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: pwm_SetCompareMode
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
        void pwm_SetCompareMode(uint8 comparemode) 
        {
            #if(pwm_UsingFixedFunction)

                #if(0 != pwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwm_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != pwm_CTRL_CMPMODE1_SHIFT) */

                pwm_CONTROL3 &= ((uint8)(~pwm_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                pwm_CONTROL3 |= comparemodemasked;

            #elif (pwm_UseControl)

                #if(0 != pwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << pwm_CTRL_CMPMODE1_SHIFT)) &
                                                pwm_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & pwm_CTRL_CMPMODE1_MASK;
                #endif /* (0 != pwm_CTRL_CMPMODE1_SHIFT) */

                #if(0 != pwm_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << pwm_CTRL_CMPMODE2_SHIFT)) &
                                               pwm_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & pwm_CTRL_CMPMODE2_MASK;
                #endif /* (0 != pwm_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                pwm_CONTROL &= ((uint8)(~(pwm_CTRL_CMPMODE1_MASK |
                                            pwm_CTRL_CMPMODE2_MASK)));
                pwm_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (pwm_UsingFixedFunction) */
        }
    #endif /* pwm_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (pwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: pwm_SetCompareMode1
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
        void pwm_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != pwm_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwm_CTRL_CMPMODE1_SHIFT)) &
                                           pwm_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & pwm_CTRL_CMPMODE1_MASK;
            #endif /* (0 != pwm_CTRL_CMPMODE1_SHIFT) */

            #if (pwm_UseControl)
                pwm_CONTROL &= ((uint8)(~pwm_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                pwm_CONTROL |= comparemodemasked;
            #endif /* (pwm_UseControl) */
        }
    #endif /* pwm_CompareMode1SW */

#if (pwm_CompareMode2SW)


    /*******************************************************************************
    * Function Name: pwm_SetCompareMode2
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
    void pwm_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != pwm_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << pwm_CTRL_CMPMODE2_SHIFT)) &
                                                 pwm_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & pwm_CTRL_CMPMODE2_MASK;
        #endif /* (0 != pwm_CTRL_CMPMODE2_SHIFT) */

        #if (pwm_UseControl)
            pwm_CONTROL &= ((uint8)(~pwm_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            pwm_CONTROL |= comparemodemasked;
        #endif /* (pwm_UseControl) */
    }
    #endif /*pwm_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!pwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwm_WriteCounter
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
    void pwm_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(pwm_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: pwm_ReadCounter
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
    uint8 pwm_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(pwm_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(pwm_CAPTURE_LSB_PTR));
    }

    #if (pwm_UseStatus)


        /*******************************************************************************
        * Function Name: pwm_ClearFIFO
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
        void pwm_ClearFIFO(void) 
        {
            while(0u != (pwm_ReadStatusRegister() & pwm_STATUS_FIFONEMPTY))
            {
                (void)pwm_ReadCapture();
            }
        }

    #endif /* pwm_UseStatus */

#endif /* !pwm_UsingFixedFunction */


/*******************************************************************************
* Function Name: pwm_WritePeriod
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
void pwm_WritePeriod(uint8 period) 
{
    #if(pwm_UsingFixedFunction)
        CY_SET_REG16(pwm_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(pwm_PERIOD_LSB_PTR, period);
    #endif /* (pwm_UsingFixedFunction) */
}

#if (pwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: pwm_WriteCompare
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
    void pwm_WriteCompare(uint8 compare) \
                                       
    {
        #if(pwm_UsingFixedFunction)
            CY_SET_REG16(pwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(pwm_COMPARE1_LSB_PTR, compare);
        #endif /* (pwm_UsingFixedFunction) */

        #if (pwm_PWMMode == pwm__B_PWM__DITHER)
            #if(pwm_UsingFixedFunction)
                CY_SET_REG16(pwm_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(pwm_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (pwm_UsingFixedFunction) */
        #endif /* (pwm_PWMMode == pwm__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: pwm_WriteCompare1
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
    void pwm_WriteCompare1(uint8 compare) \
                                        
    {
        #if(pwm_UsingFixedFunction)
            CY_SET_REG16(pwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(pwm_COMPARE1_LSB_PTR, compare);
        #endif /* (pwm_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: pwm_WriteCompare2
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
    void pwm_WriteCompare2(uint8 compare) \
                                        
    {
        #if(pwm_UsingFixedFunction)
            CY_SET_REG16(pwm_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(pwm_COMPARE2_LSB_PTR, compare);
        #endif /* (pwm_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (pwm_DeadBandUsed)


    /*******************************************************************************
    * Function Name: pwm_WriteDeadTime
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
    void pwm_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!pwm_DeadBand2_4)
            CY_SET_REG8(pwm_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            pwm_DEADBAND_COUNT &= ((uint8)(~pwm_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(pwm_DEADBAND_COUNT_SHIFT)
                pwm_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << pwm_DEADBAND_COUNT_SHIFT)) &
                                                    pwm_DEADBAND_COUNT_MASK;
            #else
                pwm_DEADBAND_COUNT |= deadtime & pwm_DEADBAND_COUNT_MASK;
            #endif /* (pwm_DEADBAND_COUNT_SHIFT) */

        #endif /* (!pwm_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: pwm_ReadDeadTime
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
    uint8 pwm_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!pwm_DeadBand2_4)
            return (CY_GET_REG8(pwm_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(pwm_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(pwm_DEADBAND_COUNT & pwm_DEADBAND_COUNT_MASK)) >>
                                                                           pwm_DEADBAND_COUNT_SHIFT));
            #else
                return (pwm_DEADBAND_COUNT & pwm_DEADBAND_COUNT_MASK);
            #endif /* (pwm_DEADBAND_COUNT_SHIFT) */
        #endif /* (!pwm_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (pwm_UseStatus || pwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwm_SetInterruptMode
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
    void pwm_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(pwm_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: pwm_ReadStatusRegister
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
    uint8 pwm_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(pwm_STATUS_PTR));
    }

#endif /* (pwm_UseStatus || pwm_UsingFixedFunction) */


#if (pwm_UseControl)


    /*******************************************************************************
    * Function Name: pwm_ReadControlRegister
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
    uint8 pwm_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(pwm_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: pwm_WriteControlRegister
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
    void pwm_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(pwm_CONTROL_PTR, control);
    }

#endif /* (pwm_UseControl) */


#if (!pwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: pwm_ReadCapture
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
    uint8 pwm_ReadCapture(void) 
    {
        return (CY_GET_REG8(pwm_CAPTURE_LSB_PTR));
    }

#endif /* (!pwm_UsingFixedFunction) */


#if (pwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: pwm_ReadCompare
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
    uint8 pwm_ReadCompare(void) 
    {
        #if(pwm_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(pwm_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(pwm_COMPARE1_LSB_PTR));
        #endif /* (pwm_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: pwm_ReadCompare1
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
    uint8 pwm_ReadCompare1(void) 
    {
        return (CY_GET_REG8(pwm_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: pwm_ReadCompare2
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
    uint8 pwm_ReadCompare2(void) 
    {
        return (CY_GET_REG8(pwm_COMPARE2_LSB_PTR));
    }

#endif /* (pwm_UseOneCompareMode) */


/*******************************************************************************
* Function Name: pwm_ReadPeriod
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
uint8 pwm_ReadPeriod(void) 
{
    #if(pwm_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(pwm_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(pwm_PERIOD_LSB_PTR));
    #endif /* (pwm_UsingFixedFunction) */
}

#if ( pwm_KillModeMinTime)


    /*******************************************************************************
    * Function Name: pwm_WriteKillTime
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
    void pwm_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(pwm_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: pwm_ReadKillTime
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
    uint8 pwm_ReadKillTime(void) 
    {
        return (CY_GET_REG8(pwm_KILLMODEMINTIME_PTR));
    }

#endif /* ( pwm_KillModeMinTime) */

/* [] END OF FILE */
