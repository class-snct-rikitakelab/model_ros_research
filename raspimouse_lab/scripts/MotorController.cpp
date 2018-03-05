#include "ros/ros.h"
#include "std_msgs/String.h"
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
ros::Publisher motor_control;

void controllMotor(const raspimouse_lab::motorParam::ConstPtr& msg)
{
	raspimouse_lab::MotorFreqs freq;
	freq.left = msg->left;
	freq.right = msg->right;
	motor_control.publish(freq);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "motor_controller");
	
	ros::ServiceClient client = n.serviceClient<raspimouse_lab::SwitchMotors>("switch_motors");
	raspimouse_lab::SwitchMotors srv;
	srv.request.on = true;
	client.call(srv);
	
	motor_control = n.advertise<raspimouse_lab::MotorFreqs>("motor_raw", 1000);
	ros::Subscriber sub = n.subscribe("lightsensors", 1, controllMotor);
	
	ros::spin();

}