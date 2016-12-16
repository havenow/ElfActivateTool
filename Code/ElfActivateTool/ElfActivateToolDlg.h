
// ElfActivateToolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "MobileInfo.h"


// CElfActivateToolDlg 对话框
class CElfActivateToolDlg : public CDialogEx
{
// 构造
public:
	CElfActivateToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ELFACTIVATETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strCmdLine;
	CRichEditCtrl m_richEditOutput;
	/*
	1、使用CRichEditCtrl
	要在InitInstance()中调用AfxInitRichEdit2();

	2、CRichEditCtrl显示多行（包含回车换行符）
	属性Multiline设置为true

	3、CRichEditCtrl
	Vertical Scroll设置为true
	*/
	char m_strOutput[CMD_OUTPUT_SIZE];

	CMobileInfo m_moblieInfo;

	BOOL ExecDosCmd(const char* strCmdLine);
	void ShowLog(const char* buffer);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnDebug();
};
