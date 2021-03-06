#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

const float waypoints[3][2][4] = {{{18.0, 19.0, 0.0}, {0.1, 0.0, 0.0, 0.9999}},
			    {{12.0, 20.0, 0.0}, {-0.4, 0.0, 0.0, 0.9999}},
			    {{12.0, 16.0, 0.0}, {-0.5, 0.0, 0.0, 0.9999}}};  

move_base_msgs::MoveBaseGoal sendGoal(const float goal[2][4])
{
  move_base_msgs::MoveBaseGoal g;
  g.target_pose.header.frame_id = "map";		//use map as reference  
  g.target_pose.header.stamp = ros::Time::now();  
  g.target_pose.pose.position.x = goal[0][0];		//x-position
  g.target_pose.pose.position.y = goal[0][1];		//y-position
  g.target_pose.pose.position.z = goal[0][2];		//z-position
  g.target_pose.pose.orientation.w = goal[1][0];	//rotation
  g.target_pose.pose.orientation.x = goal[1][1];		//x-orientation
  g.target_pose.pose.orientation.y = goal[1][2];		//y-orientation
  g.target_pose.pose.orientation.z = goal[1][3];	//z-orientation
  return g;
}


int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals_self");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }


  for(int i = 0; i < (sizeof(waypoints)/sizeof(waypoints[0])); i++)   
    {
    	
	move_base_msgs::MoveBaseGoal goal;

	goal = sendGoal(waypoints[i]);
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	ROS_INFO("Hooray, the base moved to next goal");
	else
	ROS_INFO("The base failed to move to goal for some reason");

    }
  
  return 0;
}


/*#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"	//include message type

const float waypoints[3][2][4] = {{{10.0, 10.0, 0.0}, {0.1, 0.0, 0.0, 0.9999}},
			    {{8.0, 11.0, 0.0}, {0.4, 0.0, 0.0, 0.9999}},
			    {{15.0, 9.0, 0.0}, {0.7, 0.0, 0.0, 0.9999}}};  

geometry_msgs::PoseStamped sendGoals(const float goal[][])
{
  geometry_msgs::PoseStamped msg;
  msg.header.frame_id = "map";		//use map as reference  
  msg.pose.position.x = goal[0][0];		//x-position
  msg.pose.position.y = goal[0][1];		//y-position
  msg.pose.position.z = goal[0][2];		//z-position
  msg.pose.orientation.w = goal[1][0];	//rotation
  msg.pose.orientation.x = goal[1][1];		//x-orientation
  msg.pose.orientation.y = goal[1][2];		//y-orientation
  msg.pose.orientation.z = goal[1][3];	//z-orientation
  return msg
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "pose_pub");

  ros::NodeHandle n;

  ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, true);	//publish a message of type PoseStamped. This data is published on topic /move_base_simple/goal with buffer of 1. Send only if subscriber is there (true)

  ros::Rate loop_rate(100); //every 10 ms (100 Hz)

  int count = 0;
  while (ros::ok())	//this returns false if e.g. CTRL-C is hit
  {
    geometry_msgs::PoseStamped message;
    for(int i = 0; i < (sizeof(waypoint)/sizeof(waypoint[0])); i++)   
    {
    	message = sendGoals(waypoints[i]);
	pose_pub.publish(message);			//broadcast message to anyone who is connected
    }

    ros::spinOnce();	//provide callbacks

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
*/
