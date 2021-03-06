#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/String.h>





#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint/cmd_vel", 1000);   
  ros::Rate loop_rate(10);

 int count = 0;
  while (ros::ok())
  {
    geometry_msgs::TwistStamped msg;

	msg.header.stamp = ros::Time::now();

	msg.twist.linear.x = 0.0;
    msg.twist.angular.z = 0.0;    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
