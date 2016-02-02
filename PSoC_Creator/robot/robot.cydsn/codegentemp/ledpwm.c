/*******************************************************************************
* File Name: ledpwm.c
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

#include "ledpwm.h"

/* Error message for removed <resource> through optimization */
#ifdef ledpwm_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* ledpwm_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 ledpwm_initVar = 0u;


/*******************************************************************************
* Function Name: ledpwm_Start
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
*  ledpwm_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ledpwm_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(ledpwm_initVar == 0u)
    {
        ledpwm_Init();
        ledpwm_initVar = 1u;
    }
    ledpwm_Enable();

}


/*******************************************************************************
* Function Name: ledpwm_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ledpwm_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ledpwm_Init(void) 
{
    #if (ledpwm_UsingFixedFunction || ledpwm_UseControl)
        uint8 ctrl;
    #endif /* (ledpwm_UsingFixedFunction || ledpwm_UseControl) */

    #if(!ledpwm_UsingFixedFunction)
        #if(ledpwm_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 ledpwm_interruptState;
        #endif /* (ledpwm_UseStatus) */
    #endif /* (!ledpwm_UsingFixedFunction) */

    #if (ledpwm_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        ledpwm_CONTROL |= ledpwm_CFG0_MODE;
        #if (ledpwm_DeadBand2_4)
            ledpwm_CONTROL |= ledpwm_CFG0_DB;
        #endif /* (ledpwm_DeadBand2_4) */

        ctrl = ledpwm_CONTROL3 & ((uint8 )(~ledpwm_CTRL_CMPMODE1_MASK));
        ledpwm_CONTROL3 = ctrl | ledpwm_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        ledpwm_RT1 &= ((uint8)(~ledpwm_RT1_MASK));
        ledpwm_RT1 |= ledpwm_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        ledpwm_RT1 &= ((uint8)(~ledpwm_SYNCDSI_MASK));
        ledpwm_RT1 |= ledpwm_SYNCDSI_EN;

    #elif (ledpwm_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = ledpwm_CONTROL & ((uint8)(~ledpwm_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~ledpwm_CTRL_CMPMODE1_MASK));
        ledpwm_CONTROL = ctrl | ledpwm_DEFAULT_COMPARE2_MODE |
                                   ledpwm_DEFAULT_COMPARE1_MODE;
    #endif /* (ledpwm_UsingFixedFunction) */

    #if (!ledpwm_UsingFixedFunction)
        #if (ledpwm_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            ledpwm_AUX_CONTROLDP0 |= (ledpwm_AUX_CTRL_FIFO0_CLR);
        #else /* (ledpwm_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            ledpwm_AUX_CONTROLDP0 |= (ledpwm_AUX_CTRL_FIFO0_CLR);
            ledpwm_AUX_CONTROLDP1 |= (ledpwm_AUX_CTRL_FIFO0_CLR);
        #endif /* (ledpwm_Resolution == 8) */

        ledpwm_WriteCounter(ledpwm_INIT_PERIOD_VALUE);
    #endif /* (!ledpwm_UsingFixedFunction) */

    ledpwm_WritePeriod(ledpwm_INIT_PERIOD_VALUE);

        #if (ledpwm_UseOneCompareMode)
            ledpwm_WriteCompare(ledpwm_INIT_COMPARE_VALUE1);
        #else
            ledpwm_WriteCompare1(ledpwm_INIT_COMPARE_VALUE1);
            ledpwm_WriteCompare2(ledpwm_INIT_COMPARE_VALUE2);
        #endif /* (ledpwm_UseOneCompareMode) */

        #if (ledpwm_KillModeMinTime)
            ledpwm_WriteKillTime(ledpwm_MinimumKillTime);
        #endif /* (ledpwm_KillModeMinTime) */

        #if (ledpwm_DeadBandUsed)
            ledpwm_WriteDeadTime(ledpwm_INIT_DEAD_TIME);
        #endif /* (ledpwm_DeadBandUsed) */

    #if (ledpwm_UseStatus || ledpwm_UsingFixedFunction)
        ledpwm_SetInterruptMode(ledpwm_INIT_INTERRUPTS_MODE);
    #endif /* (ledpwm_UseStatus || ledpwm_UsingFixedFunction) */

    #if (ledpwm_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        ledpwm_GLOBAL_ENABLE |= ledpwm_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        ledpwm_CONTROL2 |= ledpwm_CTRL2_IRQ_SEL;
    #else
        #if(ledpwm_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ledpwm_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            ledpwm_STATUS_AUX_CTRL |= ledpwm_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(ledpwm_interruptState);

            /* Clear the FIFO to enable the ledpwm_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            ledpwm_ClearFIFO();
        #endif /* (ledpwm_UseStatus) */
    #endif /* (ledpwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledpwm_Enable
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
void ledpwm_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ledpwm_UsingFixedFunction)
        ledpwm_GLOBAL_ENABLE |= ledpwm_BLOCK_EN_MASK;
        ledpwm_GLOBAL_STBY_ENABLE |= ledpwm_BLOCK_STBY_EN_MASK;
    #endif /* (ledpwm_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (ledpwm_UseControl || ledpwm_UsingFixedFunction)
        ledpwm_CONTROL |= ledpwm_CTRL_ENABLE;
    #endif /* (ledpwm_UseControl || ledpwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ledpwm_Stop
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
void ledpwm_Stop(void) 
{
    #if (ledpwm_UseControl || ledpwm_UsingFixedFunction)
        ledpwm_CONTROL &= ((uint8)(~ledpwm_CTRL_ENABLE));
    #endif /* (ledpwm_UseControl || ledpwm_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (ledpwm_UsingFixedFunction)
        ledpwm_GLOBAL_ENABLE &= ((uint8)(~ledpwm_BLOCK_EN_MASK));
        ledpwm_GLOBAL_STBY_ENABLE &= ((uint8)(~ledpwm_BLOCK_STBY_EN_MASK));
    #endif /* (ledpwm_UsingFixedFunction) */
}

#if (ledpwm_UseOneCompareMode)
    #if (ledpwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ledpwm_SetCompareMode
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
        void ledpwm_SetCompareMode(uint8 comparemode) 
        {
            #if(ledpwm_UsingFixedFunction)

                #if(0 != ledpwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledpwm_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != ledpwm_CTRL_CMPMODE1_SHIFT) */

                ledpwm_CONTROL3 &= ((uint8)(~ledpwm_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                ledpwm_CONTROL3 |= comparemodemasked;

            #elif (ledpwm_UseControl)

                #if(0 != ledpwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << ledpwm_CTRL_CMPMODE1_SHIFT)) &
                                                ledpwm_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & ledpwm_CTRL_CMPMODE1_MASK;
                #endif /* (0 != ledpwm_CTRL_CMPMODE1_SHIFT) */

                #if(0 != ledpwm_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << ledpwm_CTRL_CMPMODE2_SHIFT)) &
                                               ledpwm_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & ledpwm_CTRL_CMPMODE2_MASK;
                #endif /* (0 != ledpwm_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                ledpwm_CONTROL &= ((uint8)(~(ledpwm_CTRL_CMPMODE1_MASK |
                                            ledpwm_CTRL_CMPMODE2_MASK)));
                ledpwm_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (ledpwm_UsingFixedFunction) */
        }
    #endif /* ledpwm_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (ledpwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ledpwm_SetCompareMode1
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
        void ledpwm_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != ledpwm_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledpwm_CTRL_CMPMODE1_SHIFT)) &
                                           ledpwm_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & ledpwm_CTRL_CMPMODE1_MASK;
            #endif /* (0 != ledpwm_CTRL_CMPMODE1_SHIFT) */

            #if (ledpwm_UseControl)
                ledpwm_CONTROL &= ((uint8)(~ledpwm_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                ledpwm_CONTROL |= comparemodemasked;
            #endif /* (ledpwm_UseControl) */
        }
    #endif /* ledpwm_CompareMode1SW */

#if (ledpwm_CompareMode2SW)


    /*******************************************************************************
    * Function Name: ledpwm_SetCompareMode2
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
    void ledpwm_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != ledpwm_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << ledpwm_CTRL_CMPMODE2_SHIFT)) &
                                                 ledpwm_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & ledpwm_CTRL_CMPMODE2_MASK;
        #endif /* (0 != ledpwm_CTRL_CMPMODE2_SHIFT) */

        #if (ledpwm_UseControl)
            ledpwm_CONTROL &= ((uint8)(~ledpwm_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            ledpwm_CONTROL |= comparemodemasked;
        #endif /* (ledpwm_UseControl) */
    }
    #endif /*ledpwm_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!ledpwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledpwm_WriteCounter
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
    void ledpwm_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(ledpwm_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: ledpwm_ReadCounter
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
    uint8 ledpwm_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(ledpwm_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(ledpwm_CAPTURE_LSB_PTR));
    }

    #if (ledpwm_UseStatus)


        /*******************************************************************************
        * Function Name: ledpwm_ClearFIFO
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
        void ledpwm_ClearFIFO(void) 
        {
            while(0u != (ledpwm_ReadStatusRegister() & ledpwm_STATUS_FIFONEMPTY))
            {
                (void)ledpwm_ReadCapture();
            }
        }

    #endif /* ledpwm_UseStatus */

#endif /* !ledpwm_UsingFixedFunction */


/*******************************************************************************
* Function Name: ledpwm_WritePeriod
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
void ledpwm_WritePeriod(uint8 period) 
{
    #if(ledpwm_UsingFixedFunction)
        CY_SET_REG16(ledpwm_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(ledpwm_PERIOD_LSB_PTR, period);
    #endif /* (ledpwm_UsingFixedFunction) */
}

#if (ledpwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ledpwm_WriteCompare
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
    void ledpwm_WriteCompare(uint8 compare) \
                                       
    {
        #if(ledpwm_UsingFixedFunction)
            CY_SET_REG16(ledpwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(ledpwm_COMPARE1_LSB_PTR, compare);
        #endif /* (ledpwm_UsingFixedFunction) */

        #if (ledpwm_PWMMode == ledpwm__B_PWM__DITHER)
            #if(ledpwm_UsingFixedFunction)
                CY_SET_REG16(ledpwm_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(ledpwm_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (ledpwm_UsingFixedFunction) */
        #endif /* (ledpwm_PWMMode == ledpwm__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: ledpwm_WriteCompare1
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
    void ledpwm_WriteCompare1(uint8 compare) \
                                        
    {
        #if(ledpwm_UsingFixedFunction)
            CY_SET_REG16(ledpwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(ledpwm_COMPARE1_LSB_PTR, compare);
        #endif /* (ledpwm_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: ledpwm_WriteCompare2
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
    void ledpwm_WriteCompare2(uint8 compare) \
                                        
    {
        #if(ledpwm_UsingFixedFunction)
            CY_SET_REG16(ledpwm_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(ledpwm_COMPARE2_LSB_PTR, compare);
        #endif /* (ledpwm_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (ledpwm_DeadBandUsed)


    /*******************************************************************************
    * Function Name: ledpwm_WriteDeadTime
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
    void ledpwm_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!ledpwm_DeadBand2_4)
            CY_SET_REG8(ledpwm_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            ledpwm_DEADBAND_COUNT &= ((uint8)(~ledpwm_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(ledpwm_DEADBAND_COUNT_SHIFT)
                ledpwm_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << ledpwm_DEADBAND_COUNT_SHIFT)) &
                                                    ledpwm_DEADBAND_COUNT_MASK;
            #else
                ledpwm_DEADBAND_COUNT |= deadtime & ledpwm_DEADBAND_COUNT_MASK;
            #endif /* (ledpwm_DEADBAND_COUNT_SHIFT) */

        #endif /* (!ledpwm_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: ledpwm_ReadDeadTime
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
    uint8 ledpwm_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!ledpwm_DeadBand2_4)
            return (CY_GET_REG8(ledpwm_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(ledpwm_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(ledpwm_DEADBAND_COUNT & ledpwm_DEADBAND_COUNT_MASK)) >>
                                                                           ledpwm_DEADBAND_COUNT_SHIFT));
            #else
                return (ledpwm_DEADBAND_COUNT & ledpwm_DEADBAND_COUNT_MASK);
            #endif /* (ledpwm_DEADBAND_COUNT_SHIFT) */
        #endif /* (!ledpwm_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (ledpwm_UseStatus || ledpwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledpwm_SetInterruptMode
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
    void ledpwm_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(ledpwm_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: ledpwm_ReadStatusRegister
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
    uint8 ledpwm_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(ledpwm_STATUS_PTR));
    }

#endif /* (ledpwm_UseStatus || ledpwm_UsingFixedFunction) */


#if (ledpwm_UseControl)


    /*******************************************************************************
    * Function Name: ledpwm_ReadControlRegister
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
    uint8 ledpwm_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(ledpwm_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: ledpwm_WriteControlRegister
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
    void ledpwm_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(ledpwm_CONTROL_PTR, control);
    }

#endif /* (ledpwm_UseControl) */


#if (!ledpwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ledpwm_ReadCapture
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
    uint8 ledpwm_ReadCapture(void) 
    {
        return (CY_GET_REG8(ledpwm_CAPTURE_LSB_PTR));
    }

#endif /* (!ledpwm_UsingFixedFunction) */


#if (ledpwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ledpwm_ReadCompare
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
    uint8 ledpwm_ReadCompare(void) 
    {
        #if(ledpwm_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(ledpwm_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(ledpwm_COMPARE1_LSB_PTR));
        #endif /* (ledpwm_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: ledpwm_ReadCompare1
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
    uint8 ledpwm_ReadCompare1(void) 
    {
        return (CY_GET_REG8(ledpwm_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: ledpwm_ReadCompare2
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
    uint8 ledpwm_ReadCompare2(void) 
    {
        return (CY_GET_REG8(ledpwm_COMPARE2_LSB_PTR));
    }

#endif /* (ledpwm_UseOneCompareMode) */


/*******************************************************************************
* Function Name: ledpwm_ReadPeriod
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
uint8 ledpwm_ReadPeriod(void) 
{
    #if(ledpwm_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ledpwm_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(ledpwm_PERIOD_LSB_PTR));
    #endif /* (ledpwm_UsingFixedFunction) */
}

#if ( ledpwm_KillModeMinTime)


    /*******************************************************************************
    * Function Name: ledpwm_WriteKillTime
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
    void ledpwm_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(ledpwm_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: ledpwm_ReadKillTime
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
    uint8 ledpwm_ReadKillTime(void) 
    {
        return (CY_GET_REG8(ledpwm_KILLMODEMINTIME_PTR));
    }

#endif /* ( ledpwm_KillModeMinTime) */

/* [] END OF FILE */
