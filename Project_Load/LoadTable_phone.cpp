#include "LoadTable.h"

#include <cstdio>

void LoadTable_phone(MYSQL* MySQL, int abc, const std::string& type)
{
	char Str[256] = {};

	for (int i = 0; i < 1000; ++i)
	{
		std::sprintf(Str, "+5-%03d-000-%04d", abc, i);

		LoadTable(MySQL, "phone", { tSQLQueryParamPair("str", Str), tSQLQueryParamPair("phone_type", type), });
	}
}

void LoadTable_phone(MYSQL* MySQL)
{
	LoadTable_phone(MySQL, 0, "cell");
	LoadTable_phone(MySQL, 1, "home");
	LoadTable_phone(MySQL, 2, "office");
}
