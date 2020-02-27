#include "DB.h"

#include <cstdio>

void DB_Open(MYSQL* mysql, const std::string& dbname, int& cerr)
{
	if (!cerr)
	{
		cerr = mysql_query(mysql, std::string("USE " + dbname).c_str());

		if (!cerr)
		{
			// 1. check version of the DB
			// 2. update it if needed
		}
		else
		{
			if (mysql_errno(mysql) == ER_BAD_DB_ERROR)
			{
				cerr = mysql_query(mysql, std::string("CREATE DATABASE IF NOT EXISTS " + dbname).c_str());

				if (!cerr)
				{
					cerr = mysql_query(mysql, std::string("USE " + dbname).c_str());
				}

				const std::vector<std::string> ReqList
				{
					"CREATE TABLE system (update_id INT(2) NOT NULL AUTO_INCREMENT, version VARCHAR(20) NOT NULL DEFAULT '', PRIMARY KEY(update_id));",
					"INSERT INTO system (version) VALUE('DuperDBase 0.0.1');",
					"CREATE TABLE rcv (rcv_id INT(2) NOT NULL AUTO_INCREMENT, timestamp DATETIME NOT NULL, model VARCHAR(50) NOT NULL DEFAULT '', ident VARCHAR(50) NOT NULL DEFAULT '', PRIMARY KEY(rcv_id), UNIQUE INDEX(ident));",
					"CREATE TABLE pos (pos_id INT(10) NOT NULL AUTO_INCREMENT, timestamp DATETIME NOT NULL, gnss INT(2), date_time DATETIME, valid BOOLEAN, latitude DOUBLE, longitude DOUBLE, altitude DOUBLE, speed FLOAT, course FLOAT, rcv_id INT(2) NOT NULL, update_id INT(2) NOT NULL, PRIMARY KEY(pos_id), INDEX(timestamp));",
					"CREATE TABLE sat (pos_id INT(10) NOT NULL, sat_id INT(2) NOT NULL, elevation INT(2), azimuth INT(3), snr INT(2), PRIMARY KEY(pos_id, sat_id), INDEX(pos_id, sat_id));",
				};

				for (auto& i : ReqList)
				{
					if (!cerr)
					{
						mysql_query(mysql, i.c_str());

						cerr = mysql_errno(mysql);
					}
				}
			}
		}
	}
}

void DB_Insert(MYSQL* mysql, const std::string& table, const tSQLQueryParam& prm, int& cerr)
{
	if (!cerr)
	{
		char Str[256]{};

		std::string StrPrm;
		std::string StrValue;

		for (std::size_t i = 0; i < prm.size(); ++i)
		{
			StrPrm += prm[i].first;
			StrValue += "'" + prm[i].second + "'";

			if (i < prm.size() - 1)
			{
				StrPrm += ',';
				StrValue += ',';
			}
		}

		std::sprintf(Str, "INSERT INTO %s (%s) VALUE(%s);", table.c_str(), StrPrm.c_str(), StrValue.c_str());

		cerr = mysql_real_query(mysql, Str, std::strlen(Str));//Contrary to the mysql_query() function, mysql_real_query is binary safe.
	}
}

void DB_Insert(MYSQL* mysql, const std::string& table, const tVectorSQLQueryParam& prms, int& cerr)
{
	for (auto& prm : prms)
	{
		DB_Insert(mysql, table, prm, cerr);

		if (cerr)
			break;
	}
}