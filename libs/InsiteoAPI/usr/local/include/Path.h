#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Segment.h"



using namespace std;



class Path
{
public:
	Path(void);
	Path(int path_id_, string const& comment_/*, int map_id_*/);
	/*Path(int path_id_, const unsigned char * comment_);*/
	~Path(void);
	
	
	
	list<Event> mListEvents;		//Events linked to the Position, ordered chronologically
	
	string mComment;
	int mPathId;
	//int mMapId;

	bool is_static;
	float path_total_length;


	list<list<Segment>::iterator> mSegments;
	list<list<Position>::iterator> mPositions;


	//Ble RSSI
	RSSI_measure_set mAll_RSSI_container_ble;

	//Wifi RSSI
	RSSI_measure_set mAll_RSSI_container_wifi;
};




class SegmentFromPath : public Segment
{
public:
	SegmentFromPath(const Path& path);
};