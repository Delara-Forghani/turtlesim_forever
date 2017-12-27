#include<ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include <std_msgs/Int32.h>
#include <math.h>
#include <cstdlib>


using namespace std;


int imPredator=0; 
int predator=1;


class turtleBrain{

public:
ros::NodeHandle nh;
geometry_msgs::Twist twist_msg;
int turtleCounter=0;
ros::Publisher twist_pub;
ros::Subscriber sub;
ros::Subscriber movementSubscriber;
ros::Subscriber poses;
turtlesim::Pose my_pose;
turtlesim::Pose predator_pose;
turtleBrain();
void predatorMovementCallBack(geometry_msgs::Twist twist);
void controlCallBack(const turtlesim::PosePtr& pose);
void setPredatorCallback(std_msgs::Int32 counter);

};


turtleBrain::turtleBrain(){

nh.getParam("/turtle_counter",turtleCounter);
 
twist_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
// predator_pose=nh.advertise<turtlesim::Pose>("predator/pose",1);
poses = nh.subscribe("pose", 5 , &turtleBrain::controlCallBack,this);
sub= nh.subscribe("/predator/specifier", 5, &turtleBrain::setPredatorCallback,this);
movementSubscriber=nh.subscribe("/teleop/cmd_vel",5,&turtleBrain::predatorMovementCallBack,this); 
}

void turtleBrain::controlCallBack(const turtlesim::PosePtr& pose){
  // ROS_ERROR("set param pose turtle_%d", turtleCounter);
  if(imPredator==1){
    predator_pose = *pose;
    nh.setParam("predator_location_x",predator_pose.x);
    nh.setParam("predator_location_y",predator_pose.y);
    nh.setParam("predator_location_theta",predator_pose.theta);
  }else{
    my_pose = *pose;
  }
  
}


void turtleBrain::predatorMovementCallBack(geometry_msgs::Twist twist){
ROS_ERROR("predator move cb %d",imPredator);
if(imPredator==1){
  geometry_msgs::Twist iMove;
  iMove.linear.x=twist.linear.x;
  iMove.angular.z=twist.angular.z;
  twist_pub.publish(iMove);
   }
}


void turtleBrain::setPredatorCallback(std_msgs::Int32 counter){
ROS_ERROR("predator changed %d",counter.data);    
predator=counter.data;
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "Brain");
   turtleBrain turtle_brain=turtleBrain();
   ros::Rate r(10);    
  while (ros::ok())
  {
    // ROS_ERROR("t.c: %d\np: %d ",turtle_brain.turtleCounter,predator);
    if(turtle_brain.turtleCounter==predator){
      //  ROS_ERROR("i'm a predator");
      imPredator=1;
    }else{
      // ROS_ERROR("i'm thinking");
      imPredator=0;
       
        turtle_brain.nh.getParam("/predator_location_x", turtle_brain.predator_pose.x);
        turtle_brain.nh.getParam("/predator_location_y", turtle_brain.predator_pose.y);
        turtle_brain.nh.getParam("/predator_location_theta", turtle_brain.predator_pose.theta);
    
       if(( turtle_brain.my_pose.theta>0 &&  turtle_brain.predator_pose.theta<0) || ( turtle_brain.my_pose.theta<0 &&  turtle_brain.predator_pose.theta>0)){
              turtle_brain.twist_msg.angular.z=0; 
              turtle_brain.twist_msg.linear.x = rand()%5; 
              turtle_brain.twist_pub.publish( turtle_brain.twist_msg);  
      
         }else{
              
              turtle_brain.twist_msg.linear.x = 0;
             int randAngular=rand()%2;
             if(randAngular==0){
                 turtle_brain.twist_msg.angular.z=(double)(M_PI/2) +  turtle_brain.my_pose.theta;
               }else if(randAngular==1){
                   turtle_brain.twist_msg.angular.z=(double)(-(M_PI/2)) +  turtle_brain.my_pose.theta;
         }
             
              turtle_brain.twist_pub.publish(turtle_brain.twist_msg);
              turtle_brain.my_pose.theta=turtle_brain.twist_msg.angular.z;
    
            }
   
        }
   ros::spinOnce();
   r.sleep();     
  }
   
    return 0;
}