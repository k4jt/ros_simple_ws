#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

ros::Time last_time;
double x = 0.0;
double y = 0.0;
double th = 0.0;
double vx = 0.0;
double vy = 0.0;
double vth = 0.0;
geometry_msgs::Quaternion odom_quat;

void cmd_velCallback(const geometry_msgs::Twist &twist_aux) {
	vx = twist_aux.linear.x;
	vy = twist_aux.linear.y;
	vth = twist_aux.angular.z;
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "base_controller");
	ros::NodeHandle n;
	ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 10);
	ros::Subscriber cmd_vel_sub = n.subscribe("cmd_vel", 10, cmd_velCallback);
	ros::Rate loop_rate(10);
    
    last_time = ros::Time::now();
    
    
    tf::TransformBroadcaster broadcaster;
	const double degree = M_PI/180;

	// message declarations
	geometry_msgs::TransformStamped odom_trans;
	odom_trans.header.frame_id = "odom";
	odom_trans.child_frame_id = "base_footprint";

    while(ros::ok()) {
    
        ros::spinOnce();
    
        ros::Time current_time = ros::Time::now();
        double dt = (current_time - last_time).toSec();
		double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
		double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
		double delta_th = vth * dt;
        
        
        x += delta_x;
		y += delta_y;
		th += delta_th;

		geometry_msgs::Quaternion odom_quat;	
		odom_quat = tf::createQuaternionMsgFromRollPitchYaw(0,0,th);

		// update transform
		odom_trans.header.stamp = current_time; 
		odom_trans.transform.translation.x = x; 
		odom_trans.transform.translation.y = y; 
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(th);

		//filling the odometry
		nav_msgs::Odometry odom;
		odom.header.stamp = current_time;
		odom.header.frame_id = "odom";
		odom.child_frame_id = "base_footprint";

		// position
		odom.pose.pose.position.x = x;
		odom.pose.pose.position.y = y;
		odom.pose.pose.position.z = 0.0;
		odom.pose.pose.orientation = odom_quat;

		//velocity
		odom.twist.twist.linear.x = vx;
		odom.twist.twist.linear.y = vy;
		odom.twist.twist.linear.z = 0.0;
		odom.twist.twist.angular.x = 0.0;
		odom.twist.twist.angular.y = 0.0;
		odom.twist.twist.angular.z = vth;

		last_time = current_time;

		// publishing the odometry and the new tf
		broadcaster.sendTransform(odom_trans);
		odom_pub.publish(odom);
        
        loop_rate.sleep();
    }

}
