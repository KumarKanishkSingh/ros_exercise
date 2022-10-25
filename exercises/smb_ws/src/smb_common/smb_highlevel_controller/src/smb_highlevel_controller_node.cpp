#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <std_msgs/String.h>
#include<sensor_msgs/LaserScan.h>
// #include<sensor_msgs.msg/LaserScan>

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
ROS_INFO("I heard: [%f]", msg->range_min);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_highlevel_controller");
  ros::NodeHandle nodeHandle("~");

  ros::Subscriber subscriber = nodeHandle.subscribe("/scan", 50, scanCallback);

  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
