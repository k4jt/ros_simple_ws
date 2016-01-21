#!/usr/bin/env python

import rospy
from vovka_pkg.srv import *


def processing(req):
    rospy.loginfo('Max value among [%s] is %d' % (str(req.values), max(req.values)))
    return max(req.values)


def find_max_server():
    rospy.init_node('find_max_server', anonymous=True)
    rospy.Service('find_max', FindMax, processing)
    rospy.loginfo('Ready to find max')
    rospy.spin()


if __name__ == '__main__':
    find_max_server()
