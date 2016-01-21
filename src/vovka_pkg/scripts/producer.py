#!/usr/bin/env python

import rospy
from std_msgs.msg import String


def producer():
    publisher = rospy.Publisher('market', String, queue_size=5)
    rospy.init_node('producer', anonymous=True)
    rate = rospy.Rate(2)
    
    brands = ['Samsung', 'Lenovo', 'LG']
    series = ['I', 'Q', 'J', 'S', 'C']
    count = 0
    while not rospy.is_shutdown():
        msg = 'Just like origin %s %s%d' % (brands[count % len(brands)], series[count % len(series)], (count % len(brands) * len(series)))
        rospy.loginfo(msg)
        publisher.publish(msg)

        count += 1
        rate.sleep()


if __name__ == '__main__':
    try:
        producer()
    except rospy.ROSInterruptExcetion:
        pass
