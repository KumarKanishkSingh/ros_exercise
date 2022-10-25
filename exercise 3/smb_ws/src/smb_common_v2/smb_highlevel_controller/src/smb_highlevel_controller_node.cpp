// #include<algorithm>
#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <std_msgs/String.h>
#include<sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include<cmath>
using namespace std;
// #include<sensor_msgs.msg/LaserScan>

// class controller
// {
//   public:
//     controller()
//     {
//       subscriber = nodeHandle.subscribe("/scan", 50, scanCallback);
//       publisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
//       // smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

//     }
//     void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
// {


// double angle=0;
// double rangeMin=100000;
// for(double i=0;i<=720;i=i+1)
// {
//   if(msg->ranges[i] <= rangeMin)
//   {
//     rangeMin = msg->ranges[i];
//     angle = i;
//   }
// }
// ROS_INFO("Range: [%f]", msg->range_min);
// ROS_INFO("Angle: [%f]", angle);
// angle = angle*3.14/180;
// double xrel = rangeMin*cos(angle);
// double yrel = rangeMin*sin(angle);
// geometry_msgs::Twist move;
// while(msg->range_min>0)
// {
//   if(angle>0)
//   {
//     move.angular.x=move.angular.x+0.1;
//   }
//   if(xrel>0)
//   {
//     move.linear.x=10;
//   }
//   publisher.publish(move);
// }

// }

// ros::NodeHandle nodeHandle("~");
// ros::Subscriber subscriber = nodeHandle.subscribe("/scan", 50, scanCallback);
// ros::Publisher publisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
ros::Publisher publisher;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{


double angle=0;
double rangeMin=100000;
for(double i=0;i<720;i=i+1)
{
  if(msg->ranges[i] <= rangeMin)
  {
    rangeMin = msg->ranges[i];
    angle = i/2;
  }
}
ROS_INFO("Range: [%f]", rangeMin);
ROS_INFO("Angle: [%f]", angle);
double angle2 = angle*3.14/180;
double xrel = rangeMin*cos(angle2);
double yrel = rangeMin*sin(angle2);
ros::Rate loop_rate(10);
int count = 0;
  while (angle>10)
  { geometry_msgs::Twist move;
    move.linear.x=10;
    // move.angular.x=100;
    // move.angular.y=100;
    move.angular.z=10;
    publisher.publish(move);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  geometry_msgs::Twist move;
    move.linear.x=0;
    move.angular.x=0;
    move.angular.y=0;
    move.angular.z=0;
    publisher.publish(move);

  count = 0;
  while (xrel>0.6)
  { geometry_msgs::Twist move;
    move.linear.x=10;
    publisher.publish(move);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
}
// geometry_msgs::Twist move;
// while(msg->range_min>0)
// {
//   if(angle>0)
//   {
//     move.angular.x=move.angular.x+0.1;
//   }
//   if(xrel>0)
//   {
//     move.linear.x=10;
//   }
// }
// private:
// ros::NodeHandle nodeHandle("~");
// ros::Subscriber subscriber;
// ros::Publisher publisher;
// smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);



// }

int main(int argc, char** argv) {
  
  ros::init(argc, argv, "smb_highlevel_controller");
  // controller cont;
  ros::NodeHandle nodeHandle("~");
  publisher = nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 50);
  ros::Subscriber subscriber = nodeHandle.subscribe("/scan", 50, scanCallback);
  
  // ros::Rate loop_rate(10);

  // int count = 0;
  // while (ros::ok())
  // { geometry_msgs::Twist move;
  //   move.linear.x=10;
  //   move.angular.x=100;
  //   move.angular.y=100;
  //   move.angular.z=100;
  //   publisher.publish(move);
  //   ros::spinOnce();
  //   loop_rate.sleep();
  //   ++count;
  // }

  

  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
