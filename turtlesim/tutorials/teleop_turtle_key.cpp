#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <exception>
#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71
#define KEYCODE_W 0x77
#define KEYCODE_E 0x65

using namespace std;


int counter=0; 
class TeleopTurtle
{
public:
  TeleopTurtle();
  void keyLoop();
  void controlCallBack1(const turtlesim::PosePtr& pose);
  void controlCallBack2(const turtlesim::PosePtr& pose);
  void controlCallBack3(const turtlesim::PosePtr& pose);
  void controlCallBack4(const turtlesim::PosePtr& pose);
  void controlCallBack5(const turtlesim::PosePtr& pose);
  

private:
  
  ros::NodeHandle nh_;
  ros::NodeHandle nhSub_;
  ros::Publisher twist_pub_[5];
  bool flag[5]; 
  double linear_, angular_, l_scale_, a_scale_;
  //ros::Publisher selfControl[5];
  ros::Subscriber receiveControl[5];
  turtlesim::Pose positions[5];
  
};

TeleopTurtle::TeleopTurtle():
  linear_(0),
  angular_(0),
  l_scale_(2.0),
  a_scale_(2.0)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

 
  twist_pub_[0] = nh_.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);
  twist_pub_[1] = nh_.advertise<geometry_msgs::Twist>("turtle3/cmd_vel", 1);
  twist_pub_[2] = nh_.advertise<geometry_msgs::Twist>("turtle4/cmd_vel", 1);
  twist_pub_[3] = nh_.advertise<geometry_msgs::Twist>("turtle5/cmd_vel", 1);
  twist_pub_[4] = nh_.advertise<geometry_msgs::Twist>("turtle6/cmd_vel", 1);


  // selfControl[0] = nh_.advertise<turtlesim::Pose>("turtle2/pose", 1);
  // selfControl[1] = nh_.advertise<turtlesim::Pose>("turtle3/pose", 1);
  // selfControl[2] = nh_.advertise<turtlesim::Pose>("turtle4/pose", 1);
  // selfControl[3] = nh_.advertise<turtlesim::Pose>("turtle5/pose", 1);
  // selfControl[4] = nh_.advertise<turtlesim::Pose>("turtle6/pose", 1);

  receiveControl[0] = nh_.subscribe("turtle2/pose", 5 , &TeleopTurtle::controlCallBack1,this);
  receiveControl[1] = nh_.subscribe("turtle3/pose",5 , &TeleopTurtle::controlCallBack2,this);
  receiveControl[2]=  nh_.subscribe("turtle4/pose", 5 , &TeleopTurtle::controlCallBack3,this);
  receiveControl[3] = nh_.subscribe("turtle5/pose", 5 ,&TeleopTurtle::controlCallBack4,this);
  receiveControl[4] = nh_.subscribe("turtle6/pose", 5 , &TeleopTurtle::controlCallBack5,this);
  

}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}
void TeleopTurtle::controlCallBack1(const turtlesim::PosePtr& pose){
  // geometry_msgs::Twist move;
  // //twist.angular.z = pose->angular_velocity;
  // move.angular.z = -(pose->angular_velocity);
  // for(int i=0;i<5;i++){
  //   if(flag[i]==0){
  //   twist_pub_[i].publish(move);
  //   }
  // }
  positions[0]=(*pose);
  ROS_INFO("TWIST ghfhgUBLISHED");
  cout<<positions[0].angular_velocity<<endl;
 // twist1.angular.z= -(positions[counter]->angular_velocity);
  //return;
}
void TeleopTurtle::controlCallBack2(const turtlesim::PosePtr& pose){
  positions[1]=(*pose);
  
  // ROS_ERROR(positions[1]->x);
  ROS_INFO("TWIST ghfhgUBLISHED");
  cout<<positions[1].angular_velocity<<endl;
 // twist1.angular.z= -(positions[counter]->angular_velocity);
//return;
}
void TeleopTurtle::controlCallBack3(const turtlesim::PosePtr& pose){
  positions[2]=(*pose);
  ROS_INFO("TWIST ghfhgUBLISHED");
  cout<<positions[2].angular_velocity<<endl;
 // twist1.angular.z= -(positions[counter]->angular_velocity);
  // ROS_ERROR(positions[2]->x);
  //return;
}
void TeleopTurtle::controlCallBack4(const turtlesim::PosePtr& pose){
  positions[3]=(*pose);
  ROS_INFO("TWIST ghfhgUBLISHED");
  cout<<positions[3].angular_velocity<<endl;
  //twist1.angular.z= -(positions[counter]->angular_velocity);
  // ROS_ERROR(positions[3]->x);
//return;
}
void TeleopTurtle::controlCallBack5(const turtlesim::PosePtr& pose){
  positions[4]=(*pose);
  ROS_INFO("5esfgh");
  cout<<positions[4].angular_velocity<<endl;
  //twist1.angular.z= -(positions[counter]->angular_velocity);
 //  ROS_ERROR(positions[4]->x);
//return;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_turtle");
  TeleopTurtle teleop_turtle;

  signal(SIGINT,quit);
try{
  teleop_turtle.keyLoop();}
    catch(exception& ourerror){
           cout<<ourerror.what();

      };


  return(0);
}


void TeleopTurtle::keyLoop()
{
  char c;
  bool dirty=false;


  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the turtle.");


  for(;;)
  {
    // get the next event from the keyboard  
        ROS_INFO("i am waiting \n");

    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    linear_=angular_=0;
    ROS_INFO("i am running \n");
    ROS_ERROR("value: 0x%02X\n", c);
    // cout<<std :: hex<<(int)c<<endl;
    switch(c)
    {
      case KEYCODE_L:
        ROS_DEBUG("LEFT");
        angular_ = 1.0;
        dirty = true;
        break;
      case KEYCODE_R:
        ROS_DEBUG("RIGHT");
        angular_ = -1.0;
        dirty = true;
        break;
      case KEYCODE_U:
        ROS_DEBUG("UP");
        linear_ = 1.0;
        dirty = true;
        break;
      case KEYCODE_D:
        ROS_DEBUG("DOWN");
        linear_ = -1.0;
        dirty = true;
        break;
        case KEYCODE_E:
        counter++;
        if(counter > 4){
          counter=0;
        }
        break;
        case KEYCODE_W:
        counter--;
        if(counter < 0){
        counter=4;
        }
        break;
    }
   

    geometry_msgs::Twist twist;
    geometry_msgs::Twist twist1;
    twist.angular.z = a_scale_*angular_;
    twist.linear.x = l_scale_*linear_;
    if(dirty ==true)
    {
      for(int i=0 ;i<5 ; i++){
       flag[i]=0;
      }
      twist_pub_[counter].publish(twist);
      ROS_INFO("TWIST PUBLISHED");
      flag[counter]=1; 
       try {
      twist1.linear.x= -((float)(positions[counter].angular_velocity));}
      catch(exception& ourerror){
           cout<<ourerror.what();

      };
      twist1.linear.y=0;
      twist1.linear.z=0;

      twist1.angular.x=0;
      twist1.angular.y=0;
      twist1.angular.z=0;
      for(int i=0 ;i<5 ; i++){
       if(flag[i]==0){
         twist_pub_[i].publish(twist1);
               }
      }
     
      dirty=false;
      ROS_INFO("before spin");
      ros::spinOnce();   
    } 
      
    }
  }


  //return;
//}



