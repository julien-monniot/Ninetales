#include "client.h"

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

SSL* Client::SSLConnection()
{
    
    SSL_CTX* ctx_net = initClientCTX();
    loadCertificates(ctx_net, "./bin/client.pem", "./bin/client.pem");
    SSL* ssl_net = SSL_new(ctx_net);
    SSL_set_fd(ssl_net, net_fd);
    std::cout << "Trying to connect SSL..." << std::endl;
    if ( SSL_connect(ssl_net) < 0 )
    {
        std::cerr << "ERROR: Cannot connect SSL socket" << std::endl;
    }
    std::cout << "SSL NET socket connected" << std::endl;
    
    SSL_run(ssl_net, tun_fd);
    
    return 0;
}

void Client::SSLLaunch()
{
    SSL* ssl_net = SSLConnection();
    SSL_run(ssl_net, tun_fd);
}

void Client::Launch()
{
    run(net_fd, tun_fd);
}
