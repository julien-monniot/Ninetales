#!/usr/bin/env python3

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

IP_FORWARD_PATH = "/proc/sys/net/ipv4/ip_forward"
VPN_FOLDER = "Ninetale"
VPN_USER = "sslvpn"
VPN_USER_PATH = "/opt/ssl-vpn"

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
        ## TEST
        if (os.system('pacman -Qs bidon')):
            missPackets.append("bidon")
        ## TEST
        return missPackets
    else:
        print("Not an Arch - not able to check automatically for packets")
        missPackets.append("OS_UNKNOWN")
        return missPackets

# check ip forwarding
def checkIpForward():
    print("Activating ip forwarding...")
    activateCmd = "sysctl net.ipv4.ip_forward=1"
    prog = re.compile(r".*1$")
    result = prog.match(os.popen(activateCmd).read())
    if (result):
        return True
    else:
        return False

# Check for a specified user on the system
def checkForUser(username):
    etcPass = os.popen('less /etc/passwd').read()
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
    grCmd = "groupadd "+username
    usrCmd = "useradd -m -d "+homepath+" -c 'SSL VPN User' -g "+username+" "+username
    ret1 = os.system(grCmd)
    ret2 = os.system(usrCmd)
    if ( ret1 == 0 and ret2 == 0 ):
        folderCmd1 = "sudo -u sslvpn mkdir "+VPN_USER_PATH+"/etc"
        folderCmd2 = "sudo -u sslvpn mkdir "+VPN_USER_PATH+"/etc/"+VPN_FOLDER
        if (str(os.popen(folderCmd1)) + str(os.popen(folderCmd2)) == ""):
            return True
    else :
        return False

def keyAndCertGen(path):
    pass


#----------------------------------------#
# - - - - - - - -  SCRIPT - - - - - - - -#
#----------------------------------------#


# ppp, stunnel, route installed ?
print("Packet checking...")
packetList = checkPackets()
if len(packetList) == 0 :
    print("OK - No missing packet")
elif packetList[0] == "OS_UNKNOWN" :
    print("Unable to check for packets due to unsupported OS.\n Script will continue anyway but might fail")
else:
    print("Missing packets :")
    [print(x+"\n") for x in packetList]

# Activate ip forwarding :
if(checkIpForward()):
    print("Ip forwarding activated")
else:
    print("Ip forwarding failed")
    exit(1)

# Is user/group sslvpn present ?
print("User checking...")
if checkForUser(VPN_USER):
    print("User "+VPN_USER+" found.")
else:
    print("Group and user creation")
    if useradd(VPN_USER, VPN_USER_PATH):
        print("User Created")
    else:
        print("Script wasn't able to create user or group - Exiting now")
        exit(1)

# Open SSL Call for key/cert




