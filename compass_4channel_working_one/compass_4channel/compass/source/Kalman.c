#include "Kalman.h"
#include <stm32f30x_GPIO.h>
/*
Steps:
1. Calculate Update:+++++
Update_Tk_matrix();

2. Preditc State:
X(k+1)=T->Update*X(k)+++++

3. Predict ECM:
Predict_ECM();+++++++++

4. Calculate Hk matrix
Update_H_matrix();+++++

5. Calculate Gain:
Update_K();+++++++

6. Calculate euler angles using Quaternion:
Quat2_Euler_nonlinear(Quaternion* q,Euler_angles* euler);

7. Update state X(k+1)
Update_State();
 
*/
float32_t Ak_Copy[3][3];
float32_t Ak_Copy_2[3][3];
float32_t Determinant;

void Init_Kalman(Kalman* K)
{
K->Noise_measurement[0]=AccX_var;
K->Noise_measurement[1]=AccY_var;
K->Noise_measurement[2]=AccZ_var;
K->Noise_measurement[3]=0;
	
K->Gyro_noize[0]=GyroX_var;
K->Gyro_noize[1]=GyroY_var;
K->Gyro_noize[2]=GyroZ_var;	
}

void Predict_Quat(Kalman* K, Quaternion* Q)
{
uint8_t i,j;	
float32_t Q_copy[4];
	for(i=0;i<4;i++)
	{
  Q_copy[i]=K->Update[i][0]*Q->s+K->Update[i][1]*Q->x+K->Update[i][2]*Q->y+K->Update[i][3]*Q->z;
	}
    Q->s=Q_copy[0];
	Q->x=Q_copy[1];
	Q->y=Q_copy[2];
	Q->z=Q_copy[3];
	
}
void Update_H_matrix(Kalman* h, Quaternion* q)
{
float32_t den_1,den_2,den_sum,pitch_den;
	
	h->Ak_matrix[0][0]=2*q->y;
	h->Ak_matrix[0][1]=0;
	h->Ak_matrix[0][2]=2*q->s;
	
	h->Ak_matrix[1][0]=-2*q->x;
	h->Ak_matrix[1][1]=-2*q->s;
	h->Ak_matrix[1][2]=0;
	

	h->Ak_matrix[2][0]=0;
	h->Ak_matrix[2][1]=-4*q->x;
	h->Ak_matrix[2][2]=-4*q->y;

}

void Update_Tk_matrix(Kalman* T, Gyro* g)
{
T->Update[0][0]=1.0f;
T->Update[0][1]=-0.5f*(g->p);
T->Update[0][2]=-0.5f*g->q;
T->Update[0][3]=-0.5f*g->r;

T->Update[1][0]=0.5f*(g->p);
T->Update[1][1]=1.0f;
T->Update[1][2]=-0.5f*g->r;
T->Update[1][3]=0.5f*g->q;
	
T->Update[2][0]=0.5f*(g->q);
T->Update[2][1]=0.5f*g->r;
T->Update[2][2]=1.0f;
T->Update[2][3]=-0.5f*g->p;
		
T->Update[3][0]=0.5f*(g->r);
T->Update[3][1]=-0.5f*g->q;
T->Update[3][2]=0.5f*g->p;
T->Update[3][3]=1.0f;
}


void Update_Gyro_ECM(Kalman* T, Quaternion* q)
{

T->Gyro_ECM[0][0]=q->s;
T->Gyro_ECM[0][1]=-0.5f*q->x;
T->Gyro_ECM[0][2]=-0.5f*q->y;
T->Gyro_ECM[0][3]=-0.5f*q->z;

T->Gyro_ECM[1][0]=q->x;
T->Gyro_ECM[1][1]=0.5f*q->s;
T->Gyro_ECM[1][2]=0.5f*q->z;
T->Gyro_ECM[1][3]=-0.5f*q->y;
	
T->Gyro_ECM[2][0]=q->y;
T->Gyro_ECM[2][1]=-0.5*q->z;
T->Gyro_ECM[2][2]=0.5*q->s;
T->Gyro_ECM[2][3]=0.5*q->x;
		
T->Gyro_ECM[3][0]=q->z;
T->Gyro_ECM[3][1]=0.5*q->y;
T->Gyro_ECM[3][2]=-0.5*q->x;
T->Gyro_ECM[3][3]=0.5*q->s;


}

void Predict_ECM(Kalman* K)
{
uint8_t i,j;
float32_t QCopy[4][4];
float32_t mult[4];	

		for(j=0;j<4;j++)
		{
		QCopy[j][0]=0;
 		QCopy[j][1]=K->Gyro_noize[0]*K->Gyro_ECM[j][1];
 		QCopy[j][2]=K->Gyro_noize[1]*K->Gyro_ECM[j][2];
 		QCopy[j][3]=K->Gyro_noize[2]*K->Gyro_ECM[j][3];
 			
		}
		
		for(i=0;i<4;i++)
	{
		for(j=i;j<4;j++)
		{
	//	arm_mult_f32(&K->Gyro_ECM[i][0],&QCopy[j][0],mult,4);
	  K->Error_cov_pred[i][j]+=K->Gyro_ECM[i][0]*QCopy[j][0]+K->Gyro_ECM[i][1]*QCopy[j][1]+K->Gyro_ECM[i][2]*QCopy[j][2]+K->Gyro_ECM[i][3]*QCopy[j][3];
	  K->Error_cov_pred[j][i]=K->Error_cov_pred[i][j];
		}
	}

	

}

void Update_K(Kalman* K)
{

uint8_t i,j,k;
float32_t Copy[3][3];
for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{

	  Ak_Copy_2[j][i]=K->Error_cov[i][0]*K->Ak_matrix[j][0]+K->Error_cov[i][1]*K->Ak_matrix[j][1]+
			  K->Error_cov[i][2]*K->Ak_matrix[j][2];
		}
	}

for(i=0;i<3;i++)
	{
		for(j=i;j<3;j++)
		{
		Copy[i][j]=K->Ak_matrix[i][0]*Ak_Copy_2[j][0]+K->Ak_matrix[i][1]*Ak_Copy_2[j][1]+
				K->Ak_matrix[i][2]*Ak_Copy_2[j][2];
		Copy[j][i]=Copy[i][j];
		}
	}
	Copy[0][0]+=K->Noise_measurement[0];
	Copy[1][1]+=K->Noise_measurement[1];
	Copy[2][2]+=K->Noise_measurement[2];

	Determinant=Copy[0][0]*Copy[1][1]*Copy[2][2]+Copy[1][0]*Copy[2][1]*Copy[0][2]+
			Copy[2][0]*Copy[0][1]*Copy[1][2]-Copy[0][0]*Copy[2][1]*Copy[1][2]-
			Copy[2][0]*Copy[1][1]*Copy[0][2]-Copy[1][0]*Copy[0][1]*Copy[2][2];
	Determinant=1/Determinant;
	Ak_Copy[0][0]=Copy[1][1]*Copy[2][2]-Copy[1][2]*Copy[2][1];
	Ak_Copy[0][1]=Copy[0][2]*Copy[2][1]-Copy[0][1]*Copy[2][2];
	Ak_Copy[0][2]=Copy[0][1]*Copy[1][2]-Copy[0][2]*Copy[1][1];
	//Ak_Copy[1][0]=Copy[1][2]*Copy[2][0]-Copy[1][0]*Copy[2][2];
	Ak_Copy[1][1]=Copy[0][0]*Copy[2][2]-Copy[0][2]*Copy[2][0];
	Ak_Copy[1][2]=Copy[0][2]*Copy[1][0]-Copy[0][0]*Copy[1][2];
	//Ak_Copy[2][0]=Copy[1][0]*Copy[2][1]-Copy[1][1]*Copy[2][0];
	//Ak_Copy[2][1]=Copy[0][1]*Copy[2][0]-Copy[0][0]*Copy[2][1];
	Ak_Copy[2][2]=Copy[0][0]*Copy[1][1]-Copy[0][1]*Copy[1][0];



}
void Update_K_finally(Kalman* K)
{
	uint8_t i,j;
	for(i=0;i<3;i++)
			{
				for(j=i;j<3;j++)
				{
					Ak_Copy[i][j]=Ak_Copy[i][j]*Determinant;
					Ak_Copy[j][i]=Ak_Copy[i][j];
				}
			}

		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				K->K_matrix[i][j]=Ak_Copy_2[0][i]*Ak_Copy[0][j]+Ak_Copy_2[1][i]*Ak_Copy[1][j]+
						Ak_Copy_2[2][i]*Ak_Copy[2][j];

			}
		}

}
void Update_State1(Quaternion* Q, Kalman* K,Accelerometer* A,Accelerometer* A_pred)
{
	uint8_t i,j;
	float32_t Copy_Q[4][4];
	float32_t Copy1[4][2];
	float32_t mem[4];
	Accelerometer Diff;

	Diff.X=A->X-A_pred->X;
	Diff.Y=A->Y-A_pred->Y;
	Diff.Z=A->Z-A_pred->Z;
	//Calculating Gain:

	Q->s+=K->K_matrix[0][0]*Diff.X+K->K_matrix[0][1]*Diff.Y+K->K_matrix[0][2]*Diff.Z;
	Q->x+=K->K_matrix[1][0]*Diff.X+K->K_matrix[1][1]*Diff.Y+K->K_matrix[1][2]*Diff.Z;
	Q->y+=K->K_matrix[2][0]*Diff.X+K->K_matrix[2][1]*Diff.Y+K->K_matrix[2][2]*Diff.Z;

}

void Update_State2( Kalman* K)
{
	uint8_t i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			//K->Error_cov[i][j]=Ak_Copy_2[i][j];
			K->Error_cov[i][j]-=Ak_Copy_2[0][j]*K->K_matrix[i][0]+Ak_Copy_2[1][j]*K->K_matrix[i][1]+
					Ak_Copy_2[2][j]*K->K_matrix[i][2];

		}
	}
}

void increment_ECM(Kalman *K)
{
	uint8_t i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			K->Error_cov[i][j]+=K->Error_cov_pred[i][j];
			K->Error_cov_pred[i][j]=0;
		}
	}

}

void Zero_ECM(Kalman* K)
{
	uint8_t i,j;
	for(i=0;i<4;i++)
	 {
		for(j=0;j<4;j++)
		{
			K->Error_cov_pred[i][j]=0;
		}
	}

}
