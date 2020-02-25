#include <mysql.h>

#include <iostream>

#include <string>
#include <vector>

#include <cstdio>

void LoadTable_phone(MYSQL* MySQL, const std::string& table, int abc, const std::string& type)
{
	char Str[256] = {};

	for (int i = 0; i < 1000; ++i)
	{
		std::sprintf(Str, "INSERT INTO %s (phone_number, phone_type) VALUE('+5-%03d-000-%04d','%s');", table.c_str(), abc, i, type.c_str());

		if (mysql_real_query(MySQL, Str, std::strlen(Str)))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
		{
			std::cout << "Something wrong!!!\n";

			break;
		}
	}
}

void LoadTable_phone(MYSQL* MySQL)
{
	LoadTable_phone(MySQL, "phone", 0, "cell");
	LoadTable_phone(MySQL, "phone", 1, "home");
	LoadTable_phone(MySQL, "phone", 2, "office");
}