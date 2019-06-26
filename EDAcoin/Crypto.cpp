#include "Crypto.h"




string ByteVector2String(vector<byte> &dataToPrint)
{
	/*CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(dataToPrint.data(), dataToPrint.size());
	encoder.MessageEnd();
	return output;*/

	string str;
	for (int i = 0; i < dataToPrint.size(); i++)
	{
		str += dataToPrint[i];
	}
	return str;
}


vector<byte> String2ByteVector(string& str)
{
	vector<byte> v;
	//int i = (int)str.size();
	for (int i = 0; i < (int)str.size(); i++)
	{
		char c = str[i];
		v.push_back((byte)(str[i]));
	}
	return v;
}

ECDSA<ECP, SHA256>::PrivateKey generatePrivKey()
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;

	//privateKey.Initialize(autoSeededRandomPool, ASN1::secp160r1());
	privateKey.Initialize(autoSeededRandomPool, ASN1::secp256k1());
	bool result = privateKey.Validate(autoSeededRandomPool, 3);
	if (!result)
		cout << "private key is not valid!";
	return privateKey;
}

vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, string &data)
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::Signer signer(privKey); //Creamos el signador
	bool result = signer.AccessKey().Validate(autoSeededRandomPool, 3);
	if (!result)
		cout << "failed to create signer" << result;
	size_t siglen = signer.MaxSignatureLength();
	vector<byte> signature(siglen, 0x00); //Aqui guardaremos la signature
	siglen = signer.SignMessage(autoSeededRandomPool, (const byte*)data.data(), data.size(), (byte*)signature.data());
	return signature;
}

bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, string &data, vector<byte> &signature)
{
	ECDSA<ECP, SHA256>::Verifier verifier(pubKey);
	return  verifier.VerifyMessage((const byte*)data.data(), data.size(), (const byte*)signature.data(), signature.size());
}

void showData(ECDSA<ECP, SHA256>::PrivateKey &privKey, ECDSA<ECP, SHA256>::PublicKey &pubKey, vector<byte> &signature)
{
	vector<byte> privKeyByteArray(PRIVATE_KEY_CHARS), pubKeyByteArray(PUBLIC_KEY_CHARS);
	const Integer &privateKeyInteger = privKey.GetPrivateExponent(); //La key posta
	privateKeyInteger.Encode(privKeyByteArray.data(), privateKeyInteger.ByteCount());
	unsigned int auxx = privateKeyInteger.ByteCount();
	cout << "Private Key: ";
	hexPrint(privKeyByteArray);		//**Aca hay un error, se esta imprimiendo el private key.

	vector<byte> aux(PUBLIC_KEY_CHARS / 2);
	const ECP::Point &point = pubKey.GetPublicElement();
	point.x.Encode(aux.data(), point.x.ByteCount());
	pubKeyByteArray.clear();
	pubKeyByteArray.insert(pubKeyByteArray.end(), aux.begin(), aux.end());
	point.y.Encode(aux.data(), point.y.ByteCount());
	pubKeyByteArray.insert(pubKeyByteArray.end(), aux.begin(), aux.end());
	cout << "Public Key: ";
	hexPrint(pubKeyByteArray);

	cout << "Signature: ";
	hexPrint(signature);
}

void hexPrint(vector<byte> &dataToPrint)
{
	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(dataToPrint.data(), dataToPrint.size());
	encoder.MessageEnd();
	cout << output << endl;
}

string HashMessage(string& message)
{
	SHA256 hash;
	string digest;
	StringSource s(message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	return digest;
}

bool VerifyHashMessage(string& hash, string& message)
{
	SHA256 hash_;
	string digest;
	StringSource s(message, true, new HashFilter(hash_, new HexEncoder(new StringSink(digest))));
	if (digest == hash)
		return true;
	else
		return false;
}