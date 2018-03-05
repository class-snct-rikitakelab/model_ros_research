#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/int16.h"
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
ros::Publisher measue_control
void ValueMeasure(){
	measue_control = n.advertise<raspimouse_lab::measureValue>("measure_value", 1000);
}

/*float measureBrightness()
{
	
	return 0;
}*/

bool measureBrightness(const raspimouse_lab::LightSensorValues::ConstPtr& msg){
	int16 bright = msg->right_forward;
	raspimouse_lab::measureValue mea;
	mea.data = bright;
	measue_control.publish(mea);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "value_measure");
	ros::Subscriber measure = n.subscribe("lightsensors", 1, measureBrightness);

	ros::spin();
}