#ifndef LOCGENERATOR_ON_MOBILE_H__
#define LOCGENERATOR_ON_MOBILE_H__


#ifdef ANDROID
#elif __APPLE__
#else


#include <direct.h>
#include <windows.h>
#endif

/* Includes */
#include <wchar.h>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include "math.h"


#include "loc_generator_defaultparams.h"
#include "loc_generator_structs.h"
#include "FgpConvert/FgpGenerator.h"
#include "CommonLibs/Obfuscate/src/obfuscate.h"


using namespace std;


#ifdef WIN32
LPCTSTR  s2ws(const std::string& s) ;
#endif



int RSSI(int rssi, string macadresse, int setID); //Convert RSSI with offuscate
int RSSI_BLE(int rssi, string macadresse, int setID);//Convert RSSI with offuscate ble ...


bool checkAP(double distance, double RSSIm);


//Generate ./location package
int PackageGeneratorEmbedded(	vector <string> InputFolder, // InputFolder one folder for each map for android
								string arcFile, 
								string polyFile,
								string OutputFolder	,
								vector <mapSettingsParam> paramMapsSettings,	
								int percentage = DEFAULTPARAM_FGP_RELIABILITY_PERCENTAGE,
								string wapFile = string(""),
								string bapFile = string(""),
								zoneOutParams zone_out_params = zoneOutParams(),
								wifiFilteringParams wifi_filt_params = wifiFilteringParams()
								);


//Get date of the FgpConvert build
//const char* getVersionFgpConvert();
string getVersionFgpConvert();


//Deprecated
/*
int  getFGPPointReliability (	string posPath,
								string blePath,
								string wifiPath
								);
*/
//New prototype
int  getFGPPointReliability (const string& dbPath, int position_id);
/*
bool create_ZO_csv_file(const string& path, const zoneOutParams& zone_out_params, const vector<mapSettingsParam>& paramMapsSettings);
bool create_wfiltering_csv_file(const string& path, const wifiFilteringParams& wifi_filt_params);*/
bool create_autoCorrect_csv_file(const string& path);
bool create_locConf_csv_file(const string& path, const vector<int>& order_ids_used, const wifiFilteringParams& wifi_filt_params);
bool create_mapsSettings_csv_file(const string& path, const vector<mapSettingsParam>& paramMapsSettings, const zoneOutParams& zone_out_params, const vector<int>& all_map);


#endif  /* LOCGENERATOR_ON_MOBILE_H__ */