/*******************************************************************************
* File Name: capsense_TunerHelper.h
* Version 2.60
*
* Description:
*  This file provides constants and structure declarations for the tuner helper
*  APIs for the CapSense CSD component.
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_capsense_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_capsense_H

#include "capsense.h"

#if(0u != capsense_CSHL_API_GENERATE)
    #include "capsense_CSHL.h"
#endif /* (0u != capsense_CSHL_API_GENERATE) */

#if (capsense_TUNER_API_GENERATE)
    #include "capsense_MBX.h"
#endif /* (capsense_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define capsense_DEFAULT_MAILBOXES_NUMBER       (1u)

#define capsense_CENTROID_POSITION_BUFFER_SIZE  (2u)
#define capsense_MB_POSITION_BUFFER_SIZE        (2u)

#define capsense_DEFAULT_TRACKPAD_INDEX         (0u)

#define capsense_FIRST_FINGER_INDEX             (0u)
#define capsense_SECOND_FINGER_INDEX            (1u)

#define capsense_FIRST_FINGER_X_INDEX           (0u)
#define capsense_FIRST_FINGER_Y_INDEX           (1u)

#define capsense_SECOND_FINGER_X_INDEX          (2u)
#define capsense_SECOND_FINGER_Y_INDEX          (3u)

#define capsense_GESTURE_TYPE_MASK              (0xF0u)
#define capsense_INERTIAL_SCROLL                (0xB0u)
#define capsense_NON_INERTIAL_SCROLL            (0xC0u)


/***************************************
*        Function Prototypes
***************************************/

void capsense_TunerStart(void);
void capsense_TunerComm(void);

#if (capsense_TUNER_API_GENERATE)
   capsense_NO_STRICT_VOLATILE void capsense_ProcessAllWidgets(volatile capsense_OUTBOX *outbox);
#endif /* (capsense_TUNER_API_GENERATE) */


/***************************************
*     Vars with External Linkage
***************************************/
#if (capsense_TUNER_API_GENERATE)
    extern volatile capsense_MAILBOXES capsense_mailboxesComm;
#endif /* (capsense_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_capsense_H)*/


/* [] END OF FILE */
