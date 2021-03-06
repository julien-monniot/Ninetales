// ---------------------------------------------
//  main.cpp
//
//	Created	 :
//		by 	 : Pierre Godard
//		date : 22/03/2015
//
// ---------------------------------------------

// Inlude project
#include "client/client.h"
#include "server/server.h"
#include "utils/debugger.h"
#include "utils/utils.h"
#include "utils/conf_files.h"
#include "utils/argsmanager.h"
#include "common/interface.h"

// include system
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

int main( int argc, const char* argv[] )
{
    // Initialize variables
    char* vpn_interface("vpn-tun");
    char* server_ip("10.43.4.145");
    int port = 80;
    bool encryption = true;
    
    ArgsManager am(argc, argv);
    
    if (am.isError())
    {
        std::cout << am << std::endl;
        return EXIT_FAILURE;
    }
    
    TRACE("Ninetales - Another VPN Program\n")
    
    if (am.count("port"))
    {
        port = am["port"].as<int>();
    }
    
    if (am.count("no-encryption"))
    {
        encryption = false;
    }
    
    if (am.count("client"))
    {
        Client client(vpn_interface, (IFF_TUN|IFF_NO_PI), port, server_ip);
        if (encryption)
        {
            client.SSLLaunch();
        }
        else
        {
            client.Launch();
        }
    }
    else if (am.count("server"))
    {
        Server server(vpn_interface, (IFF_TUN|IFF_NO_PI), port);
        if (encryption)
        {
            server.SSLLaunch();
        }
        else
        {
            server.Launch();
        }
    }
}



