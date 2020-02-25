#include "LoadTable.h"

#include <utilsCharset.h>

#include <string>

#include <iostream>
#include <fstream>

#include <Windows.h>

#include <clocale>
#include <codecvt>
#include <cstring>

void LoadTable_people(MYSQL* MySQL, const std::string& fileName, bool male)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//std::setlocale(LC_ALL, "ru_RU.UTF-8");

	std::cout << "Load from file: " << fileName << '\n';

	if (!mysql_set_character_set(MySQL, "cp1251"))
		//if (!mysql_set_character_set(MySQL, "utf8"))//shall be set std::setlocale(LC_ALL, "ru_RU.UTF-8");
	{
		//std::locale Loc(std::locale(), new std::codecvt_utf8<wchar_t>);

		//std::wfstream File;
		//File.open(FileName, std::wfstream::in);
		//File.imbue(Loc);

		//std::wstring StrLoad;

		std::fstream File;
		File.open(fileName, std::fstream::in);

		while (File.is_open() && !File.eof())
		{
			std::string StrLoad;

			File >> StrLoad;

			if (StrLoad.size() <= 1 * 2 || StrLoad[0] == '(')//UTF8
				continue;

			//std::locale loc(std::locale(), new std::codecvt_utf8<char32_t>);
			//std::basic_ofstream<char32_t> ofs("test.txt");
			//ofs.imbue(loc);

			//std::cout << "Writing to file (UTF-8)... ";
			//ofs << str;
			//std::cout << "done!\n";

			int Size = StrLoad.size() + 1;

			char* StrCP1251 = new char[Size];

			utils::charset::Convert_UTF8_to_Windows1251(StrLoad.data(), StrCP1251, Size);

			//std::cout << StrCP1251 << '\n';
			//std::cout << StrLoad << '\n';

			std::string Request("INSERT INTO people_name (str, sex_male) VALUE('" + std::string(StrCP1251) + "', '" + std::string(male ? "1":"0") +"');");

			if (mysql_real_query(MySQL, Request.c_str(), Request.size()))//Contrary to the mysql_query() function, mysql_real_query is binary safe.
			{
				std::cout << "ERR INSERT Table: people_name -> "<< StrCP1251 <<'\n';
			}

			delete[] StrCP1251;
		}

		File.close();
	}
}

void LoadTable_people(MYSQL * MySQL)
{
	LoadTable_people(MySQL, "Source-Name_male.txt", true);
	LoadTable_people(MySQL, "Source-Name_female.txt", false);

	//[TBD]Strange code
	LoadTable(MySQL, "people_person", { tSQLQueryParamPair("name_id", "1"), tSQLQueryParamPair("birthday", "1982-01-02") });
	LoadTable(MySQL, "people_person", { tSQLQueryParamPair("name_id", "8"), tSQLQueryParamPair("birthday", "1988-03-05") });
	LoadTable(MySQL, "people_person", { tSQLQueryParamPair("name_id", "11"), tSQLQueryParamPair("birthday", "2000-04-07") });
	LoadTable(MySQL, "people_person", { tSQLQueryParamPair("name_id", "34"), tSQLQueryParamPair("birthday", "2003-09-21") });

	LoadTable(MySQL, "people_person_phone", { tSQLQueryParamPair("person_id", "1"),  tSQLQueryParamPair("phone_id", "2048"), tSQLQueryParamPair("buy_date", "2015-02-11") });
	LoadTable(MySQL, "people_person_phone", { tSQLQueryParamPair("person_id", "2"),  tSQLQueryParamPair("phone_id", "3045"), tSQLQueryParamPair("buy_date", "2015-03-10") });
	LoadTable(MySQL, "people_person_phone", { tSQLQueryParamPair("person_id", "1"),  tSQLQueryParamPair("phone_id", "3048"), tSQLQueryParamPair("buy_date", "2015-02-12") });
	LoadTable(MySQL, "people_person_phone", { tSQLQueryParamPair("person_id", "1"),  tSQLQueryParamPair("phone_id", "4048"), tSQLQueryParamPair("buy_date", "2015-02-13") });

	LoadTable(MySQL, "people_person_vehicle", { tSQLQueryParamPair("person_id", "1"),  tSQLQueryParamPair("vehicle_id", "1"), tSQLQueryParamPair("buy_date", "2014-01-15") });
	LoadTable(MySQL, "people_person_vehicle", { tSQLQueryParamPair("person_id", "4"),  tSQLQueryParamPair("vehicle_id", "2"), tSQLQueryParamPair("buy_date", "2013-02-03") });
}