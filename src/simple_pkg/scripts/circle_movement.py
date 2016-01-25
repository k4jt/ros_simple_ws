#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

class CircleMovement():

    def __init__(self):
        rospy.init_node('circle_movement', anonymous=False)
        rospy.on_shutdown(self.shutdown)
        
        self.cmd_vel = rospy.Publisher('/cmd_vel', Twist, queue_size=5)
        rate = rospy.Rate(10)
        linear_speed = 0.5
        angular_speed = 1.0

        while (not rospy.is_shutdown()):
            move_cmd = Twist()
            move_cmd.linear.x = linear_speed
            move_cmd.angular.z = angular_speed
            self.cmd_vel.publish(move_cmd)
            rate.sleep()

    def shutdown(self):
        rospy.loginfo('Stop the robot')
        self.cmd_vel.publish(Twist())
        rospy.sleep(1)


if __name__ == '__main__':
    try:
        CircleMovement()
    except rospy.ROSInterruptException:
        rospy.loginfo('Circle-Movement node teminated')
