
// ElfActivateTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CElfActivateToolApp: 
// �йش����ʵ�֣������ ElfActivateTool.cpp
//

class CElfActivateToolApp : public CWinApp
{
public:
	CElfActivateToolApp();
	
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CElfActivateToolApp theApp;
extern char g_strExeFilePath[512];