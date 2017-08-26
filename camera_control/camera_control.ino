#include <ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/JointState.h>

#include "Arduino.h"
#include "Servo.h"

Servo pan;
Servo tilt;

ros::NodeHandle nh;
sensor_msgs::JointState jointStateMsg;

void panCmd(const std_msgs::Float32& msg) {
  pan.write(msg.data/PI*180);
}

void tiltCmd(const std_msgs::Float32& msg) {
  tilt.write(msg.data/PI*180);
}

ros::Subscriber<std_msgs::Float32> panSub("pan/command", &panCmd);
ros::Subscriber<std_msgs::Float32> tiltSub("tilt/command", &tiltCmd);
ros::Publisher jointStatePub("joint_states", &jointStateMsg);

//The setup function is called once at startup of the sketch
void setup()
{
	pan.attach(4);
	tilt.attach(5);
	pan.write(90);
	tilt.write(90);

	nh.initNode();
	nh.subscribe(panSub);
	nh.subscribe(tiltSub);

	jointStateMsg.name[0] = "camera_pan";
	jointStateMsg.name[1] = "camera_tilt";
}

// The loop function is called in an endless loop
void loop()
{
	nh.spinOnce();
	delay(10);
}
