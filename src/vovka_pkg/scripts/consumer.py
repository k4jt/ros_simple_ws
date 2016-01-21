#!/usr/bin/env python

import rospy
from std_msgs.msg import String


def callback(msg):
    rospy.loginfo(rospy.get_caller_id() + ' WOW! Have you heard about %s', msg.data)


def consumer():
    rospy.init_node('consumer', anonymous=True)
    rospy.Subscriber('market', String, callback)

    rospy.spin()


if __name__ == '__main__':
    consumer()
