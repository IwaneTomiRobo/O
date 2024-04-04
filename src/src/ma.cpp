#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/MarkerArray.h>

#include <string>
#include <math.h>

geometry_msgs::Twist twist_last;
void twist_callback(const geometry_msgs::Twist& twist_msg)
{
 twist_last = twist_msg;
} 

int main(int argc, char** argv)

