#include "LoadTable.h"

void LoadTable_vehicle_colour(MYSQL* MySQL)
{
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "1") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "2") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "3") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "4") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "5") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "8") });
}

void LoadTable_vehicle(MYSQL* MySQL)
{
	LoadTable_vehicle_colour(MySQL);
}