#pragma once

//Includes
#include <list>
#include "Position.h"



using namespace std;

//Class Pause, when the user takes da pause during a Segment
class Pause
{
public:
	Pause() {};
	Pause(Event &start, Event &stop) {mStart_da_pause = start; mStop_da_pause = stop;};
	~Pause() {};


	Event mStart_da_pause;
	Event mStop_da_pause;
};


//Class Segment
class Segment
{
public:
	Segment(void);
	~Segment(void);


	//Iterators to Positions in an external container. Those will represent true positions given in the input database.
	list<Position>::iterator mStartPosition;
	list<Position>::iterator mStopPosition;


	//List of actual Position objects. Those are extrapolated positions that will be associated to measurements.
	//In dynamic mode, those positions are not directly mStartPosition and mStopPosition !!!
	list<Position> mPositionsCollection;


	Event mStartSegmentEvent;
	Event mStopSegmentEvent;
	list<Pause> mListPauses;


	int mPathId;

	float mSegmentLength;
	float mSpeedUser_mean;
	pair<float,float> mDirectorVect;
};

