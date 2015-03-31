#ifndef CLIENT_H
#define CLIENT_H // Client.h


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <stdarg.h>



class Client
{
public:
    Client();
    Client(char* p_iname, int p_flags, int port, char* ip);
    ~Client();
    int ConnectServer();
    int GetTunFD();
    int GetNetFD();
private:
    int tun_fd;
    int net_fd;
    char* iname;
    int flags;
    int port;                       // connection port
    char* remote_ip;            /* dotted quad IP string */
protected:

};
#endif // CLIENT_H
