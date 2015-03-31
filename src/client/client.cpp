#include "client.h"
#include "../common/interface.h"

//-------------------------------------------------------------------------------- Constr - Destr
Client::Client()
{
}

Client::Client(char* p_iname, int p_flags, int port, char* ip)
    : tun_fd(-1), net_fd(-1), iname(p_iname), flags(p_flags), port(port), remote_ip(ip)
{
    
    // Prepare the Tunneling Interface
    if ((tun_fd = prepare_tun(iname, flags)) < 0) 
    {
        std::cerr << "ERROR: Preparing the tun interface" << std::endl;
        exit(1);
    }
    std::cout << "Tun interface file descriptor" << std::endl;

    // Prepare the Network Interface
    if ( (net_fd = ConnectServer()) < 0 )
    {
        std::cerr << "ERROR: Connection to server failed" << std::endl;  
        exit(1);  
    }
    std::cout << "Client connected to server at " << remote_ip << ":" << port << std::endl;    

    run(net_fd, tun_fd);
}

Client::~Client()
{
}

//-------------------------------------------------------------------------------- Public methods

int Client::GetTunFD()
{
    return tun_fd;
}

int Client::GetNetFD()
{
    return net_fd;
}

int Client::ConnectServer()
{
    
    // Create socket
    int tmp_sock_fd;  // file descriptor for socket
    if ( (tmp_sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    
    // Initialize connection
    struct sockaddr_in remote;
    memset(&remote, 0, sizeof(remote)); // Clean struct
    remote.sin_family = AF_INET; // IPv4
    remote.sin_addr.s_addr = inet_addr(remote_ip); // IP address
    remote.sin_port = htons(port); // Port

    // Connect
    if ( connect(tmp_sock_fd, (struct sockaddr*) &remote, sizeof(remote)) < 0 )
    {
        std::cerr << "Socket connection failed" << std::endl;
        return -1;
    }
    
    return tmp_sock_fd;
}

int Client::SSLConnection()
{
    SSL_CTX* ctx = initCTX();
    SSL* ssl_net = SSL_new(ctx);
    SSL* ssl_tun = SSL_new(ctx);
    SSL_set_fd(ssl_net, net_fd);
    SSL_set_fd(ssl_tun, tun_fd);
    if ( (SSL_connect(ssl_tun) < 0) || (SSL_connect(ssl_net) < 0) )
    {
        std::cerr << "Cannot connect SSL socket" << std::endl;
        return -1;
    }
    std::cerr << "SSL TUN socket: " << SSL_get_cipher(ssl_tun) << std::endl;
    std::cerr << "SSL NET socket: " << SSL_get_cipher(ssl_net) << std::endl;
    
    return 0;
}
