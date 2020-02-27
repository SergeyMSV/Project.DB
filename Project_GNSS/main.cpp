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

		{
			tVectorSQLQueryParam Query
			{
				{{"timestamp", "2020-02-26 12.21:34.1234567"}, {"model", "Vasia DuperDev 4.12.01"}, {"ident", "first"}},
				{{"timestamp", "2020-02-26 12.21:34.1234567"}, {"model", "Vasia DuperDev 4.12.02"}, {"ident", "second"}},
				{{"timestamp", "2020-02-26 12.21:34.1234567"}, {"model", "Vasia DuperDev 4.12.34"}, {"ident", "third"}},
				{{"timestamp", "2020-02-26 12.21:34.1234567"}, {"model", "Vasia DuperDev 4.12.04"}, {"ident", "forth"}},
			};

			DB_Insert(&MySQL, "rcv", Query, Cerr);
		}

		{
			tVectorSQLQueryParam Query
			{
				{{"timestamp", "2020-02-28 14.23:48"}, {"rcv_id", "2"}, {"update_id", "1"}},
				{{"timestamp", "2020-02-28 14.23:48"}, {"gnss", "1"}, {"date_time", "2020-02-23 11.22.33"}, {"valid", "1"}, {"latitude", "55.123456"}, {"longitude", "37.123456"}, {"altitude", "23.45"}, {"speed", "12.34"}, {"course", "123.45"}, {"rcv_id", "2"}, {"update_id", "1"}},
				{{"timestamp", "2020-02-28 14.23:49"}, {"gnss", "1"}, {"date_time", "2020-02-23 11.22.34"}, {"valid", "0"}, {"latitude", "55.123457"}, {"longitude", "37.123457"}, {"altitude", "23.45"}, {"speed", "12.34"}, {"course", "123.45"}, {"rcv_id", "2"}, {"update_id", "1"}},
				{{"timestamp", "2020-02-28 14.23:50"}, {"gnss", "1"}, {"date_time", "2020-02-23 11.22.35"}, {"valid", "1"}, {"latitude", "55.123458"}, {"longitude", "37.123458"}, {"altitude", "23.45"}, {"speed", "12.34"}, {"course", "123.45"}, {"rcv_id", "2"}, {"update_id", "1"}},
				{{"timestamp", "2020-02-28 14.23:51"}, {"gnss", "1"}, {"date_time", "2020-02-23 11.22.36"}, {"valid", "1"}, {"latitude", "55.123459"}, {"longitude", "37.123459"}, {"altitude", "23.45"}, {"speed", "12.34"}, {"course", "123.45"}, {"rcv_id", "2"}, {"update_id", "1"}},
			};

			DB_Insert(&MySQL, "pos", Query, Cerr);
		}

		{
			tVectorSQLQueryParam Query
			{
				{{"pos_id", "1"}, {"sat_id", "31"}, {"elevation", "21"}, {"azimuth", "121"}, {"snr", "91"}},
				{{"pos_id", "1"}, {"sat_id", "32"}, {"elevation", "22"}, {"azimuth", "122"}, {"snr", "92"}},
				{{"pos_id", "1"}, {"sat_id", "33"}, {"elevation", "23"}, {"azimuth", "123"}, {"snr", "93"}},
				{{"pos_id", "1"}, {"sat_id", "34"}, {"elevation", "24"}, {"azimuth", "124"}, {"snr", "94"}},

				{{"pos_id", "2"}, {"sat_id", "31"}, {"elevation", "25"}, {"azimuth", "125"}, {"snr", "95"}},
				{{"pos_id", "2"}, {"sat_id", "32"}, {"elevation", "26"}, {"azimuth", "126"}, {"snr", "96"}},
				{{"pos_id", "2"}, {"sat_id", "33"}, {"elevation", "27"}, {"azimuth", "127"}, {"snr", "97"}},
				{{"pos_id", "2"}, {"sat_id", "34"}, {"elevation", "28"}, {"azimuth", "128"}, {"snr", "98"}},
			};

			DB_Insert(&MySQL, "sat", Query, Cerr);
		}

		mysql_close(&MySQL);
	}

	return 0;
}