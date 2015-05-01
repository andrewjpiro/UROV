
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
	
Attachments3:25 PM (2 minutes ago)
		
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
QuadMotorShields.cpp

#include "QuadMotorShields.h"

// Constructors ////////////////////////////////////////////////////////////////


/*
TODO:
	GET M3 and M4 to work (timers, PWN, pin mapping)
	GET M1 and M2 to work WHILE M3 and M4 are working (change pin mapping if needed)
	?????
	Profit
*/

QuadMotorShields::QuadMotorShields()
{
  //Pin map, Bottom Pololu (yellow) IGNORE COLORS THEY LIE NOW!
  _INA1 = 25; // M1INA, orange
  _INB1 = 27; // M1INB , Yellow
  _EN1DIAG1 = 23; // M1EN,  Black 
  _CS1 =A0;  //M1CS , gray 
  _INA2 = 24;   //M2INA2,Blue
  _INB2 = 26;   //M2INB2,Red
  _EN2DIAG2 = 22; //M2EN, Brown 
  _CS2 = A1; //M2CS White

  //Pin map, Top Pololu (pink)
  _INA3 = 30; // M1INA, orange
  _INB3 = 32; // M1INB , Yellow
  _EN3DIAG3 = 28; // M1EN,  Black 
  _INA4 = 31; //M2INA2,Blue
  _INB4 = 33; //M2INB2,Red
  _EN4DIAG4 = 29; //M2EN, Brown 

}

QuadMotorShields::QuadMotorShields(unsigned char INA1, unsigned char INB1, unsigned char EN1DIAG1, unsigned char CS1, 
                                               unsigned char INA2, unsigned char INB2, unsigned char EN2DIAG2, unsigned char CS2,
											   unsigned char INA3, unsigned char INB3, unsigned char EN3DIAG3,  
											   unsigned char INA4, unsigned char INB4, unsigned char EN4DIAG4)
{
  //Pin map
  //PWM1 and PWM2 cannot be remapped because the library assumes PWM is on timer1
  _INA1 = INA1;
  _INB1 = INB1;
  _EN1DIAG1 = EN1DIAG1;
  _CS1 = CS1;
  _INA2 = INA2;
  _INB2 = INB2;
  _EN2DIAG2 = EN2DIAG2;
  _CS2 = CS2;

  //2nd set of motors ~ custom mapping
  _INA3 = INA3;
  _INB3 = INB3;
  _EN3DIAG3 = EN3DIAG3;
  _INA4 = INA4;
  _INB4 = INB4;
  _EN4DIAG4 = EN4DIAG4;
}

// Public Methods //////////////////////////////////////////////////////////////
void QuadMotorShields::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_INA1,OUTPUT);
  pinMode(_INB1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_EN1DIAG1,INPUT);
  pinMode(_CS1,INPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_INB2,OUTPUT);
  pinMode(_PWM2,OUTPUT);
  pinMode(_EN2DIAG2,INPUT);
  pinMode(_CS2,INPUT);
  pinMode(_INA3, OUTPUT);
  pinMode(_INB3, OUTPUT);
  pinMode(_PWM3, OUTPUT);
  pinMode(_EN3DIAG3, INPUT);
  pinMode(_INA4, OUTPUT);
  pinMode(_INB4, OUTPUT);
  pinMode(_EN4DIAG4, INPUT);
  //#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  // Timer 1 configuration
  // prescaler: clockI/O / 1
  // outputs enabled
  // phase-correct PWM
  // top of 400
  //
  // PWM frequency calculation
  // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
  TCCR1A = 0b10100000;
  TCCR1B = 0b00010001;
  ICR1 = 400;

  TCCR3A = 0b10100000;
  TCCR3B = 0b00010001;
  ICR3 = 400;

  //#endif
}
// Set speed for motor 1, speed is a number betwenn -400 and 400
void QuadMotorShields::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1A = speed;
  #else
  analogWrite(_PWM1,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
  if (speed == 0)
  {
    digitalWrite(_INA1,LOW);   // Make the motor coast no
    digitalWrite(_INB1,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA1,LOW);
    digitalWrite(_INB1,HIGH);
  }
  else
  {
    digitalWrite(_INA1,HIGH);
    digitalWrite(_INB1,LOW);
  }
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void QuadMotorShields::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // Max 
    speed = 400;
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1B = speed;
  #else
  analogWrite(_PWM2,speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif 
  if (speed == 0)
  {
    digitalWrite(_INA2,LOW);   // Make the motor coast no
    digitalWrite(_INB2,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA2,LOW);
    digitalWrite(_INB2,HIGH);
  }
  else
  {
    digitalWrite(_INA2,HIGH);
    digitalWrite(_INB2,LOW);
  }
}
// Set speed for motor 3, speed is a number betwenn -400 and 400
void QuadMotorShields::setM3Speed(int speed)
{
	unsigned char reverse = 0;

	if (speed < 0)
	{
		speed = -speed;  // Make speed a positive quantity
		reverse = 1;  // Preserve the direction
	}
	if (speed > 400)  // Max PWM dutycycle
		speed = 400;
#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
	OCR0A = speed;
#else
	analogWrite(_PWM3, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
	if (speed == 0)
	{
		digitalWrite(_INA3, LOW);   // Make the motor coast no
		digitalWrite(_INB3, LOW);   // matter which direction it is spinning.
	}
	else if (reverse)
	{
		digitalWrite(_INA3, LOW);
		digitalWrite(_INB3, HIGH);
	}
	else
	{
		digitalWrite(_INA3, HIGH);
		digitalWrite(_INB3, LOW);
	}
}
// Set speed for motor 4, speed is a number betwenn -400 and 400
void QuadMotorShields::setM4Speed(int speed)
{
	unsigned char reverse = 0;

	if (speed < 0)
	{
		speed = -speed;  // Make speed a positive quantity
		reverse = 1;  // Preserve the direction
	}
	if (speed > 400)  // Max PWM dutycycle
		speed = 400;
#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
	OCR0B = speed;
#else
	analogWrite(_PWM4, speed * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
	if (speed == 0)
	{
		digitalWrite(_INA4, LOW); //digitalWrites the INA pin as if it were a digital pin
		digitalWrite(_INB4, LOW); //Make the motor coast no matter which direction it is spinning
	}
	else if (reverse)
	{
		digitalWrite(_INA4, LOW);
		digitalWrite(_INB4, HIGH);
	}
	else
	{
		digitalWrite(_INA4, HIGH);
		digitalWrite(_INB4, LOW);
	}
}
// Set speed for motor 1 and 2
void QuadMotorShields::setSpeeds(int m1Speed, int m2Speed, int m3Speed, int m4Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
  setM3Speed(m3Speed);
  setM4Speed(m4Speed);
}

// Brake motor 1, brake is a number between 0 and 400
void QuadMotorShields::setM1Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA1, LOW);
  digitalWrite(_INB1, LOW);
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1A = brake;
  #else
  analogWrite(_PWM1,brake * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
}

// Brake motor 2, brake is a number between 0 and 400
void QuadMotorShields::setM2Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA2, LOW);
  digitalWrite(_INB2, LOW);
  #if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
  OCR1B = brake;
  #else
  analogWrite(_PWM2,brake * 51 / 80); // default to using analogWrite, mapping 400 to 255
  #endif
}

void QuadMotorShields::setM3Brake(int brake)
{
	// normalize brake
	if (brake < 0)
	{
		brake = -brake;
	}
	if (brake > 400)  // Max brake
		brake = 400;
	digitalWrite(_INA3, LOW);
	digitalWrite(_INB3, LOW);
#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
	OCR0A = brake;
#else
	analogWrite(_PWM3, brake * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
}


void QuadMotorShields::setM4Brake(int brake)
{
	// normalize brake
	if (brake < 0)
	{
		brake = -brake;
	}
	if (brake > 400)  // Max brake
		brake = 400;
	digitalWrite(_INA4, LOW);
	digitalWrite(_INB4, LOW);
#if defined(__AVR_ATmega168__)|| defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__)
	OCR0B = brake;
#else
	analogWrite(_PWM4, brake * 51 / 80); // default to using analogWrite, mapping 400 to 255
#endif
}


// Brake motor 1 and 2, brake is a number between 0 and 400
void QuadMotorShields::setBrakes(int m1Brake, int m2Brake, int m3Brake, int m4Brake)
{
  setM1Brake(m1Brake);
  setM2Brake(m2Brake);
  setM3Brake(m3Brake);
  setM4Brake(m4Brake);
}

// Return motor 1 current value in milliamps.
unsigned int QuadMotorShields::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS1) * 34;
}

// Return motor 2 current value in milliamps.
unsigned int QuadMotorShields::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
  return analogRead(_CS2) * 34;
}

// Return error status for motor 1 
unsigned char QuadMotorShields::getM1Fault()
{
  return !digitalRead(_EN1DIAG1);
}

// Return error status for motor 2 
unsigned char QuadMotorShields::getM2Fault()
{
  return !digitalRead(_EN2DIAG2);
}

Displaying QuadMotorShields.cpp.
