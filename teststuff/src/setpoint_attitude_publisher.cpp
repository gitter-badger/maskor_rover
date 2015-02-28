/*

Copyright Marcel Stüttgen 2015

simple ros node that will publish cmd_vel message to /mavros/setpoint/cmd_vel

 */

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>



int main(int argc, char *argv[])
{
  ros::init(argc, argv, "setpoint_velocity_publisher");
  ros::NodeHandle nh;
  ros::Publisher chatter_pub = nh.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint/cmd_vel", 1000);   
  ros::Rate loop_rate(10);

  double ros_roll;
  double ros_pitch;
  double ros_yaw;
  double ros_throttle;
  
  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::TwistStamped msg;

    nh.param<double>("ros_roll", ros_roll, 0.0);
    nh.param<double>("ros_pitch", ros_pitch, 0.0);
    nh.param<double>("ros_yaw", ros_yaw, 0.0);
    nh.param<double>("ros_throttle", ros_throttle, 0.0);

    ROS_INFO("sening TwistStamped to /mavros/setpoint/velocity");
    ROS_INFO("ros_roll: %f", ros_roll);
    ROS_INFO("ros_pitch: %f", ros_pitch);
    ROS_INFO("ros_yaw: %f", ros_yaw);
    ROS_INFO("ros_throttle: %f", ros_throttle);

    
    msg.header.stamp = ros::Time::now();
    msg.twist.linear.x = ros_throttle;
    msg.twist.linear.y = 0.0;
    msg.twist.linear.z = 0.0;
    msg.twist.angular.x = ros_roll;
    msg.twist.angular.y = ros_pitch;
    msg.twist.angular.z = ros_yaw;    
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  
  return 0;
}

