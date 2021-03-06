#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     LeftF,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RightF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     LiftR,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     LiftF,         tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Spinner,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     LeftR,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     RightR,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C2_1,    Clamp,                tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    IRlift,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    SpinLift,             tServoStandard)
#pragma config(Servo,  srvo_S2_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "drivers/hitechnic-sensormux.h"
#define DEADBAND(n, t)	((abs(n) > t)? (n): 0)
#define BOUND(n, lo, hi)	(((n) < (lo))? lo: ((n) > (hi))? (hi): (n))
//const tMUXSensor HTIRS2 = msensor_S3_3;
//#define TOUCH1	HTSMUX_S3_1
//#define TOUCH2	HTSMUX_S3_2
//#define IR	HTSMUX_S3_3

int deadZone = 10;

void Liftup(int Height)  //How tall to go
{
 				while (nMotorEncoder[LiftR] < Height) //while the encoder wheel turns one revolution//
	        {
	        motor[LiftR] = 60;
					motor[LiftF] = 60;
	  			}

				motor[LiftR] = 0;
				motor[LiftF] = 0;
				wait1Msec(200);							// Delay before next command
}

void Basket(int Height3)
{
				nMotorEncoder[LiftR] = 0;  		//clear the TETRIX encoders in rear motor
				wait1Msec(200);
				while (nMotorEncoder[LiftR] < Height3) //Lift up the back end of basket
	        {
	    		motor[LiftR] = 60;
	  			}
			  motor[LiftR] =0;
				wait1Msec(2000);							//wait to drop balls in tube
 				while (nMotorEncoder[LiftR] > 0) //Lift up the back end of basket
	        {
	    		motor[LiftR] = -60;
	  			}
		 		motor[LiftR] =0;
}

void Liftdown(int Height2)
{
while (nMotorEncoder[LiftR] > Height2) //while the encoder wheel turns one revolution//
	        {
	    		motor[LiftR] = -60;
					motor[LiftF] = -60;
	  			}

motor[LiftR] = 0;
motor[LiftF] = 0;
}


task main()
{
  			nMotorEncoder[LiftR] = 0;  //clear the TETRIX encoders in motors left and right
  			nMotorEncoder[LiftF] = 0;  //clear the TETRIX encoders in motors left and right
  	    wait1Msec(200);							// Delay before next command

  while (true)
  {
  	getJoystickSettings(joystick);

// 	ArcadeControl((joystick.joy1_y1 * 100/128), joystick.joy1_x2);  //y1 is forward/backward.  x2 is left/right.
		int drivePower = DEADBAND(joystick.joy1_y1, deadZone)*100/128;
		int turnPower = DEADBAND(joystick.joy1_x2, deadZone)*100/128;

		motor[LeftF] = BOUND(drivePower - turnPower, -78, 100);
		motor[RightF] = BOUND(drivePower + turnPower, -78, 100);
		motor[LeftR] = BOUND(-drivePower - turnPower, -78, 100);
		motor[RightR] = BOUND(-drivePower + turnPower, -78, 100);

		wait1Msec(10);

//    THIS IS FOR USING JOYSTICK2 FOR THE LIFT
//		motor[LiftF] = (joystick.joy2_y1)*40/100;
//		motor[LiftR] = (joystick.joy2_y1)*40/100;
//		motor[LiftR] = (joystick.joy2_y2)*60/100;

			if (joy2Btn(1) == 1)
			{
				motor[LiftF] = 54;
				motor[LiftR] = 60;
			}
			else if ((joy2Btn(3) == 1) & (SensorValue(TOUCH1) == 0))
			{
				motor[LiftF] = -54;
				motor[LiftR] = -60;
			}
			else
			{
				motor[LiftF] = 0;
				motor[LiftR] = 0;
			}

			if (joy2Btn(4) == 1)
			// turn servo to position 210 Opened
			{
				servo[Clamp] = 210;        // changes the position of servo1 to 160
//				servoTarget[Clamp] = 210;  // changes the position of servo1 to 160
			}
			if (joy2Btn(2) == 1)
			// The servo to position 223 Cloesed
			{
				servo[Clamp] = 223;        // changes the position of servo1 to 160
//				servoTarget[Clamp] = 223;  // changes the position of servo1 to 160
			}

			// Close Servo IR Lift
			if (joy2Btn(10) == 1)
			{
				servo[SpinLift] = 113;
			}

			//activate spinner
			if (joy2Btn(9) == 1)
			{
				motor[Spinner] = 70;
			}

			else
			{
				motor[Spinner] = 0;
			}

// THIS IS FOR USING INCREMENTED LIFT UP AND DOWN
//			if (joy2Btn(1) == 1)
//			{
//				h++;
//				if (h < 4)
//					{
//					Liftup(2600*h);
//					}
//			}
//			if (joy2Btn(3) == 1)
//			{
//				Liftdown(100);
//				h--;
//			}

	}
}
