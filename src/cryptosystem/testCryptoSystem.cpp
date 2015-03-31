#include "cryptosystem.h"
#include <string>
#include <iostream>
#include <openssl/rsa.h>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
    Cryptosystem c;
    unsigned char aliceID[] = "Alice";
    unsigned char bobID[] = "Bob";
    unsigned char middleManID[] = "Middleman";
    RSA* aliceKey = c.generateRSAKey(aliceID);
    RSA* bobKey = c.generateRSAKey(bobID);
    RSA* middleManKey = c.generateRSAKey(middleManID);

    unsigned char baseMessage[] = "Hey bob";
    unsigned char* encryptedMessage = c.encryptRSA(baseMessage,bobID);
    unsigned char* decryptedMessage = c.decryptRSA(encryptedMessage,bobKey);
    unsigned char* interceptedMessage = c.decryptRSA(encryptedMessage,middleManKey);
    cout << "Alice sends : "<<baseMessage<<endl;
    cout << "Bob reads : "<<decryptedMessage<<endl;
    cout << "Middle man reads : "<<interceptedMessage<<endl;
    cout << "-------"<<endl;

    unsigned char signedMessage[] = "Hey bob, I signed this message";
    unsigned char signature[] = "Love,Alice";
    unsigned int aliceReturn;
    unsigned int middleManReturn;
    cout << "Alice and middle man both send : "<<signedMessage<<endl;
    pair<unsigned char*,unsigned char*> signedMessageAlice = c.encryptAndSignRSA(signedMessage,bobID,signature, aliceKey,aliceReturn );
    pair<unsigned char*,unsigned char*> signedMessageMiddleMan = c.encryptAndSignRSA(signedMessage,bobID,signature, middleManKey,middleManReturn );
    cout << "Bob verifies Alice's message: "<<endl;
    if(c.isSignatureLegit(signature, signedMessageAlice.second,aliceReturn, aliceID))
    {
        cout<<"Yup, it's Alice"<<endl;
    }
    else
    {
        cout<<"Wait a minute, that's not Alice !"<<endl;
    }
    cout << "Bob verifies middle man's fake message:"<<endl;
    if(c.isSignatureLegit(signature, signedMessageMiddleMan.second,middleManReturn, aliceID))
    {
        cout<<"Yup, it's Alice"<<endl;
    }
    else
    {
        cout<<"Wait a minute, that's not Alice !"<<endl;
    }
    cout<<"-------"<<endl;

    unsigned char* commonKey=c.decideAESKey();
    unsigned char message[] = "Viva AES !";
    unsigned char fakeKey[] = "Well, it's worth a try";
    cout<<"Alice and Bob have decided on the supersecret key : "<<commonKey<<endl;
    cout<<"Bob sends to Alice : "<<message<<endl;
    unsigned char* encryptedAesMessage=c.encryptAES(message, commonKey);
    unsigned char* decryptedAesMessage=c.decryptAES(encryptedAesMessage, commonKey);
    unsigned char* interceptedAesMessage=c.decryptAES(encryptedAesMessage, fakeKey);
    cout<<"Alice reads :"<<decryptedAesMessage<<endl;
    cout<<"Middle man, having no clue what the key is, reads :"<<interceptedAesMessage;
}
