#include "ros/ros.h"
#include "medicine_box/MsgBox.h"
#include "std_msgs/Bool.h" 

ros::Publisher medicine_box_pub;
ros::Subscriber medicine_box_sub;
medicine_box::MsgBox msg;

void msgCallback(const std_msgs::Bool state)
{
    msg.stamp = ros::Time::now();
    msg.open = state.data;
}

void sendState(const ros::TimerEvent&)
{
    medicine_box_pub.publish(msg);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"medicine_box_node");
    ros::NodeHandle nh;

    medicine_box_pub = nh.advertise<medicine_box::MsgBox>("box_state",100);
    medicine_box_sub = nh.subscribe("medicine_box",100,msgCallback);

    //1秒で時間割り込み
    ros::Timer timer = nh.createTimer(ros::Duration(1),sendState);

    //待ち処理開始
    ros::spin();

    return 0;
}