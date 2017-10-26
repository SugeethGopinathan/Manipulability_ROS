#!/usr/bin/env python  
import rospy
import tf
import geometry_msgs.msg
import numpy as np

if __name__ == '__main__':
    rospy.init_node('tf_lookup_example')

    listener = tf.TransformListener()
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform('/ar_marker_6', '/ar_marker_7', rospy.Time(0))

            rospy.loginfo("Distance between two frames are = {0:f}".format(np.linalg.norm(trans)))

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue

        rate.sleep()
