#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


void poseCallback(const nav_msgs::Odometry &msg){

  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg.pose.pose.position.x, msg.pose.pose.position.y, msg.pose.pose.position.z) );
  tf::Quaternion q(
  msg.pose.pose.orientation.x,
  msg.pose.pose.orientation.y,
  msg.pose.pose.orientation.z,
  msg.pose.pose.orientation.w);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world_frame", "robot_frame"));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_frame");
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/merged_data",10, &poseCallback);

  ros::spin();
  return 0;
};