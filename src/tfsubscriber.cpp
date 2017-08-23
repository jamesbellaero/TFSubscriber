#include <string>
#include <math.h>
#include <stdio.h>

#include "quaternion.h"
#include "xbee/device.h"
#include "xbee/serial.h"
#include "parse_serial_args.h"

float vx,vy,theta,thetaROC;
Vec3 tarLoc;
Vec3 tarAtt;
Vec3 loc;
Vec3 att;
xbee_dev_t xbee;

void sendMessage(){
//  radio.write( &vx, sizeof(float) );
//  radio.write( &vy, sizeof(float) );
//  radio.write( &theta, sizeof(float) );
//  radio.write( &thetaROC, sizeof(float) );
//  radio.startListening();

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
  }
  // else{
  //   if (radio.available()){
  //
  //     for(int i = 0; i<4; i++){
  //       char log_msg [50];
  //       float got_time;
  //       radio.read( &got_time, sizeof(float) );
  //    }
  //   }

  }

// void messageCallback( const geometry_msgs::TransformStamped& t){
//
//   std::string a =  t.header.frame_id;
//   //Set target
//   //Vec4 x;
//   Vec4 quat;
//   if(a=="tar"){
//     tarLoc.v[0] = t.transform.translation.x;
//     tarLoc.v[1] = t.transform.translation.y;
//     tarLoc.v[2] = t.transform.translation.z;
//     quat.v[0] = t.transform.rotation.w;
//     quat.v[1] = t.transform.rotation.x;
//     quat.v[2] = t.transform.rotation.y;
//     quat.v[3] = t.transform.rotation.z;
//     tarAtt = Quat2RPY(quat);
//   }
//   else{
//     loc.v[0] = t.transform.translation.x;
//     loc.v[1] = t.transform.translation.y;
//     loc.v[2] = t.transform.translation.z;
//     quat.v[0] = t.transform.rotation.w;
//     quat.v[1] = t.transform.rotation.x;
//     quat.v[2] = t.transform.rotation.y;
//     quat.v[3] = t.transform.rotation.z;
//     att = Quat2RPY(quat);
//   }
//   //edit formulas!
//   vx = (float)(tarLoc.v[0] - loc.v[0]);
//
//   vy = (float)(tarLoc.v[1] - loc.v[1]);
//
//   theta = (float)att.v[2];//yaw
//
//   thetaROC  = (float)(tarAtt.v[2]-att.v[2]);
//
//   sendMessage();
//
// }


int main(int argc, char **argv){
  xbee_serial_t serial_port;
  parse_serial_arguments(argc,argv,&serial_port);
  if (xbee_dev_init( &xbee, &serial_port, NULL, NULL))
	{
		printf( "Failed to initialize device.\n");
		return 0;
	}
  uint8_t toSend[]="hello";
  xbee_ser_write(&serial_port,toSend,sizeof toSend);
}
