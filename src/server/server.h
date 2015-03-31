#ifndef SERVER_H
#define SERVER_H // Server.h


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

#include "../common/interface.h"


class Server
{
public:
    Server();
    Server(char* p_iname, int p_flags, int port);
    ~Server();
    int Listen();
    int SSLConnection();
    int GetTunFD();
    int GetNetFD();
private:
    int tun_fd;
    int net_fd;
    char* iname;
    int flags;
    int port; // listen port
    int optval;
protected:

};
#endif // SERVER_H
