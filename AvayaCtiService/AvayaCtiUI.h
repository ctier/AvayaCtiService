#pragma once
#include "TSAPIInterface.h"
//#include "CallManager.h"
#include "AvayaCallCenterUserAgent.h"
#include "AvayaCallCenterRouting.h"
#include "KafkaConsumer.h"
#include "rdkafkacpp.h"
#include "afxwin.h"
#include "json.h"
#include "json-forwards.h"

// AvayaCtiUI 对话框

class AvayaCtiUI : public CDialog//, public AgentStateObserver//, public CallStateObserver
{
	DECLARE_DYNAMIC(AvayaCtiUI)

public:
	AvayaCtiUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AvayaCtiUI(); 

	// Dialog Data
	enum { IDD = IDD_AvayaCti };
	/*
	void Notify(long lcallID, callState eCaState, connectionState eConState, char* szCalledDevID,
		char* szCallingDevID, char* szConferDevID);
	*/
	//void Notify(AgentState agentState, AgentTalkState  agentTalkState);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	AvayaCallCenterUserAgent *m_pAgtObject;  // object of Agent Class
	AvayaCallCenterRouting *m_pRoutingObject;// object of Routing Class
	//CallManager *m_pCallManagerObject;	 // object of CallManager Class
	TSAPIInterface* m_pTSAPIInterface;		 // Handle for handling all events

	KafkaConsumer* m_pConsumerObject; 
	//KafkaProducer* m_pProducerObject;

	virtual BOOL OnInitDialog();

	string GetTimeStr();//GetLocalTime  

	CString m_strAgentStatus;
private:
	void MonitoringKafka();
	bool SelectTSAPIInterface(string message);
	// variable attach with Current AgentStatus readonly EditBox.
	CEdit m_Status;
	void InitializeDialog();
	void UpdataViewStatus(string);

public:
	DECLARE_MESSAGE_MAP()
	CString m_message;
	CString m_strRouting;
	int m_radioBtnGroup1;
	int m_radioBtnGroup2;
	int m_radioBtnGroup3;
	int m_radioBtnGroup4;

	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedLoginBtn();
	afx_msg void OnBnClickedRadioBtnGroup1();
	afx_msg void OnBnClickedRadioBtnGroup2();
	afx_msg void OnBnClickedRadioBtnGroup3();
	afx_msg void OnBnClickedRadioBtnGroup4();
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
	afx_msg void OnBnClickedSnapshotBtn();
	afx_msg void OnBnClickedParticipationtypeRadio1();
	afx_msg void OnBnClickedConsultBtn();
	afx_msg void OnBnClickedSnapshotBtn2();
	afx_msg void OnBnClickedConfBtn();
	afx_msg void OnBnClickedTransferBtn();
	afx_msg void OnBnClickedActiveRadio();
	
	afx_msg void OnBnClickedRoutingInsert();
	afx_msg void OnBnClickedRoutingDelete();
	afx_msg void OnBnClickedRoutingSelect();
	CComboBox m_cbRoutingType;
	CString m_strRoutingType;
	afx_msg void OnCbnSelchangeRoutingType();
	afx_msg void OnCbnDropdownRoutingType();
	afx_msg void OnBnClickedRoutingUpdata();
	afx_msg void OnBnClickedClearBtn();
	afx_msg void OnBnClickedRoutingRegister();
	afx_msg void OnBnClickedRoutingRegistercancel();
};
