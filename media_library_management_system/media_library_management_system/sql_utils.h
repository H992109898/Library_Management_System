#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <map>
#include <vector>
#include"book_model.h"
#include"picture_model.h"
#include"video_model.h"


class sql_utils{
public:
	sql_utils();

	const char* user = "root";         //username
	const char* pswd = "root";         //password
	const char* host = "localhost";    //or"127.0.0.1"
	const char* table = "test";        //database
	unsigned int port = 3306;           //server port        
	MYSQL *myCont;

	//custom methods 
	bool insert(picture_model& picture);
	bool insert(book_model& book);
	bool insert(video_model& video);

	bool erase(const long long id);
	
	bool alter(const media_data_base& old_model, const media_data_base& new_model);

	//vector[0~2]  分别用来存放book video picture的对象指针
	bool searchByTitle(vector<media_data_base *>[]);
	bool searchByType(vector<media_data_base *>[]);

	// media_data_base 基类里面封装了type,直接判一下type来强制向下转型。return NULL for not found
	media_data_base* searchById();


	map<string, int> summary();

	map<string, vector<media_data_base *>> showAll();

	
};