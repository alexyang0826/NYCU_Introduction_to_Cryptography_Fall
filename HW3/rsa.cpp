#include <iostream>
#include <sstream>
#include <iomanip>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <fstream>
using namespace CryptoPP;
using namespace std;


int main() {
	//cin.sync_with_stdio(0);
	ofstream fout("out.txt", ios::out);
	//encryption 1/////////////////////////////////////
	Integer* n = new Integer("0xc963f963d93559ff");
	Integer* e = new Integer("0x11");
	string message = "ElGamal";

	RSA::PublicKey pubKey;
	pubKey.Initialize(*n, *e);

	Integer* m = new Integer((const byte*)message.data(), message.size());
	Integer* c = new Integer(pubKey.ApplyFunction(*m));
	stringstream ss;
	string sc;
	ss << hex << *c;
	ss >> sc;
	sc.pop_back();
	cout << "c: " << hex << sc << endl;

	ss.clear();
	ss.str() = "";
	sc.clear();
	delete n, e, m, c;

	//encryption 2/////////////////////////////////////

	n = new Integer("0x04823f9fe38141d93f1244be161b20f");
	e = new Integer("0x11");
	message = "Hello World!";

	pubKey.Initialize(*n, *e);

	m = new Integer((const byte*)message.data(), message.size());
	c = new Integer(pubKey.ApplyFunction(*m));
	ss << hex << *c;
	ss >> sc;
	sc.pop_back();
	cout << "c: " << hex << sc << endl;
	fout << sc << endl;
	ss.clear();
	ss.str() = "";
	sc.clear();

	
	delete n, e, m, c;

	//encryption 3/////////////////////////////////////

	n = new Integer("0x9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9");
	e = new Integer("0x10001");
	message = "RSA is public key.";

	pubKey.Initialize(*n, *e);

	m = new Integer((const byte*)message.data(), message.size());
	c = new Integer(pubKey.ApplyFunction(*m));
	ss << hex << *c;
	ss >> sc;
	sc.pop_back();
	cout << "c: " << hex << sc << endl;
	fout << sc << endl;
	ss.clear();
	ss.str() = "";
	sc.clear();
	delete n, e, m;
	//decryption 1/////////////////////////////////////
	AutoSeededRandomPool prng;
	n = new Integer("0xc45350fa19fa8d93");
	e = new Integer("0x11");
	c = new Integer("0xa4a59490b843eea0");
	Integer *d = new Integer("0x454a950c5bcbaa41");
	Integer *r= new Integer();
	
	string recovered;
	RSA::PrivateKey privKey;
	privKey.Initialize(*n, *e, *d);


	*r = privKey.CalculateInverse(prng, *c);
	//cout << "r: " << hex << *r << endl;

	size_t req = r->MinEncodedSize();
	recovered.resize(req);
	r->Encode((byte*)recovered.data(), recovered.size());

	cout << "recovered: " << recovered << endl;
	delete n, e, d, c, r;
	//decryption 2/////////////////////////////////////
	n = new Integer("0xc4b361851de35f080d3ca7352cbf372d");
	e = new Integer("0x1d35");
	c = new Integer("0xa02d51d0e87efe1defc19f3ee899c31d");
	d = new Integer("0x53a0a95b089cf23adb5cc73f0700001");
	r = new Integer();
	recovered.clear();
	for (int i = 0; i < pow(2, 20); i++) {
		*d = *d + 2;
		try {
			privKey.Initialize(*n, *e, *d);
			break;
		}
		catch (...) {
			//cout << hex << *d << '\n';
		}
	}

	
	*r = privKey.CalculateInverse(prng, *c);
	cout << "r: " << hex << *r << endl;

	req = r->MinEncodedSize();
	recovered.resize(req);
	r->Encode((byte*)recovered.data(), recovered.size());
	ss << hex << *d;
	ss >> sc;
	sc.pop_back();
	cout << "d: " << hex << sc << endl;
	fout << sc << endl;
	ss.clear();
	ss.str() = "";
	sc.clear();
	cout << "recovered: " << recovered << endl;
	fout << recovered << endl;
	delete n, e, d, c, r;
	
	return 0;
}