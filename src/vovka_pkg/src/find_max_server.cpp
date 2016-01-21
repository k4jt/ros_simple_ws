#include "ros/ros.h"
#include "vovka_pkg/FindMax.h"

#include <algorithm>

bool processing(vovka_pkg::FindMax::Request &req,
                vovka_pkg::FindMax::Response & res) {
    
    int maxValue = *std::max_element(req.values.begin(), req.values.end());
    res.max_value = maxValue;
    ROS_INFO("find value: %d", maxValue);
    return true;
}

int main(int argc, char **argv) {
    
    ros::init(argc, argv, "find_max_server");
    ros::NodeHandle node;

    ros::ServiceServer service = node.advertiseService("find_max", processing);
    ROS_INFO("Ready to find max");
    ros::spin();

    return 0;
}
