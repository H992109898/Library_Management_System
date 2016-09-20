#include "stdafx.h"
#include"sql_utils.h"
#include "mysql.h"
#include <cstdlib>
#include <cstring>
#include<fstream>

#pragma comment(lib, "libmysql.lib")
sql_utils::sql_utils(){
	this->myCont = new MYSQL;
	mysql_init(this->myCont);

	if (mysql_real_connect(myCont, host, user, pswd, table, port, NULL, 0))
		;
	else
		AfxMessageBox(_T("数据库连接失败!"));



	const char databaseInit[][500] = { 
		"CREATE DATABASE IF NOT EXISTS media_library_management_system;",
		"USE media_library_management_system;",

		//create books table;
		"CREATE TABLE IF NOT EXISTS books(id BIGINT UNSIGNED UNIQUE KEY NOT NULL,\
		title VARCHAR(50) NOT NULL,\
		author VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		productionNationality VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		classification INT UNSIGNED NOT NULL DEFAULT 1,\
		width INT UNSIGNED NOT NULL DEFAULT 0,\
		height INT UNSIGNED NOT NULL DEFAULT 0,\
		hasVideoDisc BOOLEAN NOT NULL DEFAULT FALSE\
		videoDiscId BIGINT UNSIGNED\
		E_Resourse BOOLEAN NOT NULL DEFAULT FALSE);",

		//create videos table;
		"CREATE TABLE vedios(...) IF NOT EXISTS;",
		//create pictures table;
		"CREATE TABLE pictures(...) IF NOT EXISTS;"};

	
	std::ofstream out("out.txt");


	if (mysql_real_query(myCont, databaseInit[0], strlen(databaseInit[0]))!=0)
	{
		const char* pCh = mysql_error(myCont);
		out << pCh << std::endl;
	}

	if (mysql_real_query(myCont, databaseInit[1], strlen(databaseInit[1])) != 0)
	{
		const char* pCh = mysql_error(myCont);
		out << pCh << std::endl;
	}

	if (mysql_real_query(myCont, databaseInit[2], strlen(databaseInit[2])) != 0)
	{
		const char* pCh = mysql_error(myCont);
		out << pCh << std::endl;
	}
	//mysql_real_query(myCont, databaseInit[1], strlen(databaseInit[1]));
	//mysql_real_query(myCont, databaseInit[2], strlen(databaseInit[2]));
	//mysql_real_query(myCont, databaseInit[3], strlen(databaseInit[3]));
	//mysql_real_query(myCont, databaseInit[4], strlen(databaseInit[4]));

}

/*
bool sql_utils::insert(const picture_model& picture){
	char* sqlQuery = new char[200];
	sqlQuery = "INSERT INTO picture_table (id,title,author,productionNationality,classification,width,height,E_Resourse) VALUES(";
	//strcat(sqlQuery, format)
	if (mysql_real_query(myCont, sqlQuery, strlen(sqlQuery)) != 0){
		const char* pCh = mysql_error(myCont);
		//out << pCh << std::endl;
		//弹窗提醒插入失败并且给出报错信息。
	}
	return true;
}

bool sql_utils::insert(const book_model& picture){
	return true;
}
bool sql_utils::insert(const video_model& picture){
	return true;
}

*/