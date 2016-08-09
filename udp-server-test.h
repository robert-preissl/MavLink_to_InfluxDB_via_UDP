
#ifndef UDP_SERVER_TEST
#define UDP_SERVER_TEST

#include <string>
#include <functional>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <netdb.h>
#include <sys/time.h>
#include <time.h>

/* This assumes you have the mavlink headers on your include path
 or in the same folder as this source file */
#include <mavlink.h>

using namespace std;

#define BUFFER_LENGTH 2041 // minimum buffer size that can be used with qnx (I don't know why)
#define HOST_NAME_MAX 1000

uint64_t microsSinceEpoch();

struct hostent *hp; /* host information */
struct sockaddr_in servaddr; /* server address */

const int influxUDPPort = 8089;
char* host;
int fd;


void init();
void freeMemory();

void sendUDPMsg(string& sendMsg);
int sendInfluxUDP();
int sendInfluxUDP_CPP(float val, int nrTimes, int frequencyHZ, string startMsg, std::function<string (float,string)> func);

string msg_Attitude_CPP(float val, string sendMsg);


// this function will send some Mavlink messages (status, heartbeat, local postion, attitude, etc.)
//  to Qgroundcontrol and receive a Heartbeat back from Qgroundcontrol
void sendRecvMessagetoQgroundcontrol(int argc, char* argv[]);

#endif


/*
To write data send a POST request to the /write endpoint. The example below writes a single point
 to the mydb database. The data consist of:
 - the measurement cpu_load_short

 - the tag keys host and region with // indexed!!
 - the tag values server01 and us-west  //  Both tag keys and tag values are stored as strings and record metadata
 
 - the field key value with a field value of 0.64, and // not indexed. if search for a certain value, scan through all data required
 - the timestamp 1434055562000000000.

'cpu_load_short,host=server01,region=us-west value=0.64 1434055562000000000'

*/

/*
The next two columns, called butterflies and honeybees, are fields. Fields are made up of
 field keys and field values. Field keys (butterflies and honeybees) are strings and they 
 store metadata; the field key butterflies tells us that the field values 12-7 refer to
  butterflies and the field key honeybees tells us that the field values 23-22 refer to,
   well, honeybees.

Field values are your data; they can be strings, floats, integers, or booleans, and, because
 InfluxDB is a time series database, a field value is always associated with a timestamp.
  The field values in the sample data are:
  
Fields are a required piece of InfluxDB’s data structure - you cannot have data in InfluxDB
 without fields. It’s also important to note that fields are not indexed. Queries that use
  field values as filters must scan all values that match the other conditions in the query.
   As a result, those queries are not performant relative to queries on tags (more on tags below).
 In general, fields should not contain commonly-queried metadata.

The last two columns in the sample data, called location and scientist, are tags. Tags are made 
up of tag keys and tag values. Both tag keys and tag values are stored as strings and record
 metadata. The tag keys in the sample data are location and scientist. The tag key location has
  two tag values: 1 and 2. The tag key scientist also has two tag values: langstroth and perpetua.  
  
*/

/*
	to get counts: SELECT COUNT(value) from temperature;
	if insert looks like this:
		curl -i -XPOST 'http://localhost:8086/write?db=sensor' --data-binary 'temperature,node=MyFridge,location=2ndShelf,unit=Celcius value=5.40'
*/
