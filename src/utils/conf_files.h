#ifndef CONF_FILES_H
#define CONF_FILES_H

#include <string>

const std::string STUNNEL_CONF_TEXT =
    "debug = 7\n\
    foreground = yes\n\
    cert = /opt/ssl-vpn/etc/vpn1/client.pem\n\
    verify = 3\n\
    CApath = /opt/ssl-vpn/etc/vpn1/\n\
    CAfile = /opt/ssl-vpn/etc/vpn1/client.pem\n\
    connect = 192.168.0.100:9871\n\
    client = yes\n";

const std::string SSLVPN_CONF_TEXT =
    "[ req ]\n\
    default_bits = 1024\n\
    encrypt_key = yes\n\
    distinguished_name = req_dn\n\
    x509_extensions = cert_type\n\
    \n\
    [ req_dn ]\n\
    countryName			= FR\n\
    countryName_default		= FR\n\
    \n\
    stateOrProvinceName		= Rhone-Alpes\n\
    stateOrProvinceName_default	= Rhone-Alpes\n\
    \n\
    localityName			= Lyon\n\
    localityName_default		= Lyon\n\
    \n\
    0.organizationName		= Ninetales\n\
    0.organizationName_default 	= Ninetales\n\
    \n\
    0.commonName			= ninetales-client.fr\n\
    0.commonName_default 		= ninetales-client.fr\n\
    \n\
    [ cert_type ]\n\
    nsCertType = server\n";

#endif // CONF_FILES_H
