#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
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
//	bool insert(const picture_model& picture);
//	bool insert(const book_model& book);
//	bool insert(const video_model& video);

//	bool remove(const long long id);
	
//	bool alter(const picture_model& old_picture, const picture_model& new_picture);
//	bool alter(const book_model& old_book, const book_model& new_book);
//	bool alter(const video_model& old_video, const video_model& new_video);

	
};