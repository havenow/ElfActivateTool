
// ElfActivateToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MobileInfo.h"


// CElfActivateToolDlg �Ի���
class CElfActivateToolDlg : public CDialogEx
{
// ����
public:
	CElfActivateToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ELFACTIVATETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strCmdLine;
	CRichEditCtrl m_richEditOutput;
	/*
	1��ʹ��CRichEditCtrl
	Ҫ��InitInstance()�е���AfxInitRichEdit2();

	2��CRichEditCtrl��ʾ���У������س����з���
	����Multiline����Ϊtrue

	3��CRichEditCtrl
	Vertical Scroll����Ϊtrue
	*/
	char m_strOutput[CMD_OUTPUT_SIZE];

	CMobileInfo m_moblieInfo;

	BOOL ExecDosCmd(const char* strCmdLine);
	void ShowLog(const char* buffer);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnDebug();
};
