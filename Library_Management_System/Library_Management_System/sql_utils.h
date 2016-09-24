#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <map>
#include <vector>
#include <sstream>
#include "object.h"
using std::stringstream;
using std::string;

string lltos(long long l);


class sql_utils{
public:
	sql_utils();
	~sql_utils();
	const char* user = "root";         //username
	const char* pswd = "root";         //password
	const char* host = "localhost";    //or"127.0.0.1"
	const char* table = "test";        //database
	unsigned int port = 3306;           //server port        
	MYSQL *myCont;

	string insert(object& obj);
	string erase(long long id);
	bool isExistId(long long id);
	string update(object& oldObj, object& newObj);

	string searchByTitle(string title,std::vector<object>& container);
	string searchByType(int type, std::vector<object>& container);
	string searchById(long long id, std::vector<object>& container);

	//key is type and value is the total of that type obj;
	string summary(std::map<int, int>& container);

	string showAll(std::vector<object>& container);
};
