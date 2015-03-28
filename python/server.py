##########################################
#                                        #
#   Script Server for pppd/stunnel VPN   #
#   created : 28/03/15                   #
#   author : Julien M                    #
#                                        #
##########################################

import os
import re

# CST

VPN_USER = "sslvpn"



# Functions

# Check packet requirements :
# returns a list :
# - of missing packets (so an empty list means everything is ok)
# - of a single item stating that os is not supported and the
#   script can't find which packets are installed
def checkPackets():
    # Regex check on the system :
    osversion = (os.popen('uname -r')).read()
    prog = re.compile(r".*(arch).*", re.IGNORECASE)
    result = prog.match(osversion)
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

# Check for a specified user on the system
def checkForUser(username):
    etcPass = os.popen('less /etc/passwd')
    regex = "^"+username+":.*"
    prog = re.compile(regex, re.IGNORECASE)
    result = prog.match(etcPass)
    if (result):
        return True
    else:
        return False


# Add user with specified username and homepath
# Note : will prompt for user password as sudo is used, unless visudo is configured
def useradd(username, homepath):
    grCmd = "sudo groupadd "+username
    usrCmd = "sudo useradd -m -d "+homepath+" -c 'SSL VPN User' -g "+username+" "+username
    ret1 = os.system(grCmd)
    ret2 = os.system(usrCmd)
    if(ret1 == 0 && ret2 == 0):
        return True
    else :
        return False


## - - - - - - - -  SCRIPT - - - - - - - -

# Check prerequisites :

## ppp, stunnel, route installed ?
print("Packet checking...")
packetList = checkPackets()
if len(packetList) == 0 :
    print("OK - No missing packet")
else if packetList[0] == "OS_UNKNOWN" :
    print("Unable to check for packets due to unsupported OS.\n Script will continue anyway but might fail"
else :
    print("Missing packets :")
    [print(x+"\n") for x in packetList]

## Is user/group sslvpn present ?
    if checkForUser(VPN_USER):

    else:
        print("User creation failed")
        exit(1)

