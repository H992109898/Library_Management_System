#include "stdafx.h"
#include"sql_utils.h"
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")
sql_utils::sql_utils(){
	this->myCont = new MYSQL;
	mysql_init(this->myCont);

	if (mysql_real_connect(myCont, host, user, pswd, table, port, NULL, 0))
		;
	else
		AfxMessageBox(_T("数据库连接失败!"));

}