#pragma once

#include <set>

#define RSSI_MIN_FOR_ORDERIDS_TO_KEEP			-110

using namespace std;


class Map_info
{
public:
	Map_info(void);
	~Map_info(void);

	int mMapId;
	float mScale;
	float mAzimuth;
	
	set<int> mOrderIdsToKeepWifi;
	set<int> mOrderIdsToKeepBle;
};

