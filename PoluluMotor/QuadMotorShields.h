
Conversation opened. 1 unread message.

Skip to content
Using Gmail with screen readers
	“Andrew Pirondini”
	abartl02
	archang
	Jesse Tambornini
	Keiran Hansen
	Keiran Hansen
	Nick Tuong
	rtakatsu
	Shelby Boyd
	Tyler Cottle
 
 
More 
1 of 356
 
Updated header/cpp files for quadmotorshields
Inbox
	x
aarontpze@yahoo.com
	
Attachments3:25 PM (5 minutes ago)
		
to me
Here are the updated header/cpp files. Sorry I can’t make it today but I had pre-existing plans for today.
2 Attachments
Preview attachment QuadMotorShields.cpp
[C++]
Preview attachment QuadMotorShields.h
[C]
	
Click here to Reply or Forward
0.97 GB (6%) of 15 GB used
Manage
Terms - Privacy
Last account activity: 56 minutes ago
Details
	
	
	“Aaron Parisi”
Show details
QuadMotorShields.h

#ifndef QuadMotorShields_h
#define QuadMotorShields_h

#include <Arduino.h>

class QuadMotorShields
{
  public:  
    // CONSTRUCTORS
    QuadMotorShields(); // Default pin selection.
	QuadMotorShields(unsigned char INA1, unsigned char INB1, unsigned char EN1DIAG1, unsigned char CS1,
		unsigned char INA2, unsigned char INB2, unsigned char EN2DIAG2, unsigned char CS2,
		unsigned char INA3, unsigned char INB3, unsigned char EN3DIAG3,
		unsigned char INA4, unsigned char INB4, unsigned char EN4DIAG4); // User-defined pin selection. 
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
	void setM3Speed(int speed); // Set speed for M3.
	void setM4Speed(int speed); // Set speed for M4.
    void setSpeeds(int m1Speed, int m2Speed, int m3Speed, int m4Speed); // Set speed for both M1 and M2.
    void setM1Brake(int brake); // Brake M1. 
    void setM2Brake(int brake); // Brake M2.
	void setM3Brake(int brake); // Brake M3.
	void setM4Brake(int brake); // Brake M4
    void setBrakes(int m1Brake, int m2Brake, int m3Brake, int m4Brake); // Brake both M1 and M2.
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned char getM1Fault(); // Get fault reading from M1.
    unsigned char getM2Fault(); // Get fault reading from M2.
    
  private:
    unsigned char _INA1;
    unsigned char _INB1;
<<<<<<< HEAD
    static const unsigned char _PWM1 = 11; //M1PWM for Polu #1
=======
    static const unsigned char _PWM1 = 5; //M1PWM for Polu #1
>>>>>>> e2d935cb574d29ce795b90677b713245941633e2
    unsigned char _EN1DIAG1;
    unsigned char _CS1;
    unsigned char _INA2;
    unsigned char _INB2;
<<<<<<< HEAD
	static const unsigned char _PWM2 = 5; //M2PWM for Polu #1
    unsigned char _EN2DIAG2;
    unsigned char _CS2;
	static const unsigned char _PWM3 = 9; // M1PWM for Plolu #2 ORIGINALLY 10 BUT FUCK WHO GIVES A SHIT?
=======
	static const unsigned char _PWM2 = 6; //M2PWM for Polu #1
    unsigned char _EN2DIAG2;
    unsigned char _CS2;
	static const unsigned char _PWM3 = 10; // M1PWM for Plolu #2 
>>>>>>> e2d935cb574d29ce795b90677b713245941633e2
	unsigned char _INA3;
	unsigned char _INB3; 
	unsigned char _EN3DIAG3;
	static const unsigned char _PWM4 = 6; // M2PWM for Pololu #2
	unsigned char _INA4; 
	unsigned char _INB4;
	unsigned char _EN4DIAG4;

};

#endif

Displaying QuadMotorShields.cpp.
