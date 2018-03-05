#include <ros/ros.h>
#include <ros/package.h>
#include <angles/angles.h>
#include <hackev_control/hackev_hw.h>
#include <iostream> // for debug
#include <math.h>
//#include <ev3dev.h>

using namespace std;
//using namespace ev3dev;

Hackev::Hackev()
{
  // connect and register the joint state interface
  // JointStateHandleの第一引数はhackev_control.yamlのjointから
  hardware_interface::JointStateHandle state_handle_1("left_wheel_joint", &pos_[0], &vel_[0], &eff_[0]);
  jnt_state_interface.registerHandle(state_handle_1);

  hardware_interface::JointStateHandle state_handle_2("right_wheel_joint", &pos_[1], &vel_[1], &eff_[1]);
  jnt_state_interface.registerHandle(state_handle_2);

  hardware_interface::JointStateHandle state_handle_3("arm_joint", &pos_[2], &vel_[2], &eff_[2]);
  jnt_state_interface.registerHandle(state_handle_3);

  hardware_interface::JointStateHandle state_handle_4("tail_joint", &pos_[3], &vel_[3], &eff_[3]);
  jnt_state_interface.registerHandle(state_handle_4);

  registerInterface(&jnt_state_interface);
  
  // connect and register the joint position interface
  hardware_interface::JointHandle vel_handle_1(jnt_state_interface.getHandle("left_wheel_joint"), &cmd_[0]);
  jnt_vel_interface.registerHandle(vel_handle_1);
  
  hardware_interface::JointHandle vel_handle_2(jnt_state_interface.getHandle("right_wheel_joint"), &cmd_[1]);
  jnt_vel_interface.registerHandle(vel_handle_2);
  
  hardware_interface::JointHandle vel_handle_3(jnt_state_interface.getHandle("arm_joint"), &cmd_[2]);
  jnt_vel_interface.registerHandle(vel_handle_3);
  
  hardware_interface::JointHandle vel_handle_4(jnt_state_interface.getHandle("tail_joint"), &cmd_[3]);
  jnt_vel_interface.registerHandle(vel_handle_4);
  
  registerInterface(&jnt_vel_interface);
  
  /*motor_[0] = large_motor(OUTPUT_A);//
  motor_[1] = large_motor(OUTPUT_B);
  motor_[2] = large_motor(OUTPUT_C);
  motor_[3] = large_motor(OUTPUT_D);
  */
  
}

void Hackev::read(ros::Time time, ros::Duration period)
{
  for(int i=0;i<4;++i){
    /*vel_[i]=motor_[i].speed_sp();
    pos_[i]=motor_[i].position_sp();*/
  }

}

void Hackev::write(ros::Time time, ros::Duration period)
{
  for(int i=0;i<4;++i){
    /*motor_[i].set_speed_sp(-cmd_[i]);
    motor_[i].run_forever();*/
  }
  //pos_[0] = cmd_[0];
}

