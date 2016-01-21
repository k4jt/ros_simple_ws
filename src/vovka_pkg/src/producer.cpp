#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "producer");
    ros::NodeHandle node;

    ros::Publisher publisher = node.advertise<std_msgs::String>("market", 5);
    ros::Rate loop_rate(2);

    int count = 0;
    std::vector<std::string> brands;
    brands.push_back("IPhone");
    brands.push_back("Samsung");
    brands.push_back("Nokia");
    std::vector<std::string> series;
    series.push_back("S"); 
    series.push_back("A"); 
    series.push_back("K"); 
    series.push_back("J"); 
    series.push_back("C"); 

    while(ros::ok()) {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "Brand new " << brands[count % brands.size()] << " " << series[count % series.size()] << count / (brands.size() * series.size());

        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str());

        publisher.publish(msg);
        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}
