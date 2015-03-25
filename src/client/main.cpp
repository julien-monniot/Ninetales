// ---------------------------------------------
//  main.cpp
//
//	Created	 :
//		by 	 : Pierre Godard
//		date : 22/03/2015
//
// ---------------------------------------------

// Inlude project
#include "client.h"

// include system
#include <iostream>
#include <string>

int main( int argc, const char* argv[] )
{
    std::string iname = "tun2";

    std::cout << "Client creation..."<< std::endl;    
    Client clt(iname, (IFF_TUN | IFF_NO_PI));
    clt.ConnectInterface();
    int fd = clt.getFd();
    std::cout << "Client creation [DONE] - File desc = " << fd << std::endl;

    return 0;
}

