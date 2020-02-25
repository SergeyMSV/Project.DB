#include "LoadTable.h"

#include <cstdio>

void LoadTable_vehicle_colour(MYSQL* MySQL)
{
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "1") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "2") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "3") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "4") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "5") });
	LoadTable(MySQL, "vehicle_colour", { tSQLQueryParamPair("colour_id", "8") });
}

void LoadTable_vehicle_tm(MYSQL* MySQL)
{
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "Mercedes") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "Opel") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "Zaporozhetz") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "Audi") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "UAZ") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "Shacman") });
	LoadTable(MySQL, "vehicle_tm", { tSQLQueryParamPair("str", "LIAZ") });
}

void LoadTable_vehicle_type(MYSQL* MySQL)
{
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Lorry") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Truck") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Sedan") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Pickup") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Hatchback") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Bus") });
	LoadTable(MySQL, "vehicle_type", { tSQLQueryParamPair("str", "Crossover") });
}

void LoadTable_vehicle_model(MYSQL* MySQL)
{
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "1"), tSQLQueryParamPair("str", "Actros 1841") });
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "1"), tSQLQueryParamPair("str", "Sprinter") });
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "2"), tSQLQueryParamPair("str", "Astra") });
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "2"), tSQLQueryParamPair("str", "Corsa") });
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "2"), tSQLQueryParamPair("str", "Zafira") });
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "2"), tSQLQueryParamPair("str", "Frontera") });//crossover
	LoadTable(MySQL, "vehicle_model", { tSQLQueryParamPair("tm_id", "2"), tSQLQueryParamPair("str", "Omega") });//sedan
}

void LoadTable_vehicle(MYSQL* MySQL, const std::string& type_id, const std::string& model_id, const std::string& colour_id, int qty)
{
	char StrReg[256] = {};
	char StrProdDate[256] = {};

	for (int i = 0; i < qty; ++i)
	{
		std::sprintf(StrReg, "aa%s%02da333", type_id.c_str(), i);
		std::sprintf(StrProdDate, "%04d-%02d-%02d", 2001, 11, 24);

		LoadTable(MySQL, "vehicle",
			{
				tSQLQueryParamPair("type_id", type_id), tSQLQueryParamPair("model_id", model_id), tSQLQueryParamPair("colour_id", colour_id),
				tSQLQueryParamPair("reg", StrReg),tSQLQueryParamPair("prod_date", StrProdDate),
			});
	}
}

void LoadTable_vehicle(MYSQL* MySQL)
{
	LoadTable_vehicle_colour(MySQL);
	LoadTable_vehicle_tm(MySQL);
	LoadTable_vehicle_type(MySQL);

	//Linked tables
	LoadTable_vehicle_model(MySQL);

	//[TBD]Strange code
	LoadTable_vehicle(MySQL, "2", "1", "1", 10);
	LoadTable_vehicle(MySQL, "5", "3", "2", 10);
	LoadTable_vehicle(MySQL, "5", "4", "3", 10);
	LoadTable_vehicle(MySQL, "5", "5", "4", 10);
	LoadTable_vehicle(MySQL, "7", "6", "5", 10);
	LoadTable_vehicle(MySQL, "3", "7", "6", 10);
}