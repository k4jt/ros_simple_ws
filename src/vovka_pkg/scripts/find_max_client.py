#!/usr/bin/env python

import sys
import rospy
from vovka_pkg.srv import *


def find_max_client(values):
    rospy.wait_for_service('find_max')
    try:
        find_max = rospy.ServiceProxy('find_max', FindMax)
        response = find_max(values)
        return response.max_value
    except rospy.ServiceException as e:
        print 'Service call failed: %s' % e


def usage():
    return '%s x1 x2 x3 ...' % sys.argv[0]


if __name__ == '__main__':
    if len(sys.argv) <= 2:
        rospy.loginfo(usage())
        sys.exit(1)
    else:
        values = map(int, sys.argv[1:])
    print 'Request find max among [%s]' % str(values)
    print 'Max is %d' % find_max_client(values)
