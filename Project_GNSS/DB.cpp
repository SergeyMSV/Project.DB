#include "DB.h"

void DB_Open(MYSQL* mysql, const std::string& dbname, unsigned int& cerr)
{
	if (!cerr)
	{
		std::string Req = "USE " + dbname;

		if (mysql_query(mysql, Req.c_str()))
		{
			if (mysql_errno(mysql) == ER_BAD_DB_ERROR)
			{
				Req = "CREATE DATABASE IF NOT EXISTS " + dbname;
				mysql_query(mysql, Req.c_str());

				//1. create all the structure
			}
		}
		//else
		//{
		// check version of the DB and update it if needed
		//}
		cerr = mysql_errno(mysql);
	}
}