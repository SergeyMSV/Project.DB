#pragma once

#include <mysql.h>
#include <mysqld_error.h>

#include <string>
#include <vector>
#include <utility>

#include <ctime>

void DB_Open(MYSQL* mysql, const std::string& dbname, int& cerr);

void DB_Insert(MYSQL* mysql, const std::string& timestamp, const std::string& model, const std::string& ident, int& cerr);
void DB_Insert(MYSQL* mysql, const std::string& timestamp, char gnss, const std::string& dateTime, bool valid, double latitude, double longitude, double altitude, double speed, double course, unsigned char rcv_id, unsigned char update_id, int& cerr);
void DB_Insert(MYSQL* mysql, int pos_id, int sat_id, int elevation, int azimuth, int snr, int& cerr);

std::string DB_GetTimestamp(const std::time_t& timestamp);
