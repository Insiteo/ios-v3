#pragma once

//Includes
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <math.h>

/*debug*/#include <fstream>/*debug*/


#include "Path.h"
#include "Fgp_common_values.h"

#ifdef USE_EIGEN_MATRIX_LIB
#include "../CommonLibs/Eigen/Eigen/Eigen"
#include "../CommonLibs/Eigen/Eigen/Jacobi"
#include "../CommonLibs/Eigen/Eigen/src/core/util/ForwardDeclarations.h"
#endif

using namespace std;



/****************************************************************************************************/
/*** class Filter (abstract) ***/
/****************************************************************************************************/

class Filter 
{
public:

	//Measure selection : we attend to form a set of measures valid for the current point. These methods apply a criterion, proper to each kind of filter, which decides whether or not the current 
	//measure will be used. If it is, the RSSI_measure_set_iterator is added to the internal Position's container for the measures to use.
	bool use_measure_in_position_container_BLE(RSSI_measure_set_iterator meas_iterator, Position& position);	
	bool use_measure_in_position_container_Wifi(RSSI_measure_set_iterator meas_iterator, Position& position);	

	virtual void signal_conditionning_BLE(Segment& segment, double saturation_low, double saturation_high) = 0;
	virtual void signal_filter_BLE(Segment& segment, double saturation_low, double saturation_high) = 0;
	
	virtual void signal_conditionning_Wifi(Segment& segment, double saturation_low, double saturation_high) = 0;
	virtual void signal_filter_Wifi(Segment& segment, double saturation_low, double saturation_high) = 0;
	

	//virtual void set_filter_settings() = 0; 

	virtual void reset_filter() = 0;


private:
	virtual bool use_measure_criterion(RSSI_measure_set_iterator meas_iterator, Position& position) = 0;
	//RSSI_measure_set_iterator find_RSSI_by_Dichotomy(RSSI_container& container, int order_id, double timecode, bool greater_than);
};



/****************************************************************************************************/
/*** class FIR ***/
/****************************************************************************************************/

class FIR : public Filter
{
public:
	FIR(void);
	~FIR(void);


	//Overloads
	void signal_conditionning_BLE(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_BLE(Segment& segment, double saturation_low, double saturation_high);
	
	void signal_conditionning_Wifi(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_Wifi(Segment& segment, double saturation_low, double saturation_high);	
	

	//Prepare filter
	void init_filter_coefs_Gaussian_LowPass(int size, float std, float gain, float size_mesh);
	void init_filter_coefs_Rectangle_LowPass(int size, float gain, float size_mesh);

	void init_filter_coefs_custom(const vector<double>& coefs_, float size_mesh);
	void init_filter_coefs_custom(double* coefs_, size_t size_, float size_mesh);


	//Reset parameters
	void reset_filter();

	
private:
	
	bool use_measure_criterion(RSSI_measure_set_iterator meas_iterator, Position& position);

	//Pre-treatments
	void anti_fading_concatenation_BLE(Segment& segment, double saturation_low, double saturation_high);
	void anti_fading_concatenation_Wifi(Segment& segment, double saturation_low, double saturation_high);
	
	//Filtering
	void convolution_segment_Ble(Segment& segment, double saturation_low, double saturation_high);
	void convolution_segment_Wifi(Segment& segment, double saturation_low, double saturation_high);
	
	vector<double> mFilterCoefs1D;
	float mSpaceBetweenPosition;		//In meters
};



/****************************************************************************************************/
/*** class async_FIR ***/
/****************************************************************************************************/

class async_FIR : public Filter
{
public:

	//Overloads
	void signal_conditionning_BLE(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_BLE(Segment& segment, double saturation_low, double saturation_high);
	
	void signal_conditionning_Wifi(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_Wifi(Segment& segment, double saturation_low, double saturation_high);	


	void init_filter_params(float coverage, float std, float gain);


	//Reset parameters
	void reset_filter();

private:
	
	bool use_measure_criterion(RSSI_measure_set_iterator meas_iterator, Position& position);

	int generic_median_filter(Position& ref_position, InputMeasure_RSSI& input_rssi);


	float mCoverage;	//in meters
	float mStd;		//in meters
	float mGain; 
};



/****************************************************************************************************/
/*** class PolyFitting ***/
/****************************************************************************************************/

class PolyFitting : public Filter
{
public:
	PolyFitting(void);
	~PolyFitting(void);


	//Overloads	
	void signal_conditionning_BLE(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_BLE(Segment& segment, double saturation_low, double saturation_high);
	
	void signal_conditionning_Wifi(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_Wifi(Segment& segment, double saturation_low, double saturation_high);	


	//Prepare filter
	void init_filter(int reg_order, float max_dist_to_measure) ;


	//Reset parameters
	void reset_filter();


private:
	
	bool use_measure_criterion(RSSI_measure_set_iterator meas_iterator, Position& position);
	
	void signal_filter_generic(Position& ref_position, InputMeasure_RSSI& input_rssi, OutputMeasure_OrderIDs& output_order_ids, OutputMeasure_RSSI& output_rssi, OutputMeasure_NbRep& output_nb_rep, OutputMeasure_StdDev& output_std_dev, double saturation_low, double saturation_high);

	int mRegressionOrder;

	float mCoverage;	//in meters
};



/****************************************************************************************************/
/*** class StatisticalFilter ***/
/****************************************************************************************************/

class StatisticalFilter : public Filter
{
public:

	enum Stat_type {
		default_type = 0, 
		median/*, 
		first_quartile*/
	};
	

	StatisticalFilter(void);
	~StatisticalFilter(void);


	//Overloads
	void signal_conditionning_BLE(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_BLE(Segment& segment, double saturation_low, double saturation_high);
	
	void signal_conditionning_Wifi(Segment& segment, double saturation_low, double saturation_high);
	void signal_filter_Wifi(Segment& segment, double saturation_low, double saturation_high);		


	//Prepare filter
	void init_filter(Stat_type type, float max_dist_to_measure);


	//Reset parameters
	void reset_filter();

private:

	bool use_measure_criterion(RSSI_measure_set_iterator meas_iterator, Position& position);
	
	void signal_filter_generic(Position& ref_position, InputMeasure_RSSI& input_rssi, OutputMeasure_OrderIDs& output_order_ids, OutputMeasure_RSSI& output_rssi, OutputMeasure_NbRep& output_nb_rep, OutputMeasure_StdDev& output_std_dev, double saturation_low, double saturation_high);

	Stat_type mType;

	float mCoverage;	//in meters
};