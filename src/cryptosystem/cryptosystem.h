#ifndef CRYPTOSYSTEM_H
#define CRYPTOSYSTEM_H

#include <map>
#include <utility>
#include <openssl/rsa.h>

#define TAILLE_MESSAGES_RSA 30

class Cryptosystem
{
    private:
        std::map<unsigned char*,RSA*> publicKeys; //temporaire, tant qu'on sait pas trop comment on stocke les clé publiques

        void registerPublicKey(unsigned char* user, RSA* publicKey);
        RSA* getPublicKey(unsigned char* user);

    public:
        Cryptosystem();
        RSA* generateRSAKey(unsigned char* identifier);
        unsigned char* encryptRSA(unsigned char* clearMessage, unsigned char* receiver);
        unsigned char* decryptRSA(unsigned char* encryptedMessage, RSA* privateKey);
        std::pair<unsigned char*,unsigned char*> encryptAndSignRSA(unsigned char* clearMessage,unsigned char* receiver,unsigned char* signatureString, RSA* privateKey, unsigned int & returnSize);
        bool isSignatureLegit(unsigned char* signatureString, unsigned char* encryptedSignatureString, unsigned int signatureSize, unsigned char* sender);
        unsigned char* decideAESKey();
        unsigned char* encryptAES(unsigned char* clearMessage, unsigned char* communicationKey);
        unsigned char* decryptAES(unsigned char* encryptedMessage, unsigned char* communicationKey);
};
#endif
