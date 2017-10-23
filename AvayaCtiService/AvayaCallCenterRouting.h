#ifndef __AVAYACALLCENTERROUTING_H__  
#define __AVAYACALLCENTERROUTING_H__
#include <Windows.h>
#include <mysql.h>
#include <string>
#include <vector>
#include <iostream>
#include "MySQLInterface.h"

using namespace std;
class AvayaCallCenterRouting
{
private:
	const char *user;
	const char *pswd;
	const char *host;
	const char *table;
	int port;
	MYSQL myCont;
	MYSQL_RES *result;  //数据集
	MYSQL_ROW sql_row;  //行数据的类型安全表示   当前实现位一个计数字节的字符串数组
	MYSQL_FIELD *sql_field; //列相关属性
	int res;
	//string query;
	MySQLInterface mysql;
	bool init();
public:
	AvayaCallCenterRouting(const char *user, const char *pswd, const char *host, const char *table, int port);
	virtual ~AvayaCallCenterRouting();

	bool Insert(string mes);
	bool Delete(string mes);
	bool Updata(string mes);
	string Select(string mes);
};
#endif
