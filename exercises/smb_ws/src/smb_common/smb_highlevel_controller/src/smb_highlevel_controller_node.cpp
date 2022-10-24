#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <std_msgs/String.h>

void scanCallback(const std_msgs::String& msg)
{
ROS_INFO("I heard: [%s]", msg.data.c_str());
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_highlevel_controller");
  ros::NodeHandle nodeHandle("~");

  ros::Subscriber subscriber = nodeHandle.subscribe("/scan", 50, scanCallback);

  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
