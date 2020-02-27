#include "DB.h"

#include <iostream>

int main()
{
	MYSQL MySQL{};

	mysql_init(&MySQL);

	mysql_real_connect(&MySQL, "127.0.0.1", "root", "", "", 3306, "", 0);//DB is not specified intentionally

	unsigned int MySQL_CERR = mysql_errno(&MySQL);

	if (!MySQL_CERR)
	{
		int Cerr = 0;

		DB_Open(&MySQL, "test_tower1", Cerr);

		if (Cerr)
		{
			MySQL_CERR = mysql_errno(&MySQL);
			std::cout << "ERR DB: " << MySQL_CERR << '\n';
			mysql_close(&MySQL);
			return 0;
		}

		if (!mysql_errno(&MySQL))
		{
			char* SomeStr = mysql_get_server_info(&MySQL);

			if (SomeStr != nullptr)
			{
				std::cout << "Server info: " << SomeStr << "\n";
			}
		}

		//Load data...

		std::string Timestamp = DB_GetTimestamp(std::time(nullptr));

		DB_Insert(&MySQL, Timestamp, "Blablabla 11", "super new1", Cerr);
		DB_Insert(&MySQL, Timestamp, "Blablabla 11", "super new2", Cerr);
		DB_Insert(&MySQL, Timestamp, "Blablabla 12", "super new3", Cerr);
		DB_Insert(&MySQL, Timestamp, "Blablabla 14", "super new4", Cerr);
		DB_Insert(&MySQL, Timestamp, "Blablabla 11", "super new5", Cerr);

		DB_Insert(&MySQL, Timestamp, 2, "2020-01-28 14.23:51", true, 55.123456, 37.123456, 234.546344, 345.219, 123.345, 2, 1, Cerr);
		DB_Insert(&MySQL, Timestamp, 2, "2020-01-28 14.23:52", true, 55.123456, 37.123456, 234.546344, 345.219, 123.345, 2, 1, Cerr);
		DB_Insert(&MySQL, Timestamp, 2, "2020-01-28 14.23:53", true, 55.123456, 37.123456, 234.546344, 345.219, 123.345, 2, 1, Cerr);
		DB_Insert(&MySQL, Timestamp, 1, "2020-01-28 14.23:54", true, 55.123456, 37.123456, 234.546344, 345.219, 123.345, 2, 1, Cerr);
		DB_Insert(&MySQL, Timestamp, 1, "2020-01-28 14.23:55", true, 55.123456, 37.123456, 234.546344, 345.219, 123.345, 2, 1, Cerr);

		DB_Insert(&MySQL, 3, 31, 12, 345, 91, Cerr);
		DB_Insert(&MySQL, 3, 32, 12, 345, 91, Cerr);
		DB_Insert(&MySQL, 3, 33, 12, 345, 91, Cerr);
		DB_Insert(&MySQL, 3, 34, 12, 345, 91, Cerr);
		DB_Insert(&MySQL, 3, 35, 12, 345, 91, Cerr);
		DB_Insert(&MySQL, 5, 31, 13, 345, 91, Cerr);
		DB_Insert(&MySQL, 5, 32, 13, 345, 91, Cerr);
		DB_Insert(&MySQL, 5, 33, 13, 345, 91, Cerr);
		DB_Insert(&MySQL, 5, 34, 13, 345, 91, Cerr);
		DB_Insert(&MySQL, 5, 35, 13, 345, 91, Cerr);

		if (Cerr)
		{
			std::cout << "ERR DB: " << mysql_errno(&MySQL) << '\n';
		}

		mysql_close(&MySQL);
	}

	return 0;
}