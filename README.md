# MavLink_to_InfluxDB_via_UDP
A simple prototype on how to send MavLink style messages to an InfluxDB instance via UDP.

MavLink messages are converted into char arrays / strings to be sent via UDP to InfluxDB. The program sends a few messages like HeartBeat, Attitude, etc. in configurable frequency.
