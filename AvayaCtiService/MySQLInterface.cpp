#include "stdafx.h"  
#include "MySQLInterface.h"  


MySQLInterface::MySQLInterface() :
	ErrorNum(0), ErrorInfo("ok")
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&MysqlInstance);

	// �����ַ����������޷���������
	mysql_options(&MysqlInstance, MYSQL_SET_CHARSET_NAME, "utf8");//gbk
}

MySQLInterface::~MySQLInterface()
{
}

// ����������Ϣ
void MySQLInterface::SetMySQLConInfo(char* server, char* username, char* password, char* database, int port)
{
	MysqlConInfo.server = server;
	MysqlConInfo.user = username;
	MysqlConInfo.password = password;
	MysqlConInfo.database = database;
	MysqlConInfo.port = port;
}

// ������
string MySQLInterface::Open()
{
	string res = "Connected...";
	if (mysql_real_connect(&MysqlInstance, MysqlConInfo.server, MysqlConInfo.user,
		MysqlConInfo.password, MysqlConInfo.database, MysqlConInfo.port, 0, 0) != NULL)
	{
		return res;
	}
	else
	{
		//res = "Error connecting to database:" + ErrorIntoMySQL();
		//return res;
		return ErrorIntoMySQL();
	}
}

// �Ͽ�����
void MySQLInterface::Close()
{
	if (Result != NULL)
		mysql_free_result(Result);
	mysql_close(&MysqlInstance);
}

//��ȡ����
string MySQLInterface::Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data)
{
	string res = "Select Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(),(unsigned int)Querystr.size()))
	{
		return ErrorIntoMySQL();
	}

	Result = mysql_store_result(&MysqlInstance);

	// ������
	int row = mysql_num_rows(Result);
	int field = mysql_num_fields(Result);

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(Result);

	int j = 0;
	string temp;
	vector<vector<string> >().swap(data);
	if (Result)
	{
		while (NULL != line)//for(row)
		{
			vector<string> linedata;
			for (int i = 0; i < field; i++)
			{
				if (line[i])
				{
					temp = line[i];
					linedata.push_back(temp);
				}
				else
				{
					temp = "";
					linedata.push_back(temp);
				}
			}
			line = mysql_fetch_row(Result);
			data.push_back(linedata);
		}
	}
	else
	{
		string res = "Select Successful.Target don't exist!";
	}
	
	return res;
}

string MySQLInterface::SelectList(const string& Querystr, vector<string>& data)
{
	string res = "SelectList Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
	{
		return ErrorIntoMySQL();
	}

	Result = mysql_store_result(&MysqlInstance);

}

// ��������
string MySQLInterface::Query(const std::string& Querystr)
{
	string res = "Query Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(),(unsigned int)Querystr.size()))
	{
		return res;
	}
	return ErrorIntoMySQL();
}

string MySQLInterface::Insert(const string& Querystr)
{
	string res = "Insert Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return mysql_error(&MysqlInstance);
	return res;
}

string MySQLInterface::Delete(const string& Querystr)
{
	string res = "Delete Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return mysql_error(&MysqlInstance);
	return res;
}

string MySQLInterface::Updata(const string& Querystr)
{
	string res = "Updata Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return mysql_error(&MysqlInstance);
	return res;
}

//������Ϣ
string MySQLInterface::ErrorIntoMySQL()
{
	ErrorNum = mysql_errno(&MysqlInstance);
	ErrorInfo = mysql_error(&MysqlInstance);
	string res = ErrorInfo;
	return res;
}