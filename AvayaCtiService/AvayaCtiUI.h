#pragma once
#include "TSAPIInterface.h"
//#include "CallManager.h"
#include "AvayaCallCenterUserAgent.h"
#include "KafkaConsumer.h"
#include "rdkafkacpp.h"
#include "afxwin.h"
#include "json.h"
#include "json-forwards.h"

// AvayaCtiUI �Ի���

class AvayaCtiUI : public CDialog//, public AgentStateObserver//, public CallStateObserver
{
	DECLARE_DYNAMIC(AvayaCtiUI)

public:
	AvayaCtiUI(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AvayaCtiUI(); 

	// Dialog Data
	enum { IDD = IDD_AvayaCti };
	/*
	void Notify(long lcallID, callState eCaState, connectionState eConState, char* szCalledDevID,
		char* szCallingDevID, char* szConferDevID);
	*/
	//void Notify(AgentState agentState, AgentTalkState  agentTalkState);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	AvayaCallCenterUserAgent *m_pAgtObject;  // object of Agent Class
	//CallManager *m_pCallManagerObject;	 // object of CallManager Class
	TSAPIInterface* m_pTSAPIInterface;		 // Handle for handling all events

	KafkaConsumer* m_pConsumerObject; 
	//KafkaProducer* m_pProducerObject;

	virtual BOOL OnInitDialog();

	CString m_strAgentStatus;
private:
	void MonitoringKafka();
	bool SelectTSAPIInterface(string message);
	// variable attach with Current AgentStatus readonly EditBox.
	CEdit m_Status;
	void InitializeDialog();
public:
	DECLARE_MESSAGE_MAP()

	CString m_message;
	CString m_strRouting;
	int m_radioBtnGroup1;
	int m_radioBtnGroup2;

	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedLoginBtn();
	afx_msg void OnBnClickedRadioBtnGroup1();
	afx_msg void OnBnClickedRadioBtnGroup2();
	afx_msg void OnBnClickedLogoutBtn();
	afx_msg void OnBnClickedStateChangeBtn();
	afx_msg void OnBnClickedChkstateBtn();
	afx_msg void OnBnClickedCallBtn();
	afx_msg void OnBnClickedMonitorStartBtn();
	afx_msg void OnBnClickedMonitorStopBtn();
	afx_msg void OnBnClickedAnswerBtn();
	afx_msg void OnBnClickedClearconBtn();
	afx_msg void OnBnClickedHoldBtn();
	afx_msg void OnBnClickedCancelholdBtn();
	afx_msg void OnBnClickedPickupBtn();
	afx_msg void OnBnClickedMonitorcallbtn();
	afx_msg void OnBnClickedRoutingInsert();
	afx_msg void OnBnClickedRoutingDelete();
	afx_msg void OnBnClickedRoutingSelect();
};
