#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"	//include message type

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "pose_pub");

  ros::NodeHandle n;

  ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);	//publish a message of type PoseStamped. This data is published on topic /move_base_simple/goal with buffer of 1. Send only if subscriber is there (true)

  ros::Rate loop_rate(100); //every 10 ms (100 Hz)

  int count = 0;
  while (ros::ok())	//this returns false if e.g. CTRL-C is hit
  {
    geometry_msgs::PoseStamped msg;

    msg.header.frame_id = "map";	//use map as reference
    msg.pose.position.x = 20;		//x-position
    msg.pose.position.y = 19;		//y-position
    msg.pose.position.z = 0;		//z-position
    msg.pose.orientation.w = 0.01334;	//rotation
    msg.pose.orientation.x = 0;		//x-orientation
    msg.pose.orientation.y = 0;		//y-orientation
    msg.pose.orientation.z = 0.9999;	//z-orientation

    if (count == 0)	//send only once
    {
	pose_pub.publish(msg);	//broadcast message to anyone who is connected
    }

    ros::spinOnce();	//provide callbacks

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

