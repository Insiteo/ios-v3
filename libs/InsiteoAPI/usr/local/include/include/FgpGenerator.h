#pragma once

//Includes
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <set>
#include <map>
#include <sys/stat.h>
#include "sqlite3/sqlite3.h"
#ifdef WIN32
#  include <ctime>
#endif

#include "Segment.h"
#include "Position.h"
#include "Path.h"
#include "APlist_parser.h"
#include "Map_info.h"
#include "output_fgp_base_structure_v1.h"
#include "../CommonLibs/Obfuscate/src/obfuscate.h"
#include "FgpQuality_check.h"
#include "Fgp_common_values.h"
#include "Filtering.h"


#ifdef __APPLE__
#include <tr1/tuple>
#define __TUPLE					std::tr1::tuple
#define __MAKE_TUPLE			std::tr1::make_tuple
#define __GET_TUPLE(X)			std::tr1::get<X>
#elif defined(ANDROID)
#include <tr1/tuple>
#define __TUPLE					std::tr1::tuple
#define __MAKE_TUPLE			std::tr1::make_tuple
#define __GET_TUPLE(X)			std::tr1::get<X>
#else
#include <tuple>
#define __TUPLE					std::tuple
#define __MAKE_TUPLE			std::make_tuple
#define __GET_TUPLE(X)			std::get<X>
#endif


//Defines
#define FGPGENERATOR_USE_DB_MEAN					0	//Perform mean on the rssi_dB values
#define FGPGENERATOR_USE_LINEAR_MEAN				1	//Convert rssi to linear power, perform mean and convert the result back to dB

#define FGPGENERATOR_DEFAULT_FGP_VERSION			3
#define FGPGENERATOR_DEFAULT_MAX_RSSI_THRESHOLD		-30
#define FGPGENERATOR_DEFAULT_MIN_RSSI_THRESHOLD		LOW_RSSI_SATURATION_dB
#define FGPGENERATOR_DEFAULT_MEAN_TYPE				FGPGENERATOR_USE_LINEAR_MEAN

#define FGPGENERATOR_INTERP_SEGMENT_MESH			3.0//4.0	//meters
#define FGPGENERATOR_WIFIMAPID_OFFSET				1000		//In order to separate wifi and BLE zones

#define FGP_OPTION_INPUT_DB_PATH					0
#define FGP_OPTION_OUTPUT_DB_PATH					1
#define FGP_OPTION_INPUT_BLEAP_LIST_PATH			2
#define FGP_OPTION_INPUT_WIFIAP_LIST_PATH			3
#define FGP_OPTION_INPUT_POLYGONS_PATH				4
#define FGP_OPTION_INPUT_ARCS_PATH					5
#define FGP_OPTION_VERSION							6
#define FGP_OPTION_MAX_RSSI_THRESHOLD				7
#define FGP_OPTION_MIN_RSSI_THRESHOLD				8
#define FGP_OPTION_MEAN_TYPE						9
#define	FGP_OPTION_MESH_SIZE						10
#define	FGP_OPTION_SEPARATE_TECHNOS					11
//#define FGP_OPTION_USE_DEOBFUSCATE					12


#define FGP_GENERATION_SUCCESS						0
#define FGP_ERROR_NOT_READY							-1
#define FGP_ERROR_CANT_ALLOCATE_FILTER				-2
#define FGP_ERROR_CANT_CREATE_OUTPUT_FILE			-3
#define FGP_ERROR_CANT_OPEN_DATABASE_FILE			-4
#define FGP_ERROR_RETRIVING_BARO_INFORMATION		-5
#define FGP_ERROR_RETRIVING_POSITION_INFORMATION	-6
#define FGP_ERROR_INTERMED_PT_GENERATION_FAILED		-7
#define FGP_ERROR_MEASURE_GENERATION_FAILED			-8
#define FGP_ERROR_DURING_DOTBIN_FILE_ACESS			-9
#define FGP_ERROR_CANT_GENERATE_OTHER_FILES			-10
#define FGP_ERROR_CANT_CLOSE_DATABASE				-11
#define FGP_ERROR_DETERMINE_OBFUSCATE_FLAG			-12



using namespace std;


class FgpGenerator_Baro_on_map
{
public :
	FgpGenerator_Baro_on_map(int map_id = -1, int db_file_id = -1, float pressure_min = -999999, float pressure_max = -999999) :	mMapId(map_id), 
																																	mDbFileId(db_file_id), 
																																	mMinPressureMeasured(pressure_min), 
																																	mMaxPressureMeasured(pressure_max)/*, 
																																	mNbWifiAps(0), 
																																mNbBleAps(0) */{};

	int mMapId;
	int mDbFileId;
	float mMinPressureMeasured;
	float mMaxPressureMeasured;
};


//struct FgpSynthesis
struct FgpGenerator_Synthesis
{
	FgpGenerator_Synthesis() : mNbInputFiles(0) {};

	//Date and time
	time_t mStartGene_tm;
	int mGenerationTime_sec;

	//Nb of input files used
	int mNbInputFiles;


	vector<int> all_maps;
	vector<int> all_ble_order_ids;
	vector<int> all_wifi_order_ids;

	vector<Data_to_replay> replay_data_vect;
	vector<Data_for_fingerprint> fgp_data_vect;

	//vector<FgpGenerator_Baro_on_map> mPressureDuringScans;
	set<int> mMapIds;
	set<int> mDbfileIndexes;
	map<int, map<int, FgpGenerator_Baro_on_map> > mBaroSumUp;
};


//Class FgpGenerator_config
class FgpGenerator_config
{
public:
	FgpGenerator_config() {};
	~FgpGenerator_config() {};

	
	list<string> input_db_path;
	string output_db_path;
	string input_bleAP_list_path;
	string input_wifiAP_list_path;
	string input_polygones_path;
	string input_arcs_path;

	int fgp_version;

	float mesh_size;
	float max_threshold_rssi;
	float min_threshold_rssi;
	int mean_type;
	
	bool separate_wifi_ble_zones;
	bool use_obfusctaed_fingerprint;
};



//Class FgpGenerator
class FgpGenerator
{
public:
	//Public methods : fingerprint generation
	FgpGenerator(void);
	~FgpGenerator(void);


	bool check_input_data();
	bool set_option(void* option_value, int option_nb);
	//bool generate_output_database(FgpSynthesis * p_synthesis = NULL, int percentage = -1, bool create_logtest_file_flag = false);
	int generate_output_database(FgpGenerator_Synthesis * p_synthesis = NULL, int percentage = -1, bool create_logtest_file_flag = false);
	
	
	int prepare_filter_for_dynamic_fingerprint(FilterType type, float param_float_1 = -99, float param_float_2 = -99, float param_float_3 = -99, int param_int_1 = -99, int param_int_2 = -99, int param_int_3 = -99);
	void clear_existing_filter();
	FgpGenerator_config get_current_config();

	
	//Public methods : accessories
	int check_fgp_point_reliability(const string& path_database, int position_id, float threshold);


private:
	//Private methods
	int generate_fingerprint_v1(FgpGenerator_Synthesis * p_synthesis = NULL, int percentage = -1, bool create_logtest_file_flag = false);
	int generate_fingerprint_v3(FgpGenerator_Synthesis * p_synthesis = NULL, int percentage = -1, bool create_logtest_file_flag = false);


	bool create_output_files_fgp_v1();
	bool create_output_files_fgp_v3(const list<Position>& positions_list_, const APlist_parser& ble_ap_list, const APlist_parser& wifi_ap_parser, const map<int, Map_info>& map_mapping_);	

	bool baro_estimation(sqlite3* h_database, int file_ind, FgpGenerator_Synthesis * p_synthesis);
	bool populate_position_table(sqlite3 * h_database, list<Position>& position_collection_, list<Segment>& segment_collection_, list<Path>& path_collection, map<int, Map_info>& map_mapping_, FgpGenerator_Synthesis* p_synthesis);


	//Private methods : dynamic fingerprint
	
	bool generate_intermediate_positions(Segment& segment_);
	bool generate_intermediate_positions(Path& path_);

	bool generate_measurements_dynamic_from_db(sqlite3* h_database, int file_ind, Segment& segment_, APlist_parser& aplist_ble, map<string,string>& encrypted_mac_container_ble, APlist_parser& aplist_wifi, map<int, Map_info>& map_mapping_, ofstream * p_fileTest, int decimate_for_logtestfile, FgpGenerator_Synthesis* p_synthesis);
	bool generate_measurements_dynamic_from_db(sqlite3* h_database, int file_ind, Path& path_, APlist_parser& aplist_ble, map<string,string>& encrypted_mac_container_ble, APlist_parser& aplist_wifi, map<int, Map_info>& map_mapping_, Filter* pFilter, ofstream * p_fileTest, int decimate_for_logtestfile, FgpGenerator_Synthesis* p_synthesis);


	//Private methods : static fingerprint
	bool generate_measurements_static_from_db(sqlite3* h_database, int file_ind, Segment& segment_, APlist_parser& aplist_ble, map<string,string>& encrypted_mac_container_ble, APlist_parser& aplist_wifi, map<int, Map_info>& map_mapping_, ofstream * p_fileTest, int decimate_for_logtestfile, FgpGenerator_Synthesis* p_synthesis);


	//Private methods : manage files	
	/*inline*/ void write_file_header_to_dot_bin_file(ofstream * dot_bin_fgpdb, fgp_base_file_header * p_header);
	/*inline*/ void write_point_header_to_dot_bin_file(ofstream * dot_bin_fgpdb, fgp_point_descriptor_header * p_pt_header);
	void write_segment_to_dot_bin_file(ofstream * dot_bin_fgpdb, Segment& segment_);
	bool copy_file(string const& input_file_path, string const& output_file_path);
	//bool create_version_file(int v_);
	inline bool exists_test (const std::string& name);
	


	//Private methods : others
	void clear_segment_measurements(Segment& segment_);
	void clear_segment_measurements(Path& path_);
	double mean_rssi_vect(const vector<double>& rssi);
	double std_deviation(const vector<double>& rssi);
	double rssi_dB_2_linear(double rssi);
	double rssi_linear_2_dB(double rssi);
	bool isObfuscateDataDetect_from_db(sqlite3* h_database, int& obfusation_type);


private:
	list<string> input_db_path;	
	string output_db_path;
	string input_bleAP_list_path;
	string input_wifiAP_list_path;
	string input_polygones_path;
	string input_arcs_path;
	//string polygones_de_transition ?
	int fgp_version;

	double mMaxThreshold_RSSI;
	double mMinThreshold_RSSI;
	double mMaxThreshold_RSSI_dB;
	double mMinThreshold_RSSI_dB; 
	float mMeshSize;
	int mMeanType;

	bool mReady;
	bool mSeparateLocationTechnos;
	bool mObfuscatedData;

	Filter * mPathFilter;
};

