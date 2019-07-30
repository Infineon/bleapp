/*******************************************************************************
* File Name: QDLEFT.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the QDLEFT
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QDLEFT.h"

uint8 QDLEFT_initVar = 0u;


/*******************************************************************************
* Function Name: QDLEFT_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default QDLEFT configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (QDLEFT__QUAD == QDLEFT_CONFIG)
        QDLEFT_CONTROL_REG = QDLEFT_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        QDLEFT_TRIG_CONTROL1_REG  = QDLEFT_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        QDLEFT_SetInterruptMode(QDLEFT_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        QDLEFT_SetCounterMode(QDLEFT_COUNT_DOWN);
        QDLEFT_WritePeriod(QDLEFT_QUAD_PERIOD_INIT_VALUE);
        QDLEFT_WriteCounter(QDLEFT_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (QDLEFT__QUAD == QDLEFT_CONFIG) */

    #if (QDLEFT__TIMER == QDLEFT_CONFIG)
        QDLEFT_CONTROL_REG = QDLEFT_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        QDLEFT_TRIG_CONTROL1_REG  = QDLEFT_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        QDLEFT_SetInterruptMode(QDLEFT_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        QDLEFT_WritePeriod(QDLEFT_TC_PERIOD_VALUE );

        #if (QDLEFT__COMPARE == QDLEFT_TC_COMP_CAP_MODE)
            QDLEFT_WriteCompare(QDLEFT_TC_COMPARE_VALUE);

            #if (1u == QDLEFT_TC_COMPARE_SWAP)
                QDLEFT_SetCompareSwap(1u);
                QDLEFT_WriteCompareBuf(QDLEFT_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == QDLEFT_TC_COMPARE_SWAP) */
        #endif  /* (QDLEFT__COMPARE == QDLEFT_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (QDLEFT_CY_TCPWM_V2 && QDLEFT_TIMER_UPDOWN_CNT_USED && !QDLEFT_CY_TCPWM_4000)
            QDLEFT_WriteCounter(1u);
        #elif(QDLEFT__COUNT_DOWN == QDLEFT_TC_COUNTER_MODE)
            QDLEFT_WriteCounter(QDLEFT_TC_PERIOD_VALUE);
        #else
            QDLEFT_WriteCounter(0u);
        #endif /* (QDLEFT_CY_TCPWM_V2 && QDLEFT_TIMER_UPDOWN_CNT_USED && !QDLEFT_CY_TCPWM_4000) */
    #endif  /* (QDLEFT__TIMER == QDLEFT_CONFIG) */

    #if (QDLEFT__PWM_SEL == QDLEFT_CONFIG)
        QDLEFT_CONTROL_REG = QDLEFT_CTRL_PWM_BASE_CONFIG;

        #if (QDLEFT__PWM_PR == QDLEFT_PWM_MODE)
            QDLEFT_CONTROL_REG |= QDLEFT_CTRL_PWM_RUN_MODE;
            QDLEFT_WriteCounter(QDLEFT_PWM_PR_INIT_VALUE);
        #else
            QDLEFT_CONTROL_REG |= QDLEFT_CTRL_PWM_ALIGN | QDLEFT_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (QDLEFT_CY_TCPWM_V2 && QDLEFT_PWM_UPDOWN_CNT_USED && !QDLEFT_CY_TCPWM_4000)
                QDLEFT_WriteCounter(1u);
            #elif (QDLEFT__RIGHT == QDLEFT_PWM_ALIGN)
                QDLEFT_WriteCounter(QDLEFT_PWM_PERIOD_VALUE);
            #else 
                QDLEFT_WriteCounter(0u);
            #endif  /* (QDLEFT_CY_TCPWM_V2 && QDLEFT_PWM_UPDOWN_CNT_USED && !QDLEFT_CY_TCPWM_4000) */
        #endif  /* (QDLEFT__PWM_PR == QDLEFT_PWM_MODE) */

        #if (QDLEFT__PWM_DT == QDLEFT_PWM_MODE)
            QDLEFT_CONTROL_REG |= QDLEFT_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (QDLEFT__PWM_DT == QDLEFT_PWM_MODE) */

        #if (QDLEFT__PWM == QDLEFT_PWM_MODE)
            QDLEFT_CONTROL_REG |= QDLEFT_CTRL_PWM_PRESCALER;
        #endif  /* (QDLEFT__PWM == QDLEFT_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        QDLEFT_TRIG_CONTROL1_REG  = QDLEFT_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        QDLEFT_SetInterruptMode(QDLEFT_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (QDLEFT__PWM_PR == QDLEFT_PWM_MODE)
            QDLEFT_TRIG_CONTROL2_REG =
                    (QDLEFT_CC_MATCH_NO_CHANGE    |
                    QDLEFT_OVERLOW_NO_CHANGE      |
                    QDLEFT_UNDERFLOW_NO_CHANGE);
        #else
            #if (QDLEFT__LEFT == QDLEFT_PWM_ALIGN)
                QDLEFT_TRIG_CONTROL2_REG = QDLEFT_PWM_MODE_LEFT;
            #endif  /* ( QDLEFT_PWM_LEFT == QDLEFT_PWM_ALIGN) */

            #if (QDLEFT__RIGHT == QDLEFT_PWM_ALIGN)
                QDLEFT_TRIG_CONTROL2_REG = QDLEFT_PWM_MODE_RIGHT;
            #endif  /* ( QDLEFT_PWM_RIGHT == QDLEFT_PWM_ALIGN) */

            #if (QDLEFT__CENTER == QDLEFT_PWM_ALIGN)
                QDLEFT_TRIG_CONTROL2_REG = QDLEFT_PWM_MODE_CENTER;
            #endif  /* ( QDLEFT_PWM_CENTER == QDLEFT_PWM_ALIGN) */

            #if (QDLEFT__ASYMMETRIC == QDLEFT_PWM_ALIGN)
                QDLEFT_TRIG_CONTROL2_REG = QDLEFT_PWM_MODE_ASYM;
            #endif  /* (QDLEFT__ASYMMETRIC == QDLEFT_PWM_ALIGN) */
        #endif  /* (QDLEFT__PWM_PR == QDLEFT_PWM_MODE) */

        /* Set other values from customizer */
        QDLEFT_WritePeriod(QDLEFT_PWM_PERIOD_VALUE );
        QDLEFT_WriteCompare(QDLEFT_PWM_COMPARE_VALUE);

        #if (1u == QDLEFT_PWM_COMPARE_SWAP)
            QDLEFT_SetCompareSwap(1u);
            QDLEFT_WriteCompareBuf(QDLEFT_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == QDLEFT_PWM_COMPARE_SWAP) */

        #if (1u == QDLEFT_PWM_PERIOD_SWAP)
            QDLEFT_SetPeriodSwap(1u);
            QDLEFT_WritePeriodBuf(QDLEFT_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == QDLEFT_PWM_PERIOD_SWAP) */
    #endif  /* (QDLEFT__PWM_SEL == QDLEFT_CONFIG) */
    
}


/*******************************************************************************
* Function Name: QDLEFT_Enable
********************************************************************************
*
* Summary:
*  Enables the QDLEFT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    QDLEFT_BLOCK_CONTROL_REG |= QDLEFT_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (QDLEFT__PWM_SEL == QDLEFT_CONFIG)
        #if (0u == QDLEFT_PWM_START_SIGNAL_PRESENT)
            QDLEFT_TriggerCommand(QDLEFT_MASK, QDLEFT_CMD_START);
        #endif /* (0u == QDLEFT_PWM_START_SIGNAL_PRESENT) */
    #endif /* (QDLEFT__PWM_SEL == QDLEFT_CONFIG) */

    #if (QDLEFT__TIMER == QDLEFT_CONFIG)
        #if (0u == QDLEFT_TC_START_SIGNAL_PRESENT)
            QDLEFT_TriggerCommand(QDLEFT_MASK, QDLEFT_CMD_START);
        #endif /* (0u == QDLEFT_TC_START_SIGNAL_PRESENT) */
    #endif /* (QDLEFT__TIMER == QDLEFT_CONFIG) */
    
    #if (QDLEFT__QUAD == QDLEFT_CONFIG)
        #if (0u != QDLEFT_QUAD_AUTO_START)
            QDLEFT_TriggerCommand(QDLEFT_MASK, QDLEFT_CMD_RELOAD);
        #endif /* (0u != QDLEFT_QUAD_AUTO_START) */
    #endif  /* (QDLEFT__QUAD == QDLEFT_CONFIG) */
}


/*******************************************************************************
* Function Name: QDLEFT_Start
********************************************************************************
*
* Summary:
*  Initializes the QDLEFT with default customizer
*  values when called the first time and enables the QDLEFT.
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
*  QDLEFT_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time QDLEFT_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the QDLEFT_Start() routine.
*
*******************************************************************************/
void QDLEFT_Start(void)
{
    if (0u == QDLEFT_initVar)
    {
        QDLEFT_Init();
        QDLEFT_initVar = 1u;
    }

    QDLEFT_Enable();
}


/*******************************************************************************
* Function Name: QDLEFT_Stop
********************************************************************************
*
* Summary:
*  Disables the QDLEFT.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_BLOCK_CONTROL_REG &= (uint32)~QDLEFT_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the QDLEFT. This function is used when
*  configured as a generic QDLEFT and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the QDLEFT to operate in
*   Values:
*   - QDLEFT_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - QDLEFT_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - QDLEFT_MODE_QUAD - Quadrature decoder
*         - QDLEFT_MODE_PWM - PWM
*         - QDLEFT_MODE_PWM_DT - PWM with dead time
*         - QDLEFT_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_MODE_MASK;
    QDLEFT_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - QDLEFT_MODE_X1 - Counts on phi 1 rising
*         - QDLEFT_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - QDLEFT_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_QUAD_MODE_MASK;
    QDLEFT_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - QDLEFT_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - QDLEFT_PRESCALE_DIVBY2    - Divide by 2
*         - QDLEFT_PRESCALE_DIVBY4    - Divide by 4
*         - QDLEFT_PRESCALE_DIVBY8    - Divide by 8
*         - QDLEFT_PRESCALE_DIVBY16   - Divide by 16
*         - QDLEFT_PRESCALE_DIVBY32   - Divide by 32
*         - QDLEFT_PRESCALE_DIVBY64   - Divide by 64
*         - QDLEFT_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_PRESCALER_MASK;
    QDLEFT_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the QDLEFT runs
*  continuously or stops when terminal count is reached.  By default the
*  QDLEFT operates in the continuous mode.
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
void QDLEFT_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_ONESHOT_MASK;
    QDLEFT_CONTROL_REG |= ((uint32)((oneShotEnable & QDLEFT_1BIT_MASK) <<
                                                               QDLEFT_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPWMMode
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
void QDLEFT_SetPWMMode(uint32 modeMask)
{
    QDLEFT_TRIG_CONTROL2_REG = (modeMask & QDLEFT_6BIT_MASK);
}



/*******************************************************************************
* Function Name: QDLEFT_SetPWMSyncKill
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
void QDLEFT_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_PWM_SYNC_KILL_MASK;
    QDLEFT_CONTROL_REG |= ((uint32)((syncKillEnable & QDLEFT_1BIT_MASK)  <<
                                               QDLEFT_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPWMStopOnKill
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
void QDLEFT_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_PWM_STOP_KILL_MASK;
    QDLEFT_CONTROL_REG |= ((uint32)((stopOnKillEnable & QDLEFT_1BIT_MASK)  <<
                                                         QDLEFT_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPWMDeadTime
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
void QDLEFT_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_PRESCALER_MASK;
    QDLEFT_CONTROL_REG |= ((uint32)((deadTime & QDLEFT_8BIT_MASK) <<
                                                          QDLEFT_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPWMInvert
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
*         - QDLEFT_INVERT_LINE   - Inverts the line output
*         - QDLEFT_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_INV_OUT_MASK;
    QDLEFT_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: QDLEFT_WriteCounter
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
void QDLEFT_WriteCounter(uint32 count)
{
    QDLEFT_COUNTER_REG = (count & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadCounter
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
uint32 QDLEFT_ReadCounter(void)
{
    return (QDLEFT_COUNTER_REG & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - QDLEFT_COUNT_UP       - Counts up
*     - QDLEFT_COUNT_DOWN     - Counts down
*     - QDLEFT_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - QDLEFT_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_UPDOWN_MASK;
    QDLEFT_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_WritePeriod
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
void QDLEFT_WritePeriod(uint32 period)
{
    QDLEFT_PERIOD_REG = (period & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadPeriod
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
uint32 QDLEFT_ReadPeriod(void)
{
    return (QDLEFT_PERIOD_REG & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_SetCompareSwap
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
void QDLEFT_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_RELOAD_CC_MASK;
    QDLEFT_CONTROL_REG |= (swapEnable & QDLEFT_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_WritePeriodBuf
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
void QDLEFT_WritePeriodBuf(uint32 periodBuf)
{
    QDLEFT_PERIOD_BUF_REG = (periodBuf & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadPeriodBuf
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
uint32 QDLEFT_ReadPeriodBuf(void)
{
    return (QDLEFT_PERIOD_BUF_REG & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_SetPeriodSwap
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
void QDLEFT_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_CONTROL_REG &= (uint32)~QDLEFT_RELOAD_PERIOD_MASK;
    QDLEFT_CONTROL_REG |= ((uint32)((swapEnable & QDLEFT_1BIT_MASK) <<
                                                            QDLEFT_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_WriteCompare
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
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void QDLEFT_WriteCompare(uint32 compare)
{
    #if (QDLEFT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (QDLEFT_CY_TCPWM_4000) */

    #if (QDLEFT_CY_TCPWM_4000)
        currentMode = ((QDLEFT_CONTROL_REG & QDLEFT_UPDOWN_MASK) >> QDLEFT_UPDOWN_SHIFT);

        if (((uint32)QDLEFT__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)QDLEFT__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (QDLEFT_CY_TCPWM_4000) */
    
    QDLEFT_COMP_CAP_REG = (compare & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 QDLEFT_ReadCompare(void)
{
    #if (QDLEFT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (QDLEFT_CY_TCPWM_4000) */

    #if (QDLEFT_CY_TCPWM_4000)
        currentMode = ((QDLEFT_CONTROL_REG & QDLEFT_UPDOWN_MASK) >> QDLEFT_UPDOWN_SHIFT);
        
        regVal = QDLEFT_COMP_CAP_REG;
        
        if (((uint32)QDLEFT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)QDLEFT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & QDLEFT_16BIT_MASK);
    #else
        return (QDLEFT_COMP_CAP_REG & QDLEFT_16BIT_MASK);
    #endif /* (QDLEFT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: QDLEFT_WriteCompareBuf
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
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void QDLEFT_WriteCompareBuf(uint32 compareBuf)
{
    #if (QDLEFT_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (QDLEFT_CY_TCPWM_4000) */

    #if (QDLEFT_CY_TCPWM_4000)
        currentMode = ((QDLEFT_CONTROL_REG & QDLEFT_UPDOWN_MASK) >> QDLEFT_UPDOWN_SHIFT);

        if (((uint32)QDLEFT__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)QDLEFT__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (QDLEFT_CY_TCPWM_4000) */
    
    QDLEFT_COMP_CAP_BUF_REG = (compareBuf & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadCompareBuf
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
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 QDLEFT_ReadCompareBuf(void)
{
    #if (QDLEFT_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (QDLEFT_CY_TCPWM_4000) */

    #if (QDLEFT_CY_TCPWM_4000)
        currentMode = ((QDLEFT_CONTROL_REG & QDLEFT_UPDOWN_MASK) >> QDLEFT_UPDOWN_SHIFT);

        regVal = QDLEFT_COMP_CAP_BUF_REG;
        
        if (((uint32)QDLEFT__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)QDLEFT__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & QDLEFT_16BIT_MASK);
    #else
        return (QDLEFT_COMP_CAP_BUF_REG & QDLEFT_16BIT_MASK);
    #endif /* (QDLEFT_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: QDLEFT_ReadCapture
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
uint32 QDLEFT_ReadCapture(void)
{
    return (QDLEFT_COMP_CAP_REG & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadCaptureBuf
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
uint32 QDLEFT_ReadCaptureBuf(void)
{
    return (QDLEFT_COMP_CAP_BUF_REG & QDLEFT_16BIT_MASK);
}


/*******************************************************************************
* Function Name: QDLEFT_SetCaptureMode
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
*     - QDLEFT_TRIG_LEVEL     - Level
*     - QDLEFT_TRIG_RISING    - Rising edge
*     - QDLEFT_TRIG_FALLING   - Falling edge
*     - QDLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_TRIG_CONTROL1_REG &= (uint32)~QDLEFT_CAPTURE_MASK;
    QDLEFT_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDLEFT_TRIG_LEVEL     - Level
*     - QDLEFT_TRIG_RISING    - Rising edge
*     - QDLEFT_TRIG_FALLING   - Falling edge
*     - QDLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_TRIG_CONTROL1_REG &= (uint32)~QDLEFT_RELOAD_MASK;
    QDLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDLEFT_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDLEFT_TRIG_LEVEL     - Level
*     - QDLEFT_TRIG_RISING    - Rising edge
*     - QDLEFT_TRIG_FALLING   - Falling edge
*     - QDLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_TRIG_CONTROL1_REG &= (uint32)~QDLEFT_START_MASK;
    QDLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDLEFT_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDLEFT_TRIG_LEVEL     - Level
*     - QDLEFT_TRIG_RISING    - Rising edge
*     - QDLEFT_TRIG_FALLING   - Falling edge
*     - QDLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_TRIG_CONTROL1_REG &= (uint32)~QDLEFT_STOP_MASK;
    QDLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDLEFT_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - QDLEFT_TRIG_LEVEL     - Level
*     - QDLEFT_TRIG_RISING    - Rising edge
*     - QDLEFT_TRIG_FALLING   - Falling edge
*     - QDLEFT_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_TRIG_CONTROL1_REG &= (uint32)~QDLEFT_COUNT_MASK;
    QDLEFT_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << QDLEFT_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_TriggerCommand
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
*     - QDLEFT_CMD_CAPTURE    - Trigger Capture/Switch command
*     - QDLEFT_CMD_RELOAD     - Trigger Reload/Index command
*     - QDLEFT_CMD_STOP       - Trigger Stop/Kill command
*     - QDLEFT_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    QDLEFT_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QDLEFT_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the QDLEFT.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - QDLEFT_STATUS_DOWN    - Set if counting down
*     - QDLEFT_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 QDLEFT_ReadStatus(void)
{
    return ((QDLEFT_STATUS_REG >> QDLEFT_RUNNING_STATUS_SHIFT) |
            (QDLEFT_STATUS_REG & QDLEFT_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: QDLEFT_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - QDLEFT_INTR_MASK_TC       - Terminal count mask
*     - QDLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetInterruptMode(uint32 interruptMask)
{
    QDLEFT_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: QDLEFT_GetInterruptSourceMasked
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
*     - QDLEFT_INTR_MASK_TC       - Terminal count mask
*     - QDLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QDLEFT_GetInterruptSourceMasked(void)
{
    return (QDLEFT_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: QDLEFT_GetInterruptSource
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
*     - QDLEFT_INTR_MASK_TC       - Terminal count mask
*     - QDLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 QDLEFT_GetInterruptSource(void)
{
    return (QDLEFT_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: QDLEFT_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - QDLEFT_INTR_MASK_TC       - Terminal count mask
*     - QDLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_ClearInterrupt(uint32 interruptMask)
{
    QDLEFT_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: QDLEFT_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - QDLEFT_INTR_MASK_TC       - Terminal count mask
*     - QDLEFT_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void QDLEFT_SetInterrupt(uint32 interruptMask)
{
    QDLEFT_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
