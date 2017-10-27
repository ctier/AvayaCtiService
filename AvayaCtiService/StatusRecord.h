// StatusRecord  

// ����������ʵ�ֶ�ctidb���Callprocess Agentstate Stationstate Callstate���ʲ����ķ�װ   

#ifndef __STATUS_RECORD_H__    
#define __STATUS_RECORD_H__    

#include "MySQLInterface.h"
#include <string>    
#include <vector>    


class StatusRecord //: public MySQLInterface
{
public:
	StatusRecord();
	virtual ~StatusRecord();

	string Query(const string& table,const string& mothed, vector<string>& data);

private:
	//This object will contain the MySQLInterface Object
	MySQLInterface *m_pMySQLInterface;

	vector<string> CallProcessList;
	vector<string> AgentSateList;
	vector<string> CallStationList;
	vector<string> StationSateList;

private:
	bool init();

	bool GetTableList(const string& table,vector<string>& tablelist);

	string Select(const string& table, vector<string>&data, const vector<string>& tablelist);
	string Insert(const string& table, const vector<string>&data, const vector<string>& tablelist);
	string Delete(const string& table, const vector<string>&data, const vector<string>& tablelist);
	//string Updata(const string& table, const vector<string>& data, const vector<string>& tablelist);

};

#endif   