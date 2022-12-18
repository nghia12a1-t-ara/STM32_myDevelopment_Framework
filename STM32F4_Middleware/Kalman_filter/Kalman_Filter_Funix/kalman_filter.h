/*******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 *
 * Description:
 *
 * Author: HoangNH
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 21/08/2020 $
 *
 ******************************************************************************/
#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static float _err_measure;
static float _err_estimate;
static float _q;
static float _current_estimate;
static float _last_estimate;
static float _kalman_gain;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

void KalmanFilterInit(float mea_e, float est_e, float q);
float KalmanFilter_updateEstimate(float mea);
void KalmanFilter_setMeasurementError(float mea_e);
void KalmanFilter_setEstimateError(float est_e);
void KalmanFilter_setProcessNoise(float q);
float KalmanFilter_getKalmanGain(void);
float KalmanFilter_getEstimateError(void);

#endif

/* END FILE */
