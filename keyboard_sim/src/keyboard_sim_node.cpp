//AC
#include "ros/ros.h"
#include "wiimote/State.h"	//include message type

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "keyboard_sim_node");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<wiimote::State>("/wiimote/state", 1000, true);	

  ros::Rate loop_rate(100); //every 10 ms (100 Hz)

  bool pub_now = true;

  while (ros::ok())	//this returns false if e.g. CTRL-C is hit
  {
    //simulation for the wii_controller to test the A-Button recording of waypoints
    //simulate the buttons 'a' and 'c' for recording and for executing, send this as replacement for wiimote/state
    wiimote::State msg;
    ROS_INFO("Enter key");
    int pressed = getchar();

    
    switch(pressed)
    {
	case 'a':
	     msg.buttons[4] = true;
	     break;
	case 'c':
	     msg.nunchuk_buttons[1] = true;
	     break;
	case '\n':
	     pub_now = false;
	     break;
	default:
	     msg.buttons[4] = false;
	     msg.nunchuk_buttons[1] = false;
	     break;

    }

    if(pub_now)
	pub.publish(msg);	//broadcast message to anyone who is connected
    else
	pub_now = true;

    ros::spinOnce();	//provide callbacks

    loop_rate.sleep();
  }


  return 0;
}

