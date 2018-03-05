#include "ros/ros.h"  // rosで必要はヘッダーファイル
#include <geometry_msgs/Twist.h> // ロボットを動かすために必要
#include <std_msgs/Float64.h> // ロボットを動かすために必要
using namespace std;

ros::NodeHandle nh; // ノードハンドラの作成。ハンドラは必要時に起動される。

ros::Publisher  pub_left; // パブリッシャの作成。トピックに対してデータを送信。
ros::Publisher  pub_right;
std_msgs::Float64 speed, angle, vel_left, vel_right;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "hackev_teleop"); // initでROSを初期化し、名前をノードにつける

  ros::Rate rate(10); // ループの頻度を設定。この場合は10Hz

  pub_left= nh.advertise<std_msgs::Float64>("/hackev/left_joint_position_controller/command", 10);
  pub_right= nh.advertise<std_msgs::Float64>("/hackev/right_joint_position_controller/command", 10);

  std::cout << "f: forward, b: backward, r: right, l:left" << std::endl;

while (ros::ok()) // このノードが使える間は無限ループ
    {
      controlMotor();
      rate.sleep();     // 指定した周期でループするよう寝て待つ
    }

  return 0;
}
void controlMotor(){
      char key;  // 入力キーの値

      cin >> key;
      cout << key << endl;

      switch (key) {
      case 'f': speed.data  =  3.0; break;
      case 'b': speed.data  = -3.0; break;
      case 'l': angle.data =   5.0; break;
      case 'r': angle.data =  -5.0; break;
        // linear.xは前後方向の並進速度(m/s)
        // angular.zは回転速度(rad/s)
      }
      vel_left.data = speed.data+angle.data;
      vel_right.data = speed.data-angle.data;
      pub_left.publish(vel_left);
      pub_right.publish(vel_right); // 速度メッセージを送信
      ros::spinOnce(); // コールバック関数を呼ぶ
      speed.data  = 0.0; // 並進速度の初期化
      angle.data = 0.0; // 回転速度の初期化
}