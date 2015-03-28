##########################################
#                                        #
#   Server for pppd/stunnel VPN          #
#   created : 28/03/15                   #
#   author : Julien M                    #
#                                        #
##########################################

import os
import re
import subprocess

class Server:

    def __init__(self, vpn_name, vpn_user, vpn_user_path, port, r_ip, l_ip):
        # Member variable
        self.vpn_name = vpn_name
        self.vpn_user = vpn_user
        self.vpn_user_path = vpn_user_path
        self.port = port
        self.local_ip = l_ip
        self.remote_ip = r_ip

    def initialize(self):
        # ppp, stunnel, route installed ?
        print("Packet checking...")
        packetList = self.checkPackets()
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
        if self.checkIpForward():
            print("     Ip forwarding activated.")
        else:
            print("     Ip forwarding could not be set.")
            return False     # Ip forwarding could not be set

        # Is user/group sslvpn present ?
        print("Checking user "+self.vpn_user+"...")
        if self.checkForUser():
            print("     User "+self.vpn_user+" found.")
        else:
            print("     User "+self.vpn_user+" not found")
            print("     Group and user creation")
            if self.useradd():
                print("User Created")
            else:
                print("Wasn't able to create user or group.")
                return False # Group/user creation failed

        # Edit sudoers if necessary :
        print("Checking for '"+self.vpn_user+" ALL=NOPASSWD: /usr/sbin/pppd' in sudoers")
        if self.checkSudoers():
            print("     Sudoers OK")
        else:
            print("     Editing sudoers...")
            if self.editSudoers():
                print("     Sudoers OK")
            else:
                print("     Could not edit sudoers")
                return False

        # Copy certificates and stunnel.conf to /opt/'self.vpn_user'/etc/'self.vpn_name'

        #   If we've got so far, init is ok
        return True

    # method used to start stunnel with
    # "stunnel  /opt/'self.vpn_user'/etc/'self.vpn_name'/stunnel.conf" cmd
    def startTunnel(self):
        pass


    # class utils methods:

    # Check packet requirements :
    # returns a list :
    # - of missing packets (so an empty list means everything is ok)
    # - of a single item stating that os is not supported and the
    #   script can't find which packets are installed
    def checkPackets(self):
        # Regex check in the system :
        result = re.search(r".*(arch).*", os.popen('uname -r').read(), re.IGNORECASE)
        missPackets = []
        # Finding packets :
        if (result):
            print("Arch system  matched - checking required packets.")
            if (os.system('pacman -Qs ppp >/dev/null')) == 1:
                missPackets.append("ppp")
            if (os.system('pacman -Qs stunnel >/dev/null')) == 1:
                missPackets.append("stunnel")
            if (os.system('pacman -Qs net-tools >/dev/null')) == 1:
                missPackets.append("net-tools")
            return missPackets
        else:
            print("Not an Arch - not able to check automatically for packets")
            missPackets.append("OS_UNKNOWN")
            return missPackets

    # check ip forwarding
    def checkIpForward(self):
        print("Activating ip forwarding...")
        result = re.search(r".*1$", os.popen("sysctl net.ipv4.ip_forward=1").read())
        if (result):
            return True
        else:
            return False

    # Check for a specified user on the system
    def checkForUser(self):
        result = re.search(r".*"+self.vpn_user+":.*", os.popen('less /etc/passwd').read())
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
                os.popen('chmod -R 777 /opt/ssl-vpn') # that's just awful, but we have no time for full correctness of code
                return True
            else:
                return False # mkdir failed
        return False;	# User/group add failed


    # Edit sudoers file using an external bash script.
    def checkSudoers(self):
        # First check wether sudoers needs edition :
        result = re.search(r".*"+re.escape(self.vpn_user)+" ALL=NOPASSWD: /usr/sbin/pppd.*", os.popen('less /etc/sudoers').read())
        if (result):
            return True
        else:
            return False

    # To be used if sudoers doesn't contain the right line for vpn_user
    def editSudoers(self):
        f = open('cmd', 'w')
        sudoersLine = self.vpn_user+" ALL=NOPASSWD: /usr/sbin/pppd"
        f.write(sudoersLine)
        f.close()
        subprocess.call("sudoersEdit.sh",shell=True)
        os.system('rm cmd')
        return checkSudoers()
