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
bool isControlMode;


//コンストラクタ
void Controller(/*ValueMeasure measure, ControlTarget target, int cycle*/)
{
	isControlMode = false;
	// cycleを引数から指定
	// _private_param_name:=1.0
	// cycle = rospy.get_param('~cycle', 10);
	//n.param<std::int>("cycle", cycle, 10);
	cycle = 10;
	//ros::Publisher target_value_pub = n.advertise<std_msgs::Float64>("target_value", 1000);
	//ros::Subscriber target_value_sub = n.subscribe("target_value", 1, targetValueCallback);
	
	/*ros::ServiceServer target_value_get = n.advertiseService("target_value_get",&Controller::getTargetValue,this);
	ros::ServiceServer target_value_set = n.advertiseService("target_value_set",&Controller::setTargetValue,this);
	raspimouse_lab::targetGetter srv_get;
	raspimouse_lab::targetSetter srv_set;
	*/

	ros::ServiceClient client_getTarget = n.serviceClient<raspimouse_lab::ControlTarget>("target_value_get");
	ros::ServiceClient client_setTarget = n.serviceClient<raspimouse_lab::ControlTarget>("target_value_set");
	
	
	
	ros::ServiceServer start_service = n.advertiseService("start_ctrl",&Controller::startCtrl,this);
	ros::ServiceServer stop_service = n.advertiseService("stop_ctrl",&Controller::stopCtrl,this);
	
	ros::Publisher motor_control = n.advertise<raspimouse_lab::motorParam>("motor_control", 1000);
	
	ros::ServiceClient client_calc = n.serviceClient<raspimouse_lab::targetCalc>("input_calc");
}

float getTargetValue()
{
	if (client.call(srv)) {
		return srv.response.data;
	}else{
		return -1;
	}
}

void setTargetValue(float f)
{
	srv.request.request = f;
	client.call(srv)
	return;
}


// 一部の場合のみ	
// ゲッターを呼ぶ->トピックを購読する
// セッターを呼ぶ->トピックを配信する
// セッター->購読して来たらコールバック対応で

// ゲッターを呼ぶ->パラメータを取得する
// セッターを呼ぶ->パラメータを設定する
// ゲッター・セッター->消滅

// 初期値だけパラメータサーバから 以降はサービスで




/*void targetValueCallback(const std_msgs::Float64::ConstPtr& msg){
	targetValue = msg->data;
}*/

/*PIDParam getCtrlParam()
{
	return 0;
}

void setCtrlParam(PIDParam param)
{
}
*/
// ゲッターがゲッターを呼んで セッターがセッターを呼ぶパターン
// こういう場合はセッターは一番最後に呼ばれるものだけコールバック実装 ゲッターはそれぞれトピックを購読する

// 消滅
/*void setListener(TargetListener listener)
{
}*/

// サービスとして実装
//開始する
bool startCtrl(std_srvs::Empty::Request  &req, std_srvs::Empty::Response &res){
	isControlMode = true;
	res.accepted = true;
	return true;
}

//終了する
bool stopCtrl(std_srvs::Empty::Request  &req, std_srvs::Empty::Response &res){
	isControlMode = false;
	res.accepted = true;
	return true;
}

void run()
{
	ros::Rate loop_rate(cycle);
	while(ros::ok())
	{
		runOneCycle();
		ros::spinOnce();
		loop_rate.sleep();
	}
}

//1サイクル処理を行う
void runOneCycle()
{
	float target = getTargetValue();
	float measure = getMeasurement();
	raspimouse_lab::targetCalc tcalc;
	tcalc.request.target = target;
	tcalc.request.measure = measure;
	
	if(client_calc.call(tcalc)){
		int speed = tcalc.response.input;
		raspimouse_lab::motorParam param;
		param.left = speed;
		param.right = speed;
		motor_control.publish(param);
	}
	else{
		ROS_ERROR("Failed to call calculation");
	}
}

/*void changeControlMode()
{//privateだった
}*/

int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");
	
	run();

}