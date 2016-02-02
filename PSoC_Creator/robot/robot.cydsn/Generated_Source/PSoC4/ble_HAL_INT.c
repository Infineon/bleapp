/***************************************************************************//**
* \file BLE_HAL_INT.c
* \version 2.30
*
* \brief
*  This file contains the source code for the Interrupt Service Routine for the
*  HAL section of the BLE component
*
********************************************************************************
* \copyright
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLE_HAL_PVT.h"


/*******************************************************************************
* Function Name: CyBLE_Bless_Interrupt
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the BLE sub-system.
*
* \return
*  None
*
*******************************************************************************/
CY_ISR(CyBLE_Bless_Interrupt)
{
    #if(CYBLE_STACK_MODE_DEBUG)
        CyBle_ApplCallback(CYBLE_DEBUG_EVT_BLESS_INT, NULL);
    #endif /* CYBLE_STACK_MODE_DEBUG */

    /* Call stack manager bless function handler */
    CyBLE_pf_bless_event_hdlr();
    /* Host stack takes care of clearing interrupts */
}


#if(CYBLE_MODE == CYBLE_HCI)


/*******************************************************************************
* Function Name: CyBLE_Uart_Interrupt
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the UART.
*
* \return
*  None
*
*******************************************************************************/
CY_ISR(CyBLE_Uart_Interrupt)
{
    uint8  uartTxStatus = CyBLE_INTR_TX_SUCCESS;
    uint32 srcInterrupt = 0u;

    uint8 length = 0u;
    uint8 srcCount = 0u;
    uint8 uartRxStatus = CyBLE_INTR_RX_SUCCESS;
    uint8 receivedData[BLE_HAL_Uart_FIFO_SIZE] = {0u};

    /* Evaluate RX interrupt event */
    srcInterrupt = BLE_HAL_Uart_GetRxInterruptSourceMasked();

    if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_RX_NOT_EMPTY))
    {
        if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_RX_PARITY_ERROR))
        {
            uartRxStatus |= CyBLE_INTR_RX_PARITY_ERROR;
        }
        if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_RX_FRAME_ERROR))
        {
            uartRxStatus |= CyBLE_INTR_RX_FRAME_ERROR;
        }
        if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_RX_OVERFLOW))
        {
            uartRxStatus |= CyBLE_INTR_RX_OVERFLOW;
        }
        if(uartRxStatus == CyBLE_INTR_RX_SUCCESS)
        {
            length = (uint8)BLE_HAL_Uart_SpiUartGetRxBufferSize();
            for(srcCount = 0u; srcCount < length; srcCount++)
            {
                receivedData[srcCount] = (uint8)BLE_HAL_Uart_SpiUartReadRxData();
            }
        }
        else
        {
            BLE_HAL_Uart_SpiUartClearRxBuffer();
        }
        for(uartTxStatus = 0u; uartTxStatus < length; uartTxStatus++)
        {
            CyBLE_pf_handle_uart_rx_data(receivedData[uartTxStatus]);
        }
        BLE_HAL_Uart_ClearRxInterruptSource(srcInterrupt);
    }
    else
    {
        /* No RX interrupt. Do nothing. */
    }

    /* Evaluate TX interrupt event in sequence */
    srcInterrupt = BLE_HAL_Uart_GetTxInterruptSourceMasked();

    /* Stack manager TX uart complete */
    if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_TX_UART_DONE))
    {
        if(0u != (srcInterrupt & BLE_HAL_Uart_INTR_TX_OVERFLOW))
        {
            /*Stack manager TX uart error */
            uartTxStatus |= CyBLE_INTR_TX_OVERFLOW;
        }
        CyBLE_pf_handle_uart_tx_complt();
        BLE_HAL_Uart_ClearTxInterruptSource(srcInterrupt);
    }
    else
    {
        /* No TX interrupt. Do nothing. */
    }
}
#endif /* (CYBLE_MODE == CYBLE_HCI) */


/* [] END OF FILE */
