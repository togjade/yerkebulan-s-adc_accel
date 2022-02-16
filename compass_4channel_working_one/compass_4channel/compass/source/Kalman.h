#ifndef __KALMAN_H
#define __KALMAN_H


#define GyroX_var  0.00003
#define GyroY_var  0.00003
#define GyroZ_var  0.00003

#define AccX_var  0.05112
#define AccY_var  0.07291
#define AccZ_var  0.16114



#include "Quaternion.h"


extern Accelerometer A_pred;

void Update_H_matrix(Kalman* h, Quaternion* q);
void Update_Tk_matrix(Kalman* T, Gyro* q);
void Update_Gyro_ECM(Kalman* T, Quaternion* q);
void Predict_ECM(Kalman* K);
void Predict_Quat(Kalman* K,Quaternion* Q);
void Update_K(Kalman* K);
void Update_K_finally(Kalman* K);
void Update_State1(Quaternion* Q, Kalman* K,Accelerometer* A,Accelerometer* A_pred);
void Init_Kalman(Kalman* K);
void increment_ECM(Kalman *K);
void Zero_ECM(Kalman* K);
#endif
