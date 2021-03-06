#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port3,           motorLeft,     tmotorVex393_MC29, PIDControl, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port4,           motorRight,    tmotorVex393_MC29, PIDControl, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port5,           armLeft,       tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port6,           armRight,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	//PID fixup
	nMotorPIDSpeedCtrl[motorLeft] = RegIdle;
	nMotorPIDSpeedCtrl[motorRight] = RegIdle;

	resetMotorEncoder(armLeft);
	resetMotorEncoder(armRight);

	while (true)
	{
		//Assigns the value of the Y1 axis to the left motor
		motor[motorLeft] = vexRT[Ch3];
		//Assigns the value of the Y2 axis to the right motor
		motor[motorRight] = vexRT[Ch2];

		//If button 6 up (right bumper) is pressed
		if(vexRT[Btn6U] == 1)
		{
			//Raise the arm
			motor[armRight] = 100;
		}
		//Else, if button 6 down (right trigger) is pressed
		else if(vexRT[Btn6D] == 1)
		{
			//Lower the arm
			motor[armRight] = -100;
		}
		//Else (no button pressed)
		else
		{
			//Turn the arm motor off
			motor[armRight] = 0;
		}

		if(vexRT[Btn5U] == 1)
		{
			//Raise the arm
			motor[armLeft] = 100;
		}
		//Else, if button 6 down (right trigger) is pressed
		else if(vexRT[Btn5D] == 1)
		{
			//Lower the arm
			motor[armLeft] = -100;
		}
		//Else (no button pressed)
		else
		{
			//Turn the arm motor off
			motor[armLeft] = 0;
		}

		// 7L / 7R controls the hand
		if(vexRT[Btn7L] == 1)
			motor[claw] = 100;
		else if(vexRT[Btn7R] == 1)
			motor[claw] = -100;
		else
			motor[claw] = 0;
	}
}
