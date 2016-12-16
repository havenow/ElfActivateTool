
// ElfActivateToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElfActivateTool.h"
#include "ElfActivateToolDlg.h"
#include "afxdialogex.h"
#include "Tool.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CElfActivateToolDlg �Ի���



CElfActivateToolDlg::CElfActivateToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CElfActivateToolDlg::IDD, pParent)
	, m_strCmdLine(_T("adb devices"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_strOutput, 0, 8192);
}

void CElfActivateToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CMD_LINE, m_strCmdLine);
	DDX_Control(pDX, IDC_RICHEDIT2_OUTPUT, m_richEditOutput);
}

BEGIN_MESSAGE_MAP(CElfActivateToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CElfActivateToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CElfActivateToolDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CElfActivateToolDlg ��Ϣ�������

BOOL CElfActivateToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CElfActivateToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CElfActivateToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CElfActivateToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//http://www.cnblogs.com/cnarg/archive/2011/02/20/1959292.html
//VC��ִ��DOS����õ����
BOOL CElfActivateToolDlg::ExecDosCmd(const char* strCmdLine)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return FALSE;
	}
	char command[1024];    //������ 1K
	strcpy(command, "Cmd.exe /C ");
	strcat(command, strCmdLine);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ�����
	si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ�����
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//�ؼ����裬CreateProcess�����������������MSDN
	if (!CreateProcess(NULL, command, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}

	CloseHandle(hWrite);
	char buffer[4096] = { 0 };          //��������� 4K
	DWORD bytesRead;
	while (true)//���ܻ����Σ�����Log����break֮����
	{

		if (ReadFile(hRead, buffer, 4095, &bytesRead, nullptr) == FALSE)//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����
			break;

		delChr(buffer, '\r');//ȥ��'\r'��CRichEditCtrl��ʶ��"\r\r\n"��ֻ��ʶ��"\r\n"
		strcat(m_strOutput, buffer);
		memset(buffer, 0, sizeof(buffer));
	}

	//m_moblieInfo.AnalyseDevice(m_strOutput);
	
	ShowLog(m_strOutput);   //��ʾ
	memset(m_strOutput, 0, CMD_OUTPUT_SIZE);

	CloseHandle(hRead);
	return TRUE;
}

void CElfActivateToolDlg::ShowLog(const char* buffer)
{
	if (m_richEditOutput.GetLineCount() > 1000000)
	{
		m_richEditOutput.Clear();
	}

	//char buffer[10240] = { 0 };
	//va_list argsList;
	//va_start(argsList, format);
	//_vsprintf_s_l(buffer, 10240, format, NULL, argsList);
	//va_end(argsList);

	tm  nowtime;
	time_t t_time = time(nullptr);
	localtime_s(&nowtime, &t_time);

	CString strdate;
	strdate.Format(TEXT("[%d-%d-%d %d:%d:%d]\n"), nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday, nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);
	m_richEditOutput.SetSel(-1, -1);
	m_richEditOutput.ReplaceSel(strdate);


	CString str(buffer);
	m_richEditOutput.SetSel(-1, -1);
	m_richEditOutput.ReplaceSel(str);

	CString strrl(TEXT("\r\n"));
	m_richEditOutput.SetSel(-1, -1);
	m_richEditOutput.ReplaceSel(strrl);
	m_richEditOutput.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}


void CElfActivateToolDlg::OnBnClickedOk()
{
	UpdateData();
	BOOL res = ExecDosCmd(m_strCmdLine.GetBuffer());
}


void CElfActivateToolDlg::OnBnClickedBtnClear()
{
	m_richEditOutput.SetSel(0, -1);
	m_richEditOutput.Clear();
}
