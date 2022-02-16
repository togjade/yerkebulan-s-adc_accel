
#include "Quaternion.h"


void Predict_q(Quaternion* q, Kalman* K)
{
	float32_t mem[4];
	arm_mult_f32((float32_t *)&q->s,&(K->Update[0][0]),mem,4);
	q->s=mem[0]+mem[2]+mem[3]+mem[1];
	arm_mult_f32((float32_t *)&q->x,&(K->Update[1][0]),mem,4);
	q->s=mem[0]+mem[2]+mem[3]+mem[1];
  arm_mult_f32((float32_t *)&q->y,&(K->Update[2][0]),mem,4);
	q->s=mem[0]+mem[2]+mem[3]+mem[1];
	arm_mult_f32((float32_t *)&q->z,&(K->Update[3][0]),mem,4);
	q->s=mem[0]+mem[2]+mem[3]+mem[1];
  Normalise(q);
}

void Normalise(Quaternion* q)
{

	Quaternion square;
	float32_t sum;
	square.s=q->s*q->s;
	square.x=q->x*q->x;
	square.y=q->y*q->y;
	square.z=q->z*q->z;
	sum=square.s+square.x+square.y+square.z;
	arm_sqrt_f32(sum,&sum);
	//sum=sqrt(sum);
	q->s/=sum;
	q->x/=sum;
	q->y/=sum;
	q->z/=sum;
}

void Normalise_Acc(Accelerometer* A)
{
	float32_t sum=0;
	sum=A->X*A->X+A->Y*A->Y+A->Z*A->Z;

	arm_sqrt_f32(sum,&sum);
	A->X/=sum;
	A->Y/=sum;
	A->Z/=sum;
}

void Quat2_Euler_nonlinear(Quaternion* q,Euler_angles* euler)
{

euler->pitch= atan2f(2*(q->z*q->y+q->s*q->x),1-2*(q->x*q->x+q->y*q->y));
euler->roll= -asinf(2*(q->x*q->z+q->s*q->x));
euler->yaw=atan2f(2*(q->x*q->y+q->s*q->z),1-2*(q->z*q->z+q->y*q->y));;
}

void Quat2_Acceleroemter(Quaternion* q,Accelerometer* A)
{
A->X=2*(q->z*q->x+q->s*q->y);
A->Y= 2*(q->y*q->z-q->s*q->x);
A->Z=(1-2*(q->x*q->x+q->y*q->y));	
}

void Euler_acceleromter(Accelerometer* A,Euler_angles* E)
{
float32_t Square;
	
Square=A->Y*A->Y+A->Z*A->Z;
	arm_sqrt_f32(Square,&Square);
E->roll=-atan2f(A->Y,A->Z);
E->pitch=atan2f(A->X,Square);
}

void Quat4_to3(Quaternion *Q1, Quaternion *Q2)
{
	if(Q1->s>0)
	{
		Q2->s=Q1->s;
	}
	else
	{
		Q2->s=-Q1->s;

	}

	Q2->x=(Q1->x*Q1->s-Q1->z*Q1->y)/Q2->s;
	Q2->y=(Q1->s*Q1->y+Q1->z*Q1->x)/Q2->s;
}
