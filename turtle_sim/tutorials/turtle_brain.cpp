#include<ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include <std_msgs/Int32.h>
#include <math.h>
#include <cstdlib>


using namespace std;


int flag=0; 
int predator;
class pubs{

public:
int turtleName=0;



ros::Publisher twist_pub_;
ros::Subscriber sub ;
void subCallback(std_msgs::Int32 counter1);
turtlesim::Pose positions[5];
pubs();

private:
ros::NodeHandle nh;
geometry_msgs::Twist twist;


};


pubs::pubs(){
turtleName=nh.getParam("turtle_name",turtleName);

 
twist_pub = nh.advertise<geometry_msgs::Twist>("turtle/cmd_vel", 1);

 sub= nh.subscribe("predator/specifier", 5, &pubs::subCallback,this);
 movementSubscriber=nh.subscribe("teleop/cmd_vel",5,&pubs::movementCallBack,this); 
}
void pubs::movementCallBack(geometry_msgs::Twist twist){
if(flag==1){
  geometry_msgs::Twist iMove;
  iMove.linear.x=twist.linear.x;
  iMove.angular.z=twist.angular.z;
  twist_pub.public(iMove);
}

}

void pubs::subCallback(std_msgs::Int32 counter1){
ROS_INFO("got message");    
int predator=counter1.data;


ros::Rate r(1);    
  while (ros::ok())
  {
    if(turtleName==predator){
         flag=1;
    }else{
      nh2.getParam("data1x",positions[0].x);
      nh2.getParam("data1y",positions[0].y);
      nh2.getParam("data1theta",positions[0].theta);
      nh2.getParam("data1angular",positions[0].angular_velocity);
      nh2.getParam("data2x",positions[1].x);
      nh2.getParam("data2y",positions[1].y);
      nh2.getParam("data2theta",positions[1].theta);
      nh2.getParam("data2angular",positions[1].angular_velocity);
      nh2.getParam("data3x",positions[2].x);
      nh2.getParam("data3y",positions[2].y);
      nh2.getParam("data3theta",positions[2].theta);
      nh2.getParam("data3angular",positions[2].angular_velocity);
      nh2.getParam("data4x",positions[3].x);
      nh2.getParam("data4y",positions[3].y);
      nh2.getParam("data4theta",positions[3].theta);
      nh2.getParam("data4angular",positions[3].angular_velocity);
      nh2.getParam("data5x",positions[4].x);
      nh2.getParam("data5y",positions[4].y);
      nh2.getParam("data5theta",positions[4].theta);
      nh2.getParam("data5angular",positions[4].angular_velocity);

    
     
        //cout<<i<<" "<<positions[i].theta<<" "<< positions[predator].theta<<(double)(M_PI/2)<<endl;
        if((positions[i].theta>0 && positions[predator].theta<0) || (positions[i].theta<0 && positions[predator].theta>0)){
          //if(positions[i].theta==(double)(M_PI/2) + positions[predator].theta || positions[i].theta==(double)(-(M_PI/2)) + positions[predator].theta){
             twist.angular.z=0; 
             twist.linear.x = rand()%5; 
             twist_pub.publish(twist);  
      
        //} 
         
       
       // cout<<"wants to escape: "<<i<<"  "<<(int)tan(positions[i].theta)<<endl;
     //   cout<<"predator: "<<(int)(-(1/tan(positions[predator].theta)))<<endl;
// if((int)tan(positions[i].theta)== (int)(-(1/tan(positions[predator].theta)))){ 
  //  cout<<"amood"<<endl;
  //  twist.angular.z=0; 
  //  twist.linear.x = 2.0; 
  //  twist_pub_[i].publish(twist);  
 }else{
   // cout<<(atan(positions[i].y/positions[i].x)-atan(-(positions[predator].x/positions[predator].y)))<<endl;
     twist.linear.x = 0;
     //positions[i].theta=M_PI/2 + positions[predator].theta;
     int randAngular=rand()%2;
     if(randAngular==0){
    // positions[i].theta=M_PI/2 + positions[predator].theta;    
     twist.angular.z=(double)(M_PI/2) + positions[predator].theta;
     }else if(randAngular==1){
         // positions[i].theta=-(M_PI/2) + positions[predator].theta;
          twist.angular.z=(double)(-(M_PI/2)) + positions[predator].theta;
     }
     twist_pub.publish(twist);
     positions[i].theta=twist.angular.z;
     //twist.angular.z=(atan(positions[i].y/positions[i].x)-atan(-(positions[predator].x/positions[predator].y)));
     
    //  twist.linear.x=2.0;
    //  twist.angular.z=0;
    //  twist_pub_[i].publish(twist);
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