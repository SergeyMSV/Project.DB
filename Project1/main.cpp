#include <mysql.h>

#include <iostream>

#include <clocale>
#include <cstring>

#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_CTYPE, "rus");
	//std::setlocale(LC_ALL, "1251");
	//std::setlocale(LC_ALL, "CP1251");
	//std::setlocale(LC_ALL, "ru_RU.UTF-8");

	std::cout << "PREVED SQL\n";

	MYSQL MySQL{};

	mysql_init(&MySQL);

	mysql_real_connect(&MySQL, "127.0.0.1", "root", "", "town", 3306, "", 0);

	const char* StrServerInfo = mysql_get_server_info(&MySQL);

	std::cout <<"Server info: "<< StrServerInfo << "\n";

	//const char* StrCharset = mysql_character_set_name(&MySQL);

	//std::cout << "Charset: " << StrCharset << "\n";

	//if (!mysql_set_character_set(&MySQL, "utf8"))//shall be set std::setlocale(LC_ALL, "ru_RU.UTF-8");
	if (!mysql_set_character_set(&MySQL, "cp1251"))
	{
		const char Req[] = "SELECT * FROM tmp_people_name";

		if (!mysql_real_query(&MySQL, Req, sizeof(Req) - 1))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
		{
			MYSQL_RES* MySQLRes = mysql_store_result(&MySQL);
			//MYSQL_RES* MySQLRes = mysql_use_result(&MySQL);

			if (MySQLRes != nullptr)
			{
				unsigned int ColQty = mysql_num_fields(MySQLRes);
				unsigned int RowQty = mysql_num_rows(MySQLRes);//For unbuffered result sets, mysql_num_rows() will not return the correct number of rows.

				std::cout << "Col: " << ColQty << " Row: " << RowQty << "\n";

				if (RowQty > 0)
				{
					struct tRowParse
					{
						char* ID = 0;
						char* Str = 0;
						char* SexMale = 0;
					};

					while (MYSQL_ROW row = mysql_fetch_row(MySQLRes))
					{
						//MYSQL_ROW_OFFSET RowIndexCurr = mysql_row_tell(MySQLRes);//This function will not work if the result set was obtained by mysql_use_result().
						//MYSQL_FIELD* Value = mysql_fetch_field_direct(MySQLRes, 0);

						unsigned long* RawValueSize = mysql_fetch_lengths(MySQLRes);

						tRowParse* RowParse = reinterpret_cast<tRowParse*>(row);

						std::cout //<< RowIndexCurr
							<< " ID(" << RawValueSize[0] << "): " << RowParse->ID
							<< " Str(" << RawValueSize[1] << "): " << RowParse->Str
							<< " SexMale(" << RawValueSize[2] << "): " << RowParse->SexMale << "\n";
					}

					std::cout << "Row: " << ColQty << " Row: " << RowQty << "\n";
				}

				mysql_free_result(MySQLRes);
			}
		}
	}

	/*{
		const char Req[] = "DROP TABLE IF EXISTS tmp_medved, tmp_preved";

		if (!mysql_real_query(&MySQL, Req, sizeof(Req) - 1))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
		{
			std::cout << " The tables dropped\n";
		}
	}

	{
		const char Req[] = "CREATE TABLE tmp_medved LIKE medved";

		if (!mysql_real_query(&MySQL, Req, sizeof(Req) - 1))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
		{
			std::cout << " The tables created\n";

			const char Req[] = "INSERT INTO tmp_medved SELECT * FROM medved WHERE id in (SELECT id FROM preved)";
			//const char Req[] = "insert into tmp_medved select * from medved";

			if (!mysql_real_query(&MySQL, Req, sizeof(Req) - 1))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
			{
				std::cout << " #2\n";


			}
		}
	}*/


	//drop table if exists tmp_produit, tmp_lppr, tmp_locprod;

	//create table tmp_produit like produit;

	mysql_close(&MySQL);

	return 0;
}