// StatusRecord  

// ����������ʵ�ֶ�ctidb���Callprocess Agentstate Stationstate Callstate���ʲ����ķ�װ   

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