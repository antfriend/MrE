//////////////////////////////////////*
//////////////////////////////////////////////////////////*
#ifndef Motors //               MOTORS
#define Motors
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
//#include "Main.h"

#define ENABLE_MOTORS_PORT     PORTC
#define ENABLE_R_MOTOR     PC0
#define ENABLE_L_MOTOR     PC1

#define R_MOTOR_PORT     PORTC
#define R_MOTOR_F     PC3
#define R_MOTOR_B     PC2
#define L_MOTOR_PORT     PORTB
#define L_MOTOR_F    PB7
#define L_MOTOR_B    PB6

#define aQuarterTurnPause	delayms(110)
#define aQuarterTurnCorrection delayms(30)

//prototypes
void EnableLeftMotor(void);
void EnableRightMotor(void);
void DisableLeftMotor(void);
void DisableRightMotor(void);
void MyLeftWheelForward(void);
void MyLeftWheelBackward(void);
void MyRightWheelForward(void);
void MyRightWheelBackward(void);
void MyLeftWheelStop(void);
void MyRightWheelStop(void);
void MyLeftWheelBreak(void);
void MyRightWheelBreak(void);

void ForwardBreak(int QTurns);
void BackwardBreak(int QTurns);
void StepForward(int FSteps);
void StepBackward(int FSteps);

void TurnRight(void);
void TurnLeft(void);
void GoForward(void);
void BackUp(void);
void FullStop(void);




///////////////////////////////////////////////////////
//////////////////////////////////////
////////////////////////
///////////////////
#endif
