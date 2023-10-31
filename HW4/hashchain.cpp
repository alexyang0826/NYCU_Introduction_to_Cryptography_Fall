#include "cryptlib.h"
#include "cryptopp/sha.h"
#include "filters.h"
#include "hex.h"
#include "files.h"
#include "osrng.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
using namespace CryptoPP;
using namespace std;



int main() {
	AutoSeededRandomPool prng;

	byte zero[SHA256::DIGESTSIZE];
	byte preimage[SHA256::DIGESTSIZE + 4];
	byte digest[SHA256::DIGESTSIZE];
	byte nonce[4];//4byte = 32bit
	SHA256 hash; 

	HexEncoder encoder;
	HexDecoder decoder;
	fstream file;
	string hex_string;

	
	memset(zero, 0x00, SHA256::DIGESTSIZE);
	encoder.Attach(new FileSink(file));
	//---------------------------------------------------
m:
	string msg = "109704011";
	hash.Update((const byte*)msg.data(), msg.length());
	hash.Final(digest);
	file.open("out.txt", fstream::out);
	for (int num = 0; num <= 9; ++num) {
		clock_t tStart = clock();
		file << num << endl;
		encoder.PutMessageEnd(digest, SHA256::DIGESTSIZE);
		file << endl;
		memcpy(preimage, digest, SHA256::DIGESTSIZE);
		long long tried = 0;
		while (1) {		
			/*if ((double)(clock() - tStart) / CLOCKS_PER_SEC > 3600) {
				file.close();		
				cout << "________time_out____________" << endl;
				printf("Time taken: %.3lfs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
				goto m;
			}*/
			tried++;
			if (tried > 4294967296) {
				file.close();
				cout << "___none___________________" << endl;
				cout << "tried:" << tried << endl;
				printf("Time taken: %.3lfs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
				goto m;
			}
			prng.GenerateBlock(nonce, 4);
			memcpy(preimage + SHA256::DIGESTSIZE, nonce, 4);
			hash.Update(preimage, SHA256::DIGESTSIZE + 4);
			hash.Final(digest);
			if (memcmp(digest, zero, num>>1) != 0)
				continue;
			if (!((num % 2) && ((digest[(num>>1)] >> 4) ^ zero[num>>1]) != 0))
				break;
		}
		cout << "found:" << num << endl;
		encoder.PutMessageEnd(nonce, 4);
		file << endl;
		encoder.PutMessageEnd(digest, SHA256::DIGESTSIZE);
		file << endl;
		cout << "tried:" << tried << endl;
		printf("Time taken: %.3lfs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	}

	encoder.Detach();
	file.close();

	return 0;
}