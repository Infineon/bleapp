/*******************************************************************************
* File Name: capsense_CSHL.h
* Version 2.60
*
* Description:
*  This file provides constants and parameter values for the High Level APIs
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CSHL_capsense_H)
#define CY_CAPSENSE_CSD_CSHL_capsense_H

#include "capsense.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define capsense_SIGNAL_SIZE                    (8u)
#define capsense_AUTO_RESET                     (0u)
#define capsense_RAW_FILTER_MASK                (8u)

/* Signal size definition */
#define capsense_SIGNAL_SIZE_UINT8              (8u)
#define capsense_SIGNAL_SIZE_UINT16             (16u)

/* Auto reset definition */
#define capsense_AUTO_RESET_DISABLE             (0u)
#define capsense_AUTO_RESET_ENABLE              (1u)

/* Mask for RAW and POS filters */
#define capsense_MEDIAN_FILTER                  (0x01u)
#define capsense_AVERAGING_FILTER               (0x02u)
#define capsense_IIR2_FILTER                    (0x04u)
#define capsense_IIR4_FILTER                    (0x08u)
#define capsense_JITTER_FILTER                  (0x10u)
#define capsense_IIR8_FILTER                    (0x20u)
#define capsense_IIR16_FILTER                   (0x40u)
#define capsense_RAW_FILTERS_ENABLED            (0x01u)
#define capsense_RAW_FILTERS_DISABLED           (0x00u)

/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
#define capsense_LINEARSLIDER0__LS        (0u)

#define capsense_TOTAL_DIPLEXED_SLIDERS_COUNT        (0u)
#define capsense_TOTAL_LINEAR_SLIDERS_COUNT          (1u)
#define capsense_TOTAL_RADIAL_SLIDERS_COUNT          (0u)
#define capsense_TOTAL_TOUCH_PADS_COUNT              (0u)
#define capsense_TOTAL_TOUCH_PADS_BASIC_COUNT        (0u)
#define capsense_TOTAL_TRACKPAD_GESTURES_COUNT       (0u)
#define capsense_TOTAL_BUTTONS_COUNT                 (0u)
#define capsense_TOTAL_MATRIX_BUTTONS_COUNT          (0u)
#define capsense_TOTAL_GENERICS_COUNT                (0u)

#define capsense_POS_FILTERS_MASK                    (0x8u)
#define capsense_LINEAR_SLIDERS_POS_FILTERS_MASK     (0x8u)
#define capsense_RADIAL_SLIDERS_POS_FILTERS_MASK     (0x0u)
#define capsense_TOUCH_PADS_POS_FILTERS_MASK         (0x0u)
#define capsense_TRACKPAD_GEST_POS_FILTERS_MASK      (0x0u)

#define capsense_UNUSED_DEBOUNCE_COUNTER_INDEX       (0u)

#define capsense_TOTAL_PROX_SENSORS_COUNT            (0u)

#define capsense_END_OF_SLIDERS_INDEX                (0u)
#define capsense_END_OF_TOUCH_PAD_INDEX              (0u)
#define capsense_END_OF_BUTTONS_INDEX                (0u)
#define capsense_END_OF_MATRIX_BUTTONS_INDEX         (0u)
#define capsense_END_OF_WIDGETS_INDEX                (1u)



#define capsense_TOTAL_SLIDERS_COUNT            ( capsense_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          capsense_TOTAL_RADIAL_SLIDERS_COUNT )

#define capsense_TOTAL_CENTROIDS_COUNT          ( capsense_TOTAL_SLIDERS_COUNT + \
                                                         (capsense_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (capsense_TOTAL_TRACKPAD_GESTURES_COUNT * 4u))

#define capsense_TOTAL_CENTROIDS_BASIC_COUNT    ( capsense_TOTAL_SLIDERS_COUNT + \
                                                         (capsense_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u))

#define capsense_TOTAL_CENTROID_AXES_COUNT      ( capsense_TOTAL_SLIDERS_COUNT + \
                                                         (capsense_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (capsense_TOTAL_TRACKPAD_GESTURES_COUNT * 2u))

#define capsense_TOTAL_WIDGET_COUNT             ( capsense_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          capsense_TOTAL_RADIAL_SLIDERS_COUNT + \
                                                          capsense_TOTAL_TOUCH_PADS_COUNT + \
                                                          capsense_TOTAL_BUTTONS_COUNT + \
                                                          capsense_TOTAL_MATRIX_BUTTONS_COUNT )

#define capsense_ANY_POS_FILTER                 ( capsense_MEDIAN_FILTER | \
                                                          capsense_AVERAGING_FILTER | \
                                                          capsense_IIR2_FILTER | \
                                                          capsense_IIR4_FILTER | \
                                                          capsense_JITTER_FILTER )

#define capsense_IS_DIPLEX_SLIDER               ( capsense_TOTAL_DIPLEXED_SLIDERS_COUNT > 0u)

#define capsense_IS_NON_DIPLEX_SLIDER           ( (capsense_TOTAL_LINEAR_SLIDERS_COUNT - \
                                                           capsense_TOTAL_DIPLEXED_SLIDERS_COUNT) > 0u)
#define capsense_ADD_SLIDER_TYPE                ((capsense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) ? \
                                                        ((capsense_TOTAL_TOUCH_PADS_COUNT > 0u) || \
                                                         (capsense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) : 0u)

#define capsense_TOTAL_PROX_SENSOR_COUNT        (capsense_TOTAL_PROX_SENSORS_COUNT)

#define capsense_WIDGETS_TBL_SIZE               ( capsense_TOTAL_WIDGET_COUNT + \
                                                          capsense_TOTAL_GENERICS_COUNT)

#define capsense_WIDGET_PARAM_TBL_SIZE          (capsense_TOTAL_BUTTONS_COUNT + \
                                                         capsense_TOTAL_SLIDERS_COUNT +\
                                                         capsense_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u + \
                                                         capsense_TOTAL_TRACKPAD_GESTURES_COUNT * 2u +\
                                                         capsense_TOTAL_MATRIX_BUTTONS_COUNT * 2u)

#define capsense_THRESHOLD_TBL_SIZE         (capsense_WIDGET_PARAM_TBL_SIZE)
#define capsense_DEBOUNCE_CNT_TBL_SIZE      (capsense_WIDGET_PARAM_TBL_SIZE)
#define capsense_RAW_DATA_INDEX_TBL_SIZE    (capsense_WIDGET_PARAM_TBL_SIZE +\
                                                     capsense_TOTAL_GENERICS_COUNT)

#define capsense_RES_MULT                   (256u)


#define capsense_NOT_WIDGET                     (0xFFFFFFFFu)

/*Types of centroids */
#define capsense_TYPE_RADIAL_SLIDER             (0x01u)
#define capsense_TYPE_LINEAR_SLIDER             (0x02u)
#define capsense_TYPE_GENERIC                   (0xFFu)

/* Defines if sensors or widgets are active */
#define capsense_SENSOR_IS_ACTIVE               (0x01u)
#define capsense_SENSOR_1_IS_ACTIVE             (0x01u)
#define capsense_SENSOR_2_IS_ACTIVE             (0x02u)
#define capsense_WIDGET_IS_ACTIVE               (0x01u)

/* Defines diplex type of Slider */
#define capsense_IS_DIPLEX                      (0x80u)

/* Defines fingers positions on Slider  */
#define capsense_POS_PREV                       (0u)
#define capsense_POS                            (1u)
#define capsense_POS_NEXT                       (2u)
#define capsense_CENTROID_ROUND_VALUE           (0x7F00u)
#define capsense_MAXIMUM_CENTROID               (0xFFu)

#define capsense_NEGATIVE_NOISE_THRESHOLD       (20u)
#define capsense_LOW_BASELINE_RESET             (5u)


/***************************************
*        Function Prototypes
***************************************/

void capsense_InitializeSensorBaseline(uint32 sensor);
void capsense_InitializeAllBaselines(void);
void capsense_InitializeEnabledBaselines(void);
void capsense_UpdateSensorBaseline(uint32 sensor);
void capsense_UpdateBaselineNoThreshold(uint32 sensor);
void capsense_UpdateEnabledBaselines(void);
void capsense_UpdateWidgetBaseline(uint32 widget);
uint16 capsense_GetBaselineData(uint32 sensor);
void capsense_SetBaselineData(uint32 sensor, uint16 data);
void capsense_BaseInit(uint32 sensor);

#if (capsense_IS_DIPLEX_SLIDER)
    uint8 capsense_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold, const uint8 *diplex);
#else
    uint8 capsense_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold);
#endif /* (capsense_IS_DIPLEX_SLIDER) */

#if (capsense_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
    uint8 capsense_CalcCentroid(uint8 maximum, uint8 offset, \
                                    uint8 count, uint32 resolution, uint8 noiseThreshold);
#else
    uint8 capsense_CalcCentroid(uint8 maximum, uint8 offset, \
                                    uint8 count, uint16 resolution, uint8 noiseThreshold);
#endif /* (capsense_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */


uint8 capsense_GetFingerThreshold(uint32 widget);
uint8 capsense_GetNoiseThreshold(uint32 widget);
uint8 capsense_GetFingerHysteresis(uint32 widget);
uint8 capsense_GetNegativeNoiseThreshold(uint32 widget);

#if(capsense_TUNING_METHOD != capsense__TUNING_NONE)
    void capsense_SetFingerThreshold(uint32 widget, uint8 value);
    void capsense_SetNoiseThreshold(uint32 widget, uint8 value);
    void capsense_SetFingerHysteresis(uint32 widget, uint8 value);
    void capsense_SetNegativeNoiseThreshold(uint32 widget, uint8 value);
    void capsense_SetDebounce(uint32 widget, uint8 value);
    void capsense_SetLowBaselineReset(uint32 sensor, uint8 value);
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */

uint8 capsense_GetDiffCountData(uint32 sensor);
void capsense_SetDiffCountData(uint32 sensor, uint8 value);

uint32 capsense_CheckIsSensorActive(uint32 sensor);
uint32 capsense_CheckIsWidgetActive(uint32 widget);
uint32 capsense_CheckIsAnyWidgetActive(void);
void capsense_EnableWidget(uint32 widget);
void capsense_DisableWidget(uint32 widget);
void capsense_EnableRawDataFilters(void);
void capsense_DisableRawDataFilters(void);

#if (capsense_TOTAL_MATRIX_BUTTONS_COUNT)
    uint32 capsense_GetMatrixButtonPos(uint32 widget, uint8* pos);
#endif /* (capsense_TOTAL_MATRIX_BUTTONS_COUNT) */

#if((capsense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (capsense_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 capsense_GetCentroidPos(uint32 widget);
#endif /* ((capsense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (capsense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if((capsense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (capsense_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 capsense_GetRadialCentroidPos(uint32 widget);
#endif /* #if((capsense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (capsense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if (capsense_TOTAL_TOUCH_PADS_COUNT)
    uint32 capsense_GetTouchCentroidPos(uint32 widget, uint16* pos);
#endif /* (capsense_TOTAL_TOUCH_PADS_COUNT) */

uint32 capsense_GetWidgetNumber(uint32 sensor);
uint8 capsense_GetLowBaselineReset(uint32 sensor);
uint8 capsense_GetDebounce(uint32 widget);

/* Filter function prototypes for High level APIs */

/* Median filter function prototype */
#if ( (0u != (capsense_RAW_FILTER_MASK & capsense_MEDIAN_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_MEDIAN_FILTER)) || \
      ((capsense_TUNING_METHOD == capsense__TUNING_AUTO)) )
    uint16 capsense_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* ( (0u != (capsense_RAW_FILTER_MASK & capsense_MEDIAN_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_MEDIAN_FILTER)) || \
      ((capsense_TUNING_METHOD == capsense__TUNING_AUTO)) ) */

/* Averaging filter function prototype */
#if ( (0u != (capsense_RAW_FILTER_MASK & capsense_AVERAGING_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_AVERAGING_FILTER)) )
    uint16 capsense_AveragingFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* capsense_RAW_FILTER_MASK && capsense_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (0u != (capsense_RAW_FILTER_MASK & capsense_IIR2_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_IIR2_FILTER)) )
    uint16 capsense_IIR2Filter(uint16 x1, uint16 x2);
#endif /* capsense_RAW_FILTER_MASK && capsense_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (0u != (capsense_RAW_FILTER_MASK & capsense_IIR4_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_IIR4_FILTER)) )
    uint16 capsense_IIR4Filter(uint16 x1, uint16 x2);
#endif /* capsense_RAW_FILTER_MASK && capsense_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (0u != (capsense_RAW_FILTER_MASK & capsense_IIR8_FILTER))
    uint16 capsense_IIR8Filter(uint16 x1, uint16 x2);
#endif /* capsense_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (0u != (capsense_RAW_FILTER_MASK & capsense_IIR16_FILTER))
    uint16 capsense_IIR16Filter(uint16 x1, uint16 x2);
#endif /* capsense_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (0u != (capsense_RAW_FILTER_MASK & capsense_JITTER_FILTER)) || \
      (0u != (capsense_POS_FILTERS_MASK & capsense_JITTER_FILTER)) || \
      (0u != (capsense_TRACKPAD_GEST_POS_FILTERS_MASK & capsense_JITTER_FILTER)))
    uint16 capsense_JitterFilter(uint16 x1, uint16 x2);
#endif /* ( (0u != (capsense_RAW_FILTER_MASK & capsense_JITTER_FILTER)) || \
       *    (0u != (capsense_POS_FILTERS_MASK & capsense_JITTER_FILTER)) )
       *    (0u != (capsense_TRACKPAD_GEST_POS_FILTERS_MASK & capsense_JITTER_FILTER)) )
       */


/***************************************
*     Vars with External Linkage
***************************************/
extern uint16 capsense_sensorBaseline[capsense_TOTAL_SENSOR_COUNT];
extern uint8  capsense_sensorBaselineLow[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_sensorSignal[capsense_TOTAL_SENSOR_COUNT];
extern uint8  capsense_sensorOnMask[capsense_TOTAL_SENSOR_MASK];

extern uint8 capsense_lowBaselineResetCnt[capsense_TOTAL_SENSOR_COUNT];
extern uint8 capsense_lowBaselineReset[capsense_TOTAL_SENSOR_COUNT];

/* Generated by Customizer */
#if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
    extern uint8 capsense_fingerThreshold[capsense_WIDGET_PARAM_TBL_SIZE];
    extern uint8 capsense_noiseThreshold[capsense_WIDGET_PARAM_TBL_SIZE];
    extern uint8 capsense_negativeNoiseThreshold[capsense_WIDGET_PARAM_TBL_SIZE];
    extern uint8 capsense_hysteresis[capsense_WIDGET_PARAM_TBL_SIZE];
    extern uint8  capsense_debounce[capsense_WIDGET_PARAM_TBL_SIZE];
#else
    extern const uint8 capsense_fingerThreshold[capsense_WIDGET_PARAM_TBL_SIZE];
    extern const uint8 capsense_noiseThreshold[capsense_WIDGET_PARAM_TBL_SIZE];
    extern const uint8 capsense_hysteresis[capsense_WIDGET_PARAM_TBL_SIZE];
    extern const uint8  capsense_debounce[capsense_WIDGET_PARAM_TBL_SIZE];
#endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */

extern const uint8 capsense_rawDataIndex[capsense_RAW_DATA_INDEX_TBL_SIZE];
extern const uint8 capsense_numberOfSensors[capsense_RAW_DATA_INDEX_TBL_SIZE];

#if (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT)
    #if (capsense_TUNING_METHOD != capsense__TUNING_NONE)
        extern uint8 capsense_posFiltersMask[capsense_TOTAL_CENTROID_AXES_COUNT];
    #else
        extern const uint8 capsense_posFiltersMask[capsense_TOTAL_CENTROID_AXES_COUNT];
    #endif /* (capsense_TUNING_METHOD != capsense__TUNING_NONE) */

    extern uint32 capsense_centroidMult[capsense_TOTAL_CENTROID_AXES_COUNT];
#endif /* (0u != capsense_TOTAL_TRACKPAD_GESTURES_COUNT) */

/***************************************
*        Obsolete Names
***************************************/
#define capsense_SensorRaw              capsense_sensorRaw
#define capsense_SensorEnableMask       capsense_sensorEnableMask
#define capsense_SensorBaseline         capsense_sensorBaseline
#define capsense_SensorBaselineLow      capsense_sensorBaselineLow
#define capsense_SensorSignal           capsense_sensorSignal
#define capsense_SensorOnMask           capsense_sensorOnMask
#define capsense_LowBaselineResetCnt    capsense_lowBaselineResetCnt

#endif /* CY_CAPSENSE_CSD_CSHL_capsense_H */

/* [] END OF FILE */
