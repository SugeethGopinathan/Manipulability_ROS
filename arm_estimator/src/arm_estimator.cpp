#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"
#include <sstream>
#include "kdl/frames.hpp"
#include "kdl_parser/kdl_parser.hpp"
#include "geometry_msgs/Pose.h"
#include "tf/tf.h"
#include "tf/tfMessage.h"
#include "math.h"
#include "tf_conversions/tf_kdl.h"

ros::Publisher pub;
ros::Publisher pub2;
//pctx_control::Control controlmsg;
geometry_msgs::Pose shoulder_pose;
geometry_msgs::Pose grip_pose;

KDL::Frame shoulder_KDL;

void function_callback (const tf::tfMessageConstPtr &msg)
{
    for(int i=0; i < msg->transforms.size();i++){
        if (msg->transforms[i].child_frame_id == "ar_marker_8"){




            shoulder_pose.position.x = msg->transforms[i].transform.translation.x;
            shoulder_pose.position.y = msg->transforms[i].transform.translation.y;
            shoulder_pose.position.z = msg->transforms[i].transform.translation.z;

            shoulder_pose.orientation.w = msg->transforms[i].transform.rotation.w;
            shoulder_pose.orientation.x = msg->transforms[i].transform.rotation.x;
            shoulder_pose.orientation.y = msg->transforms[i].transform.rotation.y;
            shoulder_pose.orientation.z = msg->transforms[i].transform.rotation.z;

        }

        if (msg->transforms[i].child_frame_id == "ar_marker_7"){


            grip_pose.position.x = msg->transforms[i].transform.translation.x;
            grip_pose.position.y = msg->transforms[i].transform.translation.y;
            grip_pose.position.z = msg->transforms[i].transform.translation.z;

            grip_pose.orientation.w = msg->transforms[i].transform.rotation.w;
            grip_pose.orientation.x = msg->transforms[i].transform.rotation.x;
            grip_pose.orientation.y = msg->transforms[i].transform.rotation.y;
            grip_pose.orientation.z = msg->transforms[i].transform.rotation.z;

        }
    }


    //tf::PoseMsgToKDL(shoulder_pose,shoulder_KDL);

    pub.publish(shoulder_pose);
    pub2.publish(grip_pose);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_node");
    ros::NodeHandle n;

    pub = n.advertise<geometry_msgs::Pose>("shoulder_pose", 100);
    pub2 = n.advertise<geometry_msgs::Pose>("grip_pose",100);
    ros::Subscriber sub = n.subscribe("tf", 1000, function_callback);

    // Handle ROS callbacks until shutdown
    ros::spin();

    return 0;
}


