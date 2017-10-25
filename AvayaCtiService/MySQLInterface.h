// MySQLInterface  

// ����������ʵ�ֶ�MySQL���ʲ����ķ�װ  

#ifndef __MYSQL_INTERFACE_H__    
#define __MYSQL_INTERFACE_H__    

#include <string>    
#include <vector>    

//#include <winsock.h> // Զ�̷���  
#include "mysql.h"  

// ������ؿ�  
//#pragma comment(lib, "ws2_32.lib")    
//#pragma comment(lib, "libmysql.lib")  

#define ERROR_QUERY_FAIL -1 // ����ʧ��  

using namespace std;
// ����MySQL������Ϣ  
typedef struct
{
	char* server;
	char* user;
	char* password;
	char* database;
	int port;
}MySQLConInfo;

class MySQLInterface : public CWnd
{
public:
	MySQLInterface();
	virtual ~MySQLInterface();

	void SetMySQLConInfo(char* server, char* username, char* password, char* database, int port);// ����������Ϣ  
	string Open();  // ������  
	void Close(); // �ر�����  

	string Select(const string& Querystr, vector<vector<string> >& data);  // ��ȡ����  
	string SelectOneLine(const string& Querystr, vector<string>& data);    // ��ȡһ������ UQ��ֵ
	string SelectList(const string& Querystr, vector<string>& data);       // ��ȡ�����б�

	string Query(const string& Querystr);     // ��������  
	string Insert(const string& Querystr);
	string Delete(const string& Querystr);
	string Updata(const string& Querystr);

	string ErrorIntoMySQL();     // ������Ϣ  

	static MySQLInterface *GetInstance();	// This allows to create only a single Object for the MySQLInterface class

public:
	int ErrorNum;                // �������    
	const char* ErrorInfo;       //	������ʾ    

protected:
	static MySQLInterface *m_pSelf;

private:
	MySQLConInfo MysqlConInfo;   // ������Ϣ  
	MYSQL MysqlInstance;         // MySQL����  
	MYSQL_RES *Result;           // ���ڴ�Ž�� ���ݼ�
};

#endif   