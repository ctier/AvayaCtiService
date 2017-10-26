// StatusRecord  

// 功能描述：实现对ctidb库表Callprocess Agentstate Stationstate Callstate访问操作的封装   

#ifndef __STATUS_RECORD_H__    
#define __STATUS_RECORD_H__    

#include "MySQLInterface.h"
#include <string>    
#include <vector>    


class StatusRecord
{
public:
	StatusRecord();
	virtual ~StatusRecord();

protected:
	MySQLInterface *m_pMySQL;

private:
	void init();
};

#endif   