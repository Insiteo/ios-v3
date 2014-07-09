#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <cctype>


#if defined(__APPLE__)
#  include <tr1/unordered_map>
#  define __UNORDERED_MAP   std::tr1::unordered_map
# include "InsiteoMACaddress.h"
#elif defined(ANDROID)
#  include <tr1/unordered_map>
#  define __UNORDERED_MAP   std::tr1::unordered_map
# include "../../../EmbeddedLoc_trunk/src/EncryptionLib/src/InsiteoMACaddress.h"
#else
#  include <unordered_map>
#  define __UNORDERED_MAP   unordered_map
# include "..\..\..\EmbeddedLoc_trunk\src\EncryptionLib\src\InsiteoMACaddress.h"
#endif


using namespace std;

//-------
class AP_descriptor
{
public:/*
	enum techno{ Wifi, Ble };*/


	AP_descriptor() {};
	~AP_descriptor() {};


	string MACaddress;
	int orderID;/*
	techno techno_; */
};



//-------
class APlist_parser
{
public:
	APlist_parser(void);
	~APlist_parser(void);
	
	
	//Automatically set content
	bool add_AP_list_file(string const& path_);

	
	//Manually modify content
	int add_AP(string const& ap_mac_);


	//Check content
	string get_mac_from_order_id(int order_id) const;
	int get_order_id_from_mac(string const& mac) const;
	list<AP_descriptor>::const_iterator get_APdescriptor_from_order_id(int order_id) const;
	list<AP_descriptor>::const_iterator get_APdescriptor_from_mac(string const& mac) const;
	size_t get_nb_of_ap() const {return mAPdescriptors.size();};
	void get_order_ids_as_vector(vector<int>& ref_output_vector);


	//Reset
	void reset();


	//Other
	bool write_APlist_file(string const& path, bool use_encryption_flag) const;



private:
	list<AP_descriptor> mAPdescriptors;
	__UNORDERED_MAP<int, list<AP_descriptor>::iterator> mOrderID_2_descriptor;
	__UNORDERED_MAP<string, list<AP_descriptor>::iterator> mMAC_2_descriptor;
};

