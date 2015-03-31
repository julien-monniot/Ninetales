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
    
    if (sizeof(dev) > IFNAMSIZ)
    {
        std::cerr << "Error : interface name too long" << std::endl;
    }
    else 
    {
        snprintf(ifr.ifr_name, IFNAMSIZ,"%s", dev);
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
            return 0;      
        }else
        {
            left -= nread;
            buf += nread;
        }
    }
    return n;  
}

int run(int net_fd, int tun_fd)
{
    char buffer[BUFSIZE];
    int maxfd = (tun_fd > net_fd)? tun_fd : net_fd;
    

    for(;;) {
        uint16_t nread;
        uint16_t nwrite;
        uint16_t plength;
        (void) nwrite;
        int ret;
        fd_set rd_set;

        FD_ZERO(&rd_set);
        FD_SET(tun_fd, &rd_set);
        FD_SET(net_fd, &rd_set);

        // Check the file descriptors
        ret = select(maxfd + 1, &rd_set, NULL, NULL, NULL);

        //    Interruption
        if (ret < 0 && errno == EINTR){
            std::cerr << "WARNING: Interruption" << std::endl;
            continue; // Try again
        }
        //    File descriptor invalid
        else if (ret < 0 && errno == EBADF){
            std::cerr << "ERROR: File descriptor invalid" << std::endl;
            return -1;
        }
        //    Other error
        else if (ret < 0) {
            std::cerr << "ERROR: Select()" << std::endl;
            return -1;
        }

        // There is data from tun to send to the network
        if(FD_ISSET(tun_fd, &rd_set)) {

            nread = cread(tun_fd, buffer, BUFSIZE);
            plength = htons(nread);
            nwrite = cwrite(net_fd, (char *)&plength, sizeof(plength));
            nwrite = cwrite(net_fd, buffer, nread);
            std::cout << "TUN -> NET: " << buffer << std::endl;
        }

        // There is data from the network to send to tun
        if(FD_ISSET(net_fd, &rd_set)) {

            // The peer stopped the connection
            nread = read_n(net_fd, (char *)&plength, sizeof(plength));
            if(nread == 0) {
                break;
            }

            nread = read_n(net_fd, buffer, ntohs(plength));
            nwrite = cwrite(tun_fd, buffer, nread);
            std::cout << "NET -> TUN: " << buffer << std::endl;
        }
    }
    
    return 0;
}

