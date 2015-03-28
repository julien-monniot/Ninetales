##########################################
#                                        #
#   Server for pppd/stunnel VPN          #
#   created : 28/03/15                   #
#   author : Julien M                    #
#                                        #
##########################################

import os
import re

class Server:

    def __init__(self, vpn_name, vpn_user, vpn_user_path):
        # Member variable
        self.vpn_name = vpn_name
        self.vpn_user = vpn_user
        self.vpn_user_path = vpn_user_path

    def initialize(self):
        # ppp, stunnel, route installed ?
        print("Packet checking...")
        packetList = checkPackets()
        if len(packetList) == 0 :
	        print("     OK - No missing packet.")
        elif packetList[0] == "OS_UNKNOWN" :
	        print("     Unable to check for packets due to unsupported OS.\n Script will continue anyway but might fail.")
        else:
	        print("     Missing packets :")
	        [print("\t\t"+x+"\n") for x in packetList]
	        return False # Missing packets, impossible to continue

        # Activate ip forwarding :
        print("Ip forwarding...")
        if(checkIpForward()):
	        print("     Ip forwarding activated.")
        else:
	        print("     Ip forwarding could not be set.")
	        return False     # Ip forwarding could not be set

        # Is user/group sslvpn present ?
        print("Checking user "+self.vpn_user+"...")
        if checkForUser(self.vpn_user):
	        print("     User "+self.vpn_user+" found.")
        else:
	        print("     User "+self.vpn_user+" not found")
	        print("     Group and user creation")
	        if useradd():
		        print("User Created")
	        else:
		        print("Wasn't able to create user or group.")
		        return False # Group/user creation failed

        #   If we've got so far, init is ok
        return True



    # Class Methods :

    # Check packet requirements :
    # returns a list :
    # - of missing packets (so an empty list means everything is ok)
    # - of a single item stating that os is not supported and the
    #   script can't find which packets are installed
    def checkPackets():
        # Regex check in the system :
        result = re.search(r".*(arch).*", os.popen('uname -r').read(), re.IGNORECASE)
        missPackets = []
        # Finding packets :
        if (result):
	        print("Arch system  matched - checking required packets.")
	        if (os.system('pacman -Qs ppp >/dev/null')) == 1:
		        #print("PPP not installed")
		        missPackets.append("ppp")
	        if (os.system('pacman -Qs stunnel >/dev/null')) == 1:
		        #print("sTunnel not installed")
		        missPackets.append("stunnel")
	        if (os.system('pacman -Qs net-tools >/dev/null')) == 1:
		        #print("net-tools not installed")
		        missPackets.append("net-tools")
		        return missPackets
        else:
	        print("Not an Arch - not able to check automatically for packets")
	        missPackets.append("OS_UNKNOWN")
	        return missPackets

    # check ip forwarding
    def checkIpForward():
        print("Activating ip forwarding...")
        result = re.search(r".*1$", os.popen("sysctl net.ipv4.ip_forward=1").read())
        if (result):
	        return True
        else:
	        return False

    # Check for a specified user on the system
    def checkForUser(self):
        result = re.search(r".*"+self.username+":.*", os.popen('less /etc/passwd').read())
        if (result):
	        return True
        else:
	        return False

    # Add user with specified username and homepath
    # Note : will prompt for user password as sudo is used, unless visudo is configured
    def addUser(self):
        grCmd = "groupadd "+self.vpn_user
        usrCmd = "useradd -m -d "+self.vpn_user_path+" -c 'SSL VPN User' -g "+self.vpn_user+" "+self.vpn_user
        ret1 = os.system(grCmd)
        ret2 = os.system(usrCmd)
        if ( ret1 == 0 and ret2 == 0 ):
	        folderCmd1 = "sudo -u sslvpn mkdir "+self.vpn_user_path+"/etc"
	        folderCmd2 = "sudo -u sslvpn mkdir "+self.vpn_user_path+"/etc/"+self.vpn_name
	        if (os.popen(folderCmd1).read() + os.popen(folderCmd2).read() == ""):
		        return True	# mkdir failed
	        else:
		        return False
        return False;	# User/group add failed



