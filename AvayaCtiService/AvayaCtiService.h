
// AvayaCtiService.h : AvayaCtiService Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "AvayaCtiUI.h"

// CAvayaCtiServiceApp:
// �йش����ʵ�֣������ AvayaCtiService.cpp
//

class CAvayaCtiServiceApp : public CWinApp
{
public:
	CAvayaCtiServiceApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	AvayaCtiUI *m_pAvayaCtiUIDlg;
	// This contain the window handler for AgentStateUI class
	HWND m_hAgtStateUI;

protected:
	DECLARE_MESSAGE_MAP()
};

extern CAvayaCtiServiceApp theApp;
