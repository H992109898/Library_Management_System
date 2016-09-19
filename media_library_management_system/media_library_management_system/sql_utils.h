#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 


class sql_utils{
public:
	sql_utils();

	const char* user = "root";         //username
	const char* pswd = "root";         //password
	const char* host = "localhost";    //or"127.0.0.1"
	const char* table = "test";        //database
	unsigned int port = 3306;           //server port        
	MYSQL *myCont;

};