#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "fstream"
using namespace std;

int main(int argc, char* argv[]) {
	//fstream
	ofstream fout("aes-out.txt", ios::out | ios::trunc);
	//Key and IV setup
	string sKey = { "keyis84932731830" };
	string sIV = { "0000000000000000" };
	string plaintext = { "AES is the US block cipher standard." };
	string ciphertext;
	//string decryptedtext;



	CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::FeedbackSize(), 4 /*32-bits*/) //block size
		(CryptoPP::Name::IV(), CryptoPP::ConstByteArrayParameter(iv));
	// Cout Plain Text

	cout << "Plain Text:\n" << plaintext << endl << endl << endl;

	// Generate Cipher Text (CFB)
	memcpy(key, sKey.c_str(), CryptoPP::AES::MIN_KEYLENGTH);
	memcpy(iv, sIV.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfb;
	cfb.SetKey(key, sizeof(key), params);
	CryptoPP::StringSource cfbss(plaintext, true,new CryptoPP::StreamTransformationFilter(cfb,new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::NO_PADDING));

	cout << "Cipher Text (CFB mode): \n";

	for (int i = 0; i < ciphertext.size(); i++) {

		cout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
		fout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	fout << endl;
	ciphertext.clear();
	cout << endl << endl;

	// Generate Cipher Text (CBC)
	sIV = { "0000000000000000" };	
	memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(iv, sIV.c_str(), CryptoPP::AES::BLOCKSIZE);
	CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption cbc;
	cbc.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::StringSource cbcss(plaintext, true,
		new CryptoPP::StreamTransformationFilter(cbc,
			new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING) );


	std::cout << "Cipher Text (CBC mode Zero Padding): \n";

	for (int i = 0; i < ciphertext.size(); i++) {

		cout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
		fout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	fout << endl;
	ciphertext.clear();
	cout << endl << endl;

	// Generate Cipher Text (CBC2)
	sIV = { "9999999999999999" };
	memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(iv, sIV.c_str(), CryptoPP::AES::BLOCKSIZE);
	CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption cbc2;
	cbc2.SetKeyWithIV(key, key.size(), iv, iv.size());
	CryptoPP::StringSource cbc2ss(plaintext, true,
		new CryptoPP::StreamTransformationFilter(cbc2,
			new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));


	cout << "Cipher Text (CBC mode PKCS7): \n";

	for (int i = 0; i < ciphertext.size(); i++) {

		cout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
		fout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	fout << endl;
	ciphertext.clear();
	cout << endl << endl;

	// Generate Cipher Text (ECB)

	memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::ECB_Mode< CryptoPP::AES >::Encryption ecb;
	ecb.SetKey(key, key.size());
	CryptoPP::StringSource ecbss(plaintext, true,
		new CryptoPP::StreamTransformationFilter(ecb,
			new CryptoPP::StringSink(ciphertext), CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING));


	cout << "Cipher Text (ECB mode): \n";

	for (int i = 0; i < ciphertext.size(); i++) {

		cout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
		fout << setw(2) << setfill('0') << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	ciphertext.clear();
	fout << endl;
	cout << endl << endl;
	
	fout.close();
	return 0;
}