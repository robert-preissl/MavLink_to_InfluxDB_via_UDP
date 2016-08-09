
#ifndef CONVERT_MAVLINK_TO_STRING
#define CONVERT_MAVLINK_TO_STRING

#include <string>
using namespace std;


string msg_Attitude_CPP(float val, string sendMsg);

string msg_Heart_CPP(float val, string sendMsg);

string msg_Local_position_ned_CPP(float val, string sendMsg);

string msg_Global_position_int_CPP(float val, string sendMsg);

#endif
