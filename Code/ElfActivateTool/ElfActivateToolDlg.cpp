
// ElfActivateToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElfActivateTool.h"
#include "ElfActivateToolDlg.h"
#include "afxdialogex.h"
#include "Tool.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CElfActivateToolDlg 对话框



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


// CElfActivateToolDlg 消息处理程序

BOOL CElfActivateToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CElfActivateToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CElfActivateToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//http://www.cnblogs.com/cnarg/archive/2011/02/20/1959292.html
//VC下执行DOS命令并得到输出
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
	char command[1024];    //命令行 1K
	strcpy(command, "Cmd.exe /C ");
	strcat(command, strCmdLine);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;            //把创建进程的标准错误输出重定向到管道输入
	si.hStdOutput = hWrite;           //把创建进程的标准输出重定向到管道输入
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN
	if (!CreateProcess(NULL, command, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return FALSE;
	}

	CloseHandle(hWrite);
	char buffer[4096] = { 0 };          //输出的内容 4K
	DWORD bytesRead;
	while (true)//可能会读多次，处理Log，在break之后处理
	{

		if (ReadFile(hRead, buffer, 4095, &bytesRead, nullptr) == FALSE)//buffer中就是执行的结果，可以保存到文本，也可以直接输出
			break;

		delChr(buffer, '\r');//去掉'\r'，CRichEditCtrl不识别"\r\r\n"，只能识别"\r\n"
		strcat(m_strOutput, buffer);
		memset(buffer, 0, sizeof(buffer));
	}

	//m_moblieInfo.AnalyseDevice(m_strOutput);
	
	ShowLog(m_strOutput);   //显示
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
