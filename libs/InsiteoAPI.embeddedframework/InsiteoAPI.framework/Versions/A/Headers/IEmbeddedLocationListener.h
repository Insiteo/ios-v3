#pragma once

#ifdef __APPLE__
class InternalLocation;
#elif __ANDROID__

#include "entities/LocationData.h"
#else
#include "./core/entities/location_structures.h"
#include "entities/LocationData.h"
#endif

class IEmbeddedLocationListener
{

public:
    IEmbeddedLocationListener();   
	//virtual ~IEmbeddedLocationListener() ;
	~IEmbeddedLocationListener() ;
	
    virtual void onLocation(InternalLocation * aLocation) = 0;
	virtual void zoneOUT(InternalLocation * aLocation) = 0;
    virtual void onGpsStatusChange(bool aEnable) = 0;
	virtual void onUserOnSite( bool aUserOnSite )= 0;
	virtual void onAPMissing(InternalLocation * location, char * orderIDs, char * counts, int techno) = 0;
};

