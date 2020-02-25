#pragma once

#include <mysql.h>

#include <string>
#include <vector>
#include <utility>

typedef std::pair<std::string, std::string> tSQLQueryParamPair;
typedef std::vector<tSQLQueryParamPair> tSQLQueryParam;

void LoadTable(MYSQL* MySQL, const std::string& table, const tSQLQueryParam& prm);
