
// AvayaCtiService.h : AvayaCtiService 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "AvayaCtiUI.h"

// CAvayaCtiServiceApp:
// 有关此类的实现，请参阅 AvayaCtiService.cpp
//

class CAvayaCtiServiceApp : public CWinApp
{
public:
	CAvayaCtiServiceApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	AvayaCtiUI *m_pAvayaCtiUIDlg;
	// This contain the window handler for AgentStateUI class
	HWND m_hAgtStateUI;

protected:
	DECLARE_MESSAGE_MAP()
};

extern CAvayaCtiServiceApp theApp;
