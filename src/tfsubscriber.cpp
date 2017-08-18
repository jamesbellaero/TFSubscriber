#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>

#include <cstring>
#include "quaternion.h"
#include "device.h"

ros::NodeHandle nh;
float vx,vy,theta,thetaROC;
Vec3 tarLoc;
Vec3 tarAtt;
Vec3 loc;
Vec3 att;


void sendMessage(){
  radio.write( &vx, sizeof(float) );
  radio.write( &vy, sizeof(float) );
  radio.write( &theta, sizeof(float) );
  radio.write( &thetaROC, sizeof(float) );
  radio.startListening();

  unsigned long started_waiting_at = micros();
  boolean timeout = false;
  while ( ! radio.available() ){
    if (micros() - started_waiting_at > 200000 ){
        timeout = true;
        break;
    }
  }
  if ( timeout ){

  }
  else{
    if (radio.available()){

      for(int i = 0; i<4; i++){
        char log_msg [50];
        float got_time;
        radio.read( &got_time, sizeof(float) );

        delay(3);
     }
    }
  }
}
void messageCallback( const geometry_msgs::TransformStamped& t){

  string a =  t.header.frame_id;
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
    logmsg(t.transform.translation);
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

  thetaROC  = (float)(tarAtt.v[2]-att.v[2]);

  sendMessage();

}
void logmsg(float a){
  char log_msg[50];
  float temp = a;
  int temp1 = (temp - (int)temp) * 100;
  sprintf(log_msg, "Float = %0d.%d", (int)temp, temp1);
  nh.loginfo(log_msg);

}

int main(int argc, char **argv){
  ros::init(argc,argv,"omnibot_throttle");
  ros::Subscriber sub = nh.subscribe("/vicon/omnibot", 1000, messageCallback);
  ros::spinOnce();
}
