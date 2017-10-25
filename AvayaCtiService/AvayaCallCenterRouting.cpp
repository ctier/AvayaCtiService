#include "stdafx.h"
#include "AvayaCallCenterRouting.h"
#include "AvayaCtiService.h"

AvayaCallCenterRouting::AvayaCallCenterRouting()
{
	init();
}
bool AvayaCallCenterRouting::init()
{
	//创建MySQLInterface对象
	m_pMySQLInterface = MySQLInterface::GetInstance();

	char* server = "localhost";
	char* username = "root";
	char* password = "9201"; 
	char* database = "ctidb"; 
	int port = 3306;
	m_pMySQLInterface->SetMySQLConInfo(server, username, password, database, port);
	// get the TSAPIInterface Object
	m_pTsapiInterfaceObject = TSAPIInterface::GetInstance();
	return true;
}

AvayaCallCenterRouting::~AvayaCallCenterRouting()
{
	m_pMySQLInterface->Close();
	delete m_pMySQLInterface;
}


void AvayaCallCenterRouting::RouteEndInv(RouteRegisterReqID_t RouteRegisterReqID, RoutingCrossRefID_t RoutingCrossRefID)
{
	m_pTsapiInterfaceObject->RouteEndInv(RouteRegisterReqID, RoutingCrossRefID);
}

void AvayaCallCenterRouting::RouteRegisterCancel(RouteRegisterReqID_t RouteRegisterReqID)
{
	m_pTsapiInterfaceObject->RouteRegisterCancel(RouteRegisterReqID);
}

void AvayaCallCenterRouting::RouteRegister(DeviceID_t* routingDevice)
{
	m_pTsapiInterfaceObject->RouteRegister(routingDevice);
}

void AvayaCallCenterRouting::RouteSelectInv(RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID,
	DeviceID_t *routeSelected, RetryValue_t remainRetry, SetUpValues_t *setupInformation, Boolean routeUsedReq)
{
	m_pTsapiInterfaceObject->RouteSelectInv(routeRegisterReqID, routingCrossRefID,
		routeSelected, remainRetry, setupInformation, routeUsedReq);
}

string AvayaCallCenterRouting::InsertNumber(const char *telephonenumber,const char *type)
{
	//,'ADDTIME'
	string Query = "INSERT INTO NUMBERLIST('NUMBER','TYPE') VALUES('";
	Query += telephonenumber;
	Query += "','";
	Query += type;
	Query += "')";
	return m_pMySQLInterface->Insert(Query);
}

string AvayaCallCenterRouting::DeleteNumber(const char *telephonenumber)
{
	string Query = "DELETE FROM NUMBERLIST WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->Delete(Query);
}

string AvayaCallCenterRouting::UpdataNumber(const char *telephonenumber, const char *type)
{
	string Query = "UPDATE NUMBERLIST SET TYPE = '";
	Query += type;
	Query += "' WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->Updata(Query);
}

string AvayaCallCenterRouting::SelectNumber(const char *telephonenumber, vector<string>& data)
{
	string Query = "SELECT * FROM NUMBERLIST WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->SelectOneLine(Query, data);
}

void AvayaCallCenterRouting::RouteRequestExtEvent(CSTARouteRequestExtEvent_t routeRequestExt, ATTPrivateData_t privateData)
{
	RouteRegisterReqID_t routeRegisterReqID = routeRequestExt.routeRegisterReqID;//路由服务的路由注册会话的句柄
	RoutingCrossRefID_t routingCrossRefID = routeRequestExt.routingCrossRefID;//路由会话的唯一句柄
	CalledDeviceID_t currentRoute = routeRequestExt.currentRoute;//指定调用的目标
	CallingDeviceID_t callingDevice = routeRequestExt.callingDevice;//指定调用起始设备
	ConnectionID_t routedCall = routeRequestExt.routedCall;//指定要路由的调用的 callID。 这是路由设备 connectionID 的路由调用。
	SelectValue_t routedSelAlgorithm = routeRequestExt.routedSelAlgorithm;//指示所请求的路由算法的类型。它被设置为 SV_NORMAL。
	unsigned char priority = routeRequestExt.priority;//指示调用的优先级
	SetUpValues_t setupInformation = routeRequestExt.setupInformation;//包含 ISDN 呼叫设置消息

	ATTEvent_t att_event;

	if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ATT_ROUTE_REQUEST)
	{
		//att_event.u.routeRequest;
	}
}