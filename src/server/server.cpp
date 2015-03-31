#include "server.h"
#include "../common/interface.h"

//-------------------------------------------------------------------------------- Constr - Destr
Server::Server()
{
}

Server::Server(char* p_iname, int p_flags, int port)
    : tun_fd(-1), net_fd(-1), iname(p_iname), flags(p_flags), port(port), optval(1)
{
    
    // Prepare the Tunneling Interface
    if ((tun_fd = prepare_tun(iname, flags)) < 0) 
    {
        std::cerr << "ERROR: Preparing the tun interface" << std::endl;
        exit(1);
    }
    std::cout << "Tun interface file descriptor" << std::endl;

    // Prepare the Network Interface
    if ( (net_fd = Listen()) < 0 )
    {
        std::cerr << "ERROR: Listening operation failed" << std::endl;
        exit(1);
    }
    std::cout << "Client connected on port :" << port << std::endl;    

}

Server::~Server()
{
}

//-------------------------------------------------------------------------------- Public methods

int Server::GetTunFD()
{
    return tun_fd;
}

int Server::GetNetFD()
{
    return net_fd;
}


int Server::Listen()
{    
    // Create socket
    int tmp_sock_fd;  // file descriptor for socket
    if ( (tmp_sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    
    // Set socket options
    if(setsockopt(tmp_sock_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval)) < 0) {
        std::cerr << "ERROR: While setting socket options" << std::endl;
        return -1;
    }

    // Initialize acceptation
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local)); // Clean struct
    local.sin_family = AF_INET; // IPv4
    local.sin_addr.s_addr = htonl(INADDR_ANY); // Accept ny address...
    local.sin_port = htons(port); // ... on this port
    
    // Bind
    int err;
    if (err = bind(tmp_sock_fd, (struct sockaddr*) &local, sizeof(local)) < 0) {
        std::cerr << "ERROR: Bind failed" << std::endl;
        return -1;
    }
    
    std::cout << "Waiting for client to connect..." << std::endl;
    // Listen
    if (listen(tmp_sock_fd, 5) < 0) {
        std::cerr << "ERROR: While litening" << std::endl;
        return -1;
    }
    
    // Define remote client
    struct sockaddr_in remote;
    socklen_t remotelen = sizeof(remote);
    memset(&remote, 0, remotelen); // Clean struct
    
    // Wait for connection
    if ((net_fd = accept(tmp_sock_fd, (struct sockaddr*)&remote, &remotelen)) < 0) {
        std::cerr << "ERROR: While waiting for connecction" << std::endl;
        return -1;
    }
    
    return 0;
}
