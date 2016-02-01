/*******************************************************************************
* File Name: PWMLEFT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PWMLEFT
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

#include "PWMLEFT.h"

uint8 PWMLEFT_initVar = 0u;


/*******************************************************************************
* Function Name: PWMLEFT_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWMLEFT configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWMLEFT__QUAD == PWMLEFT_CONFIG)
        PWMLEFT_CONTROL_REG = PWMLEFT_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMLEFT_TRIG_CONTROL1_REG  = PWMLEFT_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        PWMLEFT_SetInterruptMode(PWMLEFT_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        PWMLEFT_SetCounterMode(PWMLEFT_COUNT_DOWN);
        PWMLEFT_WritePeriod(PWMLEFT_QUAD_PERIOD_INIT_VALUE);
        PWMLEFT_WriteCounter(PWMLEFT_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (PWMLEFT__QUAD == PWMLEFT_CONFIG) */

    #if (PWMLEFT__TIMER == PWMLEFT_CONFIG)
        PWMLEFT_CONTROL_REG = PWMLEFT_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMLEFT_TRIG_CONTROL1_REG  = PWMLEFT_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMLEFT_SetInterruptMode(PWMLEFT_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        PWMLEFT_WritePeriod(PWMLEFT_TC_PERIOD_VALUE );

        #if (PWMLEFT__COMPARE == PWMLEFT_TC_COMP_CAP_MODE)
            PWMLEFT_WriteCompare(PWMLEFT_TC_COMPARE_VALUE);

            #if (1u == PWMLEFT_TC_COMPARE_SWAP)
                PWMLEFT_SetCompareSwap(1u);
                PWMLEFT_WriteCompareBuf(PWMLEFT_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWMLEFT_TC_COMPARE_SWAP) */
        #endif  /* (PWMLEFT__COMPARE == PWMLEFT_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (PWMLEFT_CY_TCPWM_V2 && PWMLEFT_TIMER_UPDOWN_CNT_USED && !PWMLEFT_CY_TCPWM_4000)
            PWMLEFT_WriteCounter(1u);
        #elif(PWMLEFT__COUNT_DOWN == PWMLEFT_TC_COUNTER_MODE)
            PWMLEFT_WriteCounter(PWMLEFT_TC_PERIOD_VALUE);
        #else
            PWMLEFT_WriteCounter(0u);
        #endif /* (PWMLEFT_CY_TCPWM_V2 && PWMLEFT_TIMER_UPDOWN_CNT_USED && !PWMLEFT_CY_TCPWM_4000) */
    #endif  /* (PWMLEFT__TIMER == PWMLEFT_CONFIG) */

    #if (PWMLEFT__PWM_SEL == PWMLEFT_CONFIG)
        PWMLEFT_CONTROL_REG = PWMLEFT_CTRL_PWM_BASE_CONFIG;

        #if (PWMLEFT__PWM_PR == PWMLEFT_PWM_MODE)
            PWMLEFT_CONTROL_REG |= PWMLEFT_CTRL_PWM_RUN_MODE;
            PWMLEFT_WriteCounter(PWMLEFT_PWM_PR_INIT_VALUE);
        #else
            PWMLEFT_CONTROL_REG |= PWMLEFT_CTRL_PWM_ALIGN | PWMLEFT_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (PWMLEFT_CY_TCPWM_V2 && PWMLEFT_PWM_UPDOWN_CNT_USED && !PWMLEFT_CY_TCPWM_4000)
                PWMLEFT_WriteCounter(1u);
            #elif (PWMLEFT__RIGHT == PWMLEFT_PWM_ALIGN)
                PWMLEFT_WriteCounter(PWMLEFT_PWM_PERIOD_VALUE);
            #else 
                PWMLEFT_WriteCounter(0u);
            #endif  /* (PWMLEFT_CY_TCPWM_V2 && PWMLEFT_PWM_UPDOWN_CNT_USED && !PWMLEFT_CY_TCPWM_4000) */
        #endif  /* (PWMLEFT__PWM_PR == PWMLEFT_PWM_MODE) */

        #if (PWMLEFT__PWM_DT == PWMLEFT_PWM_MODE)
            PWMLEFT_CONTROL_REG |= PWMLEFT_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (PWMLEFT__PWM_DT == PWMLEFT_PWM_MODE) */

        #if (PWMLEFT__PWM == PWMLEFT_PWM_MODE)
            PWMLEFT_CONTROL_REG |= PWMLEFT_CTRL_PWM_PRESCALER;
        #endif  /* (PWMLEFT__PWM == PWMLEFT_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        PWMLEFT_TRIG_CONTROL1_REG  = PWMLEFT_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMLEFT_SetInterruptMode(PWMLEFT_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (PWMLEFT__PWM_PR == PWMLEFT_PWM_MODE)
            PWMLEFT_TRIG_CONTROL2_REG =
                    (PWMLEFT_CC_MATCH_NO_CHANGE    |
                    PWMLEFT_OVERLOW_NO_CHANGE      |
                    PWMLEFT_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWMLEFT__LEFT == PWMLEFT_PWM_ALIGN)
                PWMLEFT_TRIG_CONTROL2_REG = PWMLEFT_PWM_MODE_LEFT;
            #endif  /* ( PWMLEFT_PWM_LEFT == PWMLEFT_PWM_ALIGN) */

            #if (PWMLEFT__RIGHT == PWMLEFT_PWM_ALIGN)
                PWMLEFT_TRIG_CONTROL2_REG = PWMLEFT_PWM_MODE_RIGHT;
            #endif  /* ( PWMLEFT_PWM_RIGHT == PWMLEFT_PWM_ALIGN) */

            #if (PWMLEFT__CENTER == PWMLEFT_PWM_ALIGN)
                PWMLEFT_TRIG_CONTROL2_REG = PWMLEFT_PWM_MODE_CENTER;
            #endif  /* ( PWMLEFT_PWM_CENTER == PWMLEFT_PWM_ALIGN) */

            #if (PWMLEFT__ASYMMETRIC == PWMLEFT_PWM_ALIGN)
                PWMLEFT_TRIG_CONTROL2_REG = PWMLEFT_PWM_MODE_ASYM;
            #endif  /* (PWMLEFT__ASYMMETRIC == PWMLEFT_PWM_ALIGN) */
        #endif  /* (PWMLEFT__PWM_PR == PWMLEFT_PWM_MODE) */

        /* Set other values from customizer */
        PWMLEFT_WritePeriod(PWMLEFT_PWM_PERIOD_VALUE );
        PWMLEFT_WriteCompare(PWMLEFT_PWM_COMPARE_VALUE);

        #if (1u == PWMLEFT_PWM_COMPARE_SWAP)
            PWMLEFT_SetCompareSwap(1u);
            PWMLEFT_WriteCompareBuf(PWMLEFT_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWMLEFT_PWM_COMPARE_SWAP) */

        #if (1u == PWMLEFT_PWM_PERIOD_SWAP)
            PWMLEFT_SetPeriodSwap(1u);
            PWMLEFT_WritePeriodBuf(PWMLEFT_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWMLEFT_PWM_PERIOD_SWAP) */
    #endif  /* (PWMLEFT__PWM_SEL == PWMLEFT_CONFIG) */
    
}


/*******************************************************************************
* Function Name: PWMLEFT_Enable
********************************************************************************
*
* Summary:
*  Enables the PWMLEFT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWMLEFT_BLOCK_CONTROL_REG |= PWMLEFT_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PWMLEFT__PWM_SEL == PWMLEFT_CONFIG)
        #if (0u == PWMLEFT_PWM_START_SIGNAL_PRESENT)
            PWMLEFT_TriggerCommand(PWMLEFT_MASK, PWMLEFT_CMD_START);
        #endif /* (0u == PWMLEFT_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWMLEFT__PWM_SEL == PWMLEFT_CONFIG) */

    #if (PWMLEFT__TIMER == PWMLEFT_CONFIG)
        #if (0u == PWMLEFT_TC_START_SIGNAL_PRESENT)
            PWMLEFT_TriggerCommand(PWMLEFT_MASK, PWMLEFT_CMD_START);
        #endif /* (0u == PWMLEFT_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWMLEFT__TIMER == PWMLEFT_CONFIG) */
}


/*******************************************************************************
* Function Name: PWMLEFT_Start
********************************************************************************
*
* Summary:
*  Initializes the PWMLEFT with default customizer
*  values when called the first time and enables the PWMLEFT.
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
*  PWMLEFT_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWMLEFT_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PWMLEFT_Start() routine.
*
*******************************************************************************/
void PWMLEFT_Start(void)
{
    if (0u == PWMLEFT_initVar)
    {
        PWMLEFT_Init();
        PWMLEFT_initVar = 1u;
    }

    PWMLEFT_Enable();
}


/*******************************************************************************
* Function Name: PWMLEFT_Stop
********************************************************************************
*
* Summary:
*  Disables the PWMLEFT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_BLOCK_CONTROL_REG &= (uint32)~PWMLEFT_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWMLEFT. This function is used when
*  configured as a generic PWMLEFT and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWMLEFT to operate in
*   Values:
*   - PWMLEFT_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWMLEFT_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWMLEFT_MODE_QUAD - Quadrature decoder
*         - PWMLEFT_MODE_PWM - PWM
*         - PWMLEFT_MODE_PWM_DT - PWM with dead time
*         - PWMLEFT_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_MODE_MASK;
    PWMLEFT_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWMLEFT_MODE_X1 - Counts on phi 1 rising
*         - PWMLEFT_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWMLEFT_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_QUAD_MODE_MASK;
    PWMLEFT_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWMLEFT_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWMLEFT_PRESCALE_DIVBY2    - Divide by 2
*         - PWMLEFT_PRESCALE_DIVBY4    - Divide by 4
*         - PWMLEFT_PRESCALE_DIVBY8    - Divide by 8
*         - PWMLEFT_PRESCALE_DIVBY16   - Divide by 16
*         - PWMLEFT_PRESCALE_DIVBY32   - Divide by 32
*         - PWMLEFT_PRESCALE_DIVBY64   - Divide by 64
*         - PWMLEFT_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_PRESCALER_MASK;
    PWMLEFT_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWMLEFT runs
*  continuously or stops when terminal count is reached.  By default the
*  PWMLEFT operates in the continuous mode.
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
void PWMLEFT_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_ONESHOT_MASK;
    PWMLEFT_CONTROL_REG |= ((uint32)((oneShotEnable & PWMLEFT_1BIT_MASK) <<
                                                               PWMLEFT_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPWMMode
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
void PWMLEFT_SetPWMMode(uint32 modeMask)
{
    PWMLEFT_TRIG_CONTROL2_REG = (modeMask & PWMLEFT_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWMLEFT_SetPWMSyncKill
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
void PWMLEFT_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_PWM_SYNC_KILL_MASK;
    PWMLEFT_CONTROL_REG |= ((uint32)((syncKillEnable & PWMLEFT_1BIT_MASK)  <<
                                               PWMLEFT_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPWMStopOnKill
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
void PWMLEFT_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_PWM_STOP_KILL_MASK;
    PWMLEFT_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWMLEFT_1BIT_MASK)  <<
                                                         PWMLEFT_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPWMDeadTime
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
void PWMLEFT_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_PRESCALER_MASK;
    PWMLEFT_CONTROL_REG |= ((uint32)((deadTime & PWMLEFT_8BIT_MASK) <<
                                                          PWMLEFT_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPWMInvert
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
*         - PWMLEFT_INVERT_LINE   - Inverts the line output
*         - PWMLEFT_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_INV_OUT_MASK;
    PWMLEFT_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWMLEFT_WriteCounter
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
void PWMLEFT_WriteCounter(uint32 count)
{
    PWMLEFT_COUNTER_REG = (count & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadCounter
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
uint32 PWMLEFT_ReadCounter(void)
{
    return (PWMLEFT_COUNTER_REG & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PWMLEFT_COUNT_UP       - Counts up
*     - PWMLEFT_COUNT_DOWN     - Counts down
*     - PWMLEFT_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWMLEFT_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_UPDOWN_MASK;
    PWMLEFT_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_WritePeriod
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
void PWMLEFT_WritePeriod(uint32 period)
{
    PWMLEFT_PERIOD_REG = (period & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadPeriod
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
uint32 PWMLEFT_ReadPeriod(void)
{
    return (PWMLEFT_PERIOD_REG & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetCompareSwap
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
void PWMLEFT_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_RELOAD_CC_MASK;
    PWMLEFT_CONTROL_REG |= (swapEnable & PWMLEFT_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_WritePeriodBuf
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
void PWMLEFT_WritePeriodBuf(uint32 periodBuf)
{
    PWMLEFT_PERIOD_BUF_REG = (periodBuf & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadPeriodBuf
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
uint32 PWMLEFT_ReadPeriodBuf(void)
{
    return (PWMLEFT_PERIOD_BUF_REG & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetPeriodSwap
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
void PWMLEFT_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_CONTROL_REG &= (uint32)~PWMLEFT_RELOAD_PERIOD_MASK;
    PWMLEFT_CONTROL_REG |= ((uint32)((swapEnable & PWMLEFT_1BIT_MASK) <<
                                                            PWMLEFT_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_WriteCompare
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
void PWMLEFT_WriteCompare(uint32 compare)
{
    #if (PWMLEFT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMLEFT_CY_TCPWM_4000) */

    #if (PWMLEFT_CY_TCPWM_4000)
        currentMode = ((PWMLEFT_CONTROL_REG & PWMLEFT_UPDOWN_MASK) >> PWMLEFT_UPDOWN_SHIFT);

        if (((uint32)PWMLEFT__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)PWMLEFT__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (PWMLEFT_CY_TCPWM_4000) */
    
    PWMLEFT_COMP_CAP_REG = (compare & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadCompare
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
uint32 PWMLEFT_ReadCompare(void)
{
    #if (PWMLEFT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMLEFT_CY_TCPWM_4000) */

    #if (PWMLEFT_CY_TCPWM_4000)
        currentMode = ((PWMLEFT_CONTROL_REG & PWMLEFT_UPDOWN_MASK) >> PWMLEFT_UPDOWN_SHIFT);
        
        regVal = PWMLEFT_COMP_CAP_REG;
        
        if (((uint32)PWMLEFT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMLEFT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMLEFT_16BIT_MASK);
    #else
        return (PWMLEFT_COMP_CAP_REG & PWMLEFT_16BIT_MASK);
    #endif /* (PWMLEFT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMLEFT_WriteCompareBuf
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
void PWMLEFT_WriteCompareBuf(uint32 compareBuf)
{
    #if (PWMLEFT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMLEFT_CY_TCPWM_4000) */

    #if (PWMLEFT_CY_TCPWM_4000)
        currentMode = ((PWMLEFT_CONTROL_REG & PWMLEFT_UPDOWN_MASK) >> PWMLEFT_UPDOWN_SHIFT);

        if (((uint32)PWMLEFT__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)PWMLEFT__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (PWMLEFT_CY_TCPWM_4000) */
    
    PWMLEFT_COMP_CAP_BUF_REG = (compareBuf & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadCompareBuf
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
uint32 PWMLEFT_ReadCompareBuf(void)
{
    #if (PWMLEFT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMLEFT_CY_TCPWM_4000) */

    #if (PWMLEFT_CY_TCPWM_4000)
        currentMode = ((PWMLEFT_CONTROL_REG & PWMLEFT_UPDOWN_MASK) >> PWMLEFT_UPDOWN_SHIFT);

        regVal = PWMLEFT_COMP_CAP_BUF_REG;
        
        if (((uint32)PWMLEFT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMLEFT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMLEFT_16BIT_MASK);
    #else
        return (PWMLEFT_COMP_CAP_BUF_REG & PWMLEFT_16BIT_MASK);
    #endif /* (PWMLEFT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadCapture
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
uint32 PWMLEFT_ReadCapture(void)
{
    return (PWMLEFT_COMP_CAP_REG & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadCaptureBuf
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
uint32 PWMLEFT_ReadCaptureBuf(void)
{
    return (PWMLEFT_COMP_CAP_BUF_REG & PWMLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetCaptureMode
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
*     - PWMLEFT_TRIG_LEVEL     - Level
*     - PWMLEFT_TRIG_RISING    - Rising edge
*     - PWMLEFT_TRIG_FALLING   - Falling edge
*     - PWMLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_TRIG_CONTROL1_REG &= (uint32)~PWMLEFT_CAPTURE_MASK;
    PWMLEFT_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMLEFT_TRIG_LEVEL     - Level
*     - PWMLEFT_TRIG_RISING    - Rising edge
*     - PWMLEFT_TRIG_FALLING   - Falling edge
*     - PWMLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_TRIG_CONTROL1_REG &= (uint32)~PWMLEFT_RELOAD_MASK;
    PWMLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMLEFT_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMLEFT_TRIG_LEVEL     - Level
*     - PWMLEFT_TRIG_RISING    - Rising edge
*     - PWMLEFT_TRIG_FALLING   - Falling edge
*     - PWMLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_TRIG_CONTROL1_REG &= (uint32)~PWMLEFT_START_MASK;
    PWMLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMLEFT_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMLEFT_TRIG_LEVEL     - Level
*     - PWMLEFT_TRIG_RISING    - Rising edge
*     - PWMLEFT_TRIG_FALLING   - Falling edge
*     - PWMLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_TRIG_CONTROL1_REG &= (uint32)~PWMLEFT_STOP_MASK;
    PWMLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMLEFT_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMLEFT_TRIG_LEVEL     - Level
*     - PWMLEFT_TRIG_RISING    - Rising edge
*     - PWMLEFT_TRIG_FALLING   - Falling edge
*     - PWMLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_TRIG_CONTROL1_REG &= (uint32)~PWMLEFT_COUNT_MASK;
    PWMLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMLEFT_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_TriggerCommand
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
*     - PWMLEFT_CMD_CAPTURE    - Trigger Capture command
*     - PWMLEFT_CMD_RELOAD     - Trigger Reload command
*     - PWMLEFT_CMD_STOP       - Trigger Stop command
*     - PWMLEFT_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMLEFT_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMLEFT_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWMLEFT.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWMLEFT_STATUS_DOWN    - Set if counting down
*     - PWMLEFT_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWMLEFT_ReadStatus(void)
{
    return ((PWMLEFT_STATUS_REG >> PWMLEFT_RUNNING_STATUS_SHIFT) |
            (PWMLEFT_STATUS_REG & PWMLEFT_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWMLEFT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWMLEFT_INTR_MASK_TC       - Terminal count mask
*     - PWMLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetInterruptMode(uint32 interruptMask)
{
    PWMLEFT_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWMLEFT_GetInterruptSourceMasked
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
*     - PWMLEFT_INTR_MASK_TC       - Terminal count mask
*     - PWMLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMLEFT_GetInterruptSourceMasked(void)
{
    return (PWMLEFT_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWMLEFT_GetInterruptSource
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
*     - PWMLEFT_INTR_MASK_TC       - Terminal count mask
*     - PWMLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMLEFT_GetInterruptSource(void)
{
    return (PWMLEFT_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWMLEFT_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWMLEFT_INTR_MASK_TC       - Terminal count mask
*     - PWMLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_ClearInterrupt(uint32 interruptMask)
{
    PWMLEFT_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWMLEFT_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWMLEFT_INTR_MASK_TC       - Terminal count mask
*     - PWMLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMLEFT_SetInterrupt(uint32 interruptMask)
{
    PWMLEFT_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
