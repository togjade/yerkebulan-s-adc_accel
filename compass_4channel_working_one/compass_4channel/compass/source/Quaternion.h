

#ifndef __QUATERNION_H
#define __QUATERNION_H


#include "arm_math.h"
typedef struct
{
float32_t Tk[4][4];	
}
Tk_matrix;

typedef struct
{
float32_t Variance_Roll;
float32_t Variance_Pitch;
} Noise_measurement;


typedef struct
{
float32_t K_matrix[3][3];       //GAIN
float32_t Noise_measurement[4]; // R matrix
float32_t Error_cov[4][4];		//Q matrix
float32_t Update[4][4];				// Tk matrix	
float32_t Gyro_ECM[4][4];	    //Gyroscope ECM. It is used when predicting ECM of quaternion
float32_t Ak_matrix[4][4];	 //H matrix
float32_t Gyro_noize[3];	
float32_t Error_cov_pred[4][4];		//Q matrix
	
} Kalman;

typedef struct
{
float32_t s;
float32_t x;
float32_t y;
float32_t z;
}
Quaternion;

typedef struct
{
float32_t p;
float32_t q;
float32_t r;
}
Gyro;

typedef struct
{
float32_t roll;
float32_t pitch;
float32_t yaw;
}
Euler_angles;

typedef struct
{
float32_t X;
float32_t Y;
float32_t Z;
}
Accelerometer;

void Normalise(Quaternion* q);
void Normalise_Acc(Accelerometer* A);
void Predict_q(Quaternion* q, Kalman* K);
void Quat2_Euler_nonlinear(Quaternion* q,Euler_angles* euler);
void Quat2_Acceleroemter(Quaternion* q,Accelerometer* A);
void Quat2_Euler_linear(Quaternion* q,Euler_angles* euler);
void Euler_acceleromter(Accelerometer* A,Euler_angles* E);
void Quat4_to3(Quaternion *Q1, Quaternion *Q2);
void Get_gyro_acc();
#endif
