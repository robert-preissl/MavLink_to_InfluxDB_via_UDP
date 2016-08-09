
/*
 This program sends some data based on the mavlink protocol to an InfluxDB instance
 via UDP.
 
 I compiled this program sucessfully on Mac OS with the following command
 
 g++ -c convertMavlinkToString.c
 g++ -I kittypilot/ -c udp-server-test.c
 g++ -I kittypilot/ -o udp-server udp-server-test.o convertMavlinkToString.o
 
 some material used from here:
   // create UDP socket, etc.
   https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html
 
   // Create a new MAVLink Message
   http://qgroundcontrol.org/mavlink/create_new_mavlink_message

   // use some example code to communicate to a ground station
   http://qgroundcontrol.org/dev/mavlink_linux_integration_tutorial
 
 */
 
#include "udp-server-test.h"
#include "convertMavlinkToString.h"

void init() { 
	// get my host name
    host = (char*) malloc( sizeof(char) * (HOST_NAME_MAX + 1) ); // new char[HOST_NAME_MAX];
    int returnHN = gethostname(host, HOST_NAME_MAX);
    printf("My hostname: %s\n", host);
    
    // create a UDP socket:
    //   For UDP/IP sockets, we want to specify the IP address family (AF_INET) and datagram
    //   service (SOCK_DGRAM). Since there's only one form of datagram service, there are no
    //   variations of the protocol, so the last argument, protocol, is zero.
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		exit(EXIT_FAILURE);
	}
	
	// look up the address of the server given its name
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "could not obtain address of %s\n", host);
		exit(EXIT_FAILURE);
	}
	
	// ensure that we have a 32-bit IPv4 address
	if(( hp->h_addrtype != AF_INET) || (hp->h_length != 4) ) {
		fprintf(stderr, "Not a 32-bit IPv4 address\n");
		exit(EXIT_FAILURE);
	}
	
	// setup the server's IP address family and port and address
	memset((char*)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(influxUDPPort); // host to network - short : convert a number into a 16-bit network representation. This is commonly used to store a port number into a sockaddr structure. 
	// put the host's address into the server address structure
	memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length); // we are lazy here and just use the first address in the list of hp. 
	
}

// free up memory and close sockets
void end() {
	free(host);
	close(fd);
}

// convert milliseconds to timespec
static void ms2ts(struct timespec *ts, long ms) {
    ts->tv_sec = ms / 1000;
    ts->tv_nsec = (ms % 1000) * 1000000;
}

static void print_ts(unsigned long ms) {
    struct timespec ts;
    ms2ts(&ts, ms);
    printf("%lu milliseconds is %ld seconds and %ld nanoseconds.\n",
           ms, ts.tv_sec, ts.tv_nsec);
}

void sendUDPMsg(string& sendMsg) {
	fprintf(stdout, "sendMsg = %s \n", sendMsg.c_str());
	// send a message to the server
	if (sendto(fd, sendMsg.c_str(), strlen(sendMsg.c_str()), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		fprintf(stderr, "sendTo failed\n");
	} else {
		fprintf(stdout, "sendTo succeeded. sent %lu bytes \n", strlen(sendMsg.c_str()));
	}
}

// http://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
int sendInfluxUDP_CPP(
	float val,
	int nrTimes,
	int frequencyHZ,
	string startMsg,
	function<string (float,string)> func
) {

	struct timespec* req = (timespec*) malloc( sizeof(struct timespec) );
	ms2ts(req, 1000 / frequencyHZ );
	print_ts(1000 / frequencyHZ);
	
	for(int i = 0; i < nrTimes; ++i) {
		val = (i + 3) % 5 + 0.5;
		string sendMsg = func(val, startMsg);
		sendUDPMsg( sendMsg );
		nanosleep(req, NULL);
	}
	
	free(req);
	return 1;
}

int main(int argc, char* argv[])
{

	init();	

	// sending attitude
	float val = 0.5; 
	string msg1 = "attitude,vehicleId=ABC123,pilot=Joe,location=CA ";
	int r1 = sendInfluxUDP_CPP(val, 100, 10, msg1, msg_Attitude_CPP);

	val = 4.5;
	string msg2 = "heartbeat,vehicleId=ABC123,pilot=Joe,location=CA ";
	int r2 = sendInfluxUDP_CPP(val, 100, 10, msg2, msg_Heart_CPP);

	val = 3.5; 
	string msg3 = "Local_position_ned,vehicleId=ABC123,pilot=Joe,location=CA ";
	int r3 = sendInfluxUDP_CPP(val, 100, 10, msg3, msg_Local_position_ned_CPP);

	val = 1.5; 
	string msg4 = "Global_position_int,vehicleId=ABC123,pilot=Joe,location=CA ";
	int r4 = sendInfluxUDP_CPP(val, 100, 10, msg3, msg_Global_position_int_CPP);

    end();
    
}
