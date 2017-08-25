#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>

#include <string>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "quaternion.h"
#include "xbee/device.h"
#include "xbee/serial.h"
#include "parse_serial_args.h"


float vx,vy,theta,omega;
Vec3 tarLoc;
Vec3 tarAtt;
Vec3 loc;
Vec3 att;
xbee_dev_t xbee;
xbee_serial_t serial_port;

void sendMessage(){
  uint8_t toSend[4*sizeof(float)];
  int loc=0;
  vx=3.3;
  vy=4.2;
  theta=10;
  omega=91.1;
  memcpy(&toSend+(sizeof(float)*loc++),&vx,sizeof(float));
  //std::cout<<""<<*((float*)&vx)<<"\n";
  std::cout<<""<<*((float*)&toSend)<<"\n";
  memcpy(&toSend+1,&vy,sizeof(vy));
  std::cout<<""<<*((float*)&toSend+)<<"\n";
  memcpy(&toSend+1,&theta,sizeof(float));
  std::cout<<""<<*((float*)&toSend)<<"\n";
  memcpy(&toSend,&omega,sizeof(float));
  std::cout<<""<<*((float*)&toSend)<<"\n";
  float check[4];
  xbee_ser_write(&serial_port,toSend,sizeof toSend);
  ROS_INFO("Finished send message\n");
  for(int i =0;i<4;i++){
    // memcpy(&check+i,&toSend+(sizeof(float)*i),sizeof(float));
    // for(int j=0;j<4;j++){
    //   std::cout<<""<<check[j]<<"\n";
    // }
    std::cout<<""<<(&toSend+(4*i))<<"\n";
  }
  time_t  startTime,currTime;
  time(&startTime);//seconds
  bool timeout = false;
  while ( false ){//!radio.available()
    time(&currTime);
    if ((currTime-startTime) > 10 ){//timeout after 10 seconds
        timeout = true;
        break;
    }
  }
  if ( timeout ){
    //TODO: fill this in lol
    // else{
  //   if (radio.available()){
  //
  //     for(int i = 0; i<4; i++){
  //       char log_msg [50];
  //       float got_time;
  //       radio.read( &got_time, sizeof(float) );
  //     }
  //   }
  // }

  }
}

void messageCallback( geometry_msgs::TransformStamped t){
  //const geometry_msgs::TransformStamped *t = &transform;
  std::string a =  t.header.frame_id;
  //Set target
  //Vec4 x;
  Vec4 quat;
  if(a=="tar"){
    tarLoc.v[0] = t.transform.translation.x;
    tarLoc.v[1] = t.transform.translation.y;
    tarLoc.v[2] = t.transform.translation.z;
    quat.v[0] = t.transform.rotation.w;
    quat.v[1] = t.transform.rotation.x;
    quat.v[2] = t.transform.rotation.y;
    quat.v[3] = t.transform.rotation.z;
    tarAtt = Quat2RPY(quat);
  }
  else{
    loc.v[0] = t.transform.translation.x;
    loc.v[1] = t.transform.translation.y;
    loc.v[2] = t.transform.translation.z;
    quat.v[0] = t.transform.rotation.w;
    quat.v[1] = t.transform.rotation.x;
    quat.v[2] = t.transform.rotation.y;
    quat.v[3] = t.transform.rotation.z;
    att = Quat2RPY(quat);
  }
  //edit formulas!
  vx = (float)(tarLoc.v[0] - loc.v[0]);

  vy = (float)(tarLoc.v[1] - loc.v[1]);

  theta = (float)att.v[2];//yaw

  omega  = (float)(tarAtt.v[2]-att.v[2]);

  sendMessage();

}


int main(int argc, char **argv){
  
  parse_serial_arguments(argc,argv,&serial_port);
 //  if (xbee_dev_init( &xbee, &serial_port, NULL, NULL))
	// {
	// 	printf( "Failed to initialize device.\n");
	// 	return 0;
	// }
  xbee_ser_open(&serial_port,9600);
  ros::init(argc,argv,"omnibot_throttle");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/vicon/omnibot",1000,messageCallback);
  ros::spin();
  

}
