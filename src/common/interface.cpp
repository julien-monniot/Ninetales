#include "interface.h"

int prepare_tun(char* dev, int flags) {
    std::cout << "Start of ConnectInterface()" << std::endl;
    struct ifreq ifr;
    int fd, err;    
    std::string clonedev = "/dev/net/tun";

    if( (fd = open(clonedev.c_str() , O_RDWR)) < 0 ) 
    {
        std::cerr << "Error when opening tun file" << std::endl;
        return false;
    }

    std::cout << "File " << clonedev << " opened" << std::endl;

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = flags;
    
    if (sizeof(iname.c_str()) > IFNAMSIZ)
    {
        std::cerr << str << std::endl;
    }
    else 
    {
        snprintf(ifr.ifr_name, IFNAMSIZ,"%s",  iname.c_str());
    }

    std::cout << "Ifr flag and name filled" << std::endl;
    
    if( (err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0 ) 
    {
        std::cerr << "Error when using ioctl TUNSETIFF" << std::endl;
        close(fd);
        return -1;
    }
    //strcpy(dev, ifr.ifr_name);
    
    std::cout << "Iotcl ok" << std::endl;

    // store fd value in member variable
    return fd;
}

int cread(int fd, char *buf, int n)
{

    int nread;

    if((nread=read(fd, buf, n)) < 0)
    {
        perror("Reading data");
        exit(1);
    }
    return nread;
}

int cwrite(int fd, char *buf, int n)
{

    int nwrite;

    if((nwrite=write(fd, buf, n)) < 0)
    {
        perror("Writing data");
        exit(1);
    }
    return nwrite;
}

int read_n(int fd, char *buf, int n)
{

    int nread, left = n;

    while(left > 0)
    {
        if ((nread = cread(fd, buf, left)) == 0)
        {
            return 0 ;      
        }else
        {
            left -= nread;
            buf += nread;
        }
    }
    return n;  
}
