#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <string>
#include <math.h>

int main(int argc, char** argv)
{
 ros::init(argc, argv, "info_marker_publisher1");
 ros::NodeHandle nh;
 
 //publisher
 ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("marker", 1);
 
 ros::Rate loop_rate(10);
 while(ros::ok())
 {
  visualization_msgs::Marker marker;//ros::init(argc, argv, "info_marker_publisher
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;
  
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;
  marker.lifetime = ros::Duration();
  
  marker.scale.x = 12.1;
  marker.scale.y = 0.05;
  marker.scale.z = 0.212;
  marker.pose.position.x = 0;
  marker.pose.position.y = 6.05;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0;
  marker.pose.orientation.y = 0;
  marker.pose.orientation.z = 0;
  marker.pose.orientation.w = 1;
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0f;
  marker_pub.publish(marker);
  
  ros::spinOnce();
  loop_rate.sleep();
 }
 return 0;
}
