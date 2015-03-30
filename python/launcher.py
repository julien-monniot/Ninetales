#!/usr/bin/env python3

##########################################
#                                        #
#   Launcher for pppd/stunnel VPN        #
#   created : 28/03/15                   #
#   author :                             #
#                                        #
##########################################

from server import *
from client import *
import argparse
import re

VPN_NAME = "Ninetales"
VPN_USER = "sslvpn"
VPN_USER_PATH = "/opt/ssl-vpn"

def validate_port(parser, arg):
    arg = int(arg)
    if arg >= 0 and arg <= 65535:
        parser.error("The port number must be between 0 and 65535")
    return arg

def validate_ip(parser, arg):
    arg = str(arg)
    if not re.match(r"^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$", arg):
        parser.error("Invalid IP : " + arg)
    return arg

def arguments_parser():
    # General
    parser = argparse.ArgumentParser(prog="ninetales", description="Another VPN program")
    subparser = parser.add_subparsers()
    
    # Client parser
    subparser_client = subparser.add_parser("client", help="Manage a VPN client")
    subparser_client.add_argument("address", type=lambda x: validate_ip(parser, x), nargs=1, help="IP address to connect to.")
    subparser_client.add_argument("-p", "--port", type=lambda x: validate_port(parser, x), required=False, nargs=1, default=42421, help="Port connection to accept. Default port is 42421.")
    subparser_client.set_defaults(func=launch_client)
    
    # Server parser
    subparser_server = subparser.add_parser("server", help="Manage a VPN server")
    subparser_server.add_argument("-p", "--port", type=lambda x: validate_port(parser, x), required=False, nargs=1, default=42421, help="Port connection to accept. Default port is 42421.")
    subparser_server.add_argument("-l", "--local", type=lambda x: validate_ip(parser, x), required=False, nargs=1, default="192.168.0.1", help="Local IP in the ppp network. Default IP is 192.168.0.1.")
    subparser_server.add_argument("-r", "--remote", type=lambda x: validate_ip(parser, x), required=False, nargs=1, default="192.168.0.2", help="Remote IP in the ppp network. Default IP is 192.168.0.2.")
    subparser_server.set_defaults(func=launch_server)
    
    # Return result
    args = parser.parse_args()
    return args

def launch_client(args):
    print("Client initialization...")
    client = Client(VPN_NAME, VPN_USER, VPN_USER_PATH, args.address, args.port)
    if client.initialize():
        print("Server initialized")
    else:
        print("Error during server init")

def launch_server(args):
    print("Server initialization...")
    server = Server(VPN_NAME, VPN_USER, VPN_USER_PATH, args.port, args.local, args.remote)
    if server.initialize():
        print("Server initialized")
    else:
        print("Error during server init")


if __name__ == '__main__':
    args = arguments_parser()
    args.func(args);




