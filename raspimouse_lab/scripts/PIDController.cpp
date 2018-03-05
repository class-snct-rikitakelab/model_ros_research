#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/float32.h"
#include <sstream>
#include <cmath>
#include "raspimouse_lab/MotorFreqs.h"
#include "raspimouse_lab/SwitchMotors.h"
#include "raspimouse_lab/measureValue.h"
#include "raspimouse_lab/motorParam.h"
#include "raspimouse_lab/LightSensorValues.h"
#include "raspimouse_lab/PIDParam.h"
#include "raspimouse_lab/ctrl.h"
#include "raspimouse_lab/measure.h"
#include "raspimouse_lab/paramGetter.h"
#include "raspimouse_lab/paramSetter.h"
#include "raspimouse_lab/PutMotorFreqs.h"
#include "raspimouse_lab/SwitchMotors.h"
#include "raspimouse_lab/targetCalc.h"
#include "raspimouse_lab/targetGetter.h"
#include "raspimouse_lab/targetSetter.h"

ros::NodeHandle n;
float32 KP;
float32 KI;
float32 KD;
float32 DELTA_T;
float32 preDiff;

void PIDController()
{
	ros::ServiceServer param_get = n.advertiseService("param_get",&PIDController::getParam,this);
	ros::ServiceServer param_set = n.advertiseService("param_set",&PIDController::setParam,this);
	ros::ServiceServer input_calc = n.advertiseService("input_calc",&PIDController::calcInput,this);
}

bool getParam(raspimouse_lab::paramGetter::Request  &req, raspimouse_lab::paramGetter::Response &res)
{
	res->KP = KP;
	res->KI = KI;
	res->KD = KD;
	return true;
}

bool setParam(raspimouse_lab::paramSetter::Request  &req, raspimouse_lab::paramSetter::Response &res)
{
	KP = req->KP;
	KI = req->KI;
	KD = req->KD;
	return true;
}

bool calcInput(raspimouse_lab::targetCalc::Request  &req, raspimouse_lab::targetCalc::Response &res)
{
	float32 currentDiff = brightness - target_brightness;

	float32 turn = KP * currentDiff;

	turn += KI * (currentDiff - preDiff)/DELTA_T;
	turn += KD * ((currentDiff + preDiff) / 2.0F)*DELTA_T;

	preDiff = currentDiff;
	res->input = turn;
	
	return true;
}

bool initialize(std_srvs::Empty::Request  &req, std_srvs::Empty::Response &res)
{
	int a;
	n.param<std::double>("PID_KP", KP, 10);
	n.param<std::double>("PID_KI", KI, 1);
	n.param<std::double>("PID_KD", KD, 1);
	n.param<std::int>("cycle", a, 10);
	DELTA_T = 1.0 / a;

	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pid_controller");
	
	ros::spin();
}