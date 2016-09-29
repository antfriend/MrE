#ifndef Main
#define Main
//////////////

// Typedefs
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

// Defines
#define bit_set(p,m) ((p) |= (1<<m)) 
#define bit_clear(p,m) ((p) &= ~(1<<m)) 
#define forever	117
//#define aPowerOn	PORTD |= (1<<PD1) //high voltage
//#define aPowerOff 	PORTD &= ~(1<<PD1)//low voltage
//#define SpeakerOn	PORTD |= (1<<PD0) //high voltage
//#define SpeakerOff	PORTD &= ~(1<<PD1)//low voltage
//#define LEDOFF	PORTD |= (1<<PD2) //high voltage
//#define LEDON	PORTD &= ~(1<<PD2)//low voltage
#define SETBIT(ADDRESS,BIT)      (ADDRESS |= (1<<BIT)) 
#define CLEARBIT(ADDRESS,BIT)    (ADDRESS &= ~(1<<BIT)) 
#define TESTBIT(ADDRESS,BIT)     (ADDRESS & (1<<BIT)) 
//example
// Get the state of the input pin 
//TESTBIT( PINC, 3); 

//Prototypes
void InitEverything (void);
void Delay (u32 count);
int NoProx(void);
int bit_get(int daPIN,int daBIT);
int daRandomNo(void);
void DebugMode(void);
void DemoMode1(void);
void DemoMode2(void);
void MrE_Mode(void);
void MakeAMove(int daTypeOMove);
void delayms(int millis);
//variables


///////////////////
#endif
