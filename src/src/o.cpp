/*ROSlibrary*/
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>

/*ROS変数*/
geometry_msgs::Twist cmd_vel;
std_msgs::Int32 c_msg;
std_msgs::Int32 LE_msg;
std_msgs::Int32 short_msg;



bool shouldShutdown = false;
int a = 1;
double b = 1;
int c;
int cnt;

void end(){
if(a == 1 & b ==3){



}
}


void joy_callback(const sensor_msgs::Joy &joy_msg)
{
 /*cmd_vel.linear.x = joy_msg.axes[1] * 0.7;
 cmd_vel.linear.y = joy_msg.axes[0] * 0.7;*/

 if (joy_msg.axes[1] > 0)
  cmd_vel.linear.x = 0.026 * a;//20mm/s
 else if (joy_msg.axes[1] < 0)
  cmd_vel.linear.x = -0.026 * a;
  else 
  cmd_vel.linear.x = 0;
  
 if (joy_msg.axes[0] >0.31)
  cmd_vel.linear.y = 0.026 * a;
 else if (joy_msg.axes[0] < -0.31)
  cmd_vel.linear.y = -0.026;
 else 
 cmd_vel.linear.y = 0;
  
 if (joy_msg.axes[3] > 0)
  cmd_vel.angular.z =  0.029 * a;
 else if (joy_msg.axes[3] < 0)
  cmd_vel.angular.z = - 0.029 * a;
 else
   cmd_vel.angular.z = 0;
   
  if (joy_msg.buttons[5] > 0)
  c_msg.data = 1;
 else if (joy_msg.buttons[4] > 0)
  c_msg.data = -1;
else if (joy_msg.buttons[0] > 0)
   c_msg.data = 2;
  else if (joy_msg.buttons[2] > 0)
  c_msg.data = -2;
  else if (joy_msg.axes[7] == 1)
   c_msg.data = 3;
  else if (joy_msg.axes[7] == -1)
  c_msg.data = -3; 
  else c_msg.data = 0;
 // else if (joy_msg.buttons[2] == 1) 
 // c_msg.data =  4; 
 // else if (joy_msg.axes[6] == 1) 
 // c_msg.data = -4;
 
  if (joy_msg.buttons[8] > 0)
   {LE_msg.data = 2;
  
    
   a=3;
   //startTime();
   }
     else if (joy_msg.buttons[1] > 0) 
  LE_msg.data =  1;
     else if (joy_msg.axes[6] > 0) 
  LE_msg.data = -1;
 //else LE_msg.data = 0;
   
  
   
  
 /*c_msg.data = joy_msg.buttons[0];
 c_msg.data = joy_msg.buttons[1];*/
}

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
 a = 0;
 b++;
 cmd_vel.linear.x = 0;
cmd_vel.linear.y = 0;
 LE_msg.data = 3;
 end();
 
 //ros::Duration(10.0).sleep();
 //a = 1;
// ros::shutdown();
}

void LE_Callback(const std_msgs::Int32 &LE_msg)
{
 if(LE_msg.data == 3 )
 { //shouldShutdown = true;
 }
}

void short_Callback(const std_msgs::Int32 &short_msg)
{if(short_msg.data == 1){

ros::shutdown();
}
}
int main(int argc, char **argv)
{

  

//end_time = time(NULL);
 ros::init(argc, argv, "o_node");
 ros::NodeHandle nh;
 
 ros::Subscriber joy_sub = nh.subscribe("joy", 10, joy_callback);
 ros::Subscriber sub = nh.subscribe("chatter", 100, chatterCallback);
 ros::Subscriber sub_LE = nh.subscribe("LE", 10, LE_Callback);
 ros::Subscriber sub_short = nh.subscribe("short",5,short_Callback);
 ros::Publisher  cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
 ros::Publisher pub_c = nh.advertise<std_msgs::Int32>("c", 10);
 ros::Publisher pub_LE = nh.advertise<std_msgs::Int32>("LE",10);
 //ros::Publisher pub_a = nh.advertise<std_msgs::Int16>("a", 10);
 
 ros::Rate loop_rate(30);
 if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
   ros::console::notifyLoggerLevelsChanged();
}
 
 //if(a==1)
 
 while (ros::ok() && !shouldShutdown)
 {
  cmd_vel_pub.publish(cmd_vel);
  pub_c.publish(c_msg);
  pub_LE.publish(LE_msg);
  ros::spinOnce();
  loop_rate.sleep();
 }
 return 0;
}
