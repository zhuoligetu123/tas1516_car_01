#include "ros/ros.h"
#include "std_msgs/String.h"
#include "control/control.h"
#include <sstream>
#include "rect/rect.h" 


int main(int argc, char **argv)
{
  ros::init(argc, argv, "speed_gain");

  control speed_gain_controller;

  ros::NodeHandle n;

  ros::Rate loop_rate(10);
  while(ros::ok())  
  {
      ros::spinOnce();

      loop_rate.sleep();
  }

   return 0;
}