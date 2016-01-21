#include "ros/ros.h"
#include "vovka_pkg/FindMax.h"

#include <cstdlib>

int main(int argc, char **argv) {

    ros::init(argc, argv, "find_max_client");
    if (argc <= 2) {
        ROS_INFO("usage: find_max_client x1 x2 x3 x4 ...");
        return 1;
    }

    ros::NodeHandle node;
    ros::ServiceClient client = node.serviceClient<vovka_pkg::FindMax>("find_max");

    vovka_pkg::FindMax srv;
    for (int i = 1; i < argc; ++i) {
        srv.request.values.push_back(atoll(argv[i]));
    }

    if (client.call(srv)) {
        ROS_INFO("Max is %d", (int)srv.response.max_value);
    } else {
        ROS_ERROR("Failed to call service find_max");
        return 1;
    }

    return 0;
}
