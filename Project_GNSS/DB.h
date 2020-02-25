#pragma once

#include <mysql.h>
#include <mysqld_error.h>

#include <string>

void DB_Open(MYSQL* mysql, const std::string& dbname, unsigned int& cerr);
