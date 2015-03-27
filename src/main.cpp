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
#include "utils/debugger.h"
#include "utils/utils.h"
#include "utils/conf_files.h"
#include "utils/argsmanager.h"

// include system
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

/*
 * PREREQUISITES:
 *  - Install packages sudo, pppd, stunnel and route
 * 
 * 
 */

int initialize()
{
    DISPLAY("INIT", "Initialization starting...")
    
    //// Allow IP forward (TODO: reset the default value when user specifies it)
    // By default, most of the linux distributions don't allow it.
    // It is required as we will route our packages throught the PPP interface.
    DISPLAY("INIT", "IP Forwarding activation")
    if(system("/usr/bin/echo 1 > /proc/sys/net/ipv4/ip_forward"))
    {
        return EXIT_FAILURE;
    }
    DISPLAY("INIT", " . . . success")
    
    //// Create accounts for VPN user
    // Creation of the users accounts that will use the VPN.
    DISPLAY("INIT", "User VPN account creation")
    if(system("/usr/bin/groups sslvpn >> /dev/null") && system("groupadd sslvpn \
        && /usr/bin/useradd -m -d /opt/ssl-vpn -c \"SSL VPN User\" -g sslvpn \
        sslvpn >> /dev/null"))
    {
        return EXIT_FAILURE;
    }
    DISPLAY("INIT", " . . . success")
    
    //// Set up the VPN user home
    // This will be need in some future steps
    DISPLAY("INIT", "Setting the VPN user home up")
    if(system("/usr/bin/mkdir -p /opt/ssl-vpn/etc/vpn1"))
    {
        return EXIT_FAILURE;
    }
    std::ofstream sslvpn_conf_file;
    std::ofstream stunnel_conf_file;
    sslvpn_conf_file.open("/opt/ssl-vpn/etc/vpn1/sslvpn.cnf");
    stunnel_conf_file.open("/opt/ssl-vpn/etc/stunnel.cnf");
    sslvpn_conf_file << SSLVPN_CONF_TEXT;
    stunnel_conf_file << STUNNEL_CONF_TEXT;
    sslvpn_conf_file.close();
    stunnel_conf_file.close();
    DISPLAY("INIT", " . . . success")
    
    DISPLAY("INIT", "Initialization terminated !")
    
    return EXIT_SUCCESS;
}

int main( int argc, const char* argv[] )
{
    ArgsManager am(argc, argv);
    
    if (am.isError())
    {
        std::cout << am << std::endl;
        return EXIT_FAILURE;
    }
    
    TRACE("Ninetales - Another VPN Program\n")
    
    if (am.count("init") && initialize())
    {
        DISPLAY("INIT", " . . . fail")
        DEBUGERR("A problem occured in the initialization")
        return EXIT_FAILURE;
    }
    
}

