/*******************************************************************************
* File Name: QDRIGHT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the QDRIGHT
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

#include "QDRIGHT.h"

uint8 QDRIGHT_initVar = 0u;


/*******************************************************************************
* Function Name: QDRIGHT_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default QDRIGHT configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (QDRIGHT__QUAD == QDRIGHT_CONFIG)
        QDRIGHT_CONTROL_REG = QDRIGHT_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        QDRIGHT_TRIG_CONTROL1_REG  = QDRIGHT_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        QDRIGHT_SetInterruptMode(QDRIGHT_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        QDRIGHT_SetCounterMode(QDRIGHT_COUNT_DOWN);
        QDRIGHT_WritePeriod(QDRIGHT_QUAD_PERIOD_INIT_VALUE);
        QDRIGHT_WriteCounter(QDRIGHT_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (QDRIGHT__QUAD == QDRIGHT_CONFIG) */

    #if (QDRIGHT__TIMER == QDRIGHT_CONFIG)
        QDRIGHT_CONTROL_REG = QDRIGHT_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        QDRIGHT_TRIG_CONTROL1_REG  = QDRIGHT_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        QDRIGHT_SetInterruptMode(QDRIGHT_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        QDRIGHT_WritePeriod(QDRIGHT_TC_PERIOD_VALUE );

        #if (QDRIGHT__COMPARE == QDRIGHT_TC_COMP_CAP_MODE)
            QDRIGHT_WriteCompare(QDRIGHT_TC_COMPARE_VALUE);

            #if (1u == QDRIGHT_TC_COMPARE_SWAP)
                QDRIGHT_SetCompareSwap(1u);
                QDRIGHT_WriteCompareBuf(QDRIGHT_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == QDRIGHT_TC_COMPARE_SWAP) */
        #endif  /* (QDRIGHT__COMPARE == QDRIGHT_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (QDRIGHT_CY_TCPWM_V2 && QDRIGHT_TIMER_UPDOWN_CNT_USED && !QDRIGHT_CY_TCPWM_4000)
            QDRIGHT_WriteCounter(1u);
        #elif(QDRIGHT__COUNT_DOWN == QDRIGHT_TC_COUNTER_MODE)
            QDRIGHT_WriteCounter(QDRIGHT_TC_PERIOD_VALUE);
        #else
            QDRIGHT_WriteCounter(0u);
        #endif /* (QDRIGHT_CY_TCPWM_V2 && QDRIGHT_TIMER_UPDOWN_CNT_USED && !QDRIGHT_CY_TCPWM_4000) */
    #endif  /* (QDRIGHT__TIMER == QDRIGHT_CONFIG) */

    #if (QDRIGHT__PWM_SEL == QDRIGHT_CONFIG)
        QDRIGHT_CONTROL_REG = QDRIGHT_CTRL_PWM_BASE_CONFIG;

        #if (QDRIGHT__PWM_PR == QDRIGHT_PWM_MODE)
            QDRIGHT_CONTROL_REG |= QDRIGHT_CTRL_PWM_RUN_MODE;
            QDRIGHT_WriteCounter(QDRIGHT_PWM_PR_INIT_VALUE);
        #else
            QDRIGHT_CONTROL_REG |= QDRIGHT_CTRL_PWM_ALIGN | QDRIGHT_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (QDRIGHT_CY_TCPWM_V2 && QDRIGHT_PWM_UPDOWN_CNT_USED && !QDRIGHT_CY_TCPWM_4000)
                QDRIGHT_WriteCounter(1u);
            #elif (QDRIGHT__RIGHT == QDRIGHT_PWM_ALIGN)
                QDRIGHT_WriteCounter(QDRIGHT_PWM_PERIOD_VALUE);
            #else 
                QDRIGHT_WriteCounter(0u);
            #endif  /* (QDRIGHT_CY_TCPWM_V2 && QDRIGHT_PWM_UPDOWN_CNT_USED && !QDRIGHT_CY_TCPWM_4000) */
        #endif  /* (QDRIGHT__PWM_PR == QDRIGHT_PWM_MODE) */

        #if (QDRIGHT__PWM_DT == QDRIGHT_PWM_MODE)
            QDRIGHT_CONTROL_REG |= QDRIGHT_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (QDRIGHT__PWM_DT == QDRIGHT_PWM_MODE) */

        #if (QDRIGHT__PWM == QDRIGHT_PWM_MODE)
            QDRIGHT_CONTROL_REG |= QDRIGHT_CTRL_PWM_PRESCALER;
        #endif  /* (QDRIGHT__PWM == QDRIGHT_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        QDRIGHT_TRIG_CONTROL1_REG  = QDRIGHT_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        QDRIGHT_SetInterruptMode(QDRIGHT_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (QDRIGHT__PWM_PR == QDRIGHT_PWM_MODE)
            QDRIGHT_TRIG_CONTROL2_REG =
                    (QDRIGHT_CC_MATCH_NO_CHANGE    |
                    QDRIGHT_OVERLOW_NO_CHANGE      |
                    QDRIGHT_UNDERFLOW_NO_CHANGE);
        #else
            #if (QDRIGHT__LEFT == QDRIGHT_PWM_ALIGN)
                QDRIGHT_TRIG_CONTROL2_REG = QDRIGHT_PWM_MODE_LEFT;
            #endif  /* ( QDRIGHT_PWM_LEFT == QDRIGHT_PWM_ALIGN) */

            #if (QDRIGHT__RIGHT == QDRIGHT_PWM_ALIGN)
                QDRIGHT_TRIG_CONTROL2_REG = QDRIGHT_PWM_MODE_RIGHT;
            #endif  /* ( QDRIGHT_PWM_RIGHT == QDRIGHT_PWM_ALIGN) */

            #if (QDRIGHT__CENTER == QDRIGHT_PWM_ALIGN)
                QDRIGHT_TRIG_CONTROL2_REG = QDRIGHT_PWM_MODE_CENTER;
            #endif  /* ( QDRIGHT_PWM_CENTER == QDRIGHT_PWM_ALIGN) */

            #if (QDRIGHT__ASYMMETRIC == QDRIGHT_PWM_ALIGN)
                QDRIGHT_TRIG_CONTROL2_REG = QDRIGHT_PWM_MODE_ASYM;
            #endif  /* (QDRIGHT__ASYMMETRIC == QDRIGHT_PWM_ALIGN) */
        #endif  /* (QDRIGHT__PWM_PR == QDRIGHT_PWM_MODE) */

        /* Set other values from customizer */
        QDRIGHT_WritePeriod(QDRIGHT_PWM_PERIOD_VALUE );
        QDRIGHT_WriteCompare(QDRIGHT_PWM_COMPARE_VALUE);

        #if (1u == QDRIGHT_PWM_COMPARE_SWAP)
            QDRIGHT_SetCompareSwap(1u);
            QDRIGHT_WriteCompareBuf(QDRIGHT_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == QDRIGHT_PWM_COMPARE_SWAP) */

        #if (1u == QDRIGHT_PWM_PERIOD_SWAP)
            QDRIGHT_SetPeriodSwap(1u);
            QDRIGHT_WritePeriodBuf(QDRIGHT_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == QDRIGHT_PWM_PERIOD_SWAP) */
    #endif  /* (QDRIGHT__PWM_SEL == QDRIGHT_CONFIG) */
    
}


/*******************************************************************************
* Function Name: QDRIGHT_Enable
********************************************************************************
*
* Summary:
*  Enables the QDRIGHT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    QDRIGHT_BLOCK_CONTROL_REG |= QDRIGHT_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (QDRIGHT__PWM_SEL == QDRIGHT_CONFIG)
        #if (0u == QDRIGHT_PWM_START_SIGNAL_PRESENT)
            QDRIGHT_TriggerCommand(QDRIGHT_MASK, QDRIGHT_CMD_START);
        #endif /* (0u == QDRIGHT_PWM_START_SIGNAL_PRESENT) */
    #endif /* (QDRIGHT__PWM_SEL == QDRIGHT_CONFIG) */

    #if (QDRIGHT__TIMER == QDRIGHT_CONFIG)
        #if (0u == QDRIGHT_TC_START_SIGNAL_PRESENT)
            QDRIGHT_TriggerCommand(QDRIGHT_MASK, QDRIGHT_CMD_START);
        #endif /* (0u == QDRIGHT_TC_START_SIGNAL_PRESENT) */
    #endif /* (QDRIGHT__TIMER == QDRIGHT_CONFIG) */
}


/*******************************************************************************
* Function Name: QDRIGHT_Start
********************************************************************************
*
* Summary:
*  Initializes the QDRIGHT with default customizer
*  values when called the first time and enables the QDRIGHT.
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
*  QDRIGHT_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time QDRIGHT_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the QDRIGHT_Start() routine.
*
*******************************************************************************/
void QDRIGHT_Start(void)
{
    if (0u == QDRIGHT_initVar)
    {
        QDRIGHT_Init();
        QDRIGHT_initVar = 1u;
    }

    QDRIGHT_Enable();
}


/*******************************************************************************
* Function Name: QDRIGHT_Stop
********************************************************************************
*
* Summary:
*  Disables the QDRIGHT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_BLOCK_CONTROL_REG &= (uint32)~QDRIGHT_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the QDRIGHT. This function is used when
*  configured as a generic QDRIGHT and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the QDRIGHT to operate in
*   Values:
*   - QDRIGHT_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - QDRIGHT_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - QDRIGHT_MODE_QUAD - Quadrature decoder
*         - QDRIGHT_MODE_PWM - PWM
*         - QDRIGHT_MODE_PWM_DT - PWM with dead time
*         - QDRIGHT_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_MODE_MASK;
    QDRIGHT_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - QDRIGHT_MODE_X1 - Counts on phi 1 rising
*         - QDRIGHT_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - QDRIGHT_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_QUAD_MODE_MASK;
    QDRIGHT_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - QDRIGHT_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - QDRIGHT_PRESCALE_DIVBY2    - Divide by 2
*         - QDRIGHT_PRESCALE_DIVBY4    - Divide by 4
*         - QDRIGHT_PRESCALE_DIVBY8    - Divide by 8
*         - QDRIGHT_PRESCALE_DIVBY16   - Divide by 16
*         - QDRIGHT_PRESCALE_DIVBY32   - Divide by 32
*         - QDRIGHT_PRESCALE_DIVBY64   - Divide by 64
*         - QDRIGHT_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_PRESCALER_MASK;
    QDRIGHT_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the QDRIGHT runs
*  continuously or stops when terminal count is reached.  By default the
*  QDRIGHT operates in the continuous mode.
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
void QDRIGHT_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_ONESHOT_MASK;
    QDRIGHT_CONTROL_REG |= ((uint32)((oneShotEnable & QDRIGHT_1BIT_MASK) <<
                                                               QDRIGHT_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPWMMode
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
void QDRIGHT_SetPWMMode(uint32 modeMask)
{
    QDRIGHT_TRIG_CONTROL2_REG = (modeMask & QDRIGHT_6BIT_MASK);
}



/*******************************************************************************
* Function Name: QDRIGHT_SetPWMSyncKill
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
void QDRIGHT_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_PWM_SYNC_KILL_MASK;
    QDRIGHT_CONTROL_REG |= ((uint32)((syncKillEnable & QDRIGHT_1BIT_MASK)  <<
                                               QDRIGHT_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPWMStopOnKill
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
void QDRIGHT_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_PWM_STOP_KILL_MASK;
    QDRIGHT_CONTROL_REG |= ((uint32)((stopOnKillEnable & QDRIGHT_1BIT_MASK)  <<
                                                         QDRIGHT_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPWMDeadTime
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
void QDRIGHT_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_PRESCALER_MASK;
    QDRIGHT_CONTROL_REG |= ((uint32)((deadTime & QDRIGHT_8BIT_MASK) <<
                                                          QDRIGHT_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPWMInvert
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
*         - QDRIGHT_INVERT_LINE   - Inverts the line output
*         - QDRIGHT_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_INV_OUT_MASK;
    QDRIGHT_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: QDRIGHT_WriteCounter
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
void QDRIGHT_WriteCounter(uint32 count)
{
    QDRIGHT_COUNTER_REG = (count & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadCounter
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
uint32 QDRIGHT_ReadCounter(void)
{
    return (QDRIGHT_COUNTER_REG & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - QDRIGHT_COUNT_UP       - Counts up
*     - QDRIGHT_COUNT_DOWN     - Counts down
*     - QDRIGHT_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - QDRIGHT_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_UPDOWN_MASK;
    QDRIGHT_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_WritePeriod
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
void QDRIGHT_WritePeriod(uint32 period)
{
    QDRIGHT_PERIOD_REG = (period & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadPeriod
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
uint32 QDRIGHT_ReadPeriod(void)
{
    return (QDRIGHT_PERIOD_REG & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetCompareSwap
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
void QDRIGHT_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_RELOAD_CC_MASK;
    QDRIGHT_CONTROL_REG |= (swapEnable & QDRIGHT_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_WritePeriodBuf
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
void QDRIGHT_WritePeriodBuf(uint32 periodBuf)
{
    QDRIGHT_PERIOD_BUF_REG = (periodBuf & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadPeriodBuf
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
uint32 QDRIGHT_ReadPeriodBuf(void)
{
    return (QDRIGHT_PERIOD_BUF_REG & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetPeriodSwap
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
void QDRIGHT_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_CONTROL_REG &= (uint32)~QDRIGHT_RELOAD_PERIOD_MASK;
    QDRIGHT_CONTROL_REG |= ((uint32)((swapEnable & QDRIGHT_1BIT_MASK) <<
                                                            QDRIGHT_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_WriteCompare
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
void QDRIGHT_WriteCompare(uint32 compare)
{
    #if (QDRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (QDRIGHT_CY_TCPWM_4000) */

    #if (QDRIGHT_CY_TCPWM_4000)
        currentMode = ((QDRIGHT_CONTROL_REG & QDRIGHT_UPDOWN_MASK) >> QDRIGHT_UPDOWN_SHIFT);

        if (((uint32)QDRIGHT__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)QDRIGHT__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (QDRIGHT_CY_TCPWM_4000) */
    
    QDRIGHT_COMP_CAP_REG = (compare & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadCompare
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
uint32 QDRIGHT_ReadCompare(void)
{
    #if (QDRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (QDRIGHT_CY_TCPWM_4000) */

    #if (QDRIGHT_CY_TCPWM_4000)
        currentMode = ((QDRIGHT_CONTROL_REG & QDRIGHT_UPDOWN_MASK) >> QDRIGHT_UPDOWN_SHIFT);
        
        regVal = QDRIGHT_COMP_CAP_REG;
        
        if (((uint32)QDRIGHT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)QDRIGHT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & QDRIGHT_16BIT_MASK);
    #else
        return (QDRIGHT_COMP_CAP_REG & QDRIGHT_16BIT_MASK);
    #endif /* (QDRIGHT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: QDRIGHT_WriteCompareBuf
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
void QDRIGHT_WriteCompareBuf(uint32 compareBuf)
{
    #if (QDRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (QDRIGHT_CY_TCPWM_4000) */

    #if (QDRIGHT_CY_TCPWM_4000)
        currentMode = ((QDRIGHT_CONTROL_REG & QDRIGHT_UPDOWN_MASK) >> QDRIGHT_UPDOWN_SHIFT);

        if (((uint32)QDRIGHT__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)QDRIGHT__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (QDRIGHT_CY_TCPWM_4000) */
    
    QDRIGHT_COMP_CAP_BUF_REG = (compareBuf & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadCompareBuf
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
uint32 QDRIGHT_ReadCompareBuf(void)
{
    #if (QDRIGHT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (QDRIGHT_CY_TCPWM_4000) */

    #if (QDRIGHT_CY_TCPWM_4000)
        currentMode = ((QDRIGHT_CONTROL_REG & QDRIGHT_UPDOWN_MASK) >> QDRIGHT_UPDOWN_SHIFT);

        regVal = QDRIGHT_COMP_CAP_BUF_REG;
        
        if (((uint32)QDRIGHT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)QDRIGHT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & QDRIGHT_16BIT_MASK);
    #else
        return (QDRIGHT_COMP_CAP_BUF_REG & QDRIGHT_16BIT_MASK);
    #endif /* (QDRIGHT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadCapture
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
uint32 QDRIGHT_ReadCapture(void)
{
    return (QDRIGHT_COMP_CAP_REG & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadCaptureBuf
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
uint32 QDRIGHT_ReadCaptureBuf(void)
{
    return (QDRIGHT_COMP_CAP_BUF_REG & QDRIGHT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetCaptureMode
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
*     - QDRIGHT_TRIG_LEVEL     - Level
*     - QDRIGHT_TRIG_RISING    - Rising edge
*     - QDRIGHT_TRIG_FALLING   - Falling edge
*     - QDRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_TRIG_CONTROL1_REG &= (uint32)~QDRIGHT_CAPTURE_MASK;
    QDRIGHT_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDRIGHT_TRIG_LEVEL     - Level
*     - QDRIGHT_TRIG_RISING    - Rising edge
*     - QDRIGHT_TRIG_FALLING   - Falling edge
*     - QDRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_TRIG_CONTROL1_REG &= (uint32)~QDRIGHT_RELOAD_MASK;
    QDRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDRIGHT_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDRIGHT_TRIG_LEVEL     - Level
*     - QDRIGHT_TRIG_RISING    - Rising edge
*     - QDRIGHT_TRIG_FALLING   - Falling edge
*     - QDRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_TRIG_CONTROL1_REG &= (uint32)~QDRIGHT_START_MASK;
    QDRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDRIGHT_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDRIGHT_TRIG_LEVEL     - Level
*     - QDRIGHT_TRIG_RISING    - Rising edge
*     - QDRIGHT_TRIG_FALLING   - Falling edge
*     - QDRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_TRIG_CONTROL1_REG &= (uint32)~QDRIGHT_STOP_MASK;
    QDRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDRIGHT_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDRIGHT_TRIG_LEVEL     - Level
*     - QDRIGHT_TRIG_RISING    - Rising edge
*     - QDRIGHT_TRIG_FALLING   - Falling edge
*     - QDRIGHT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_TRIG_CONTROL1_REG &= (uint32)~QDRIGHT_COUNT_MASK;
    QDRIGHT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDRIGHT_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_TriggerCommand
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
*     - QDRIGHT_CMD_CAPTURE    - Trigger Capture command
*     - QDRIGHT_CMD_RELOAD     - Trigger Reload command
*     - QDRIGHT_CMD_STOP       - Trigger Stop command
*     - QDRIGHT_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDRIGHT_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDRIGHT_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the QDRIGHT.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - QDRIGHT_STATUS_DOWN    - Set if counting down
*     - QDRIGHT_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 QDRIGHT_ReadStatus(void)
{
    return ((QDRIGHT_STATUS_REG >> QDRIGHT_RUNNING_STATUS_SHIFT) |
            (QDRIGHT_STATUS_REG & QDRIGHT_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: QDRIGHT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - QDRIGHT_INTR_MASK_TC       - Terminal count mask
*     - QDRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetInterruptMode(uint32 interruptMask)
{
    QDRIGHT_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: QDRIGHT_GetInterruptSourceMasked
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
*     - QDRIGHT_INTR_MASK_TC       - Terminal count mask
*     - QDRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QDRIGHT_GetInterruptSourceMasked(void)
{
    return (QDRIGHT_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: QDRIGHT_GetInterruptSource
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
*     - QDRIGHT_INTR_MASK_TC       - Terminal count mask
*     - QDRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QDRIGHT_GetInterruptSource(void)
{
    return (QDRIGHT_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: QDRIGHT_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - QDRIGHT_INTR_MASK_TC       - Terminal count mask
*     - QDRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_ClearInterrupt(uint32 interruptMask)
{
    QDRIGHT_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: QDRIGHT_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - QDRIGHT_INTR_MASK_TC       - Terminal count mask
*     - QDRIGHT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDRIGHT_SetInterrupt(uint32 interruptMask)
{
    QDRIGHT_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
