#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <map>
#include <string>
#include <vector>
//#include <ev3dev.h>

class Hackev : public hardware_interface::RobotHW
{
public:
  Hackev();

  ros::Time getTime() const { return ros::Time::now(); }
  ros::Duration getPeriod() const { return ros::Duration(0.01); }

  void read(ros::Time, ros::Duration);

  void write(ros::Time, ros::Duration);

protected:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::VelocityJointInterface jnt_vel_interface;
  double cmd_[4];
  double pos_[4];
  double vel_[4];
  double eff_[4];
  //motor motor_[4];//largeでなく普通にmotor?

};

