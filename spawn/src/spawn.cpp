#include"ros/ros.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/SpawnRequest.h"
#include "turtlesim/SpawnResponse.h"

using namespace std;


int turtle_num=0;

int main(int argc,char ** argv){

    ros::init(argc,argv,"myTurtle");
    ros::NodeHandle nh;
    nh.getParam("turtle_counter",turtle_num);
    turtle_num++;
    nh.setParam("turtle_counter",turtle_num);
    ros::service::waitForService("spawn",20);
    ros::ServiceClient add_turtle = nh.serviceClient<turtlesim::Spawn>("/spawn");
    
    turtlesim::Spawn srv;
    srv.request.x = atof(argv[1]); //added
    srv.request.y = atof(argv[2]); //added
    srv.request.theta = atof(argv[3]);
    srv.request.name=argv[4];
    

    nh.getParam("turtle_counter",turtle_num);
   // ROS_INFO("%d  %s",argc,argv);
    cout<<turtle_num<<endl;
    
    add_turtle.call(srv);
    

}


