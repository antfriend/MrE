//Mr.E. the Mister E
//http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=8764&start=0
//http://svn.tuxisalive.com/firmware/tuxcore/tags/0.3.0/global.h
/** This code layout is  an instance of "crystalline formatting". **/
/**** J. Schmidhuber's philosophy behind crystalline formatting is:*/
/** Some programmers prefer to debug code that looks nice. *********/
#include		<avr/io.h>
#include		<util/delay.h>
#include		<math.h>
#include		<stdlib.h>

#include		"Main.h"
#include		"Motors.h"
#include		"Prox.h"
#include		"MyEepromDream.h"			
#include		"Compass.h"				
#include 		"LEDs.h"					
#include		"Jumpers.h"					
#include		"Distance.h"				
#include 		"StateOfMind.h"				/* deal with state 		*/

//defines
#define 		F_CPU 8000000UL

//variables
int 			MyStateOfMind=0,			/* see states below		*/
	 			MyPreviousStateOfMind=1,	/* history, one
													degree			*/

	 			PreviousProxState=0,		/* prox history			*/

	 			daWaitingCount=0;			/* universal count
												of loops in current
												state				*/
/*
MyStateOfMind states
0 to 9 		~ prox dots activated
10 to 19	~ too close
20 to 29	~ comfort zone
30 to 39	~ not close enough
40 to 49	~ too far
50 to 59	~ 
60 to 69	~ 
70 to 79	~ 
Mr_E good
TOO_CLOSE=225;
ITZ_TOO_CLOSE=200;
ITZ_TOO_FAR=180;
TOO_FAR=140;
*/
const int 		TOO_CLOSE=225,				/* raise this (up to 255)
												 to look closer 
												 250=3.5 inches
												 200=7 inches
												 */
				ITZ_TOO_CLOSE=200,			/* raise this (up to 
												TOO_CLOSE) to look 
												closer				*/
				ITZ_TOO_FAR=180,			/* lower this (down to TOO_FAR)
												 to look further 	*/
				TOO_FAR=140;				/* lower this (down to 1) 
												to look further 	
												150=2.4 inches
												100<= infinite
												*/

//prototypes
void 			IndicateJumperViaLED(void);
int 			IFeelDifferent(int NewStateOfMind);
void 			MrEhasStoppedNow(void);

//functions
void 			InitEverything(void)
{
					DDRB = 255;				/* set all of port B 
												for output 			*/
					DDRC = 255;				/* set all of port C for 
												output 				*/
					DDRD = 0;				/* set all of port D for 
												input				*/
					bit_set(DDRD,PD1);
					DDRD |= (1 << PD2); 	/* Set PORTD bit 2 as an 
												output				*/
					PORTC |= (0<<PC1);		/* set enable bit to 0 
												and disable motors	*/
					PORTC |= (0<<PC0);		/* set enable bit to 0 
												and disable motors	*/
					InitLEDs();
					InitJumpers();
					InitializeDistance();
					srand(42);
}

void 			delayms(int millis) {
					while ( millis ) {
						_delay_ms( 1 );
						millis--;
					}
}

void 			Delay(u32 count)
{
					while(count--);
}

int bit_get(int daPIN,int daBIT)
{
	//PINC & (1<<1) 
	return ~daPIN & (1<<daBIT);
}

int daRandomNo(void)
{
/*
	"daRandomNo" will return 0 or 1 twice as often as 2 or 3.
	It might return 0 more often.
	It will always return a number between 0 and 3.
*/

	while(1)
	{  
		int random=0;
	    random = rand();
	    random = random / 5461.1667; 
	    if (random <=1)
		{
	        random = 1;
		}
	    else if (random >1 && random <= 2)  
		{
	        random = 2;
		}
	    else if (random >2 && random <= 3)  
		{
	        random = 3;   
		}
	    else if (random >3 && random <= 4)  
		{
	        random = 0;
		}
	    else if (random >4 && random <= 5)  
		{
	        random = 1;       
		}
	    else
		{ 
	        random = 0;
		}
		return random;
	}
}

int main(void)			//program start
{
	InitEverything();

	DisableLeftMotor(); //Enable
	DisableRightMotor();//and Disable
	EnableLeftMotor();  //seem to do
	EnableRightMotor(); //nothing, oh well

	for(int i=3;i>=0;i--)
	{
		ShowLEDvalue(i);
		delayms(750);
	}
	ALL_Off;
	delayms(200);
	ALL_Off;
	delayms(200);
	for(int i=3;i>=0;i--)
	{
		IndicateJumperViaLED();
		delayms(100);
		ALL_Off;
		delayms(50);
	}
	switch(GetJumperValue())
//	switch(2)//force jumper value
	{
		case 4: //binary 00 //no jumpers
			DebugMode();
			break;
		case 1: //binary 01
			DemoMode1();
			break;
		case 2: //binary 10
			DemoMode2();
			break;
		case 3: //binary 11 //both jumpers
			MrE_Mode();
			break;
	}
	return (0);
}

//Prox Dots
int NoProx(void)
{
	int TempMyStateOfMind=0;
	int NoProxHere=0;
	if(RightProxOn())
	{
		if(LeftProxOn())
		{
			TempMyStateOfMind=3;
			BackUp();
			delayms(100);
		}
		else
		{
			TempMyStateOfMind=2;
			TurnRight();
		}
	}
	else
	{
		if(LeftProxOn())
		{
			TempMyStateOfMind=1;
			TurnLeft();
		}
		else
		{
// ****************************************************************************************
// ****************************************************************************************
// ****************************************************************************************
// ****************************************************************************************
// need to create a STATE_OF_BEHAVIOR_STRUCT with a dirty bit
// here we will call FullStop 
// only if the dirty bit is set, 
// indicating a state change
			TempMyStateOfMind=0;
			NoProxHere=1;
		}
	}
	//if NoProxHere=0 then we are close.
	//if we also are in the distance sensor blind spot, 
	//then we are in the zone
	//time to jump to a sub that lets us determine
	//with prox sensors alone that this is an appropriate 
	//cave-home
	if(!(PreviousProxState==TempMyStateOfMind))
	{
		FullStop();
		/*
		if!(NoProxHere)
		{
			//
			MyStateOfMind=TempMyStateOfMind;
		}
		*/
	}
	PreviousProxState=TempMyStateOfMind;
	return NoProxHere;
}

int IFeelDifferent(int NewStateOfMind)
{
	int IAmDifferent=1;
	if (NewStateOfMind==MyStateOfMind)
	{
		IAmDifferent=0;
	}
	else
	{
		IAmDifferent=1;
	}
	return IAmDifferent;
}
void IndicateJumperViaLED(void)
{
	ShowLEDvalue(GetJumperValue());
}
void DebugMode(void)
{
//  ******************************
//  discovery on DISTANCE SENSOR
//  ******************************
	int daTestValue=0;
	while(forever)
	{
		//just the LEDs showing the distance
		daTestValue=0;
		daTestValue=GetDistance();
		BlinkANumber(8,daTestValue);
		delayms(2500);
	}
}
void DemoMode2(void)
{
//  ******************************
//  DISTANCE demo
//  ******************************


	int HowFarToWhatever=0;
	int TheDistanceMeasurement=0;
	int RandIterations=0;
//	int RandLeftOrRight=0;
	

//	******************************
	while(forever)
	{
		//MyPreviousStateOfMind=MyStateOfMind;
		if(NoProx())
		{
			/*
			if(IFeelDifferent(MyPreviousStateOfMind))
			{
				//we just had a prox hit
				
			}
			*/

			TheDistanceMeasurement=GetDistance();
			HowFarToWhatever=IsCloseEnough(TOO_FAR, TOO_CLOSE, TheDistanceMeasurement);
			/*
			MyStateOfMind states
			0 to 9 		~ prox dots activated
			10 to 19	~ too close
			20 to 29	~ comfort zone
			30 to 39	~ not close enough
			40 to 49	~ too far
			*/
			switch(HowFarToWhatever)
			{
				case 0://not close enough
					MyStateOfMind=30;
					B_On;
					//wonder mode
					//loop left or right 
					if (daRandomNo()>1)
					{
						//start turning Left
						TurnLeft();
					}
					else
					{
						//start turning right
						TurnRight();
					}
					//a random number of iterations
					//*************************
					//get # of iterations to turn
					RandIterations=50*(daRandomNo()+1);
					//loop for RandIterations, stopping if the state changes
					for(int i=RandIterations;i>=0;i--)
					{
						if(NoProx())
						{
							//if the proximity is too near, 
							//break this loop
							if(IsCloseEnough(TOO_FAR, TOO_CLOSE, GetDistance()))
							{
								//it's close or too close
								FullStop();
								break;
							}
							else
							{
								//keep doing whatever we 
								//are doing
								delayms(10);	
							}
						}
						else//if either prox dot is hit, 
						//break this loop
						{
							FullStop();
							break;
						}
					}
					//stop everything
					//FullStop();//CHANGED
					break;

				case 1://too close
					MyStateOfMind=10;
					R_On;
					// back up until you don't need to back up any more
					BackUp();
					delayms(50);
					//over compensate with a tiny delay
					break;

				default://Yeah baby, we are 
					//IN THE ZONE OF GOODNESS!
					MyStateOfMind=20;
					G_On;
					//and exactly where are we?
					switch (IsCloseEnough(ITZ_TOO_FAR,ITZ_TOO_CLOSE,HowFarToWhatever))
					{
						case 0://not close enough
							B_On;
							//step forward or pause
							StepForward(1);
							break;
						case 1://just right, stop here
							R_On;
							FullStop();
							MyStateOfMind=29;
							MrEhasStoppedNow();
							break;
						default: //in the zone of the zone
							//let it be green
							//zip forward
							GoForward();
							break;
					}
					break;
			}
			if(IFeelDifferent(MyPreviousStateOfMind))
			{
				//Pause to notice that something is different
				//and re-assess
				//ALL_Off;
				//StepBackward(2);
				FullStop();
				//TheDistanceMeasurement=GetDistance();
				//HowFarToWhatever=IsCloseEnough(TOO_FAR, TOO_CLOSE, TheDistanceMeasurement);
			}
			MyPreviousStateOfMind=MyStateOfMind;
	//		delayms(40); //about 25 frames per second flickers
			delayms(20); //about 50 frames per second
			ALL_Off;
		}
//	******************************
	}//end while
}

void DemoMode1(void)
{
	int daPause=1000;
	while(forever)
	{
		//do a little dance
		ShowLEDvalue(daRandomNo());
		ForwardBreak(1);
		delayms(daPause);
		BackwardBreak(1);
		delayms(daPause);
		ForwardBreak(2);
		delayms(daPause);
		BackwardBreak(2);
		delayms(daPause);
		ForwardBreak(4);
		delayms(daPause);
		BackwardBreak(4);
		delayms(daPause);
		ForwardBreak(16);
		delayms(daPause);
		BackwardBreak(16);
		delayms(daPause);
	}
}


void MrE_Mode(void)
{
	int intWhileCount=0;
	int muhRand=0;
	int daLoopMax=2000;
	muhRand=daRandomNo();//get an inital random value
	
	while(forever)
	{
		ShowLEDvalue(muhRand);
		if(NoProx())
		{
			intWhileCount++;
			delayms(1);
			if(intWhileCount>=daLoopMax)
			{
				intWhileCount=0;
				//StepForward(2);
				muhRand=daRandomNo();//get a new random value
				MakeAMove(muhRand);
				daLoopMax=(100 + (1000 * muhRand));
			}
		}
		else
		{
			//delayms(200);
		}
	}
}

void MrEhasStoppedNow(void)
{
	//we've found the sweet spot in which to pause
	int TheDistanceMeasurement=0;
	int HowFarToWhatever=0;

	for(int x=0;x<=500;x++)
	{
		TheDistanceMeasurement=GetDistance();
		HowFarToWhatever=IsCloseEnough(ITZ_TOO_CLOSE, TOO_CLOSE, TheDistanceMeasurement);

		if(HowFarToWhatever==0)
		{
			//we are still in it
			ALL_Off;
			R_On;
			delayms(200);
		}
		else
		{
			ALL_Off;
			B_On;
			delayms(200);
		}
	}//end for
	if(IFeelDifferent(MyPreviousStateOfMind))
	{
		daWaitingCount=0;
	}
	else
	{
		daWaitingCount++;
		if(daWaitingCount >= 3)
		{
			daWaitingCount=0;
			TurnLeft();
			delayms(1000);
		}
	}

}
void MakeAMove(int daTypeOMove)
{
	switch (daTypeOMove)
	{
		case 0 : 
			StepForward(daRandomNo());
			break;
		case 1 : 
			TurnRight();
			delayms(40 * daRandomNo());
			FullStop();
			if(NoProx())
			{
				TurnLeft();
				delayms(40*daRandomNo());
				FullStop();
			}
			break;
		case 2 : 
			TurnRight();
			delayms(200 * daRandomNo());
			FullStop();
			break;
		case 3 : 
			TurnLeft();
			delayms(200*daRandomNo());
			FullStop();
			break;
	}
}
