#include "stdafx.h"
#include"sql_utils.h"
#include "mysql.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

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

		//create pictures table;
		"CREATE TABLE IF NOT EXISTS pictures(id BIGINT UNSIGNED UNIQUE KEY NOT NULL,\
		title VARCHAR(50) NOT NULL,\
		author VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		productionNationality VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		classification INT UNSIGNED NOT NULL DEFAULT 1,\
		width INT UNSIGNED NOT NULL DEFAULT 0,\
		height INT UNSIGNED NOT NULL DEFAULT 0,\
		E_Resourse BOOLEAN NOT NULL DEFAULT FALSE);",
		
		//create videos table;   //production_time request param as string format yyyy-mm-dd; 
		"CREATE TABLE IF NOT EXISTS videos(id BIGINT UNSIGNED UNIQUE KEY NOT NULL,\
		title VARCHAR(50) NOT NULL,\
		author VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		classification INT UNSIGNED NOT NULL DEFAULT 1,\
		producer VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		production_time DATE,\
		duration INT,\
		E_Resourse BOOLEAN NOT NULL DEFAULT FALSE);",

		//create books table;
		"CREATE TABLE IF NOT EXISTS books(id BIGINT UNSIGNED UNIQUE KEY NOT NULL,\
		title VARCHAR(50) NOT NULL,\
		author VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		classification INT UNSIGNED NOT NULL DEFAULT 1,\
		publishing_company VARCHAR(50) NOT NULL DEFAULT 'UNKNOW',\
		ISBN VARCHAR(50) NOT NULL,\
		page INT,\
		has_video_disc BOOLEAN NOT NULL DEFAULT FALSE,\
	    video_disc_id BIGINT DEFAULT NULL,\
		E_Resourse BOOLEAN NOT NULL DEFAULT FALSE);"};

	

	//init sql database and tables;
	for (int i = 0; i < 5; i++){
		if (mysql_real_query(myCont, databaseInit[i], strlen(databaseInit[i])) != 0)
		{
			const char* pCh = mysql_error(myCont);
			Log << pCh << std::endl;
		}
	}

	insert(picture_model(2, "title", "author", 1, false, "china", 200, 200));

}


bool sql_utils::insert(picture_model& picture){
	char* sqlQuery = new char[500];
	std::stringstream sstr;
	string sqlQueryCat("INSERT INTO pictures (id,title,author,productionNationality,classification,width,height,E_Resourse) VALUES(");
	sstr << picture.getId() << ",'"
		<< picture.getTitle() << "','"
		<< picture.getAuthor() << "','"
		<< picture.getProductionNationality() << "',"
		<< picture.getClassification() << ","
		<< picture.getWidth() << ","
		<< picture.getHeight() << ","
		<< picture.isE_Resourse() << ");";
	sstr >> sqlQuery;
	sqlQueryCat += sqlQuery;
	Log << sqlQueryCat.c_str() << endl;
	if (mysql_real_query(myCont, sqlQueryCat.c_str(), sqlQueryCat.length()) != 0){
		const char* pCh = mysql_error(myCont);
		Log << pCh << std::endl;
		//弹窗提醒插入失败并且给出报错信息。
		delete sqlQuery;
		return false;
	}

	delete sqlQuery;
	return true;
}

bool sql_utils::insert(book_model& book){
	
	return true;
}
bool sql_utils::insert(video_model& picture){
	return true;
}

//custom methods 

bool erase(const long long id);

bool alter(const media_data_base& old_model, const media_data_base& new_model);

//vector[0~2]  分别用来存放book video picture的对象指针
bool searchByTitle(vector<media_data_base *>[]);
bool searchByType(vector<media_data_base *>[]);

// media_data_base 基类里面封装了type,直接判一下type来强制向下转型。return NULL for not found
media_data_base* searchById();


map<string, int> summary();

map<string, vector<media_data_base *>> showAll();