#include "stdafx.h"
#include "StatusRecord.h"


StatusRecord::StatusRecord()
{
	init();
}

bool StatusRecord::init()
{
	//����MySQLInterface����
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

	//������¼��  //Delivered Event  �绰�͵��¼�
	CallProcessList.push_back("ID");//����
	CallProcessList.push_back("CALLID");//����ID
	CallProcessList.push_back("CALLER");//���к���
	CallProcessList.push_back("CALLED");//���к���
	CallProcessList.push_back("STATE");//����״̬
	CallProcessList.push_back("TIME");//ʱ��

	//��ϯ״̬��¼��  //CSTAQueryAgentStateConfEvent ��ѯ��ϯ״̬�����¼� 
	AgentSateList.push_back("ID");//����
	AgentSateList.push_back("AGENTID");//·��id
	AgentSateList.push_back("STATION");//�ֻ���
	AgentSateList.push_back("STATE");//����״̬
	AgentSateList.push_back("TIME");//ʱ��

	//����״̬��¼��  //CSTAQueryAgentStateConfEvent ��ѯ��ϯ״̬�����¼� 
	StationSateList.push_back("ID");//����
	StationSateList.push_back("AGENTID");//·��id
	StationSateList.push_back("STATION");//�ֻ���
	StationSateList.push_back("STATE");//����״̬
	StationSateList.push_back("TIME");//ʱ��

	//ͨ��״̬��¼��
	CallStationList.push_back("ID");//����
	CallStationList.push_back("CALLID");//����id
	CallStationList.push_back("CALLER");//·��id
	CallStationList.push_back("STATION");//�ֻ���
	CallStationList.push_back("STATE");//����״̬
	CallStationList.push_back("TIME");//ʱ��


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
		data.push_back(message["callID"]);//����ID
		data.push_back(message["calling_devID"]);//���к���
		data.push_back(message["called_devID"]);//���к���
		data.push_back(message["localConnectionInfo"]);//����״̬
		data.push_back(message["time"]);//ʱ��
	}
	else if (table == "Agentstate")//
	{
		data.push_back(message["AgentID"]);//·��ID �� ����û�� ����������ӳ���ϵm_InvokeID2AgentID �� m_DeviceID2AgentID
		data.push_back(message["DeviceID"]);//�ֻ���
		data.push_back(message["AgentState"]);//����״̬
		data.push_back(message["time"]);//ʱ��
	}
	else if (table == "Stationstate")
	{
		data.push_back(message["AgentID"]);//·��ID �� ����û�� ����������ӳ���ϵm_InvokeID2AgentID �� m_DeviceID2AgentID
		data.push_back(message["DeviceID"]);//�ֻ���
		data.push_back(message["TalkState"]);//����״̬
		data.push_back(message["time"]);//ʱ��
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

//��ʱ����һ�нӿ�
string StatusRecord::Select(const string& table, vector<string>&data, const vector<string>& tablelist)
{
	string ret;
	string query = "SELECT * FROM " + table + " WHERE ";
	string list;
	string value;
	//vector<string> getdata;  ��data�����ݲ�ѯ���ٰѲ�ѯ���д��data��

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
	//vector<string> getdata;  ��data�����ݲ�ѯ���ٰѲ�ѯ���д��data��

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


