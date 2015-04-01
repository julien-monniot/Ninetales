#ifndef INTERFACE_H
#define INTERFACE_H // Interface_H

#include <iostream>
#include <sys/ioctl.h> 
#include <net/if.h> 
#include <stdio.h> 
#include <string.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include <openssl/bio.h> 
#include <openssl/ssl.h> 
#include <openssl/err.h>
#include <openssl/rand.h>

#define BUFSIZE 2000


extern int prepare_tun(char *dev, int flags);
extern int cread(int fd, char *buf, int n);
extern int cwrite(int fd, char *buf, int n);
extern int read_n(int fd, char *buf, int n);
extern int run(int net_fd, int tap_fd);
extern SSL_CTX* initClientCTX();
extern SSL_CTX* initServerCTX();
extern void loadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
extern int SSL_run(SSL* ssl_net, int tun_fd);


#endif // Interface_H
