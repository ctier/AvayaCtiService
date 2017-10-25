#include "stdafx.h"  
#include "MySQLInterface.h"  


MySQLInterface::MySQLInterface() :
	ErrorNum(0), ErrorInfo("ok")
{
	mysql_library_init(0, NULL, NULL);
	mysql_init(&MysqlInstance);

	// 设置字符集，否则无法处理中文
	mysql_options(&MysqlInstance, MYSQL_SET_CHARSET_NAME, "utf8");//gbk
}

MySQLInterface::~MySQLInterface()
{
}

//////////////////////////////////////////////////////////
MySQLInterface * MySQLInterface::m_pSelf = NULL;

// Creating a Single object of the class
// Returns one and only instance of this class
MySQLInterface* MySQLInterface::GetInstance()
{
	if (m_pSelf == NULL)
	{
		m_pSelf = new MySQLInterface();
		if (m_pSelf != NULL)
		{
			// memory has been allocated.
			m_pSelf->CreateEx(0, AfxRegisterWndClass(CS_GLOBALCLASS), "", 0, 0, 0, 0, 0, 0, 0);
		}
	}
	return m_pSelf;
}


// 设置连接信息
void MySQLInterface::SetMySQLConInfo(char* server, char* username, char* password, char* database, int port)
{
	MysqlConInfo.server = server;
	MysqlConInfo.user = username;
	MysqlConInfo.password = password;
	MysqlConInfo.database = database;
	MysqlConInfo.port = port;
}

// 打开连接
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

// 断开连接
void MySQLInterface::Close()
{
	if (Result != NULL)
		mysql_free_result(Result);
	mysql_close(&MysqlInstance);
}

//读取数据
string MySQLInterface::Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data)
{
	string res = "Select Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(),(unsigned int)Querystr.size()))
	{
		return ErrorIntoMySQL();
	}

	Result = mysql_store_result(&MysqlInstance);

	// 行列数
	int row = mysql_num_rows(Result);
	int field = mysql_num_fields(Result);

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(Result);

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
		res = "Select Successful.Target don't exist!";
	}
	
	return res;
}
//读取数据列表 一行/多行？
string MySQLInterface::SelectList(const string& Querystr, vector<string>& data)
{
	string res = "SelectList Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
	{
		return ErrorIntoMySQL();
	}

	MYSQL_FIELD *Field;
	vector<string>().swap(data);
	string temp;
	Result = mysql_store_result(&MysqlInstance);

	if (Result)
	{
		unsigned int num_fields = mysql_num_fields(Result);
		Field = mysql_fetch_fields(Result);
		for (unsigned int i = 0; i < num_fields; i++)
		{
			temp = Field[i].name;
			data.push_back(temp);
		}
	}
	else
	{
		res = "Select Successful.Target don't exist!";
	}
	return res;
}
// 读取一行数据
string MySQLInterface::SelectOneLine(const string& Querystr, vector<string>& data)
{
	string res = "Select Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
	{
		return ErrorIntoMySQL();
	}

	Result = mysql_store_result(&MysqlInstance);

	// 行列数
	int row = mysql_num_rows(Result);//行
	int field = mysql_num_fields(Result);//列

	MYSQL_ROW line = NULL;
	line = mysql_fetch_row(Result);

	string temp;
	vector<string>().swap(data);

	if (Result)
	{
		if (row != 1)
		{
			res = "Select Successful.There are more than one line.";
			return res;
		}
		for (int i = 0; i < field; i++)
		{
			if (line[i])
			{
				temp = line[i];
				data.push_back(temp);
			}
			else
			{
				temp = "";
				data.push_back(temp);
			}
		}
	}
	else
	{
		res = "Select Successful.Target don't exist!";
	}

	return res;
}
// 其他操作
string MySQLInterface::Query(const std::string& Querystr)
{
	string res = "Query Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(),(unsigned int)Querystr.size()))
		return ErrorIntoMySQL();
	return res;

}

string MySQLInterface::Insert(const string& Querystr)
{
	string res = "Insert Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return ErrorIntoMySQL();
	return res;
}

string MySQLInterface::Delete(const string& Querystr)
{
	string res = "Delete Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return ErrorIntoMySQL();
	return res;
}

string MySQLInterface::Updata(const string& Querystr)
{
	string res = "Updata Successful.";
	if (mysql_real_query(&MysqlInstance, Querystr.c_str(), (unsigned int)Querystr.size()))
		return ErrorIntoMySQL();
	return res;
}

//错误信息
string MySQLInterface::ErrorIntoMySQL()
{
	ErrorNum = mysql_errno(&MysqlInstance);//未返回 是否需要ErrorNum接口 ？
	ErrorInfo = mysql_error(&MysqlInstance);
	string res = ErrorInfo;
	return res;
}