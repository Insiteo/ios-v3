#pragma once


#include <vector>


struct Measurement
{
	int order_id;
	float rssi_mean;
};



struct Data_to_replay {
	
	Data_to_replay() : position_ID(-1),/* iteration_count(0),*/ map_id(-1), x(0), y(0), delta_x(0), delta_y(0) {};
	
	int position_ID;
	
	vector<Measurement> ble_measurements;
	vector<Measurement> wifi_measurements;

	int map_id;
	float x;
	float y;

	float delta_x;
	float delta_y;
};



struct Data_for_fingerprint {
	
	Data_for_fingerprint() : position_ID(-1), map_id(-1), x(0), y(0) {};

	int position_ID;
	
	vector<Measurement> ble_measurements;
	vector<Measurement> wifi_measurements;
	
	int map_id;
	float x;
	float y;
};


