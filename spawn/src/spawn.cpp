#include"ros/ros.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/SpawnRequest.h"
#include "turtlesim/SpawnResponse.h"

using namespace std;

ros::Publisher pub;



int main(int argc,char ** argv){

    ros::init(argc,argv,"myTurtle");
    ros::NodeHandle nh;
    int turtle_name=0;
    nh.getParam("turtle_name",turtle_name);
    nh.setParam("turtle_name",turtle_name++);
    ros::service::waitForService("spawn",20);
    ros::ServiceClient add_turtle = nh.serviceClient<turtlesim::Spawn>("spawn");
    

    turtlesim::Spawn srv;
    srv.request.x = atof(argv[1]); //added
    srv.request.y = atof(argv[2]); //added
    srv.request.theta = atof(argv[3]);
    srv.request.name=argv[4];
    
    ROS_INFO("%d  %s",argc,argv);
   // cout<<turtle_name<<endl;
    
    add_turtle.call(srv);
    

}


