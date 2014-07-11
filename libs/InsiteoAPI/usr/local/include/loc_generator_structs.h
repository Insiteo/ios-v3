#pragma once

#include <vector>



using namespace std;


struct arc{
	int arcID;
	int mapID;
	int nodeID1,nodeID2;
	double X1,Y1,X2,Y2;
};


struct APvu
{
public :
	vector<int> RSSI;
	int orderID;
	double RSSImoyen;
	int RSSI0;
};


struct APvuBLE
{
public :
	vector<double> RSSI;
	vector<double> RSSIsquare;
	int orderID;
	double RSSImoyen;
	double stdmoy;
	int RSSI0;
	vector <int> frequency;
	int meanfreq;
};


struct map_for_index
{
	int mapID;
	double scale;
	vector <int> index;
	vector <int> indexBLE;
	vector <double> maxRSSI;
	vector <double> maxRSSI_BLE;
	vector <int> belief;
	vector <double> maxRSSI2;
	vector <double> minRSSI; 
	vector <double> Xmin;
	vector <double> Xmax;
	vector <double> Ymin;
	vector <double> Ymax;
	bool scan_done;
};

typedef struct 
{
public :
	string MacAdress;
	int orderID;
	double Xpos ;
	double Ypos ;
	int mapID ;
	double Zalti ;
} AP;

typedef struct 
{
	bool testQuality ;
	vector <AP> AccessPointToControl;
} FGPPointReliability;


struct pos
{
public :
	int IDpos;
	double Xm ,Ym;
	int MapID;
	vector <APvu> listeAPparPoint;
	vector <APvuBLE> listeAPparPointBLE;
};

struct scan
{
public :
	int IDpos,setID;
	string MacAdress;
	int strength;
};

struct scanBLE
{
public :
	int IDpos,setID;
	string MacAdress;
	int strength;
	vector <int> RSSIvector;
	int sumrssi ;
	int sumrssi2 ;
	int freq;
};

struct scanBLEsetID 
{
public :

	int setID;
	vector <int> RSSIvector;
};


struct scanBLEmacAdresse
{
public :

	string MacAdress;
	
	vector <scanBLEsetID> ascanBLEsetID;
};

struct scanBLEposID
{
public :
	int posID;
	vector <scanBLEmacAdresse> ascanBLEmacAdresse;
};

struct zoneOutParams 
{
	zoneOutParams();
	
	bool flagOnOff;		
	
	double ratioWknnBle;
	double ratioWknnWifi;

	int thresholdRSSIBLE;
	int thresholdRSSIWifi;
	
	int hysteresis_stop;
	int hysteresis_on;
};

struct wifiFilteringParams
{
	wifiFilteringParams();
	
	bool flagOnOff;			//This flag only enables the file's generation on the mobile. But the treatement is not performed if not activated at the same time on the server.
	double alpha_1_ble;
	double alpha_2_ble;

	int RSSI_garbage_high;
	int RSSI_garbage_low;
	double delta_dB;
};

struct mapSettingsParam
{
	int mapID ;//MapID
	int mapID_on_fingerprint ;//MapID on fingerprint
	int PosTechnique ; //0
	int k ;//3
	int typeFiltre ;//6
	double dynamiqueUser;//0.1
	double vmaxUser ;//2
	int sensorNoise;//6
	int nFiltre;//4
	double penteFiltre ;//0.75
	int mapMatchingTechnique; //0
	int markerSize;//5
	int nbCalledBeforeFirstFix ;//1
	int azimuth ;//-1
};

/* struct dynamicFgpConf defines parameters for the filtering methods of the dynamic/static fingerprint generation. 

max_threshold_rssi_dB corresponds to the high limit for rssi. Power above this value will be removed;

min_threshold_rssi_dB corresponds to the high limit for rssi. Power below this value will be removed;
 
int mean_type corresponds to the type of rssi values to work with. Values available are : 
	0 - Work directly on dB values
	1 - Convert dB values to linear before using it. When treatment is finished, convert back to dB.

filterTypes corresponds to the enum FilterType in Fgp_common_values. Values available are : 
	0 - Low pass with gaussian weights
	1 - Polynomial fitting 

mesh_size corresponds to the size of the reconstructed mesh along dynamic paths. It is a distance in meters.

filter_param_float_xxx are parameters of type float, proper to each type of filter. They are : 
			Filter type :	0									1								2				
	filter_param_float_1 -	Aperture of filter (in m.)			Coverage of filter, in m.		Coverage of filter, in m.
	filter_param_float_2 -	Gain of filter						Aperture of filter, in m.		Not used
	filter_param_float_3 -	Not used							Gain of filter					Not used	

filter_param_int_xxx are parameters of type int, proper to each type of filter. They are : 
			Filter type :	0									1								2				
	filter_param_int_1	-	Filter size (in m.)					Not used						Order of polynomial regression
	filter_param_int_2	-	Not used							Not used						Not used
	filter_param_int_3	 -	Not used							Not used						Not used	
*/
struct dynamicFgpConf 
{
	//Constructor for default values
	dynamicFgpConf();

	//General
	float max_threshold_rssi_dB;
	float min_threshold_rssi_dB; 
	int mean_type;
	int filterType;
	float mesh_size;
	bool mSeparateTechnos;


	//Filter params : float values (depends on the type filter)
	float filter_param_float_1;
	float filter_param_float_2;
	float filter_param_float_3;

	//Filter params : integer values (depends on the type filter)
	int filter_param_int_1;
	int filter_param_int_2;
	int filter_param_int_3;
};