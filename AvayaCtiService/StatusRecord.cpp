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

	//来话记录表  //Delivered Event  电话送递事件
	CallProcessList.push_back("ID");//主键
	CallProcessList.push_back("CALLID");//呼叫ID
	CallProcessList.push_back("CALLER");//主叫号码
	CallProcessList.push_back("CALLED");//被叫号码
	CallProcessList.push_back("STATE");//所在状态
	CallProcessList.push_back("TIME");//时间

	//座席状态记录表  //CSTAQueryAgentStateConfEvent 查询坐席状态返回事件 
	AgentSateList.push_back("ID");//主键
	AgentSateList.push_back("AGENTID");//路由id
	AgentSateList.push_back("STATION");//分机号
	AgentSateList.push_back("STATE");//所在状态
	AgentSateList.push_back("TIME");//时间

	//话机状态记录表  //CSTAQueryAgentStateConfEvent 查询坐席状态返回事件 
	StationSateList.push_back("ID");//主键
	StationSateList.push_back("AGENTID");//路由id
	StationSateList.push_back("STATION");//分机号
	StationSateList.push_back("STATE");//所在状态
	StationSateList.push_back("TIME");//时间

	//通话状态记录表
	CallStationList.push_back("ID");//主键
	CallStationList.push_back("CALLID");//呼叫id
	CallStationList.push_back("CALLER");//路由id
	CallStationList.push_back("STATION");//分机号
	CallStationList.push_back("STATE");//所在状态
	CallStationList.push_back("TIME");//时间


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

string StatusRecord::Request(const string& table, const string& mothed, map<string, string>& message)
{
	vector<string> data;
	//
	data.push_back("");//ID
	if (table == "Callprocess")
	{
		data.push_back(message["callID"]);//呼叫ID
		data.push_back(message["calling_devID"]);//主叫号码
		data.push_back(message["called_devID"]);//被叫号码
		data.push_back(message["localConnectionInfo"]);//所在状态
		data.push_back(message["time"]);//时间
	}
	else if (table == "Agentstate")//
	{
		data.push_back(message["AgentID"]);//路由ID ？ 现在没加 可以再增添映射关系m_InvokeID2AgentID 或 m_DeviceID2AgentID
		data.push_back(message["DeviceID"]);//分机号
		data.push_back(message["AgentState"]);//所在状态
		data.push_back(message["time"]);//时间
	}
	else if (table == "Stationstate")
	{
		data.push_back(message["AgentID"]);//路由ID ？ 现在没加 可以再增添映射关系m_InvokeID2AgentID 或 m_DeviceID2AgentID
		data.push_back(message["DeviceID"]);//分机号
		data.push_back(message["TalkState"]);//所在状态
		data.push_back(message["time"]);//时间
	}
	else if (table == "Callstate")
	{

	}
	else
	{
		return "Table name is wrong.";
	}
	return Request(table, mothed, data);
}

string StatusRecord::Request(const string& table, const string& mothed, vector<string>& data)
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


