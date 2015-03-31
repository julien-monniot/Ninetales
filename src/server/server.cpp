#include "server.h"


//-------------------------------------------------------------------------------- Constr - Destr
Server::Server() : interface_fd(-1), iname("vpn-tun"), flags(IFF_TUN | IFF_NO_PI)
{
}

Server::Server(std::string p_iname, int p_flags) : interface_fd(-1), iname(p_iname), flags(p_flags)
{
}

Server::~Server()
{
    
}

//-------------------------------------------------------------------------------- Public methods
bool Server::ConnectInterface()
{ 
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
    
    try 
    {
        if (sizeof(iname.c_str()) > IFNAMSIZ)
        {
            throw new std::string("Erreur : interface name too long");
        } else 
	{
           snprintf(ifr.ifr_name, IFNAMSIZ,"%s",  iname.c_str());
        }
    } 
    catch ( std::string str ) 
    {
        std::cerr << str << std::endl;
        return false;
    }

    std::cout << "Ifr flag and name filled" << std::endl;
    
    if( (err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0 ) 
    {
        std::cerr << "Error when using ioctl TUNSETIFF" << std::endl;
        close(fd);
        return false;
    }
    //strcpy(dev, ifr.ifr_name);
    
    std::cout << "Iotcl ok" << std::endl;

    // store fd value in member variable
    this->interface_fd = fd;
    
    return true;
}

// debug : 
int Server::getFd()
{
    return this->interface_fd;
}


