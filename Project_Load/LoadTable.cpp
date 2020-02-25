#include "LoadTable.h"

#include <iostream>

#include <cstdio>

void LoadTable(MYSQL* MySQL, const std::string& table, const tSQLQueryParam& prm)
{
	char Str[256] = {};

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

	if (mysql_real_query(MySQL, Str, std::strlen(Str)))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
	{
		std::cout << "ERR INSERT Table: " << table << '\n';
	}
}