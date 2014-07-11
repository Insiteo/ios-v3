#pragma once

#include <stdio.h>
#include <string>

/* This is the description of the format of a v.1 fingerprint output file (FGP_with_BLE.bin) */
/* Note that this output format is exactly the same for the v.2 fgp format */


/* Data structures */

//Header of the FGP_with_BLE.bin file
typedef struct fgp_base_file_header {
	unsigned char nb_Wifi_AP[3];
	unsigned char nb_BLE_AP[3];
} fgp_base_file_header;


//Header of a point descriptor 
typedef struct fgp_point_descriptor_header {
	unsigned char nb_Wifi_AP[2];
	unsigned char nb_BLE_AP[2];
	unsigned char X_mm[3];
	unsigned char Y_mm[3];
	unsigned char Map_id[3];
} fgp_point_descriptor_header;


//Wifi measurement descriptor
typedef struct wifi_measurement {
	unsigned char order_id[2];
	unsigned char rssi[1];
} wifi_measurement;


//Wifi measurement descriptor
typedef struct ble_measurement {
	unsigned char order_id[2];
	unsigned char rssi[1];
	unsigned char nb_rep[1];
	unsigned char std_dev[1];
} ble_measurement;



/* Functions to fill the data structures */

// round()
int round(float f_);

// make_fgp_base_file_header()
fgp_base_file_header make_fgp_base_file_header(int nb_Wifi_AP, int nb_BLE_AP);

// make_fgp_point_descriptor_header()
fgp_point_descriptor_header make_fgp_point_descriptor_header(int nb_Wifi_AP, int nb_BLE_AP, float X_m, float Y_m, int Map_id);

// make_wifi_measurement()
wifi_measurement make_wifi_measurement(int order_id, float rssi);

// make_ble_measurement()
ble_measurement make_ble_measurement(int order_id, float rssi, int nb_rep, float std_dev);
