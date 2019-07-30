/*******************************************************************************
* File Name: capsense_TunerHelper.c
* Version 2.60
*
* Description:
*  This file provides the source code of the Tuner helper APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "capsense_TunerHelper.h"


#if (capsense_TUNER_API_GENERATE)
    #include "SCB.h"
    #include "SCB_EZI2C.h"
    volatile capsense_MAILBOXES capsense_mailboxesComm;
#endif  /* (capsense_TUNER_API_GENERATE) */

/* `#START capsense_TunerHelper_HEADER` */

/* `#END` */

/*******************************************************************************
* Function Name: capsense_TunerStart
********************************************************************************
*
* Summary:
*  Initializes the CapSense CSD component and EzI2C communication component to use
*  a mailbox data structure for communication with the Tuner GUI.
*  Start the scanning, after initialization is complete.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void capsense_TunerStart(void)
{
    #if (0u != capsense_TUNER_API_GENERATE)

        /* Init mbx and quick check */
        capsense_InitMailbox(&capsense_mailboxesComm.csdMailbox);
        capsense_mailboxesComm.numMailBoxes = capsense_DEFAULT_MAILBOXES_NUMBER;

        /* Start CapSense and baselines */
        capsense_Start();

        /* Initialize baselines */
        #if(0u != capsense_CSHL_API_GENERATE)
            capsense_InitializeEnabledBaselines();
        #endif /* (0u != capsense_CSHL_API_GENERATE) */

        /* Start EzI2C, clears buf pointers */
        SCB_Start();

        /* Setup EzI2C buffers */
        SCB_EzI2CSetBuffer1(sizeof(capsense_mailboxesComm), sizeof(capsense_mailboxesComm),
                                                   (volatile uint8 *) &capsense_mailboxesComm);

        /* Starts scan all enabled sensors */
        capsense_ScanEnabledWidgets();

    #endif  /* (0u != capsense_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: capsense_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scanning loop is completed and applies
*  the new parameters from the Tuner GUI if available (the manual tuning mode only). Updates
*  the enabled baselines and state of widgets. Waits while the Tuner GUI reports that
*  the mailbox content  could be modified. Then loads the report data into the outbox
*  and sets a busy flag. Starts a new scanning loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void capsense_TunerComm(void)
{
    #if (0u != capsense_TUNER_API_GENERATE)
        if (0u == capsense_IsBusy())
        {
            /* Apply new settings */
            #if((capsense_TUNING_METHOD != capsense__TUNING_NONE) &&\
                (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                (capsense_TUNING_METHOD == capsense__TUNING_MANUAL))

                capsense_ReadMessage(&capsense_mailboxesComm.csdMailbox);

            #endif  /* ((capsense_TUNING_METHOD != capsense__TUNING_NONE) &&\
                        (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                        (capsense_TUNING_METHOD == capsense__TUNING_MANUAL)) */

            #if(0u != capsense_CSHL_API_GENERATE)
                /* Update all baselines and process all widgets */
                capsense_UpdateEnabledBaselines();
                capsense_ProcessAllWidgets(&capsense_mailboxesComm.csdMailbox.outbox);
            #endif /* (0u != capsense_CSHL_API_GENERATE) */

            capsense_PostMessage(&capsense_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            SCB_EnableInt();

            while((capsense_mailboxesComm.csdMailbox.type != capsense_TYPE_ID) ||
                  (0u != (SCB_EzI2CGetActivity() & SCB_EZI2C_STATUS_BUSY))){}

            /* Disable EZI2C interrupts, while scanning */
            SCB_DisableInt();

            /* Start scan all sensors */
            capsense_ScanEnabledWidgets();
        }
    #endif /* (0u != capsense_TUNER_API_GENERATE) */
}


#if ((0u != capsense_TUNER_API_GENERATE) && (0u != capsense_CSHL_API_GENERATE))
    /*******************************************************************************
    * Function Name: capsense_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Calls the required functions to update all the widgets' state:
    *   - capsense_GetCentroidPos() - calls only if linear sliders are
    *     available.
    *   - capsense_GetRadialCentroidPos() - calls only if the  radial slider is
    *     available.
    *   - capsense_GetTouchCentroidPos() - calls only if the  touchpad slider
    *     available.
    *   - capsense_CheckIsAnyWidgetActive();
    *  The results of operations are copied to OUTBOX.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  capsense_OUTBOX outbox - the structure which is used as an output
    *  buffer to report data to the Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Global Variables:
    *  None
    *
    *******************************************************************************/
    void capsense_ProcessAllWidgets(volatile capsense_OUTBOX *outbox)
    {
        uint8  i = 0u;

        #if (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT)
            uint8 mbPositionBuf[capsense_MB_POSITION_BUFFER_SIZE];
        #endif /* (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if (0u != capsense_TOTAL_TOUCH_PADS_BASIC_COUNT)
            uint16 centroidPosBuf[capsense_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != capsense_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if(0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT)
            capsense_POSITION_STRUCT trackpadPosBuf[capsense_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if ( (0u != capsense_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != capsense_TOTAL_TOUCH_PADS_COUNT) || \
              (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT))
            uint8 widgetCnt;
        #endif  /* ((0u != capsense_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != capsense_TOTAL_TOUCH_PADS_COUNT)) ||
                *   (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT)
                */

        /* Calculate widget with centroids */
        #if (0u != capsense_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < capsense_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->centroidPosition[i] = (uint16)capsense_GetCentroidPos((uint32)i);
            }
        #endif /* (0u != capsense_TOTAL_LINEAR_SLIDERS_COUNT) */

        #if (0u != capsense_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + capsense_TOTAL_RADIAL_SLIDERS_COUNT); i++)
            {
                outbox->centroidPosition[i] = (uint16)capsense_GetRadialCentroidPos((uint32)i);
            }
        #endif /* (0u != capsense_TOTAL_RADIAL_SLIDERS_COUNT) */

        #if (0u != capsense_TOTAL_TOUCH_PADS_BASIC_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (capsense_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u)); i=i+2u)
            {
                if(capsense_GetTouchCentroidPos((uint32)i, centroidPosBuf) == 0u)
                {
                    outbox->centroidPosition[i + capsense_FIRST_FINGER_X_INDEX] = capsense_MAX_UINT_16;
                    outbox->centroidPosition[i + capsense_FIRST_FINGER_Y_INDEX] = capsense_MAX_UINT_16;
                }
                else
                {
                    outbox->centroidPosition[i + capsense_FIRST_FINGER_X_INDEX] =
                    (uint16) centroidPosBuf[capsense_FIRST_FINGER_X_INDEX];

                    outbox->centroidPosition[i + capsense_FIRST_FINGER_Y_INDEX] =
                    (uint16) centroidPosBuf[capsense_FIRST_FINGER_Y_INDEX];
                }
            }
        #endif /* (0u != capsense_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (capsense_TOTAL_TRACKPAD_GESTURES_COUNT * 4u)); i=i+4u)
            {
                outbox->fingersNum[capsense_DEFAULT_TRACKPAD_INDEX] =
                (uint8)capsense_GetDoubleTouchCentroidPos(trackpadPosBuf);

                outbox->gestureID[capsense_DEFAULT_TRACKPAD_INDEX] =
                (uint8)capsense_DecodeAllGestures((uint32)outbox->fingersNum[capsense_DEFAULT_TRACKPAD_INDEX], trackpadPosBuf);

                #if((0u != capsense_ST_SCROLL_GEST_ENABLED) || (0u != capsense_DT_SCROLL_GEST_ENABLED))
                    /*
                    Report Scroll count only for scroll and Inertial Scroll gestures.
                    For all other gestures report scroll count as zero to tuner.
                     */
                    if (((outbox->gestureID[capsense_DEFAULT_TRACKPAD_INDEX] & capsense_GESTURE_TYPE_MASK) == capsense_NON_INERTIAL_SCROLL) ||
                        ((outbox->gestureID[capsense_DEFAULT_TRACKPAD_INDEX] & capsense_GESTURE_TYPE_MASK) == capsense_INERTIAL_SCROLL))
                    {
                        outbox->scrollCnt = capsense_GetScrollCnt();
                    }
                    else
                    {
                        outbox->scrollCnt = 0u;
                    }
                #endif /* ((0u != capsense_ST_SCROLL_GEST_ENABLED) || (0u != capsense_DT_SCROLL_GEST_ENABLED)) */

                outbox->centroidPosition[i + capsense_FIRST_FINGER_X_INDEX] = capsense_MAX_UINT_16;
                outbox->centroidPosition[i + capsense_FIRST_FINGER_Y_INDEX] = capsense_MAX_UINT_16;
                outbox->centroidPosition[i + capsense_SECOND_FINGER_X_INDEX] = capsense_MAX_UINT_16;
                outbox->centroidPosition[i + capsense_SECOND_FINGER_Y_INDEX] = capsense_MAX_UINT_16;

                if(0u != outbox->fingersNum[capsense_DEFAULT_TRACKPAD_INDEX])
                {
                    outbox->centroidPosition[i + capsense_FIRST_FINGER_X_INDEX] =
                    (uint16) trackpadPosBuf[capsense_FIRST_FINGER_INDEX].x;

                    outbox->centroidPosition[i + capsense_FIRST_FINGER_Y_INDEX] =
                    (uint16) trackpadPosBuf[capsense_FIRST_FINGER_INDEX].y;

                    if(outbox->fingersNum[capsense_DEFAULT_TRACKPAD_INDEX] > 1u)
                    {
                        outbox->centroidPosition[i + capsense_SECOND_FINGER_X_INDEX] =
                        (uint16) trackpadPosBuf[capsense_SECOND_FINGER_INDEX].x;

                        outbox->centroidPosition[i + capsense_SECOND_FINGER_Y_INDEX] =
                        (uint16) trackpadPosBuf[capsense_SECOND_FINGER_INDEX].y;
                    }
                }
            }
        #endif /* (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT)
            i += capsense_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0u;
            for(; widgetCnt < (capsense_TOTAL_MATRIX_BUTTONS_COUNT * 2u); widgetCnt += 2u)
            {
                if(capsense_GetMatrixButtonPos((uint32)i, mbPositionBuf) == 0u)
                {
                    outbox->mbPosition[widgetCnt] = capsense_MAX_UINT_8;
                    outbox->mbPosition[widgetCnt+1u] = capsense_MAX_UINT_8;
                }
                else
                {
                    outbox->mbPosition[widgetCnt] = mbPositionBuf[0u];
                    outbox->mbPosition[widgetCnt+1u] = mbPositionBuf[1u];
                }
                i += 2u;
            }
        #endif /* (0u != capsense_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if(0u != capsense_CSHL_API_GENERATE)
            /* Update On/Off State */
            (void)capsense_CheckIsAnyWidgetActive();

            /* Copy OnMask */
            for(i=0u; i < capsense_TOTAL_SENSOR_MASK_COUNT; i++)
            {
                outbox->onMask[i]  = capsense_sensorOnMask[i];
            }
        #endif /* (0u != capsense_CSHL_API_GENERATE) */

        /* `#START capsense_ProcessAllWidgets_Debug` */

        /* `#END` */

        #ifdef capsense_PROCESS_ALL_WIDGETS_CALLBACK
            capsense_ProcessAllWidgets_Callback();
        #endif /* capsense_PROCESS_ALL_WIDGETS_CALLBACK */
    }


#endif /* ((0u != capsense_TUNER_API_GENERATE) && (0u != capsense_CSHL_API_GENERATE)) */


/* [] END OF FILE */
