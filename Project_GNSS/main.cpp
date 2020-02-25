#include "DB.h"

#include <iostream>

//void LoadTable_colour(MYSQL* MySQL);
//void LoadTable_phone(MYSQL* MySQL);
void LoadTable_vehicle(MYSQL* MySQL);

//void LoadTable_people(MYSQL* MySQL);



int main()
{
	MYSQL MySQL{};

	mysql_init(&MySQL);

	mysql_real_connect(&MySQL, "127.0.0.1", "root", "", "", 3306, "", 0);//DB is not specified intentionally

	unsigned int MySQL_CERR = mysql_errno(&MySQL);

	DB_Open(&MySQL, "test_gnss3", MySQL_CERR);

	if (MySQL_CERR)
	{
		mysql_close(&MySQL);
		std::cout << "ERR DB: UNKNOWN";
		return 0;
	}
	

	if (!mysql_errno(&MySQL))
	{
		char* SomeStr = mysql_get_server_info(&MySQL);

		if (SomeStr != nullptr)
		{

			std::cout << "Server info: " << SomeStr << "\n";

			//LoadTable_colour(&MySQL);

			//LoadTable_phone(&MySQL);

			LoadTable_vehicle(&MySQL);

			//LoadTable_people(&MySQL);
		}

		mysql_close(&MySQL);
	}
	return 0;
}