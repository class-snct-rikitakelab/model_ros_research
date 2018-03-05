#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/float32.h"
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

// 計測して変換して

int16 lightValue;
float32 targetValue;
ros::NodeHandle n;
void ControlTarget(/*ValueMeasure measure*/)
{
	//ros::Publisher target_value_pub = n.advertise<std_msgs::Float64>("target_value", 1000);
	ros::ServiceServer measurement_get = n.advertiseService("measurement_get",&ControlTarget::getMeasurement,this);

	ros::ServiceServer target_value_get = n.advertiseService("target_value_get",&ControlTarget::getTargetValue,this);
	ros::ServiceServer target_value_set = n.advertiseService("target_value_set",&ControlTarget::setTargetValue,this);


}

bool getMeasurement(raspimouse_lab::measure::Request  &req, raspimouse_lab::measure::Response &res)
{
	res.data = targetValue;
	return true;
}

// 目標値取得
bool getTargetValue(raspimouse_lab::targetGetter::Request  &req, raspimouse_lab::targetGetter::Response &res)
{
	res.data = targetValue;
	return true;
}

// 目標値設定
bool setTargetValue(raspimouse_lab::targetGetter::Request  &req, raspimouse_lab::targetGetter::Response &res)
{
	targetValue = req.data;
	return true;
}

void measureCallback(const raspimouse_lab::measureValue::ConstPtr& msg){
	targetValue = msg->data;
}

/*void setListener(TargetListener listener)
{
}
*/

int main(int argc, char **argv)
{
	ros::init(argc, argv, "control_target");
	ros::Subscriber measure = n.subscribe("measure_value", 1, measureCallback);
	ros::spin();

}