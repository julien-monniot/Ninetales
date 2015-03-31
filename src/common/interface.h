#ifndef CLIENT_H
#define CLIENT_H // Client.h

#include <iostream>
#include <sys/ioctl.h> 
#include <net/if.h>  

int prepare_tun(char *dev, int flags);
int cread(int fd, char *buf, int n);
int cwrite(int fd, char *buf, int n);
int read_n(int fd, char *buf, int n);

#endif // CLIENT_H
