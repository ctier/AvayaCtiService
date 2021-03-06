#ifndef __AVAYACALLCENTERROUTING_H__  
#define __AVAYACALLCENTERROUTING_H__
#include <string>
#include <vector>
#include <iostream>
#include <sys/timeb.h>
#include "MySQLInterface.h"
#include "TSAPIInterface.h"

using namespace std;
class AvayaCallCenterRouting
{
private:
	// This object will contain the MySQLInterface Object
	MySQLInterface *m_pMySQLInterface;
	// This object will contain the TSAPIInterface Object
	TSAPIInterface *m_pTsapiInterfaceObject;

	timeb time;
	//vector<string> selectline;
	//string Querystr;

	bool init();
public:
	AvayaCallCenterRouting();
	virtual ~AvayaCallCenterRouting();

	//RouteRegisterReqID_t routeRegisterReqID;//save route Register Request ID 


	//Using MySQL Database NUMBERLIST
	string InsertNumber(const char *telephonenumber, const char *type);//const string& Querystr
	string DeleteNumber(const char *telephonenumber);
	string UpdataNumber(const char *telephonenumber, const char *type);
	string SelectNumber(const char *telephonenumber, vector<string>& data);
	//Routing Service Group Function
	void RouteRegister(DeviceID_t*);	//A NULL device identifier indicates that the requesting application will be the default routing server for Communication Manager.
	void RouteRegisterCancel(DeviceID_t);

	void RouteEndInv(RouteRegisterReqID_t, RoutingCrossRefID_t);
	void RouteSelectInv(RouteRegisterReqID_t, RoutingCrossRefID_t, DeviceID_t *, RetryValue_t, SetUpValues_t *, Boolean, PrivateData_t *);
	//Routing Service Group Event
	//map<string, string>
	void RouteRequestExtEvent(CSTARouteRequestExtEvent_t routeRequestExt, ATTPrivateData_t privateData);
	void RouteRequestReqConfEvent(CSTAEvent_t routeRegister, ATTPrivateData_t privateData);
	void RouteEndEvent(CSTAEvent_t routeEnd);
	void RouteRegisterAbortEvent(CSTAEvent_t& registerAbort);
	void RouteUsedExtEvent(CSTARouteUsedExtEvent_t routeUsedExt);

	map<string, string> m_DeviceID2RouteRegisterReqID;//
	map<string, string> m_DeviceID2RoutingCrossRefID;//�ỰΨһ���

};
#endif
