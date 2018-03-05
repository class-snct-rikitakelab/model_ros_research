#include <ros/ros.h>
#include <controller_manager/controller_manager.h>
#include <hackev_control/hackev_hw.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "hackev_control");
  ros::NodeHandle nh;

  Hackev robot;
  controller_manager::ControllerManager cm(&robot, nh);

  ros::Rate rate(1.0 / robot.getPeriod().toSec());
  ros::AsyncSpinner spinner(1);
  spinner.start();

  while(ros::ok())
  {
    ros::Time now = robot.getTime();
    ros::Duration dt = robot.getPeriod();

    robot.read(now, dt);
    cm.update(now, dt);

    robot.write(now, dt);
    rate.sleep();
  }
  spinner.stop();

  return 0;
}

