#include "stdafx.h"
#include"sql_utils.h"
#include "mysql.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

#pragma comment(lib, "libmysql.lib")

string lltos(long long l){
	stringstream sstr;
	sstr << l;
	string result;
	sstr >> result;
	return result;
}

//write object
bool writeObjBySqlRow(object& obj, MYSQL_ROW& row){
	//0~5是基础字段，6~8 是picture的私有字段，9~11是video的私有字段，12~16是book的私有字段
	obj.id = atoll(row[0]);
	obj.type = atoi(row[1]);
	obj.title = row[2];
	obj.author = row[3];
	obj.classification = atoi(row[4]);
	obj.E_Resourse = *(row[5]) == '0' ? false : true;

	switch (obj.type){
	case object::TYPE_BOOK:
		obj.publishingCompany = row[12];
		obj.ISBN = row[13];
		obj.page = atoi(row[14]);
		obj.hasVideoDisc = *(row[15]) == '0' ? false : true;
		if (obj.hasVideoDisc)
			obj.videoDiscId = atoll(row[16]);
		else
			obj.videoDiscId = -1;
		break;
	case object::TYPE_VIDEO:
		obj.producer = row[9];
		obj.production_time = row[10];
		obj.duration = atoi(row[11]);
		break;

	case object::TYPE_PICTURE:
		obj.productionNationality = row[6];
		obj.width = atoi(row[7]);
		obj.height = atoi(row[8]);
		break;

	default:
		return false;
	}
	return true;
}

sql_utils::sql_utils(){
	this->myCont = new MYSQL;
	mysql_init(this->myCont);

	if (mysql_real_connect(myCont, host, user, pswd, table, port, NULL, 0))
		;
	else{
		AfxMessageBox(_T("数据库连接失败!"));
		exit(0);
	}


	const char databaseInit[][700] = {
		"CREATE DATABASE IF NOT EXISTS media_library_management_system;",
		"USE media_library_management_system;",

		//create pictures table;
		"CREATE TABLE IF NOT EXISTS media_library(id BIGINT UNSIGNED UNIQUE KEY NOT NULL,\
		type INT NOT NULL,\
		title VARCHAR(50) NOT NULL,\
		author VARCHAR(30) NOT NULL DEFAULT 'UNKNOW',\
		classification INT UNSIGNED NOT NULL DEFAULT 1,\
		E_Resourse BOOLEAN NOT NULL DEFAULT FALSE,\
		production_nationality VARCHAR(30),\
		width INT UNSIGNED,\
		height INT UNSIGNED,\
		producer VARCHAR(30),\
		production_time DATE,\
		duration INT,\
		publishing_company VARCHAR(50),\
		ISBN VARCHAR(50),\
		page INT,\
		has_video_disc BOOLEAN,\
		video_disc_id BIGINT) ENGINE=MyISAM DEFAULT CHARSET=GBK;",
		"ALTER TABLE media_library ADD INDEX title_index(title);"};



	//init sql database and tables;
	for (int i = 0; i < 4; i++){
		if (mysql_real_query(myCont, databaseInit[i], strlen(databaseInit[i])) != 0)
		{
			const char* pCh = mysql_error(myCont);
		}
	}

	std::ifstream in("object_in.txt");
	for (char buffer[500]; !in.eof();){
		in.getline(buffer, 500);
		insert(object(buffer));
	}
	in.close();
}


sql_utils::~sql_utils(){
	mysql_close(myCont);
}

//custom methods

//check whether a id is existed;
bool sql_utils::isExistId(long long id){
	string sqlQuery("SELECT * FROM media_library WHERE id=");
	sqlQuery += lltos(id);
	sqlQuery += ";";
	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//Log << pCh << std::endl;
		//弹窗提醒插入失败并且给出报错信息。
		return false;
	}
	else{
		MYSQL_RES * res = mysql_store_result(myCont);
		if (mysql_num_rows(res) == 0)
			return false;
		else{
			mysql_free_result(res);
			return true;
		}
	}
}


string sql_utils::insert(object& obj){

	if (obj.checkData() == false)
		return string("非法数据！");
	else if (isExistId(obj.id))
		return string("id已存在！");

	//set base data;
	std::ostringstream sstr;
	sstr << obj.id << ","
		<< obj.type << ",'"
		<< obj.title << "','"
		<< obj.author << "',"
		<< obj.classification << ","
		<< obj.E_Resourse;

	string sqlQuery("INSERT INTO media_library(id,type,title,author,classification,E_Resourse,");
	switch (obj.type){
	case object::TYPE_BOOK:
		sqlQuery += "ISBN,publishing_company,page,has_video_disc,video_disc_id) VALUES(";
		sstr << ",'" << obj.ISBN << "','"
			<< obj.publishingCompany << "',"
			<< obj.page << ","
			<< obj.hasVideoDisc;

		if (obj.hasVideoDisc)
			sstr << "," << obj.videoDiscId;
		else
			sstr << ",NULL";
		sstr << ");";
		break;

	case object::TYPE_VIDEO:
		sqlQuery += "producer,production_time,duration) VALUES(";
		sstr << ",'" << obj.producer << "','"
			<< obj.production_time << "',"
			<< obj.duration << ");";
		break;

	case object::TYPE_PICTURE:
		sqlQuery += "production_nationality,width,height) VALUES(";
		sstr << ",'" << obj.productionNationality << "',"
			<< obj.width << ","
			<< obj.height << ");";
		break;

	default:break;
	}

	sqlQuery += sstr.str();

	mysql_real_query(myCont, "set names GBK", strlen("set names GBK"));
	if (mysql_real_query(myCont, sqlQuery.c_str(), strlen(sqlQuery.c_str())) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute 出错！";
	}

	return "OK!";
}
string sql_utils::erase(long long id){
	if (isExistId(id) == false)
		return "id 不存在！";

	string sqlQuery("DELETE FROM media_library WHERE id=");
	sqlQuery += lltos(id);

	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute 出错！";
	}

	return "OK!";
}

string sql_utils::update(object& oldObj, object& newObj){
	if (isExistId(newObj.id) && oldObj.id != newObj.id)
		return "新修改的 id 已存在！";

	erase(oldObj.id);
	return insert(newObj);
}

string sql_utils::searchByTitle(string title, std::vector<object>& container){
	string sqlQuery("SELECT * FROM media_library WHERE title='");
	sqlQuery += title;
	sqlQuery += "';";

	mysql_real_query(myCont, "set names GBK", strlen("set names GBK"));
	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute fail!";
	}
	else{
		MYSQL_RES * res = mysql_store_result(myCont);
		if (mysql_num_rows(res) == 0){
			mysql_free_result(res);
			return "empty set!";
		}
		else{
			MYSQL_ROW row;

			while ((row = mysql_fetch_row(res)))
			{
				object obj;
				//得到一行记录，把他写进obj中；
				if (writeObjBySqlRow(obj, row))
					container.push_back(obj);
			}

			mysql_free_result(res);
			return "OK!";
		}
	}
}
string sql_utils::searchByType(int type, std::vector<object>& container){
	string sqlQuery("SELECT * FROM media_library WHERE type=");
	sqlQuery += lltos(type);
	sqlQuery += ";";

	mysql_real_query(myCont, "set names GBK", strlen("set names GBK"));
	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute fail!";
	}
	else{
		MYSQL_RES * res = mysql_store_result(myCont);
		if (mysql_num_rows(res) == 0){
			mysql_free_result(res);
			return "empty set!";
		}
		else{
			MYSQL_ROW row;

			while ((row = mysql_fetch_row(res)))
			{
				object obj;
				//得到一行记录，把他写进obj中；
				if (writeObjBySqlRow(obj, row))
					container.push_back(obj);
			}

			mysql_free_result(res);
			return "OK!";
		}
	}
}
string sql_utils::searchById(long long id, std::vector<object>& container){
	string sqlQuery("SELECT * FROM media_library WHERE id=");
	sqlQuery += lltos(id);
	sqlQuery += ";";

	mysql_real_query(myCont, "set names GBK", strlen("set names GBK"));
	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute fail!";
	}
	else{
		MYSQL_RES * res = mysql_store_result(myCont);
		if (mysql_num_rows(res) == 0){
			mysql_free_result(res);
			return "empty set!";
		}
		else{
			//id 唯一，只有一行
			MYSQL_ROW row = mysql_fetch_row(res);
			object obj;
			if (writeObjBySqlRow(obj, row))
				container.push_back(obj);

			mysql_free_result(res);
			return "OK!";
		}
	}
}

//key is type and value is the total of that type obj;
string sql_utils::summary(std::map<int, int>& container){
	string sqlQueryCat("SELECT COUNT(id) FROM media_library WHERE type=");
	for (int i = 1; i <= 3; i++){
		string sqlQuery = sqlQueryCat;
		sqlQuery += lltos(i);
		if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
			const char* pCh = mysql_error(myCont);
			//弹窗提醒插入失败并且给出报错信息。
			//total for -1 to show error;
			container[i] = -1;
			return "sql execute error!";
		}
		else{
			//只有count 一列。
			MYSQL_RES * res = mysql_store_result(myCont);
			MYSQL_ROW row = mysql_fetch_row(res);
			container[i] = atoi(row[0]);

			mysql_free_result(res);
		}
	}
	return "OK!";
}

string sql_utils::showAll(std::vector<object>& container){

	string sqlQuery("SELECT * FROM media_library ORDER BY id DESC;");

	mysql_real_query(myCont, "set names GBK", strlen("set names GBK"));
	if (mysql_real_query(myCont, sqlQuery.c_str(), sqlQuery.length()) != 0){
		const char* pCh = mysql_error(myCont);
		//弹窗提醒插入失败并且给出报错信息。
		return "sql execute error!";
	}
	else{
		MYSQL_RES * res = mysql_store_result(myCont);
		if (mysql_num_rows(res) == 0){
			mysql_free_result(res);
			return "empty set!";
		}
		else{
			MYSQL_ROW row;

			while ((row = mysql_fetch_row(res)))
			{
				object obj;
				//得到一行记录，把他写进obj中；
				if (writeObjBySqlRow(obj, row))
					container.push_back(obj);
			}

			mysql_free_result(res);
			return "OK!";
		}
	}
}


