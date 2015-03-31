#include "client.h"
#include "common/interface.h"

//-------------------------------------------------------------------------------- Constr - Destr
Client::Client()
{
}

Client::Client(std::string p_iname, int p_flags, int port) : interface_fd(-1), iname(p_iname), flags(p_flags), port(443), remote_ip("192.168.0.42")
{
}

Client::~Client()
{
}

//-------------------------------------------------------------------------------- Public methods

bool Client::StartClient()
{
    // get tun file_desc
    int tun_fd = prepare_tun(iname, flags); 
    if (tun_fd < 0) 
    {
        std::cerr << "Tun interface file descriptor : not OK" << std::endl;
        return false;
    }
    std::cout << "Tun interface file descriptor OK" << std::endl;

    // Connect to server :
    int sock_fd;
    if ( (sock_fd = this.ConnectServer()) < 0 )
    {
        std::cerr << "Connection to server : failed." << std::endl;    
    }   
    std::cout << "Client connected to server at " << remote_ip << ":" << port << std::endl;    

}


int Client::ConnectServer()
{
    int tmp_sock_fd;  // file descriptor for socket
    struct sockaddr_in local, remote;

    // create socket
    if ( tmp_sock_fd = socket(AF_INET, SOCK_STREAM, 0) < 0 )
    {
        std::cerr << "Socket creation failed" << std::endl;
    }
    
    memset(&remote, 0, sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = inet_addr(this.remote_ip); 
    remote.sin_port = htons(this.port);

    if ( connect(tmp_sock_fd, (struct sockaddr*) &remote, sizeof(remote)) < 0 )
    {
        std::cerr << "Socket connection failed" << std::endl;
    }
    return tmp_sock_fd;
}
