#include "stdafx.h"
#include "AvayaCallCenterRouting.h"
#include "AvayaCtiService.h"

AvayaCallCenterRouting::AvayaCallCenterRouting(
	const char *user, const char *pswd, const char *host,
	const char *table, int port)
	:user(user), pswd(pswd), host(host),
	table(table),port(port)
{
	init();
}
bool AvayaCallCenterRouting::init()
{
	mysql_init(&myCont);
	if (!mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Error connecting to database:" + mysql_error(&myCont) + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		return false;
	}
	else
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Connected..." + "\r\n";
		char *query = "SET CHARACTER SET utf8";//设置编码
		res = mysql_real_query(&myCont, query, (unsigned int)strlen(query));
		if (res)
		{
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Encoding settings failed" + "\r\n";
		}
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);

		return true;
	}
}

AvayaCallCenterRouting::~AvayaCallCenterRouting()
{
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&myCont);
}

bool AvayaCallCenterRouting::Insert(string mes)
{
	bool ret = false;
	res = mysql_real_query(&myCont, mes.c_str(), (unsigned int)mes.size());
	if (res)
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Error inserting data to database:" + mysql_error(&myCont) + "\r\n";
	else
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Insert Successful:" + mes.c_str() + "\r\n";
		ret = true;
	}
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	return ret;
}

bool AvayaCallCenterRouting::Delete(string mes)//先确定有删除目标
{
	bool ret = false;
	res = mysql_real_query(&myCont, mes.c_str(), (unsigned int)mes.size());
	if (res)
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Error deleting database data:" + mysql_error(&myCont) + "\r\n";
	else
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Delete Successful:" + mes.c_str() + "\r\n";
		ret = true;
	}
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	return ret;
}

bool AvayaCallCenterRouting::Updata(string mes)//确定有更新目标
{
	bool ret = false;
	res = mysql_real_query(&myCont, mes.c_str(), (unsigned int)mes.size());
	if (res)
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Error updating database data:" + mysql_error(&myCont) + "\r\n";
	else
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Updata Successful:" + mes.c_str() + "\r\n";
		ret = true;
	}
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	return ret;
}

string AvayaCallCenterRouting::Select(string mes)
{
	string ret;
	res = mysql_real_query(&myCont, mes.c_str(), (unsigned int)mes.size());
	if (res)
	{
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + "Error selecting database data:" + mysql_error(&myCont) + "\r\n";
		ret = "error:";
		ret += mysql_error(&myCont);
	}
	else
	{	//select request succeeded
		result = mysql_store_result(&myCont);
		if (result)
		{   //target is in the database
			sql_row = mysql_fetch_row(result);//获取具体的数据,查找的number键设为UQ,只取一行值
			ret = "ID:";
			ret += sql_row[0];
			ret += ";number:";
			ret += sql_row[1];
			if (sql_row[2])
			{
				ret += ";details:";
				ret += sql_row[2];
			}
			else{}//没写details
		}
		else
		{
			ret = "target don't exist!";
		}
	}
	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + ret.c_str() + "\r\n";
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);

	result = mysql_store_result(&myCont);
	
	return ret;
}