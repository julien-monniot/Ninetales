#!/usr/bin/env python3

##########################################
#                                        #
#   Launcher for pppd/stunnel VPN        #
#   created : 28/03/15                   #
#   author :                             #
#                                        #
##########################################

import server

VPN_NAME = "Ninetales"
VPN_USER = "sslvpn"
VPN_USER_PATH = "/opt/ssl-vpn"

def laucher():
    server1 = Server(VPN_NAME, VPN_USER, VPN_USER_PATH)
    if server1.Initialize():
        print("Server initialized")
    else:
        print("Error during server init")




if __name__ == '__main__':
    launcher()




