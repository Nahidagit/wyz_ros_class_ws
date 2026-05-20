#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/Quaternion.h>
#include <cmath>
#include <my_class_pkg/WindowStatus.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "send_goals_node");
    ros::NodeHandle nh;

    // 创建发布器
    ros::Publisher window_pub = nh.advertise<my_class_pkg::WindowStatus>("window", 10);

    MoveBaseClient ac("move_base", true);

    ac.waitForServer();

    // 自定义消息变量，初始化为 0
    my_class_pkg::WindowStatus window_msg;
    window_msg.status = 0;
    window_pub.publish(window_msg);
    ros::Duration(0.2).sleep();
    ROS_INFO("Window status initialized to 0");

    move_base_msgs::MoveBaseGoal goal0;
    move_base_msgs::MoveBaseGoal goald1;
    move_base_msgs::MoveBaseGoal goal1;
    move_base_msgs::MoveBaseGoal goal1_2;
    move_base_msgs::MoveBaseGoal goal2;
    move_base_msgs::MoveBaseGoal goald2;
    move_base_msgs::MoveBaseGoal goal2_3;
    move_base_msgs::MoveBaseGoal goal3;
    tf2::Quaternion quaternion;

    // 待发送的目标点d1 在 map 坐标系下的坐标位置（将上一节标定的位置填写到对应的x，y，yaw）
    quaternion.setRPY(0, 0, 1.37); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goald1.target_pose.pose.position.x = 2.60; //x，相对于建图起点前后的值，前正后负
    goald1.target_pose.pose.position.y = 1.26; //y，相对于建图起点左右的值，左正右负
    goald1.target_pose.pose.orientation.z = quaternion.z();
    goald1.target_pose.pose.orientation.w = quaternion.w();
    goald1.target_pose.header.frame_id = "map";
    goald1.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goald1);
    ROS_INFO("Send Desk  1 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Desk  1 Reached Successfully!!!");

        // 到达 d1，发布 window = 1
        window_msg.status = 1;
        window_pub.publish(window_msg);
        ROS_INFO("Window status = 1");

        ros::Duration(0.2).sleep();  // 停止 1 秒

        // 发布 window = 0
        window_msg.status = 0;
        window_pub.publish(window_msg);
        ROS_INFO("Window status = 0");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    
    // 待发送的目标点1 在 map 坐标系下的坐标位置
    quaternion.setRPY(0, 0, -1.57); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal1.target_pose.pose.position.x = 0.30;
    goal1.target_pose.pose.position.y = 1.05;
    goal1.target_pose.pose.orientation.z = quaternion.z();
    goal1.target_pose.pose.orientation.w = quaternion.w();
    goal1.target_pose.header.frame_id = "map";
    goal1.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal1);
    ROS_INFO("Send Goal 1 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Goal 1 Reached Successfully!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    
    /*
    // 待发送的目标点1_2 在 map 坐标系下的坐标位置
    quaternion.setRPY(0, 0, -1.57); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal1_2.target_pose.pose.position.x = 0.05;
    goal1_2.target_pose.pose.position.y = 2.60;
    goal1_2.target_pose.pose.orientation.z = quaternion.z();
    goal1_2.target_pose.pose.orientation.w = quaternion.w();
    goal1_2.target_pose.header.frame_id = "map";
    goal1_2.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal1_2);
    ROS_INFO("Send Goal 1_2 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Goal 1_2 Reached Successfully!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    */

    // 待发送的目标点2 在 map 坐标系下的坐标位置
    quaternion.setRPY(0, 0, -0.524); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal2.target_pose.pose.position.x = 0.45;
    goal2.target_pose.pose.position.y = 4.32;
    goal2.target_pose.pose.orientation.z = quaternion.z();
    goal2.target_pose.pose.orientation.w = quaternion.w();
    goal2.target_pose.header.frame_id = "map";
    goal2.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal2);
    ROS_INFO("Send Goal 2 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Goal 2 Reached Successfully!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    
    // 待发送的目标点d2 在 map 坐标系下的坐标位置（将上一节标定的位置填写到对应的x，y，yaw）
    quaternion.setRPY(0, 0, -1.57); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goald2.target_pose.pose.position.x = 2.61; //x，相对于建图起点前后的值，前正后负
    goald2.target_pose.pose.position.y = 3.15; //y，相对于建图起点左右的值，左正右负
    goald2.target_pose.pose.orientation.z = quaternion.z();
    goald2.target_pose.pose.orientation.w = quaternion.w();
    goald2.target_pose.header.frame_id = "map";
    goald2.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goald2);
    ROS_INFO("Send Desk  2 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Desk  2 Reached Successfully!!!");

        // 到达 d2，发布 window = 1
        window_msg.status = 1;
        window_pub.publish(window_msg);
        ROS_INFO("Window status = 1");

        ros::Duration(0.2).sleep();  // 停止 1 秒

        // 发布 window = 0
        window_msg.status = 0;
        window_pub.publish(window_msg);
        ROS_INFO("Window status = 0");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    
    // 待发送的目标点2_3 在 map 坐标系下的坐标位置
    quaternion.setRPY(0, 0, 0.96); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal2_3.target_pose.pose.position.x = 1.77;
    goal2_3.target_pose.pose.position.y = 4.32;
    goal2_3.target_pose.pose.orientation.z = quaternion.z();
    goal2_3.target_pose.pose.orientation.w = quaternion.w();
    goal2_3.target_pose.header.frame_id = "map";
    goal2_3.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal2_3);
    ROS_INFO("Send Goal 2_3 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Goal 2_3 Reached Successfully!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }
    // 待发送的目标点3 在 map 坐标系下的坐标位置
    quaternion.setRPY(0, 0, 1.34); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal3.target_pose.pose.position.x = 1.59;
    goal3.target_pose.pose.position.y = 3.56;
    goal3.target_pose.pose.orientation.z = quaternion.z();
    goal3.target_pose.pose.orientation.w = quaternion.w();
    goal3.target_pose.header.frame_id = "map";
    goal3.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal3);
    ROS_INFO("Send Goal 3 !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("The Goal 3 Reached Successfully!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }

    // 待发送的 home 目标点 在 map 坐标系下的坐标位置
//    quaternion.setRPY(0, 0, 0); // 最后一个数对应 yaw 角，正前方向量顺时针旋转
    goal0.target_pose.pose.position.x = -0.35;
    goal0.target_pose.pose.position.y = 2.49;
    goal0.target_pose.pose.orientation.z = 0.0;
    goal0.target_pose.pose.orientation.w = 1.0;
    goal0.target_pose.header.frame_id = "map";
    goal0.target_pose.header.stamp = ros::Time::now();
    ac.sendGoal(goal0);
    ROS_INFO("Send Goal Home !!!");
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("Back !!!!");
    }
    else
    {
        ROS_WARN("The Goal Planning Failed for some reason");
    }

    return 0;
}
