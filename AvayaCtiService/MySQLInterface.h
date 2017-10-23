// MySQLInterface  

// 功能描述：实现对MySQL访问操作的封装  

#ifndef __MYSQL_INTERFACE_H__    
#define __MYSQL_INTERFACE_H__    

#include <string>    
#include <vector>    

//#include <winsock.h> // 远程访问  
#include "mysql.h"  

// 引入相关库  
//#pragma comment(lib, "ws2_32.lib")    
//#pragma comment(lib, "libmysql.lib")  

#define ERROR_QUERY_FAIL -1 // 操作失败  

using namespace std;
// 定义MySQL连接信息  
typedef struct
{
	char* server;
	char* user;
	char* password;
	char* database;
	int port;
}MySQLConInfo;

class MySQLInterface
{
public:
	MySQLInterface();
	virtual ~MySQLInterface();

	void SetMySQLConInfo(char* server, char* username, char* password, char* database, int port);// 设置连接信息  
	string Open();  // 打开连接  
	void Close(); // 关闭连接  

	string Select(const string& Querystr, vector<vector<string> >& data);  // 读取数据  
	string SelectOneLine(const string& Querystr, vector<string>& data);    // 读取一行数据 UQ键值
	string SelectList(const string& Querystr, vector<string>& data);       // 获取数据列表

	string Query(const string& Querystr);     // 其他操作  
	string Insert(const string& Querystr);
	string Delete(const string& Querystr);
	string Updata(const string& Querystr);

	string ErrorIntoMySQL();     // 错误消息  

public:
	int ErrorNum;                // 错误代号    
	const char* ErrorInfo;       //	错误提示    

private:
	MySQLConInfo MysqlConInfo;   // 连接信息  
	MYSQL MysqlInstance;         // MySQL对象  
	MYSQL_RES *Result;           // 用于存放结果 数据集
	MYSQL_FIELD *Field;			 // 用于存放列相关属性
};

#endif   