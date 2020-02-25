#include "LoadTable.h"

void LoadTable_colour(MYSQL* MySQL)
{
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Black") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Red") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Green") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Yellow") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Blue") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Magenta") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "Cyan") });
	LoadTable(MySQL, "colour", { tSQLQueryParamPair("str", "White") });
}