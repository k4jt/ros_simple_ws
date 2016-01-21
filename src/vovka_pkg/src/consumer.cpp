#include "ros/ros.h"
#include "std_msgs/String.h"

void callback(const std_msgs::String::ConstPtr & msg) {

    ROS_INFO("WOW, I've just heard about %s, it's awesome!", msg->data.c_str());
}


int main(int argc, char **argv) {
    
    ros::init(argc, argv, "consumer");
    ros::NodeHandle node;
    ros::Subscriber subscriber = node.subscribe("market", 5, callback);
    ros::spin();

    return 0;
}
