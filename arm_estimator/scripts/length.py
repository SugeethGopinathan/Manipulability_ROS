#!/usr/bin/env python  
import rospy
import tf
import geometry_msgs.msg
import numpy as np
from  geometry_msgs.msg import Pose

if __name__ == '__main__':
    rospy.init_node('tf_lookup_example')

    listener = tf.TransformListener()

    pub_grip = rospy.Publisher('grip_pose',Pose , queue_size=10)
    pub_shoulder = rospy.Publisher('shoulder_pose',Pose , queue_size=10)
    pose = geometry_msgs.msg.Pose()
    pose_sh = geometry_msgs.msg.Pose()
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform('/ar_marker_3', '/ar_marker_7', rospy.Time(0))
            pose.position.x= trans[0];
            pose.position.y= trans[1];
	    pose.position.z= trans[2];
            pose.orientation.x= rot[0];
            pose.orientation.y= rot[1];
            pose.orientation.z= rot[2];
            pose.orientation.w= rot[3];

            pose_sh.position.x= 0;
            pose_sh.position.y= 0;
	    pose_sh.position.z= 0;
            pose_sh.orientation.x= 0;
            pose_sh.orientation.y= 0;
            pose_sh.orientation.z= 0;
            pose_sh.orientation.w= 0;

            pub_grip.publish(pose)
            pub_shoulder.publish(pose_sh)
            #rospy.loginfo("Distance between two frames are = {0:f}".format(np.linalg.norm(trans)))


        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue

        rate.sleep()
