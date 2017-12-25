#include<ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include <std_msgs/Int32.h>
#include <math.h>
#include <cstdlib>


using namespace std;


int flagImPredator=0; 
int predator;

class turtleBrain{

public:
int turtleCounter=0;



ros::Publisher twist_pub;
ros::Subscriber sub;
void setPredatorCallback(std_msgs::Int32 counter);
turtlesim::Pose positions;
turtleBrain();

private:
ros::NodeHandle nh;
geometry_msgs::Twist twist;
};


turtleBrain::turtleBrain(){

nh.getParam("turtle_counter",turtleCounter); 
twist_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
poses = nh.subscribe("pose", 5 , &Subs::controlCallBack,this);

 sub= nh.subscribe("/predator/specifier", 5, &turtleBrain::setPredatorCallback,this);
 movementSubscriber=nh.subscribe("/teleop/cmd_vel",5,&turtleBrain::movementCallBack,this); 
}

void turtleBrain::movementCallBack(geometry_msgs::Twist twist){
if(flagImPredator==1){
  geometry_msgs::Twist iMove;
  iMove.linear.x=twist.linear.x;
  iMove.angular.z=twist.angular.z;
  twist_pub.public(iMove);
}
}
void Subs::controlCallBack(const turtlesim::PosePtr& pose){

  ROS_INFO("set param pose turtle_%d", turtleName);
  // nh.setParam(turtleName,pose);
  nh.setParam("1",pose);
}



void turtleBrain::setPredatorCallback(std_msgs::Int32 counter){
ROS_INFO("predator changed");    
int predator=counter1.data;


ros::Rate r(1);    
  while (ros::ok())
  {
    if(turtleName==predator){
         flag=1;
    }else{
// for each turtle get position
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
   turtleBrain publishers=turtleBrain();
   ros::spin();  
    return 0;
}