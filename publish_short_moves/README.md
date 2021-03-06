# Contribution Anthony Carnevale: Execute short moves for better localization

The contribution consists of writing the node "short_moves_pub" which makes the car move back and forth for a better localization after giving an initial pose, and changing/adding some code inside the wii_lib class and the tas_autonomous_control node to avoid "collisions" with the wii data.

The written/changed code is in the files: 
- https://github.com/tas1516-group-01/tas1516_car_01/blob/master/publish_short_moves/src/short_moves_pub.cpp
- https://github.com/tas1516-group-01/tas1516_car_01/blob/master/wii_control/src/wii_lib/wii_lib.cpp
- https://github.com/tas1516-group-01/tas1516_car_01/blob/master/wii_control/src/wii_lib/wii_lib.h
- https://github.com/tas1516-group-01/tas1516_car_01/blob/master/tas_autonomous_control/src/tas_autonomous_control_node.cpp

Program Flow:
  1. Initialization: Add publisher that publishes a flag (bool) to a topic called "interrupt". This topic is the one the wii_control node subscribes to. 
  2. What publish_short_moves does: This node can execute two tasks. Here we look at the UNCOMMENTED part (other one is explained in README-File of my other contribution detect_stuck). After half a second it starts publishing a PWM-value to the servo which is bigger than 1500 for driving forward and at the same time it sends a signal to the topic "interrupt" (set flag), which basically indicates that the topic servo now is occupied. After a few seconds it stops by sending 1500 and afterwards a smaller value than 1500 makes the car drive backwards. While stopping for the last time we reset the flag to show that the servo is now again available. As you can see the procedure of moving and stopping is repeating twice. I found out that the car needs this double indication for doing what it is supposed to do, at least the car we were working at.
  3. What wii_control was changed for: As already mentioned this node now is subscribet to the new topic "interrupt". The created callback function stores the arriving flag change from the short_moves-node and if the flag is set (what means that the servo topic is "busy" because short moves are executed) neither in the case of driving autonomous (change in tas_autonomous_control node) nor in the case of driving manually (change in wii_control node) the servo value gets published. That is a required function to ensure that the PWM-values don't get overwritten by the wii controller.

## Execution

Starting the node:

> rosrun publish_short_moves short_moves_pub

## Video

The following video shows the working code:

https://www.dropbox.com/s/wxnmmmxl2lvyi0h/short_moves_video.MOV?dl=0
