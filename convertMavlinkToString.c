
#include "convertMavlinkToString.h"


/*
HEARTBEAT: 0.811593920291
SYS_STATUS: 3.30693029041
SYSTEM_TIME: 2.91707873096
TERRAIN_REPORT: 2.91703023596
BATTERY_ESSENTIALS: 0
GPS_RAW_INT: 3.30698237426
RAW_IMU: 3.37641331017
SCALED_PRESSURE: 3.37621648245
ATTITUDE: 2.99998437861
LOCAL_POSITION_NED: 3.1040977757
GLOBAL_POSITION_INT: 3.13771375353
RC_CHANNELS_RAW: 3.0415129014
SERVO_OUTPUT_RAW: 3.04150425725
HWSTATUS: 2.91714383913
FLIGHT_TIME: 3.23559196585
MISSION_CURRENT: 3.30702011977
AHRS2: 2.99996884835
JETI_SERIAL: 0
NAV_CONTROLLER_OUTPUT: 3.30696892383
EKF_STATUS_REPORT: 2.91697074628
VFR_HUD: 2.94662104748
COMMAND_ACK: 0.305456802549
AHRS: 2.9171823016
VIBRATION: 2.91696009945
SCALED_IMU2: 3.37623243168
POWER_STATUS: 3.30707902983
*/



/*
typedef struct __mavlink_attitude_t {
 uint32_t time_boot_ms; // < Timestamp (milliseconds since system boot)
 float roll; //< Roll angle (rad, -pi..+pi)
 float pitch; //< Pitch angle (rad, -pi..+pi)
 float yaw; //< Yaw angle (rad, -pi..+pi)
 float rollspeed; //< Roll angular speed (rad/s)
 float pitchspeed; //< Pitch angular speed (rad/s)
 float yawspeed; //< Yaw angular speed (rad/s)
}) mavlink_attitude_t;
*/
string msg_Attitude_CPP(float val, string sendMsg) {
	// "attitude,vehicleId=ABC123,pilot=Joe,location=CA roll=1.2,pitch=2.3,yaw=1.1,rollspeed=12.4,pitchspeed=5.5,yawspeed=23.4";
	sendMsg += "roll="        + to_string(val);
	sendMsg += ",pitch="      + to_string(val);
	sendMsg += ",yaw="        + to_string(val);
	sendMsg += ",rollspeed="  + to_string(val+2);
	sendMsg += ",pitchspeed=" + to_string(val+2);
	sendMsg += ",yawspeed="   + to_string(val+2);				
	return sendMsg;
}

/*
typedef struct __mavlink_heartbeat_t {
 uint32_t custom_mode; 
 uint8_t type; 
 uint8_t autopilot;
 uint8_t base_mode;
 uint8_t system_status;
 uint8_t mavlink_version;
})
*/
string msg_Heart_CPP(float val, string sendMsg) {
	// "heartbeat,vehicleId=ABC123,pilot=Joe,location=CA custom_mode=2,type=3,autopilot=1,base_mode=4,system_status=5,mavlink_version=4";
	sendMsg += "custom_mode="      + to_string(val);
	sendMsg += ",type="            + to_string(val);
	sendMsg += ",autopilot="       + to_string(val);
	sendMsg += ",base_mode="       + to_string(val);
	sendMsg += ",system_status="   + to_string(val);
	sendMsg += ",mavlink_version=" + to_string(val);						
	return sendMsg;
}

/*
typedef struct __mavlink_local_position_ned_t {
 uint32_t time_boot_ms;
 float x;
 float y;
 float z;
 float vx;
 float vy;
 float vz;
}) mavlink_local_position_ned_t;
*/
string msg_Local_position_ned_CPP(float val, string sendMsg) {
	// "Local_position_ned,vehicleId=ABC123,pilot=Joe,location=CA x=2,y=3,z=1,vx=4,vy=5,vz=4";
	sendMsg += "x="   + to_string(val);
	sendMsg += ",y="  + to_string(val);
	sendMsg += ",z="  + to_string(val);
	sendMsg += ",vx=" + to_string(val);
	sendMsg += ",vy=" + to_string(val);
	sendMsg += ",vz=" + to_string(val);				
	return sendMsg;
}

/*
typedef struct __mavlink_global_position_int_t {
 uint32_t time_boot_ms; 
 int32_t lat; 
 int32_t lon; 
 int32_t alt;
 int32_t relative_alt;
 int16_t vx;
 int16_t vy;
 int16_t vz;
 uint16_t hdg;
}) mavlink_global_position_int_t;
*/
string msg_Global_position_int_CPP(float val, string sendMsg) {
	// "Global_position_int,vehicleId=ABC123,pilot=Joe,location=CA ..";
	sendMsg += "lat="           + to_string(val);
	sendMsg += ",lon="          + to_string(val);
	sendMsg += ",alt="          + to_string(val);
	sendMsg += ",relative_alt=" + to_string(val);
	sendMsg += ",vx="           + to_string(val);
	sendMsg += ",vy="           + to_string(val);
	sendMsg += ",vz="           + to_string(val);
	sendMsg += ",hdg="          + to_string(val);					
	return sendMsg;
}


