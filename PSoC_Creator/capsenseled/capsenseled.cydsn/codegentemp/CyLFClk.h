/*******************************************************************************
* File Name: .h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the cy_lfclk Component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_LFCLK_CYLIB_H)
#define CY_LFCLK_CYLIB_H

#include "cytypes.h"
#include "cydevice_trm.h"

typedef enum
{
    CY_SYS_TIMER_WAIT = 0u,
    CY_SYS_TIMER_INTERRUPT = 1u
} cy_sys_timer_delaytype_enum;


/***************************************
*    Function Prototypes
***************************************/

/* Clocks API */
void CySysClkIloStart(void);
void CySysClkIloStop(void);

#if (CY_IP_WCO)
    void   CySysClkWcoStart(void);
    void   CySysClkWcoStop(void);
    uint32 CySysClkWcoSetPowerMode(uint32 mode);

    void CySysClkSetLfclkSource(uint32 source);
    uint32 CySysClkWcoEnabled(void);
#endif /* (CY_IP_WCO) */

typedef void (*cyWdtCallback)(void);

#if(CY_IP_SRSSV2)
    /* WDT API */
    void   CySysWdtLock(void);
    void   CySysWdtUnlock(void);
    void   CySysWdtSetMode(uint32 counterNum, uint32 mode);
    uint32 CySysWdtGetMode(uint32 counterNum);
    uint32 CySysWdtGetEnabledStatus(uint32 counterNum);
    void   CySysWdtSetClearOnMatch(uint32 counterNum, uint32 enable);
    uint32 CySysWdtGetClearOnMatch(uint32 counterNum);
    void   CySysWdtEnable(uint32 counterMask);
    void   CySysWdtDisable(uint32 counterMask);
    void   CySysWdtSetCascade(uint32 cascadeMask);
    uint32 CySysWdtGetCascade(void);
    void   CySysWdtSetMatch(uint32 counterNum, uint32 match);
    void   CySysWdtSetToggleBit(uint32 bits);
    uint32 CySysWdtGetToggleBit(void);
    uint32 CySysWdtGetMatch(uint32 counterNum);
    uint32 CySysWdtGetCount(uint32 counterNum);
    uint32 CySysWdtGetInterruptSource(void);
    void   CySysWdtClearInterrupt(uint32 counterMask);
    void   CySysWdtResetCounters(uint32 countersMask);
    cyWdtCallback  CySysWdtSetInterruptCallback(uint32 counterNum, cyWdtCallback function);
    cyWdtCallback  CySysWdtGetInterruptCallback(uint32 counterNum);
    void   CySysTimerDelay(uint32 counterNum, cy_sys_timer_delaytype_enum delayType, uint32 delay);
    void   CySysTimerDelayUntilMatch(uint32 counterNum, cy_sys_timer_delaytype_enum delayType, uint32 match);
    void   CySysWatchdogFeed(uint32 counterNum);
    void   CySysWdtEnableCounterIsr(uint32 counterNum);
    void   CySysWdtDisableCounterIsr(uint32 counterNum);
    void   CySysWdtIsr(void);
#else
    /* WDT API */
    uint32 CySysWdtGetEnabledStatus(void);
    void   CySysWdtEnable(void);
    void   CySysWdtDisable(void);
    void   CySysWdtSetMatch(uint32 match);
    uint32 CySysWdtGetMatch(void);
    uint32 CySysWdtGetCount(void);
    void   CySysWdtSetIgnoreBits(uint32 bitsNum);
    uint32 CySysWdtGetIgnoreBits(void);
    void   CySysWdtClearInterrupt(void);
    void   CySysWdtMaskInterrupt(void);
    void   CySysWdtUnmaskInterrupt(void);
    cyWdtCallback CySysWdtSetInterruptCallback(cyWdtCallback function);
    cyWdtCallback CySysWdtGetInterruptCallback(void);
    void   CySysWdtIsr(void);
#endif  /* (CY_IP_SRSSV2) */


/***************************************
* API Constants
***************************************/

#define UINT16_MAX_VAL    (0xFFFFu)


/*******************************************************************************
* Clock API Constants
*******************************************************************************/
/* CySysClkIloStart()/CySysClkIloStop() - implementation definitions */
#define CY_SYS_CLK_ILO_CONFIG_ENABLE                    (( uint32 )(( uint32 )0x01u << 31u))


/* CySysClkSetLfclkSource() - parameter definitions */
#if (CY_IP_WCO)
    #define CY_SYS_CLK_LFCLK_SRC_ILO                    (0u)
    #define CY_SYS_CLK_LFCLK_SRC_WCO                    (( uint32 )(( uint32 )0x01u << 30u))
#endif /* (CY_IP_WCO) */


/* CySysClkSetLfclkSource() - implementation definitions */
#if (CY_IP_WCO)
    #define CY_SYS_CLK_LFCLK_SEL_MASK                   (( uint32 )(( uint32 )0x03u << 30u))
#endif /* (CY_IP_WCO) */

#if (CY_IP_WCO)
    /* WCO Configuration Register */
    #define CY_SYS_CLK_WCO_CONFIG_LPM_EN                (( uint32 )(( uint32 )0x01u <<  0u))
    #define CY_SYS_CLK_WCO_CONFIG_LPM_AUTO              (( uint32 )(( uint32 )0x01u <<  1u))
    #define CY_SYS_CLK_WCO_CONFIG_LPM_ENABLE            (( uint32 )(( uint32 )0x01u << 31u))

    /* WCO Status Register */
    #define CY_SYS_CLK_WCO_STATUS_OUT_BLNK_A            (( uint32 )(( uint32 )0x01u <<  0u))

    /* WCO Trim Register */
    #define CY_SYS_CLK_WCO_TRIM_XGM_MASK                (( uint32 ) 0x07u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_SHIFT               (( uint32 ) 0x00u)

    #define CY_SYS_CLK_WCO_TRIM_XGM_3370NA              (( uint32 ) 0x00u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_2620NA              (( uint32 ) 0x01u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_2250NA              (( uint32 ) 0x02u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_1500NA              (( uint32 ) 0x03u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_1870NA              (( uint32 ) 0x04u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_1120NA              (( uint32 ) 0x05u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_750NA               (( uint32 ) 0x06u)
    #define CY_SYS_CLK_WCO_TRIM_XGM_0NA                 (( uint32 ) 0x07u)

    #define CY_SYS_CLK_WCO_TRIM_GM_MASK                 (( uint32 )(( uint32 )0x03u << 4u))
    #define CY_SYS_CLK_WCO_TRIM_GM_SHIFT                (( uint32 ) 0x04u)
    #define CY_SYS_CLK_WCO_TRIM_GM_HPM                  (( uint32 ) 0x01u)
    #define CY_SYS_CLK_WCO_TRIM_GM_LPM                  (( uint32 ) 0x02u)
#endif  /* (CY_IP_WCO) */


/*******************************************************************************
* WDT API Constants
*******************************************************************************/
#if(CY_IP_SRSSV2)
    #define CY_SYS_WDT_MODE_NONE                (0u)
    #define CY_SYS_WDT_MODE_INT                 (1u)
    #define CY_SYS_WDT_MODE_RESET               (2u)
    #define CY_SYS_WDT_MODE_INT_RESET           (3u)

    #define CY_SYS_WDT_COUNTER0_MASK            ((uint32)((uint32)0x01u))
    #define CY_SYS_WDT_COUNTER1_MASK            ((uint32)((uint32)0x01u << 8u))
    #define CY_SYS_WDT_COUNTER2_MASK            ((uint32)((uint32)0x01u << 16u))

    #define CY_SYS_WDT_CASCADE_NONE             ((uint32)0x00u)
    #define CY_SYS_WDT_CASCADE_01               ((uint32)0x01u << 3u)
    #define CY_SYS_WDT_CASCADE_12               ((uint32)0x01u << 11u)

    #define CY_SYS_WDT_COUNTER0_INT             ((uint32)0x01u << 2u)
    #define CY_SYS_WDT_COUNTER1_INT             ((uint32)0x01u << 10u)
    #define CY_SYS_WDT_COUNTER2_INT             ((uint32)0x01u << 18u)

    #define CY_SYS_WDT_COUNTER0_RESET           ((uint32)0x01u << 3u)
    #define CY_SYS_WDT_COUNTER1_RESET           ((uint32)0x01u << 11u)
    #define CY_SYS_WDT_COUNTER2_RESET           ((uint32)0x01u << 19u)
    #define CY_SYS_WDT_COUNTERS_RESET           (CY_SYS_WDT_COUNTER0_RESET |\
                                                 CY_SYS_WDT_COUNTER1_RESET |\
                                                 CY_SYS_WDT_COUNTER2_RESET)

    #define CY_SYS_WDT_COUNTER0                 (0x00u)
    #define CY_SYS_WDT_COUNTER1                 (0x01u)
    #define CY_SYS_WDT_COUNTER2                 (0x02u)

    #define CY_SYS_WDT_COUNTER0_OFFSET            (0x00u)
    #define CY_SYS_WDT_COUNTER1_OFFSET            (0x02u)
    #define CY_SYS_WDT_COUNTER2_OFFSET            (0x04u)

    #define CY_SYS_WDT_MODE_MASK                ((uint32)(0x03u))

    #define CY_SYS_WDT_CLK_LOCK_BITS_MASK       ((uint32)0x03u << 14u)
    #define CY_SYS_WDT_CLK_LOCK_BIT0            ((uint32)0x01u << 14u)
    #define CY_SYS_WDT_CLK_LOCK_BIT1            ((uint32)0x01u << 15u)

    #define CY_SYS_WDT_CONFIG_BITS2_MASK        (uint32)(0x1Fu)
    #define CY_SYS_WDT_CONFIG_BITS2_POS         (uint32)(24u)
    #define CY_SYS_WDT_LOWER_16BITS_MASK        (uint32)(0x0000FFFFu)
    #define CY_SYS_WDT_HIGHER_16BITS_MASK       (uint32)(0xFFFF0000u)
    #define CY_SYS_WDT_COUNTERS_MAX             (0x03u)
    #define CY_SYS_WDT_CNT_SHIFT                (0x08u)
    #define CY_SYS_WDT_CNT_MATCH_CLR_SHIFT      (0x02u)
    #define CY_SYS_WDT_CNT_STTS_SHIFT           (0x01u)
    #define CY_SYS_WDT_CNT_MATCH_SHIFT          (0x10u)

    #define CY_WDT_NUM_OF_WDT                    (3u)
    #define CY_WDT_NUM_OF_CALLBACKS             (3u)

    #if (CY_PSOC4_4100 || CY_PSOC4_4200)
        #define CY_SYS_WDT_1LFCLK_DELAY_US      ((uint16)( 67u))
        #define CY_SYS_WDT_3LFCLK_DELAY_US      ((uint16)(201u))
    #endif /* (CY_PSOC4_4100 || CY_PSOC4_4200) */

    #if (CY_PSOC4_4000)
        #define CY_SYS_WDT_1LFCLK_DELAY_US      ((uint16)( 50u))
        #define CY_SYS_WDT_3LFCLK_DELAY_US      ((uint16)(150u))
    #endif /* (CY_PSOC4_4000) */

    #if (CY_IP_WCO)

        #define CY_SYS_WDT_1LFCLK_DELAY_US      \
            ((CY_SYS_CLK_LFCLK_SRC_ILO == (CY_SYS_WDT_CONFIG_REG & CY_SYS_CLK_LFCLK_SEL_MASK)) ? \
                                                ((uint16)(67u)) : \
                                                ((uint16)(31u)))

        #define CY_SYS_WDT_3LFCLK_DELAY_US      \
            ((CY_SYS_CLK_LFCLK_SRC_ILO == (CY_SYS_WDT_CONFIG_REG & CY_SYS_CLK_LFCLK_SEL_MASK)) ? \
                                                ((uint16)(201u)) : \
                                                ((uint16)(93u)))

    #endif /* (CY_IP_WCO) */

#else
    #define CY_SYS_WDT_KEY                      ((uint32)(0xACED8865u))
    #define CY_SYS_WDT_MATCH_MASK               ((uint32)(0x0000FFFFu))
    #define CY_SYS_WDT_IGNORE_BITS_MASK         ((uint32)(0x000F0000u))
    #define CY_SYS_WDT_IGNORE_BITS_SHIFT        ((uint32)(16u))
    #define CY_SYS_WDT_LOWER_BIT_MASK           ((uint32)(0x00000001u))

    #define CY_SYS_WDT_COUNTER0                 (0x00u)

    #define CY_WDT_NUM_OF_WDT                   (1u)
    #define CY_WDT_NUM_OF_CALLBACKS             (3u)
#endif  /* (CY_IP_SRSSV2) */

#define CY_INT_WDT_IRQN                            (7u)

/* CySysXTAL_32KHZ_SetPowerMode() */
#define CY_SYS_CLK_WCO_HPM                   (0x0u)
#if(0u == (CY_PSOC4_4100M || CY_PSOC4_4200M))
    #define CY_SYS_CLK_WCO_LPM               (0x1u)
#endif /* (0u == (CY_PSOC4_4100M || CY_PSOC4_4200M)) */


#define CY_SYS_CLK_ILO_CONFIG_REG           (*(reg32 *) CYREG_CLK_ILO_CONFIG)
#define CY_SYS_CLK_ILO_CONFIG_PTR           ( (reg32 *) CYREG_CLK_ILO_CONFIG)

#if(CY_IP_SRSSV2)
    #define CY_SYS_CLK_ILO_TRIM_REG             (*(reg32 *) CYREG_CLK_ILO_TRIM)
    #define CY_SYS_CLK_ILO_TRIM_PTR             ( (reg32 *) CYREG_CLK_ILO_TRIM)
#endif  /* (CY_IP_SRSSV2) */

#if (CY_IP_WCO)

    #if (CY_PSOC4_4100BL || CY_PSOC4_4200BL)
        /* WCO Status Register */
        #define CY_SYS_CLK_WCO_STATUS_REG               (*(reg32 *) CYREG_BLE_BLESS_WCO_STATUS)
        #define CY_SYS_CLK_WCO_STATUS_PTR               ( (reg32 *) CYREG_BLE_BLESS_WCO_STATUS)

        /* WCO Configuration Register */
        #define CY_SYS_CLK_WCO_CONFIG_REG               (*(reg32 *) CYREG_BLE_BLESS_WCO_CONFIG)
        #define CY_SYS_CLK_WCO_CONFIG_PTR               ( (reg32 *) CYREG_BLE_BLESS_WCO_CONFIG)

        /* WCO Trim Register */
        #define CY_SYS_CLK_WCO_TRIM_REG                 (*(reg32 *) CYREG_BLE_BLESS_WCO_TRIM)
        #define CY_SYS_CLK_WCO_TRIM_PTR                 ( (reg32 *) CYREG_BLE_BLESS_WCO_TRIM)
    #else   /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */
        /* WCO Status Register */
        #define CY_SYS_CLK_WCO_STATUS_REG               (*(reg32 *) CYREG_WCO_STATUS)
        #define CY_SYS_CLK_WCO_STATUS_PTR               ( (reg32 *) CYREG_WCO_STATUS)

        /* WCO Configuration Register */
        #define CY_SYS_CLK_WCO_CONFIG_REG               (*(reg32 *) CYREG_WCO_CONFIG)
        #define CY_SYS_CLK_WCO_CONFIG_PTR               ( (reg32 *) CYREG_WCO_CONFIG)

        /* WCO Trim Register */
        #define CY_SYS_CLK_WCO_TRIM_REG                 (*(reg32 *) CYREG_WCO_TRIM)
        #define CY_SYS_CLK_WCO_TRIM_PTR                 ( (reg32 *) CYREG_WCO_TRIM)
    #endif /* (CY_PSOC4_4100BL || CY_PSOC4_4200BL) */

#endif  /* (CY_IP_WCO) */


/*******************************************************************************
* WDT API Registers
*******************************************************************************/
#if(CY_IP_SRSSV2)
    #define CY_SYS_WDT_CTRLOW_REG               (*(reg32 *) CYREG_WDT_CTRLOW)
    #define CY_SYS_WDT_CTRLOW_PTR               ( (reg32 *) CYREG_WDT_CTRLOW)

    #define CY_SYS_WDT_CTRHIGH_REG              (*(reg32 *) CYREG_WDT_CTRHIGH)
    #define CY_SYS_WDT_CTRHIGH_PTR              ( (reg32 *) CYREG_WDT_CTRHIGH)

    #define CY_SYS_WDT_MATCH_REG                (*(reg32 *) CYREG_WDT_MATCH)
    #define CY_SYS_WDT_MATCH_PTR                ( (reg32 *) CYREG_WDT_MATCH)

    #define CY_SYS_WDT_CONFIG_REG               (*(reg32 *) CYREG_WDT_CONFIG)
    #define CY_SYS_WDT_CONFIG_PTR               ( (reg32 *) CYREG_WDT_CONFIG)

    #define CY_SYS_WDT_CONTROL_REG              (*(reg32 *) CYREG_WDT_CONTROL)
    #define CY_SYS_WDT_CONTROL_PTR              ( (reg32 *) CYREG_WDT_CONTROL)
#else
    #define CY_SYS_WDT_DISABLE_KEY_REG          (*(reg32 *) CYREG_WDT_DISABLE_KEY)
    #define CY_SYS_WDT_DISABLE_KEY_PTR          ( (reg32 *) CYREG_WDT_DISABLE_KEY)

    #define CY_SYS_WDT_MATCH_REG                (*(reg32 *) CYREG_WDT_MATCH)
    #define CY_SYS_WDT_MATCH_PTR                ( (reg32 *) CYREG_WDT_MATCH)

    #define CY_SYS_WDT_COUNTER_REG              (*(reg32 *) CYREG_WDT_COUNTER)
    #define CY_SYS_WDT_COUNTER_PTR              ( (reg32 *) CYREG_WDT_COUNTER)

    #define CY_SYS_SRSS_INTR_REG                (*(reg32 *) CYREG_SRSS_INTR)
    #define CY_SYS_SRSS_INTR_PTR                ( (reg32 *) CYREG_SRSS_INTR)

    #define CY_SYS_SRSS_INTR_MASK_REG           (*(reg32 *) CYREG_SRSS_INTR_MASK)
    #define CY_SYS_SRSS_INTR_MASK_PTR           ( (reg32 *) CYREG_SRSS_INTR_MASK)
#endif  /* (CY_IP_SRSSV2) */

#if (CY_IP_WCO)

    /*******************************************************************************
    * Function Name: CySysClkWcoSetHighPowerMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the high power mode for the 32 KHz WCO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    *******************************************************************************/
    static CY_INLINE void CySysClkWcoSetHighPowerMode(void)
    {
        /* Switch off low power mode for WCO */
        CY_SYS_CLK_WCO_CONFIG_REG &= (uint32) ~CY_SYS_CLK_WCO_CONFIG_LPM_EN;
        
        /* Switch off auto low power mode in WCO */
        CY_SYS_CLK_WCO_CONFIG_REG &= ((uint32)~CY_SYS_CLK_WCO_CONFIG_LPM_AUTO);

        /* Restore WCO trim register HPM settings */
        CY_SYS_CLK_WCO_TRIM_REG = (CY_SYS_CLK_WCO_TRIM_REG & (uint32)(~CY_SYS_CLK_WCO_TRIM_GM_MASK)) \
                    | (uint32)(CY_SYS_CLK_WCO_TRIM_GM_HPM << CY_SYS_CLK_WCO_TRIM_GM_SHIFT);
        CY_SYS_CLK_WCO_TRIM_REG = (CY_SYS_CLK_WCO_TRIM_REG & (uint32)(~CY_SYS_CLK_WCO_TRIM_XGM_MASK)) \
                    | (uint32)(CY_SYS_CLK_WCO_TRIM_XGM_2620NA << CY_SYS_CLK_WCO_TRIM_XGM_SHIFT);
    }

    #if(!CY_PSOC4_4100M && !CY_PSOC4_4200M)
        /*******************************************************************************
        * Function Name: CySysClkWcoSetLowPowerMode
        ********************************************************************************
        *
        * Summary:
        *  Sets the low power mode for the 32 KHz WCO.
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Side Effects:
        *  None.
        *
        *******************************************************************************/
        static CY_INLINE void CySysClkWcoSetLowPowerMode(void)
        {
            /* Switch off auto low power mode in WCO */
            CY_SYS_CLK_WCO_CONFIG_REG &= ((uint32)~CY_SYS_CLK_WCO_CONFIG_LPM_AUTO);

            /* Change WCO trim register settings to LPM */
            CY_SYS_CLK_WCO_TRIM_REG = (CY_SYS_CLK_WCO_TRIM_REG & (uint32)(~CY_SYS_CLK_WCO_TRIM_XGM_MASK)) \
                        | (uint32)(CY_SYS_CLK_WCO_TRIM_XGM_2250NA << CY_SYS_CLK_WCO_TRIM_XGM_SHIFT);
            CY_SYS_CLK_WCO_TRIM_REG = (CY_SYS_CLK_WCO_TRIM_REG & (uint32)(~CY_SYS_CLK_WCO_TRIM_GM_MASK)) \
                        | (uint32)(CY_SYS_CLK_WCO_TRIM_GM_LPM << CY_SYS_CLK_WCO_TRIM_GM_SHIFT);

            /* Switch on low power mode for WCO */
            CY_SYS_CLK_WCO_CONFIG_REG |= CY_SYS_CLK_WCO_CONFIG_LPM_EN;
        }
    #endif /* (!CY_PSOC4_4100M && !CY_PSOC4_4200M) */

#endif  /* (CY_IP_WCO) */


/* These defines are intended to maintain the backward compatibility for
 * projects which use cy_boot_v4_20 or earlier.
*/
#define CySysWdtWriteMode           CySysWdtSetMode
#define CySysWdtReadMode            CySysWdtGetMode
#define CySysWdtWriteClearOnMatch   CySysWdtSetClearOnMatch
#define CySysWdtReadClearOnMatch    CySysWdtGetClearOnMatch
#define CySysWdtReadEnabledStatus   CySysWdtGetEnabledStatus
#define CySysWdtWriteCascade        CySysWdtSetCascade
#define CySysWdtReadCascade         CySysWdtGetCascade
#define CySysWdtWriteMatch          CySysWdtSetMatch
#define CySysWdtWriteToggleBit      CySysWdtSetToggleBit
#define CySysWdtReadToggleBit       CySysWdtGetToggleBit
#define CySysWdtReadMatch           CySysWdtGetMatch
#define CySysWdtReadCount           CySysWdtGetCount
#define CySysWdtWriteIgnoreBits     CySysWdtSetIgnoreBits
#define CySysWdtReadIgnoreBits      CySysWdtGetIgnoreBits
#define CySysWdtSetIsrCallback      CySysWdtSetInterruptCallback
#define CySysWdtGetIsrCallback      CySysWdtGetInterruptCallback

#endif /* (CY_LFCLK_CYLIB_H) */

/* [] END OF FILE */
