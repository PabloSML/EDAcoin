#pragma once

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"
#include "oids.h"
#include "hex.h"
#include "sha3.h"

#include <string>

//using BOOLEAN = namespaceapi::BOOLEAN;
using namespace std;
using namespace CryptoPP;

#define PRIVATE_KEY_CHARS 32
#define PUBLIC_KEY_CHARS 64


string ByteVector2String(vector<byte> &dataToPrint);
vector<byte> String2ByteVector(string& str);

ECDSA<ECP, SHA256>::PrivateKey generatePrivKey();
vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, string &data);
bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, string &data, vector<byte> &signature);
void showData(ECDSA<ECP, SHA256>::PrivateKey &pubKey, ECDSA<ECP, SHA256>::PublicKey &privKey, vector<byte> &signature);
void hexPrint(vector<byte> &dataToPrint);

string HashMessage(string& message);
bool VerifyHashMessage(string& hash, string& message);

