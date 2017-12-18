#include<ros/ros.h>
#include<turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

//turtlesim::Pose positions[5];

class Subs{

public:
void controlCallBack1(const turtlesim::PosePtr& pose);
void controlCallBack2(const turtlesim::PosePtr& pose);
void controlCallBack3(const turtlesim::PosePtr& pose);
void controlCallBack4(const turtlesim::PosePtr& pose);
void controlCallBack5(const turtlesim::PosePtr& pose);
Subs();    

private:  
ros::Subscriber receiveControl[5];
ros::NodeHandle nh;


};

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "Subscribers");
    return 0;
}


Subs::Subs(){


receiveControl[0] = nh.subscribe("turtle2/pose", 5 , &Subs::controlCallBack1,this);
receiveControl[1] = nh.subscribe("turtle3/pose",5 , &Subs::controlCallBack2,this);
receiveControl[2]=  nh.subscribe("turtle4/pose", 5 , &Subs::controlCallBack3,this);
receiveControl[3] = nh.subscribe("turtle5/pose", 5 ,&Subs::controlCallBack4,this);
receiveControl[4] = nh.subscribe("turtle6/pose", 5 , &Subs::controlCallBack5,this);
    

}
void Subs::controlCallBack1(const turtlesim::PosePtr& pose){

 
  nh.setParam("data1x",pose->x);
  nh.setParam("data1y",pose->y);

  ROS_INFO("TWIST ghfhgUBLISHED");
 

}
void Subs::controlCallBack2(const turtlesim::PosePtr& pose){
  
  nh.setParam("data2x", pose->x);
  nh.setParam("data2y", pose->y);

  ROS_INFO("TWIST ghfhgUBLISHED");
 
}
void Subs::controlCallBack3(const turtlesim::PosePtr& pose){
  
  nh.setParam("data3x",pose->x);
  nh.setParam("data3y",pose->y);
  ROS_INFO("TWIST ghfhgUBLISHED");
  
 
}
void Subs::controlCallBack4(const turtlesim::PosePtr& pose){

  nh.setParam("data4x",pose->x);
  nh.setParam("data4y",pose->y);
  ROS_INFO("TWIST ghfhgUBLISHED");
  
 }

void Subs::controlCallBack5(const turtlesim::PosePtr& pose){

  nh.setParam("data5x",pose->x);
  nh.setParam("data5y",pose->y);

  ROS_INFO("5esfgh"); 
  }


