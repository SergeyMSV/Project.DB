#pragma once

#include <mysql.h>
#include <mysqld_error.h>

#include <string>
#include <vector>
#include <utility>

void DB_Open(MYSQL* mysql, const std::string& dbname, int& cerr);

typedef std::pair<std::string, std::string> tSQLQueryParamPair;
typedef std::vector<tSQLQueryParamPair> tSQLQueryParam;

void DB_Insert(MYSQL* mysql, const std::string& table, const tSQLQueryParam& prm, int& cerr);

typedef std::vector<std::vector<tSQLQueryParamPair>> tVectorSQLQueryParam;
void DB_Insert(MYSQL* mysql, const std::string& table, const tVectorSQLQueryParam& prms, int& cerr);