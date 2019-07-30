/*******************************************************************************
* File Name: capsense_INT.c
* Version 2.60
*
* Description:
*  This file provides the source code of the  Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "capsense.h"
#include "capsense_PVT.h"



/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START capsense_ISR_INTC` */

/* `#END` */


/*******************************************************************************
* Function Name: capsense_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window
*  depends on the sensor scan resolution parameter.
*  The ISR has two modes:
*   1. Scans a single sensor and stores the measure result.
*   2. Stores the result of the current measure and starts the next scan till all
*      the enabled sensors are scanned.
*  This interrupt handler is only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  capsense_csv - used to provide the status and mode of the scanning process.
*   Mode - a single scan or scan of all the enabled sensors.
*   Status - scan is in progress or ready for new scan.
*  capsense_sensorIndex - used to store a sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(capsense_ISR)
{
    static uint8 capsense_snsIndexTmp;

    #ifdef capsense_ISR_ENTRY_CALLBACK
        capsense_ISR_EntryCallback();
    #endif /* capsense_ISR_ENTRY_CALLBACK */

    /*  Place your Interrupt code here. */
    /* `#START capsense_ISR_ENTER` */

    /* `#END` */

    CyIntDisable(capsense_ISR_NUMBER);

    capsense_CSD_INTR_REG = 1u;

    capsense_PostScan((uint32)capsense_sensorIndex);

    if ((capsense_csdStatusVar & capsense_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        capsense_csdStatusVar &= (uint8)~capsense_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        capsense_sensorIndex = capsense_FindNextSensor(capsense_sensorIndex);

        /* Check end of scan */
        if(capsense_sensorIndex < capsense_TOTAL_SENSOR_COUNT)
        {
            capsense_PreScan((uint32)capsense_sensorIndex);
        }
        else
        {
            capsense_csdStatusVar &= (uint8)~capsense_SW_STS_BUSY;

             /* Check if widget has been scanned */
            if((capsense_csdStatusVar & capsense_SW_CTRL_WIDGET_SCAN) != 0u)
            {
                /* Restore sensorEnableMask array */
                for(capsense_snsIndexTmp = 0u;
                    capsense_snsIndexTmp < capsense_TOTAL_SENSOR_MASK;
                    capsense_snsIndexTmp++)
                {
                    /* Backup sensorEnableMask array */
                    capsense_sensorEnableMask[capsense_snsIndexTmp] = capsense_sensorEnableMaskBackup[capsense_snsIndexTmp];
                }
            }
        }
    }
    CyIntEnable(capsense_ISR_NUMBER);

    /*  Place your Interrupt code here. */
    /* `#START capsense_ISR_EXIT` */

    /* `#END` */

    #ifdef capsense_ISR_EXIT_CALLBACK
        capsense_ISR_ExitCallback();
    #endif /* capsense_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
