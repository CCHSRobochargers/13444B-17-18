#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl11, AutonomousMobileConeScoreSelect, sensorDigitalIn)
#pragma config(Sensor, dgtl12, AutonomousSelect, sensorDigitalIn)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           BackR,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           DriveR,        tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port3,           DriveL,        tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           Left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Pully,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BLR,           tmotorVex393_MC29, PIDControl, encoderPort, I2C_4)
#pragma config(Motor,  port7,           BLL,           tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port8,           Claw,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Right,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BackL,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(MotorPidSetting,  port2,  50, 10, 1000, 12, 10,   33, 45, 0)
#pragma config(MotorPidSetting,  port3,  50, 10, 1000, 12, 10,   33, 45, 0)
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
static const float ticksPerInch = 4650 / 96.0; //(627.2 / (4.0 * PI));
//adjust to compensate for wheel slip
static const float ticksPerRev = -1.2 * (ticksPerInch * 14.5 * PI);

static const float ticksPerLiftInch = 598.0 / 20.0;

void move(float dist, int speed, bool hold)
{
	resetMotorEncoder(DriveR);
	resetMotorEncoder(DriveL);

	setMotorTarget(DriveR, dist*ticksPerInch, speed, hold);
	setMotorTarget(DriveL, dist*ticksPerInch, speed, hold);

	while (!getMotorTargetCompleted(DriveR) && !getMotorTargetCompleted(DriveL))
		wait1Msec(10);
}

void spin(float dist, int speed, bool hold)
{
	resetMotorEncoder(DriveR);
	resetMotorEncoder(DriveL);

	setMotorTarget(DriveR, dist*ticksPerRev, speed, hold);
	setMotorTarget(DriveL, -dist*ticksPerRev, speed, hold);

	while (!getMotorTargetCompleted(DriveR) && !getMotorTargetCompleted(DriveL))
		wait1Msec(10);
}

void lift(float height, int speed, bool hold, bool waitComp)
{
	setMotorTarget(BLR, height * ticksPerLiftInch, speed, hold);

	if (waitComp)
	{
		while (!getMotorTargetCompleted(BLR))
			wait1Msec(10);
	}
}


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

  slaveMotor(BackR, DriveR);
  slaveMotor(BackL, DriveL);
	slaveMotor(BLL, BLR);

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

void corner_goal(void)
{
	resetMotorEncoder(BLR);

  //pinching and picking up cone
	motor[Claw] = -20;
	lift(14.0, 90, true, false);

	//moving to the goals
	move(53.5, 127, true);

	lift(8.0, 90, true, true);

	//dropping the cone
	motor[Claw] = 90;
	wait1Msec(1000);
	motor[Claw] = 0;

	move(-18.0, 63, true);
}

void tall_goal(void)
{;
	resetMotorEncoder(BLR);

	//pinching and picking up cone
	motor[Claw] = -20;
	lift(30.0, 90, true, true);

	//moving to the goal
	move(16.0, 90, true);

	//dropping the cone
	lift(22.0, 50, true, true);
	motor[Claw] = 90;
	wait1Msec(1000);
	motor[Claw] = 0;

	//moving beckwards from cone to score cleanly
	move(-5.0, 90, true);
}

void MobileConeScore(void)
{
	resetMotorEncoder(BLL);
	resetMotorEncoder(BLR);

	motor[Right] = motor [Left] =-100;
	wait1Msec(400);
	motor [Right] = motor [Left] = 0;

	move(-46.0, 127, true);

	motor [Pully] = -100;
	wait1Msec(600);
	motor [Pully] = 0;

	motor[Right] = motor[Left] = 100;
	wait1Msec(1000);
	motor[Right] = motor[Left] = 0.0;

	move(36.0, 127, true);

	spin(-0.125, 127, true);

	move(18.0, 127, true);

	spin(-0.25, 100, true);

	move(-24.0, 127, true);

	motor[Pully] = 100;
	wait1Msec(375);
	motor[Right] = motor[Left] = 127;
	motor[Pully] = 0;
	wait1Msec(250);

	move(36.0, 127, true);
}

task autonomous()
{
	if(SensorValue(AutonomousSelect))
	{
		corner_goal();
	}
	else if(SensorValue(AutonomousMobileConeScoreSelect))
	{
		MobileConeScore();
	}
	else
	{
		tall_goal();
	}
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
  // User control code here, inside the loop

	nMotorPIDSpeedCtrl[DriveL] = RegIdle;
	nMotorPIDSpeedCtrl[DriveR] = RegIdle;
	nMotorPIDSpeedCtrl[BLL] = RegIdle;
	nMotorPIDSpeedCtrl[BLR] = RegIdle;

	while (true)
  {
  		//Assigns the value of the Y1 axis to the left motor
		motor[DriveL] = vexRT[Ch2];
		//Assigns the value of the Y2 axis to the right motor
		motor[DriveR] = vexRT[Ch3];

		motor[BLR] = motor[BLL] = vexRT[Ch2Xmtr2];
		motor[Claw] = vexRT[Ch4Xmtr2];

		if (vexRT[Btn6U])
		{
			//Raise the lift
			motor[Right] = motor[Left] = 100;
		}
		//Else, if button 6 down (right trigger) is pressed
		else if(vexRT[Btn6D])
	  {
			motor[Right] = motor[Left] = -100;
	  }
	  else
    {
    	motor[Right] = motor[Left] = 0;
    }
		//Else if the left bumper or left trigger is pressed
		if(vexRT[Btn5U])
		{
			motor[Pully] = 100;
	  }
	  else if (vexRT[Btn5D])
	  {
	  	motor[Pully] = -100;
	  }
	  else
	  {
	  	motor[Pully] = 0;
	  }
	}
}
