#include<ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include <std_msgs/Int32.h>



int flag[5]; 
int predator;
class pubs{

public:

ros::Publisher twist_pub_[5];
ros::Subscriber sub ;
void subCallback(std_msgs::Int32 counter1);
//void loop();
turtlesim::Pose positions[5];
pubs();

private:
ros::NodeHandle nh2;
geometry_msgs::Twist twist;
geometry_msgs::Twist twist1;

};


pubs::pubs(){

   for(int i=0;i<5;i++){
       flag[i]=0;
   } 
 
  twist_pub_[0] = nh2.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);
  twist_pub_[1] = nh2.advertise<geometry_msgs::Twist>("turtle3/cmd_vel", 1);
  twist_pub_[2] = nh2.advertise<geometry_msgs::Twist>("turtle4/cmd_vel", 1);
  twist_pub_[3] = nh2.advertise<geometry_msgs::Twist>("turtle5/cmd_vel", 1);
  twist_pub_[4] = nh2.advertise<geometry_msgs::Twist>("turtle6/cmd_vel", 1);

 sub= nh2.subscribe("turtle8/cmd_vel_temp", 5, &pubs::subCallback,this);
}
//void pubs::loop(){
  
//}
void pubs::subCallback(std_msgs::Int32 counter1){
ROS_INFO("got message");    
int counter=counter1.data;
for(int i=0;i<5;i++){
    if(i == counter){
    flag[i]=1;
    predator=i;
    }else{
    flag[i]=0;
    }
  }  
ros::Rate r(1);    
  while (ros::ok())
  {
      nh2.getParam("data1x",positions[0].x);
      nh2.getParam("data1y",positions[0].y);
      nh2.getParam("data2x",positions[1].x);
      nh2.getParam("data2y",positions[1].y);
      nh2.getParam("data3x",positions[2].x);
      nh2.getParam("data3y",positions[2].y);
      nh2.getParam("data4x",positions[3].x);
      nh2.getParam("data4y",positions[3].y);
      nh2.getParam("data5x",positions[4].x);
      nh2.getParam("data5y",positions[4].y);
    
      

     for(int i=0;i<5;i++){
     if(flag[i]==0){

     twist.angular.z=(atan(positions[i].y/positions[i].x)-atan(-(positions[predator].x/positions[predator].y)));
     twist.linear.x = 2.0;
     twist_pub_[i].publish(twist);    
       }
     }

   r.sleep();  
  }
}
int main(int argc, char *argv[])
{
   ros::init(argc, argv, "publishers");
   pubs publishers=pubs();
   ros::spin();  
    return 0;
}