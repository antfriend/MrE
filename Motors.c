//////////////////////////////////////*
//////////////////////////////////////////////////////////*
//               MOTORS
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
#include <avr/io.h>
#include "Main.h"
#include "Motors.h"

//functions
void EnableLeftMotor(void)
{
	bit_set(ENABLE_MOTORS_PORT,ENABLE_L_MOTOR);
	//PORTC |= (1<<PC1);	//set enable bit to 1 enabling motors
	//PORTC |= (1<<PC0);	//set enable bit to 1 enabling motors
}
void DisableLeftMotor(void)
{
	bit_clear(ENABLE_MOTORS_PORT,ENABLE_L_MOTOR);
}
void EnableRightMotor(void)
{
	bit_set(ENABLE_MOTORS_PORT,ENABLE_R_MOTOR);
}
void DisableRightMotor(void)
{
	bit_clear(ENABLE_MOTORS_PORT,ENABLE_R_MOTOR);
}

void MyLeftWheelForward(void)
{
	bit_clear(L_MOTOR_PORT,L_MOTOR_B);
	bit_set(L_MOTOR_PORT,L_MOTOR_F);
}
void MyLeftWheelBackward(void)
{
	bit_clear(L_MOTOR_PORT,L_MOTOR_F);
	bit_set(L_MOTOR_PORT,L_MOTOR_B);
}
void MyLeftWheelStop(void)
{
	bit_clear(L_MOTOR_PORT,L_MOTOR_B);
	bit_clear(L_MOTOR_PORT,L_MOTOR_F);
}
void MyLeftWheelBreak(void)
{
//	bit_clear(L_MOTOR_PORT,L_MOTOR_B);
//	bit_clear(L_MOTOR_PORT,L_MOTOR_F);
	bit_set(L_MOTOR_PORT,L_MOTOR_F);
	bit_set(L_MOTOR_PORT,L_MOTOR_B);
}

void MyRightWheelForward(void)
{
	bit_clear(R_MOTOR_PORT,R_MOTOR_B);
	bit_set(R_MOTOR_PORT,R_MOTOR_F);
}
void MyRightWheelBackward(void)
{
	bit_clear(R_MOTOR_PORT,R_MOTOR_F);
	bit_set(R_MOTOR_PORT,R_MOTOR_B);
}
void MyRightWheelStop(void)
{
	bit_clear(R_MOTOR_PORT,R_MOTOR_B);
	bit_clear(R_MOTOR_PORT,R_MOTOR_F);
}
void MyRightWheelBreak(void)
{
//	bit_clear(R_MOTOR_PORT,R_MOTOR_B);
//	bit_clear(R_MOTOR_PORT,R_MOTOR_F);
	bit_set(R_MOTOR_PORT,R_MOTOR_F);
	bit_set(R_MOTOR_PORT,R_MOTOR_B);
}

void ForwardBreak(int QTurns)
{
	MyLeftWheelForward();
	MyRightWheelForward();
	while(QTurns)
	{
		aQuarterTurnPause;
		QTurns--;
	}
	MyRightWheelBreak();
	MyLeftWheelBreak();
	MyLeftWheelStop();
	MyRightWheelStop();
}
void BackwardBreak(int QTurns)
{
	MyLeftWheelBackward();
	MyRightWheelBackward();
	while(QTurns)
	{
		aQuarterTurnPause;
		QTurns--;
	}
	MyLeftWheelBreak();
	MyRightWheelBreak();
	MyLeftWheelStop();
	MyRightWheelStop();
}


void StepForward(int FSteps)
{
	//MyLeftWheelForward();
	while(FSteps)
	{
		MyRightWheelForward();
		aQuarterTurnPause;
		//aQuarterTurnCorrection; //correction
		MyRightWheelBreak();
		delayms(250);//pause for reflection
		MyLeftWheelForward();
		aQuarterTurnPause;
		MyLeftWheelBreak();
		delayms(250);//pause for reflection
		FSteps--;
	}
	FullStop();
}

void StepBackward(int FSteps)
{
	//MyLeftWheelBackward();
	while(FSteps)
	{
		MyRightWheelBackward();
		aQuarterTurnPause;
		MyRightWheelBreak();
		MyLeftWheelBackward();
		aQuarterTurnPause;
//		aQuarterTurnCorrection; //correction
		MyLeftWheelBreak();
		FSteps--;
	}
	FullStop();
}

void TurnRight(void)
{
	MyLeftWheelForward();
	MyRightWheelBackward();
}
void TurnLeft(void)
{
	MyRightWheelForward();
	MyLeftWheelBackward();
}
void GoForward(void)
{
	MyRightWheelForward();
	MyLeftWheelForward();
}
void BackUp(void)
{
	MyLeftWheelBackward();
	MyRightWheelBackward();
}
void FullStop(void)
{
	MyLeftWheelStop();
	MyRightWheelStop();
}
