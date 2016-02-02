/*******************************************************************************
* File Name: PWMRIGHT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PWMRIGHT
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWMRIGHT.h"

uint8 PWMRIGHT_initVar = 0u;


/*******************************************************************************
* Function Name: PWMRIGHT_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWMRIGHT configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWMRIGHT__QUAD == PWMRIGHT_CONFIG)
        PWMRIGHT_CONTROL_REG = PWMRIGHT_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMRIGHT_TRIG_CONTROL1_REG  = PWMRIGHT_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        PWMRIGHT_SetInterruptMode(PWMRIGHT_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        PWMRIGHT_SetCounterMode(PWMRIGHT_COUNT_DOWN);
        PWMRIGHT_WritePeriod(PWMRIGHT_QUAD_PERIOD_INIT_VALUE);
        PWMRIGHT_WriteCounter(PWMRIGHT_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (PWMRIGHT__QUAD == PWMRIGHT_CONFIG) */

    #if (PWMRIGHT__TIMER == PWMRIGHT_CONFIG)
        PWMRIGHT_CONTROL_REG = PWMRIGHT_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMRIGHT_TRIG_CONTROL1_REG  = PWMRIGHT_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMRIGHT_SetInterruptMode(PWMRIGHT_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        PWMRIGHT_WritePeriod(PWMRIGHT_TC_PERIOD_VALUE );

        #if (PWMRIGHT__COMPARE == PWMRIGHT_TC_COMP_CAP_MODE)
            PWMRIGHT_WriteCompare(PWMRIGHT_TC_COMPARE_VALUE);

            #if (1u == PWMRIGHT_TC_COMPARE_SWAP)
                PWMRIGHT_SetCompareSwap(1u);
                PWMRIGHT_WriteCompareBuf(PWMRIGHT_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWMRIGHT_TC_COMPARE_SWAP) */
        #endif  /* (PWMRIGHT__COMPARE == PWMRIGHT_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (PWMRIGHT_CY_TCPWM_V2 && PWMRIGHT_TIMER_UPDOWN_CNT_USED && !PWMRIGHT_CY_TCPWM_4000)
            PWMRIGHT_WriteCounter(1u);
        #elif(PWMRIGHT__COUNT_DOWN == PWMRIGHT_TC_COUNTER_MODE)
            PWMRIGHT_WriteCounter(PWMRIGHT_TC_PERIOD_VALUE);
        #else
            PWMRIGHT_WriteCounter(0u);
        #endif /* (PWMRIGHT_CY_TCPWM_V2 && PWMRIGHT_TIMER_UPDOWN_CNT_USED && !PWMRIGHT_CY_TCPWM_4000) */
    #endif  /* (PWMRIGHT__TIMER == PWMRIGHT_CONFIG) */

    #if (PWMRIGHT__PWM_SEL == PWMRIGHT_CONFIG)
        PWMRIGHT_CONTROL_REG = PWMRIGHT_CTRL_PWM_BASE_CONFIG;

        #if (PWMRIGHT__PWM_PR == PWMRIGHT_PWM_MODE)
            PWMRIGHT_CONTROL_REG |= PWMRIGHT_CTRL_PWM_RUN_MODE;
            PWMRIGHT_WriteCounter(PWMRIGHT_PWM_PR_INIT_VALUE);
        #else
            PWMRIGHT_CONTROL_REG |= PWMRIGHT_CTRL_PWM_ALIGN | PWMRIGHT_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (PWMRIGHT_CY_TCPWM_V2 && PWMRIGHT_PWM_UPDOWN_CNT_USED && !PWMRIGHT_CY_TCPWM_4000)
                PWMRIGHT_WriteCounter(1u);
            #elif (PWMRIGHT__RIGHT == PWMRIGHT_PWM_ALIGN)
                PWMRIGHT_WriteCounter(PWMRIGHT_PWM_PERIOD_VALUE);
            #else 
                PWMRIGHT_WriteCounter(0u);
            #endif  /* (PWMRIGHT_CY_TCPWM_V2 && PWMRIGHT_PWM_UPDOWN_CNT_USED && !PWMRIGHT_CY_TCPWM_4000) */
        #endif  /* (PWMRIGHT__PWM_PR == PWMRIGHT_PWM_MODE) */

        #if (PWMRIGHT__PWM_DT == PWMRIGHT_PWM_MODE)
            PWMRIGHT_CONTROL_REG |= PWMRIGHT_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (PWMRIGHT__PWM_DT == PWMRIGHT_PWM_MODE) */

        #if (PWMRIGHT__PWM == PWMRIGHT_PWM_MODE)
            PWMRIGHT_CONTROL_REG |= PWMRIGHT_CTRL_PWM_PRESCALER;
        #endif  /* (PWMRIGHT__PWM == PWMRIGHT_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        PWMRIGHT_TRIG_CONTROL1_REG  = PWMRIGHT_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMRIGHT_SetInterruptMode(PWMRIGHT_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (PWMRIGHT__PWM_PR == PWMRIGHT_PWM_MODE)
            PWMRIGHT_TRIG_CONTROL2_REG =
                    (PWMRIGHT_CC_MATCH_NO_CHANGE    |
                    PWMRIGHT_OVERLOW_NO_CHANGE      |
                    PWMRIGHT_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWMRIGHT__LEFT == PWMRIGHT_PWM_ALIGN)
                PWMRIGHT_TRIG_CONTROL2_REG = PWMRIGHT_PWM_MODE_LEFT;
            #endif  /* ( PWMRIGHT_PWM_LEFT == PWMRIGHT_PWM_ALIGN) */

            #if (PWMRIGHT__RIGHT == PWMRIGHT_PWM_ALIGN)
                PWMRIGHT_TRIG_CONTROL2_REG = PWMRIGHT_PWM_MODE_RIGHT;
            #endif  /* ( PWMRIGHT_PWM_RIGHT == PWMRIGHT_PWM_ALIGN) */

            #if (PWMRIGHT__CENTER == PWMRIGHT_PWM_ALIGN)
                PWMRIGHT_TRIG_CONTROL2_REG = PWMRIGHT_PWM_MODE_CENTER;
            #endif  /* ( PWMRIGHT_PWM_CENTER == PWMRIGHT_PWM_ALIGN) */

            #if (PWMRIGHT__ASYMMETRIC == PWMRIGHT_PWM_ALIGN)
                PWMRIGHT_TRIG_CONTROL2_REG = PWMRIGHT_PWM_MODE_ASYM;
            #endif  /* (PWMRIGHT__ASYMMETRIC == PWMRIGHT_PWM_ALIGN) */
        #endif  /* (PWMRIGHT__PWM_PR == PWMRIGHT_PWM_MODE) */

        /* Set other values from customizer */
        PWMRIGHT_WritePeriod(PWMRIGHT_PWM_PERIOD_VALUE );
        PWMRIGHT_WriteCompare(PWMRIGHT_PWM_COMPARE_VALUE);

        #if (1u == PWMRIGHT_PWM_COMPARE_SWAP)
            PWMRIGHT_SetCompareSwap(1u);
            PWMRIGHT_WriteCompareBuf(PWMRIGHT_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWMRIGHT_PWM_COMPARE_SWAP) */

        #if (1u == PWMRIGHT_PWM_PERIOD_SWAP)
            PWMRIGHT_SetPeriodSwap(1u);
            PWMRIGHT_WritePeriodBuf(PWMRIGHT_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWMRIGHT_PWM_PERIOD_SWAP) */
    #endif  /* (PWMRIGHT__PWM_SEL == PWMRIGHT_CONFIG) */
    
}


/*******************************************************************************
* Function Name: PWMRIGHT_Enable
********************************************************************************
*
* Summary:
*  Enables the PWMRIGHT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWMRIGHT_BLOCK_CONTROL_REG |= PWMRIGHT_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PWMRIGHT__PWM_SEL == PWMRIGHT_CONFIG)
        #if (0u == PWMRIGHT_PWM_START_SIGNAL_PRESENT)
            PWMRIGHT_TriggerCommand(PWMRIGHT_MASK, PWMRIGHT_CMD_START);
        #endif /* (0u == PWMRIGHT_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWMRIGHT__PWM_SEL == PWMRIGHT_CONFIG) */

    #if (PWMRIGHT__TIMER == PWMRIGHT_CONFIG)
        #if (0u == PWMRIGHT_TC_START_SIGNAL_PRESENT)
            PWMRIGHT_TriggerCommand(PWMRIGHT_MASK, PWMRIGHT_CMD_START);
        #endif /* (0u == PWMRIGHT_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWMRIGHT__TIMER == PWMRIGHT_CONFIG) */
}


/*******************************************************************************
* Function Name: PWMRIGHT_Start
********************************************************************************
*
* Summary:
*  Initializes the PWMRIGHT with default customizer
*  values when called the first time and enables the PWMRIGHT.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMRIGHT_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWMRIGHT_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PWMRIGHT_Start() routine.
*
*******************************************************************************/
void PWMRIGHT_Start(void)
{
    if (0u == PWMRIGHT_initVar)
    {
        PWMRIGHT_Init();
        PWMRIGHT_initVar = 1u;
    }

    PWMRIGHT_Enable();
}


/*******************************************************************************
* Function Name: PWMRIGHT_Stop
********************************************************************************
*
* Summary:
*  Disables the PWMRIGHT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_BLOCK_CONTROL_REG &= (uint32)~PWMRIGHT_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWMRIGHT. This function is used when
*  configured as a generic PWMRIGHT and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWMRIGHT to operate in
*   Values:
*   - PWMRIGHT_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWMRIGHT_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWMRIGHT_MODE_QUAD - Quadrature decoder
*         - PWMRIGHT_MODE_PWM - PWM
*         - PWMRIGHT_MODE_PWM_DT - PWM with dead time
*         - PWMRIGHT_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_MODE_MASK;
    PWMRIGHT_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWMRIGHT_MODE_X1 - Counts on phi 1 rising
*         - PWMRIGHT_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWMRIGHT_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_QUAD_MODE_MASK;
    PWMRIGHT_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWMRIGHT_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWMRIGHT_PRESCALE_DIVBY2    - Divide by 2
*         - PWMRIGHT_PRESCALE_DIVBY4    - Divide by 4
*         - PWMRIGHT_PRESCALE_DIVBY8    - Divide by 8
*         - PWMRIGHT_PRESCALE_DIVBY16   - Divide by 16
*         - PWMRIGHT_PRESCALE_DIVBY32   - Divide by 32
*         - PWMRIGHT_PRESCALE_DIVBY64   - Divide by 64
*         - PWMRIGHT_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_PRESCALER_MASK;
    PWMRIGHT_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWMRIGHT runs
*  continuously or stops when terminal count is reached.  By default the
*  PWMRIGHT operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_ONESHOT_MASK;
    PWMRIGHT_CONTROL_REG |= ((uint32)((oneShotEnable & PWMRIGHT_1BIT_MASK) <<
                                                               PWMRIGHT_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPWMMode(uint32 modeMask)
{
    PWMRIGHT_TRIG_CONTROL2_REG = (modeMask & PWMRIGHT_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWMRIGHT_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_PWM_SYNC_KILL_MASK;
    PWMRIGHT_CONTROL_REG |= ((uint32)((syncKillEnable & PWMRIGHT_1BIT_MASK)  <<
                                               PWMRIGHT_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_PWM_STOP_KILL_MASK;
    PWMRIGHT_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWMRIGHT_1BIT_MASK)  <<
                                                         PWMRIGHT_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_PRESCALER_MASK;
    PWMRIGHT_CONTROL_REG |= ((uint32)((deadTime & PWMRIGHT_8BIT_MASK) <<
                                                          PWMRIGHT_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - PWMRIGHT_INVERT_LINE   - Inverts the line output
*         - PWMRIGHT_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_INV_OUT_MASK;
    PWMRIGHT_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWMRIGHT_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_WriteCounter(uint32 count)
{
    PWMRIGHT_COUNTER_REG = (count & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadCounter(void)
{
    return (PWMRIGHT_COUNTER_REG & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PWMRIGHT_COUNT_UP       - Counts up
*     - PWMRIGHT_COUNT_DOWN     - Counts down
*     - PWMRIGHT_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWMRIGHT_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_UPDOWN_MASK;
    PWMRIGHT_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_WritePeriod(uint32 period)
{
    PWMRIGHT_PERIOD_REG = (period & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadPeriod(void)
{
    return (PWMRIGHT_PERIOD_REG & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_RELOAD_CC_MASK;
    PWMRIGHT_CONTROL_REG |= (swapEnable & PWMRIGHT_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_WritePeriodBuf(uint32 periodBuf)
{
    PWMRIGHT_PERIOD_BUF_REG = (periodBuf & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadPeriodBuf(void)
{
    return (PWMRIGHT_PERIOD_BUF_REG & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_CONTROL_REG &= (uint32)~PWMRIGHT_RELOAD_PERIOD_MASK;
    PWMRIGHT_CONTROL_REG |= ((uint32)((swapEnable & PWMRIGHT_1BIT_MASK) <<
                                                            PWMRIGHT_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_WriteCompare(uint32 compare)
{
    #if (PWMRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */

    #if (PWMRIGHT_CY_TCPWM_4000)
        currentMode = ((PWMRIGHT_CONTROL_REG & PWMRIGHT_UPDOWN_MASK) >> PWMRIGHT_UPDOWN_SHIFT);

        if (((uint32)PWMRIGHT__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)PWMRIGHT__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */
    
    PWMRIGHT_COMP_CAP_REG = (compare & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadCompare(void)
{
    #if (PWMRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */

    #if (PWMRIGHT_CY_TCPWM_4000)
        currentMode = ((PWMRIGHT_CONTROL_REG & PWMRIGHT_UPDOWN_MASK) >> PWMRIGHT_UPDOWN_SHIFT);
        
        regVal = PWMRIGHT_COMP_CAP_REG;
        
        if (((uint32)PWMRIGHT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMRIGHT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMRIGHT_16BIT_MASK);
    #else
        return (PWMRIGHT_COMP_CAP_REG & PWMRIGHT_16BIT_MASK);
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMRIGHT_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_WriteCompareBuf(uint32 compareBuf)
{
    #if (PWMRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */

    #if (PWMRIGHT_CY_TCPWM_4000)
        currentMode = ((PWMRIGHT_CONTROL_REG & PWMRIGHT_UPDOWN_MASK) >> PWMRIGHT_UPDOWN_SHIFT);

        if (((uint32)PWMRIGHT__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)PWMRIGHT__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */
    
    PWMRIGHT_COMP_CAP_BUF_REG = (compareBuf & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadCompareBuf(void)
{
    #if (PWMRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */

    #if (PWMRIGHT_CY_TCPWM_4000)
        currentMode = ((PWMRIGHT_CONTROL_REG & PWMRIGHT_UPDOWN_MASK) >> PWMRIGHT_UPDOWN_SHIFT);

        regVal = PWMRIGHT_COMP_CAP_BUF_REG;
        
        if (((uint32)PWMRIGHT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMRIGHT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMRIGHT_16BIT_MASK);
    #else
        return (PWMRIGHT_COMP_CAP_BUF_REG & PWMRIGHT_16BIT_MASK);
    #endif /* (PWMRIGHT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadCapture(void)
{
    return (PWMRIGHT_COMP_CAP_REG & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 PWMRIGHT_ReadCaptureBuf(void)
{
    return (PWMRIGHT_COMP_CAP_BUF_REG & PWMRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMRIGHT_TRIG_LEVEL     - Level
*     - PWMRIGHT_TRIG_RISING    - Rising edge
*     - PWMRIGHT_TRIG_FALLING   - Falling edge
*     - PWMRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_TRIG_CONTROL1_REG &= (uint32)~PWMRIGHT_CAPTURE_MASK;
    PWMRIGHT_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMRIGHT_TRIG_LEVEL     - Level
*     - PWMRIGHT_TRIG_RISING    - Rising edge
*     - PWMRIGHT_TRIG_FALLING   - Falling edge
*     - PWMRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_TRIG_CONTROL1_REG &= (uint32)~PWMRIGHT_RELOAD_MASK;
    PWMRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMRIGHT_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMRIGHT_TRIG_LEVEL     - Level
*     - PWMRIGHT_TRIG_RISING    - Rising edge
*     - PWMRIGHT_TRIG_FALLING   - Falling edge
*     - PWMRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_TRIG_CONTROL1_REG &= (uint32)~PWMRIGHT_START_MASK;
    PWMRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMRIGHT_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMRIGHT_TRIG_LEVEL     - Level
*     - PWMRIGHT_TRIG_RISING    - Rising edge
*     - PWMRIGHT_TRIG_FALLING   - Falling edge
*     - PWMRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_TRIG_CONTROL1_REG &= (uint32)~PWMRIGHT_STOP_MASK;
    PWMRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMRIGHT_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMRIGHT_TRIG_LEVEL     - Level
*     - PWMRIGHT_TRIG_RISING    - Rising edge
*     - PWMRIGHT_TRIG_FALLING   - Falling edge
*     - PWMRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_TRIG_CONTROL1_REG &= (uint32)~PWMRIGHT_COUNT_MASK;
    PWMRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMRIGHT_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - PWMRIGHT_CMD_CAPTURE    - Trigger Capture command
*     - PWMRIGHT_CMD_RELOAD     - Trigger Reload command
*     - PWMRIGHT_CMD_STOP       - Trigger Stop command
*     - PWMRIGHT_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMRIGHT_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWMRIGHT.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWMRIGHT_STATUS_DOWN    - Set if counting down
*     - PWMRIGHT_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWMRIGHT_ReadStatus(void)
{
    return ((PWMRIGHT_STATUS_REG >> PWMRIGHT_RUNNING_STATUS_SHIFT) |
            (PWMRIGHT_STATUS_REG & PWMRIGHT_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWMRIGHT_INTR_MASK_TC       - Terminal count mask
*     - PWMRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetInterruptMode(uint32 interruptMask)
{
    PWMRIGHT_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWMRIGHT_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - PWMRIGHT_INTR_MASK_TC       - Terminal count mask
*     - PWMRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMRIGHT_GetInterruptSourceMasked(void)
{
    return (PWMRIGHT_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWMRIGHT_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - PWMRIGHT_INTR_MASK_TC       - Terminal count mask
*     - PWMRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMRIGHT_GetInterruptSource(void)
{
    return (PWMRIGHT_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWMRIGHT_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWMRIGHT_INTR_MASK_TC       - Terminal count mask
*     - PWMRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_ClearInterrupt(uint32 interruptMask)
{
    PWMRIGHT_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWMRIGHT_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWMRIGHT_INTR_MASK_TC       - Terminal count mask
*     - PWMRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMRIGHT_SetInterrupt(uint32 interruptMask)
{
    PWMRIGHT_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
