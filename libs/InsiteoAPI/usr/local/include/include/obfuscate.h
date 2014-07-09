#pragma once

#include <string>
#include <iostream>
#include <sstream>


using namespace std;


// #define DISABLE_FINGERPRINT_OBFUSCATION

class EncryptFgp
{
public:
	EncryptFgp() {};
	~EncryptFgp() {};

	int GetOffset(string formated_mac_str, int key);
};



class Obfuscate : public EncryptFgp
{
public :

	Obfuscate() {};
	~Obfuscate() {};
	
	int RSSI(int rssi, string macadresse, int positionID);		//Convert RSSI with offuscate
	int RSSI_BLE(int rssi, string macadresse, int positionID);	//Convert RSSI with offuscate ble ...
};



class Deobfuscate : public EncryptFgp
{
public :

	Deobfuscate() {};
	~Deobfuscate() {};
	
	int RSSI(int rssi, string macadresse, int positionID);		//Convert RSSI with offuscate
	int RSSI_BLE(int rssi, string macadresse, int positionID);	//Convert RSSI with offuscate ble ...
};