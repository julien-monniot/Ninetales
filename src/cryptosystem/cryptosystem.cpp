#include "cryptosystem.h"

#include <openssl/sha.h>
#include <openssl/objects.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <time.h>

using namespace std;

Cryptosystem::Cryptosystem()
{}

void Cryptosystem::registerPublicKey(unsigned char* user, RSA* publicKey)
{
    publicKeys[user]=publicKey; //implémentation temporaire, en attendant de voir comment on stocke les clés
}

RSA* Cryptosystem::getPublicKey(unsigned char* user)
{
    return publicKeys.find(user)->second; //implémentation temporaire, en attendant de voir comment on stocke les clés
}

RSA* Cryptosystem::generateRSAKey(unsigned char* identifier)
{
    RSA* privateKey = RSA_new();
	RSA* publicKey = RSA_new();
	BIGNUM* exponent = BN_new();
	BN_dec2bn(&exponent,"65537");
	RSA_generate_key_ex(privateKey,2048,exponent,NULL);
	*publicKey = *privateKey;
	publicKey->d = NULL;
	publicKey->p = NULL;
	publicKey->q = NULL;
	registerPublicKey(identifier,publicKey);
	return privateKey;
}

unsigned char* Cryptosystem::encryptRSA(unsigned char* clearMessage, unsigned char* receiver)
{
    RSA* receiverPublicKey = getPublicKey(receiver);
    unsigned char* encryptedMessage = new unsigned char[RSA_size(receiverPublicKey)];
	RSA_public_encrypt(TAILLE_MESSAGES_RSA,clearMessage,encryptedMessage,receiverPublicKey,RSA_PKCS1_OAEP_PADDING);
	return encryptedMessage;
}

unsigned char* Cryptosystem::decryptRSA(unsigned char* encryptedMessage, RSA* privateKey)
{
    unsigned char* decryptedMessage= new unsigned char[TAILLE_MESSAGES_RSA];
	RSA_private_decrypt(RSA_size(privateKey),encryptedMessage,decryptedMessage,privateKey,RSA_PKCS1_OAEP_PADDING);
	return decryptedMessage;
}

pair<unsigned char*,unsigned char*> Cryptosystem::encryptAndSignRSA(unsigned char* clearMessage,unsigned char* receiver,unsigned char* signature,RSA* privateKey, unsigned int & returnSize)
{
    unsigned char* encryptedMessage = encryptRSA(clearMessage,receiver);
    unsigned char digestMessage[20];
    SHA1(signature, strlen((char*) signature), digestMessage);
    unsigned char* encryptedSignature = new unsigned char[RSA_size(privateKey)];
    RSA_sign(NID_sha1, digestMessage, 20, encryptedSignature, &returnSize, privateKey);
    return make_pair(encryptedMessage,encryptedSignature);
}

bool Cryptosystem::isSignatureLegit(unsigned char* signature,unsigned char* encryptedSignature, unsigned int signatureSize, unsigned char* sender)
{
    unsigned char digestMessage[20];
    RSA* senderPublicKey = getPublicKey(sender);
    SHA1(signature, strlen((char*)signature), digestMessage);
    return RSA_verify(NID_sha1, digestMessage, 20, encryptedSignature, signatureSize, senderPublicKey)==1;
}

unsigned char* Cryptosystem::decideAESKey()
{
    srand(time(NULL));
    int character;
    unsigned char* retour = new unsigned char[128];
    for(int i=0;i<128;i++)
    {
        character=rand();
        retour[i]=(unsigned char)character;
    }
    return retour; //implémentation temporaire, il faut que les deux partis obtiennent la clé et qu'ils décident ensemble
}

unsigned char* Cryptosystem::encryptAES(unsigned char* clearMessage, unsigned char* communicationKey)
{
	unsigned char* encryptedMessage = new unsigned char[128];
    AES_KEY aesCommunicationKey;
	AES_set_encrypt_key(communicationKey, 128, &aesCommunicationKey);
	AES_encrypt(clearMessage, encryptedMessage, &aesCommunicationKey);
	return encryptedMessage;
}

unsigned char* Cryptosystem::decryptAES(unsigned char* encryptedMessage, unsigned char* communicationKey)
{
	unsigned char* decryptedMessage = new unsigned char[128];
    AES_KEY aesCommunicationKey;
	AES_set_decrypt_key(communicationKey, 128, &aesCommunicationKey);
	AES_decrypt(encryptedMessage, decryptedMessage, &aesCommunicationKey);
	return decryptedMessage;
}

