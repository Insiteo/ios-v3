#pragma once


// Includes
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include "Fgp_common_values.h"


#define POSITION_TECHNO_WIFI									false
#define POSITION_TECHNO_BLE										true


using namespace std;					



/****************************************************************************************************/
/*** class Event ***/
/****************************************************************************************************/

class Event {
public:
	//unsigned long long mTimestamp;
	double mTimestamp;
	unsigned short mPositionId;
	unsigned char mEventType;
};



/****************************************************************************************************/
/*** class RSSImeasure ***/
/****************************************************************************************************/

class RSSImeasure : public Event {
public:
	string mMAC;
	double mRSSI;
	bool mTechno;

	float mPressure;
	float mAzimuth;

	
	//After RSSImeasure is placed in set container, it is unmodified since set returns const iterators. The following fields are to be modified, then they shall be noted as mutable.
	mutable float mPlaceHolder_float_1;
	mutable float mPlaceHolder_float_2;
	mutable double mPlaceHolder_double_1;
	mutable double mPlaceHolder_double_2;
};




/* Defining a custom container able to sort rssi entries both by order ID and by timestamp */

	//Compare operator
struct compare_timestamps {
public:
	bool operator()(const RSSImeasure& left_, const RSSImeasure& right_) {
		return left_.mTimestamp < right_.mTimestamp;
	};
};

	//Container itself
//typedef set<RSSImeasure,compare_timestamps> RSSI_measure_set;
typedef multiset<RSSImeasure,compare_timestamps> RSSI_measure_set;
typedef map<int,set<RSSImeasure,compare_timestamps> > RSSI_container;

	//Container iterator
//typedef set<RSSImeasure,compare_timestamps>::iterator RSSI_measure_set_iterator;
typedef multiset<RSSImeasure,compare_timestamps>::iterator RSSI_measure_set_iterator;
typedef map<int,set<RSSImeasure,compare_timestamps> >::iterator RSSI_container_iterator;


typedef map<int,list<RSSI_measure_set_iterator> >				InputMeasure_RSSI;
typedef vector<int>												OutputMeasure_OrderIDs;
typedef vector<double>											OutputMeasure_RSSI;
typedef vector<int>												OutputMeasure_NbRep;
typedef vector<float>											OutputMeasure_StdDev;





/****************************************************************************************************/
/*** class Position ***/
/****************************************************************************************************/

class Position
{
public:
	Position(void);
	~Position(void);
	
	int mPosId;
	float mX_pixels;
	float mY_pixels;
	float mX_m;
	float mY_m;
	int mMapId;
	//int mPosId;
	int mOrder;

	int mPathId;
	int mSegmentId[2];
	
	list<Event> mListEvents;		//Events linked to the Position, ordered chronologically

	double mDistFromPathBeginning;
	

	/* Input data */

	//Ble RSSI
	InputMeasure_RSSI		mRSSI_container_ble;

	//Wifi RSSI
	InputMeasure_RSSI		mRSSI_container_wifi;



	/* Output data */

	//RSSI information (temporaire, à modifier en fonction des évolutions)
		//BLE
	OutputMeasure_OrderIDs	mBle_VectOrderIds;
	OutputMeasure_RSSI		mBle_VectRSSI;
	OutputMeasure_NbRep		mBle_VectNbRep;			
	OutputMeasure_StdDev	mBle_VectStdDev;		
		//Wifi
	OutputMeasure_OrderIDs	mWifi_VectOrderIds;
	OutputMeasure_RSSI		mWifi_VectRSSI;
};