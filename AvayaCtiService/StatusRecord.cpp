#include "stdafx.h"
#include "StatusRecord.h"


StatusRecord::StatusRecord()
{
	init();
}

bool StatusRecord::init()
{
	//创建MySQLInterface对象
	m_pMySQLInterface = new MySQLInterface();
	if (m_pMySQLInterface == NULL)
	{
		return FALSE;
	}
	char* server = "localhost";
	char* username = "root";
	char* password = "9201";
	char* database = "ctidb";
	int port = 3306;
	m_pMySQLInterface->SetMySQLConInfo(server, username, password, database, port);

	return TRUE;
}

StatusRecord::~StatusRecord()
{
	m_pMySQLInterface->Close();
	delete m_pMySQLInterface;
}

bool StatusRecord::GetTableList(const string& table, vector<string>& tablelist)
{
	if (table == "CALLPROCESS")
	{
		tablelist = CallProcessList;
	}
	else if (table == "AGENTSATE")
	{
		tablelist = AgentSateList;
	}
	else if (table == "STATIONSATE")
	{
		tablelist = StationSateList;
	}
	else if (table == "CALLSTATION")
	{
		tablelist = CallStationList;
	}
	else
		return FALSE;
	return TRUE;
}

string StatusRecord::Query(const string& table, const string& mothed, vector<string>& data)
{
	string ret;
	vector<string> tablelist;
	if (GetTableList(table, tablelist))
	{
		if (mothed == "Select")
		{
			ret = Select(table, data, tablelist);
		}
		else if (mothed == "Insert")
		{
			ret = Insert(table, data, tablelist);
		}
		else if (mothed == "Delete")
		{
			ret = Delete(table, data, tablelist);
		}
		/*
		else if (mothed == "Updata")
		{
			ret = Updata(table, data, tablelist);
		}
		*/
		else
		{
			ret = "Error : Input mothed is not legal";
		}
	}
	else
	{
		ret = "Error : Input table name is not legal";
	}
	return ret;
}

//暂时留查一行接口
string StatusRecord::Select(const string& table, vector<string>&data, const vector<string>& tablelist)
{
	string ret;
	string query = "SELECT * FROM " + table + " WHERE ";
	string list;
	string value;
	//vector<string> getdata;  用data中数据查询，再把查询结果写入data中

	if ((data.size() != tablelist.size()) || (data.size() == 0))
	{
		ret = "Error : Data size does not match tablelist";
		return ret;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != "")
		{
			if (!list.empty())
			{
				query += " AND ";
			}
			list = tablelist[i];
			value = data[i];
			query += list + " = '" + value + "'";
		}
	}	

	ret = m_pMySQLInterface->SelectOneLine(query, data);
	return ret;
}

string StatusRecord::Insert(const string& table, const vector<string>&data, const vector<string>& tablelist)
{
	string ret;
	string query = "INSERT INTO " + table ;
	string lists;
	string list;
	string values;
	string value;

	if ((data.size() != tablelist.size()) || (data.size() == 0))
	{
		ret = "Error : Data size does not match tablelist";
		return ret;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != "")
		{
			if (!list.empty())
			{
				lists += ",";
				values += ",";
			}

			list = tablelist[i];
			value = data[i];
	
			lists += "'" + list + "'";
			values += "'" + value = "'";
		}
	}
	query += "(" + lists + ") VALUES(" + values + ")";
	ret = m_pMySQLInterface->Insert(query);

	return ret;
}

string StatusRecord::Delete(const string& table, const vector<string>&data, const vector<string>& tablelist)
{
	string ret;
	string query = "DELETE FROM " + table + " WHERE ";
	string list;
	string value;
	//vector<string> getdata;  用data中数据查询，再把查询结果写入data中

	if ((data.size() != tablelist.size()) || (data.size() == 0))
	{
		ret = "Error : Data size does not match tablelist";
		return ret;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != "")
		{
			if (!list.empty())
			{
				query += " AND ";
			}
			list = tablelist[i];
			value = data[i];
			query += list + " = '" + value + "'";
		}
	}

	ret = m_pMySQLInterface->Delete(query);
	return ret;
}


