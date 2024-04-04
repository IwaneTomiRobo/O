/*ROSlibrary*/
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>

/*C_library*/
#include <time.h>

/*時間定数定義*/
time_t start_time, end_time;

/*ROS_Publisherの変数宣言（topicのclass)*/
ros::Publisher chatter_pub;

void startTime(){
 ROS_INFO("start");
 double total_sec = 10;
 start_time = time(NULL);
 for(;;){end_time = time(NULL);
 double sec = (double)(end_time - start_time);
 if (sec >= total_sec){
 break;
 }
 }
 std_msgs::String msg;
 msg.data = "Hello";
 chatter_pub.publish(msg);
 chatter_pub.publish(msg);
 chatter_pub.publish(msg);
 ros::shutdown();
 }
 
 void joy_callback(const sensor_msgs::Joy &joy_msg){
  if(joy_msg.buttons[8] > 0){
 startTime();
 }
 }
int main(int argc, char **argv)
{
 ros::init(argc, argv, "t_node");
 ros::NodeHandle nh;
 chatter_pub = nh.advertise<std_msgs::String>("chatter", 100);
 ros::Subscriber sub = nh.subscribe("joy", 10, joy_callback);
 ros::Rate loop_rate(30);
 while (ros::ok())
{
 ros::spinOnce();
 loop_rate.sleep();
}
 return 0;
}

