// TestDemoDlg.cpp: 实现文件
//
#include "stdafx.h"
#include "TestDemo.h"
#include "TestDemoDlg.h"
#include "afxdialogex.h"

#include <afxinet.h>

#include "md5.h"

#include "json/json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDemoDlg 对话框



CTestDemoDlg::CTestDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(/*IDR_MAINFRAME*/IDI_ICON1);
}

void CTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Url);
	DDX_Control(pDX, IDC_EDIT2, m_Response);
	DDX_Control(pDX, IDC_EDIT3, m_Uid);
	DDX_Control(pDX, IDC_EDIT4, m_Key);
	DDX_Control(pDX, IDC_EDIT5, m_Printerid);
	DDX_Control(pDX, IDC_EDIT6, m_Oid);
	DDX_Control(pDX, IDC_EDIT7, m_Date_from);
	DDX_Control(pDX, IDC_EDIT8, m_Date_to);
	DDX_Control(pDX, IDC_EDIT9, m_Printerkey);
	DDX_Control(pDX, IDC_COMBO1, m_API_Options);

}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDemoDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTestDemoDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDemoDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTestDemoDlg 消息处理程序

BOOL CTestDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_init_printer.php");
	m_API_Options.SetCurSel(0);
	m_Uid.SetWindowTextW(L"1088201904239558");
	m_Key.SetWindowTextW(L"c65ef70a-b734-aea0-64fa-d9d30792f8f1");
	m_Printerkey.SetWindowTextW(L"2088212114563161");
	m_Printerid.SetWindowTextW(L"05");
	m_Oid.SetWindowTextW(L"2016111504");
	taskid = L"cf5b6752-70aa-4d4a-aa55-5e653b821b92";


	m_Printerid.EnableWindow(FALSE);
	m_Oid.EnableWindow(FALSE);
	m_Date_from.EnableWindow(FALSE);
	m_Date_to.EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDemoDlg::OnPaint()
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
HCURSOR CTestDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CTestDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CTestDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//CInternetSession session;
	//session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	//session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	//session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	//CHttpConnection* pConnection = session.GetHttpConnection(TEXT("www.baidu.com"), (INTERNET_PORT)80);
	//CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,
	//	TEXT("/Practice/index.jsp"));

	//CString szHeaders = L"Accept: audio/x-aiff, audio/basic, audio/midi,\
 //                    audio/mpeg, audio/wav, image/jpeg, image/gif, image/jpg, image/png,\
 //                    image/mng, image/bmp, text/plain, text/html, text/htm\r\n";

	//pFile->AddRequestHeaders(szHeaders);

	//pFile->SendRequest();

	//DWORD dwRet;
	//pFile->QueryInfoStatusCode(dwRet);

	//if (dwRet != HTTP_STATUS_OK)
	//{
	//	CString errText;
	//	errText.Format(L"POST出错，错误码：%d", dwRet);
	//	AfxMessageBox(errText);
	//}
	//else
	//{
	//	int len = pFile->GetLength();
	//	char buf[2000];
	//	int numread;
	//	CString filepath;
	//	CString strFile = L"response.txt";
	//	filepath.Format(L".\\%s", strFile);
	//	CFile myfile(filepath,
	//		CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	//	while ((numread = pFile->Read(buf, sizeof(buf) - 1)) > 0)
	//	{
	//		buf[numread] = '\0';
	//		strFile += buf;
	//		myfile.Write(buf, numread);
	//	}
	//	myfile.Close();
	//}

	//session.Close();
	//pFile->Close();
	//delete pFile;

	string tmp;
	hc.HttpGet(L"https://www.baidu.com/index.html", NULL, tmp);

	//CString filepath;
	//CString strFile = L"response.txt";
	//filepath.Format(L".\\%s", strFile);
	//CFile myfile(filepath,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	//myfile.Write(tmp.c_str(), tmp.length());
	//myfile.Close();
}


void CTestDemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString url,uid,key,printerid,oid,date_from,date_to,printerkey;

	m_Url.GetWindowTextW(url);
	m_Uid.GetWindowTextW(uid);
	m_Key.GetWindowTextW(key);
	m_Printerid.GetWindowTextW(printerid);
	m_Oid.GetWindowTextW(oid);
	m_Date_from.GetWindowTextW(date_from);
	m_Date_to.GetWindowTextW(date_to);
	m_Printerkey.GetWindowTextW(printerkey);

	
	SYSTEMTIME tmSys;
	GetLocalTime(&tmSys);
	CTime tm3(tmSys);
	__int64 tmDst = __int64(tm3.GetTime()) * 1000 + tmSys.wMilliseconds;
	char sMS[100];
	_i64toa(tmDst, sMS, 10);
	//CString time(sMS);
	CString time = L"1479181567721";

	int index = m_API_Options.GetCurSel();
	CString ret;
	switch (index)
	{
	case 0://初始化打印机; 
	{
		ret = do_init_printer(url, uid, key, time);
		if (L"0x000" == ret)
			MessageBox(L"用户编号不存在!");
		else if (L"0x001" == ret)
			MessageBox(L"签名错误!");
		else if (L"0x002" == ret)
			MessageBox(L"初始化成功!");
		else
			MessageBox(ret);
	}
	break;
	case 1://打印订单; 
	{
		ret = do_print_data(url, uid, key, time, printerid, printerkey, oid);
		if (L"0x000" == ret)
			MessageBox(L"用户编号不存在!");
		else if (L"0x001" == ret)
			MessageBox(L"打印机编号不存在!");
		else if (L"0x002" == ret)
			MessageBox(L"签名错误!");
		else if (L"true" == ret)
			MessageBox(taskid);
		else
			MessageBox(ret);
	}
	break;
	case 2://查询订单打印结果; 
	{
		ret = do_get_order_print_result(url, uid, key, time, printerid, taskid);
		if (L"0x000" == ret)
			MessageBox(L"用户编号不存在!");
		else if (L"0x001" == ret)
			MessageBox(L"签名错误!");
		else if (L"0x002" == ret)
			MessageBox(L"任务编号不存在!");
		else if (L"0" == ret)
			MessageBox(L"等待!");
		else if (L"1" == ret)
			MessageBox(L"成功!");
		else if (L"2" == ret)
			MessageBox(L"失败!");
		else
			MessageBox(ret);
	}
	break;
	case 3://查询打印机状态;
	{
		ret = do_get_printer_state(url, uid, key, time, printerid, printerkey);
		if (L"0x000" == ret)
			MessageBox(L"用户编号不存在!");
		else if (L"0x001" == ret)
			MessageBox(L"打印机编号不存在!");
		else if (L"0x002" == ret)
			MessageBox(L"签名错误!");
		else if (L"0" == ret)
			MessageBox(L"在线!");		
		else if (L"1" == ret)
			MessageBox(L"缺纸!");
		else if (L"2" == ret)
			MessageBox(L"忙碌!");
		else if (L"3" == ret)
			MessageBox(L"其它错误!");
		else if (L"4" == ret)
			MessageBox(L"离线!");
		else
			MessageBox(ret);
	}
	break;
	case 4://获取打印机信息;
	{
		ret = do_get_printer_info(url, uid, key, time, date_from, date_to);
		if (L"0x000" == ret)
			MessageBox(L"用户编号不存在!");
		else if (L"0x001" == ret)
			MessageBox(L"指定时间段内没有添加打印机!");
		else
			MessageBox(ret);
	}
	break;
	case 5://订单打印完成上报;
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/空");
	}
	break;

	default:
		break;
	}
	
}

//*********************************************************
//post提交的参数说明：
//名称	描述
//uid	用户编号(管理系统中获取)
//time	时间戳(服务器用于验证超时)
//sign	签名验证
//举例
//post 提交内容如下：
//uid = 1088201610083578 & time = 1479182074776 & sign = 88CCE81628D51923DCCB1896A17C3438
//返回json数据如下：
//{ "message":true }，即初始化打印机成功。
//举例
//post 提交内容如下：
//uid = 1088201610083578 & time = 1479182074776 & sign = 88CCE81628D51923DCCB1896A17C3438
CString CTestDemoDlg::do_init_printer(CString url, CString uid, CString key, CString time)
{
	//组织sign  apikey=值&time=值&uid=值
	CString sign;
	sign += "apikey=";
	sign += key;
	sign += "&time=";
	sign += time;
	sign += "&uid=";
	sign += uid;

	//将sign以md5方式加密
	MD5 md5;                 //定义MD5的类
	md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

	char*   utf8Str;
	int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

	md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

	CString sign2;
	sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

	//组织POST "uid=值&time=值&sign=大写值"
	CString postStr;
	postStr += "uid=";
	postStr += uid;
	postStr += "&time=";
	postStr += time;
	postStr += "&sign=";
	postStr += sign2.MakeUpper();//全部转大写

	string tmp;
	int ret = hc.HttpPost(url, postStr, tmp);
	//int ret = hc.HttpGet(url, postStr, tmp);

	//test json
	//CString strJson = L"{\"message\": \"中文\"}";
	//Json::Reader reader;
	//Json::Value root;
	//USES_CONVERSION;
	//char* cJson = T2A(strJson.GetBuffer(0));
	//strJson.ReleaseBuffer();
	//CString test;
	//if (reader.parse(tmp.c_str(), root))
	//{
	//	test = root["message"].asCString();
	//}
	//MessageBox(test);

	Json::Reader reader;
	Json::Value root;
	CString response;
	if (reader.parse(tmp.c_str(), root))
	{
		response = root["message"].asCString();
		m_Response.SetWindowTextW(response);
	}
	else
	{
		response = L"Json 解析错误";
		m_Response.SetWindowTextW(response);
	}

	CString filepath;
	CString strFile = L"response.html";
	filepath.Format(L".\\%s", strFile);
	CFile myfile(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	myfile.Write(tmp.c_str(), tmp.length());
	myfile.Close();

	if (NULL != utf8Str)
	{
		free(utf8Str);
		utf8Str = NULL;
	}

	return response;
}


//*********************************************************
//post提交的参数说明：
//名称	描述
//uid	用户编号(管理系统中获取)
//time	时间戳(服务器用于验证超时)
//sign	签名验证
//printerid	打印机编号（调用4.5获取打印机信息接口获取）
//oid	订单编号
//content	订单内容
//post提交内容如下：
//uid = 1088201610083578 & time = 1479182074776 & sign = 88CCE81628D51923DCCB1896A17C3438&printerid = 98 & oid = 2016111504 & content = 测试打印！
//举例
//post提交内容如下：
//uid = 1088201610083578 & time = 1479182074776 & sign = 88CCE81628D51923DCCB1896A17C3438&printerid = 98 & oid = 2016111504 & content = 测试打印！
CString CTestDemoDlg::do_print_data(CString url, CString uid, CString key, CString time, CString printerid, CString printerkey, CString oid)
{
	//组织sign  apikey=值&printerid=值&time=值&uid=值&printerkey=值
	CString sign;
	sign += "apikey=";
	sign += key;
	sign += "&printerid=";
	sign += printerid;
	sign += "&time=";
	sign += time;
	sign += "&uid=";
	sign += uid;
	sign += "&printerkey=";
	sign += printerkey;

	//将sign以md5方式加密
	MD5 md5;                 //定义MD5的类
	md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

	char*   utf8Str;
	int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

	md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

	CString sign2;
	sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

	//组织POST
	CString postStr;
	postStr += "uid=";
	postStr += uid;
	postStr += "&time=";
	postStr += time;
	postStr += "&sign=";
	postStr += sign2.MakeUpper();//全部转大写
	postStr += "&printerid=";
	postStr += printerid;
	postStr += "&oid=";
	postStr += oid;
	postStr += "&content=测试打印！";

	string tmp;
	int ret = hc.HttpPost(url, postStr, tmp);

	Json::Reader reader;
	Json::Value root;
	CString response;
	if (reader.parse(tmp.c_str(), root))
	{
		if (root["message"].isBool())
		{
			if (root["message"].asBool())
			{
				m_Response.SetWindowTextW(L"true");
				response = L"true";
				taskid = root["taskid"].asCString();
			}
			else
			{
				m_Response.SetWindowTextW(L"false");
				response = L"false";
			}
		}
		else
		{
			response = root["message"].asCString();
			m_Response.SetWindowTextW(response);
		}
	}
	else
	{
		response = L"Json 解析错误";
		m_Response.SetWindowTextW(response);
	}

	CString filepath;
	CString strFile = L"response.html";
	filepath.Format(L".\\%s", strFile);
	CFile myfile(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	myfile.Write(tmp.c_str(), tmp.length());
	myfile.Close();

	if (NULL != utf8Str)
	{
		free(utf8Str);
		utf8Str = NULL;
	}
	return response;
}


//*********************************************************
//post提交的参数说明：
//名称	描述
//uid	用户编号(管理系统中获取)
//taskid	订单唯一任务编号（可在发送数据接口的返回值中获取）
//time	时间戳(服务器用于验证超时)
//sign	签名验证
//post提交内容如下：
//uid = 1088201610083578 & time = 1479182074776 & sign = 88CCE81628D51923DCCB1896A17C3438&printerid = 98 & oid = 2016111402
//举例
//post提交内容如下：
//uid=1088201610083578&time=1479182074776&sign=88CCE81628D51923DCCB1896A17C3438&printerid=98&taskid=cf5b6752-70aa-4d4a-aa55-5e653b821b92
CString CTestDemoDlg::do_get_order_print_result(CString url, CString uid, CString key, CString time, CString printerid, CString taskid)
{
	//组织sign  apikey=值&time=值&uid=值
	CString sign;
	sign += "apikey=";
	sign += key;
	sign += "&time=";
	sign += time;
	sign += "&uid=";
	sign += uid;

	//将sign以md5方式加密
	MD5 md5;                 //定义MD5的类
	md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

	char*   utf8Str;
	int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

	md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

	CString sign2;
	sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

	//组织POST
	CString postStr;
	postStr += "uid=";
	postStr += uid;
	postStr += "&time=";
	postStr += time;
	postStr += "&sign=";
	postStr += sign2.MakeUpper();//全部转大写
	postStr += "&printerid=";
	postStr += printerid;
	postStr += "&taskid=";
	postStr += taskid;

	string tmp;
	int ret = hc.HttpPost(url, postStr, tmp);

	Json::Reader reader;
	Json::Value root;
	CString response;
	if (reader.parse(tmp.c_str(), root))
	{
		response = root["state"].asCString();
		m_Response.SetWindowTextW(response);
	}
	else
	{
		response = L"Json 解析错误";
		m_Response.SetWindowTextW(response);
	}

	CString filepath;
	CString strFile = L"response.html";
	filepath.Format(L".\\%s", strFile);
	CFile myfile(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	myfile.Write(tmp.c_str(), tmp.length());
	myfile.Close();

	if (NULL != utf8Str)
	{
		free(utf8Str);
		utf8Str = NULL;
	}
	return response;
}

//*********************************************************
//post提交的参数说明：
//名称	描述
//uid	用户编号(管理系统中获取)
//time	时间戳(服务器用于验证超时)
//sign	签名验证
//printerid	打印机编号（调用4.5获取打印机信息接口获取）
//post提交内容如下：

//返回的json数据如下：
//printerid = 98 & time = 1479181567721 & sign = 2BA31823DC72BE2C8223ED28930DA843&uid = 1088201610083578
//{"state":1}, 即编号98的打印机处于缺纸状态
CString CTestDemoDlg::do_get_printer_state(CString url, CString uid, CString key, CString time, CString printerid, CString printerkey)
{
	//组织sign  apikey=值&printerid=值&time=值&uid=值&printerkey=值
	CString sign;
	sign += "apikey=";
	sign += key;
	sign += "&printerid=";
	sign += printerid;
	sign += "&time=";
	sign += time;
	sign += "&uid=";
	sign += uid;
	sign += "&printerkey=";
	sign += printerkey;

	//将sign以md5方式加密
	MD5 md5;                 //定义MD5的类
	md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

	char*   utf8Str;
	int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

	md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

	CString sign2;
	sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

	//组织POST
	CString postStr;
	postStr += "printerid=";
	postStr += printerid;
	postStr += "&time=";
	postStr += time;
	postStr += "&sign=";
	postStr += sign2.MakeUpper();//全部转大写
	postStr += "&uid=";
	postStr += uid;


	string tmp;
	int ret = hc.HttpPost(url, postStr, tmp);


	Json::Reader reader;
	Json::Value root;
	CString response;
	if (reader.parse(tmp.c_str(), root))
	{
		response = root["state"].asCString();
		m_Response.SetWindowTextW(response);
	}
	else
	{
		response = L"Json 解析错误";
		m_Response.SetWindowTextW(response);
	}


	CString filepath;
	CString strFile = L"response.html";
	filepath.Format(L".\\%s", strFile);
	CFile myfile(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	myfile.Write(tmp.c_str(), tmp.length());
	myfile.Close();

	if (NULL != utf8Str)
	{
		free(utf8Str);
		utf8Str = NULL;
	}
	return response;
}

////*********************************************************
//接口说明：查询在指定的时间段内该用户添加的所有的打印机的信息, 如未指定日期则默认查询该用户的所有打印机信息。
//post提交的参数说明：
//名称	描述
//uid	用户编号(管理系统中获取)
//time	时间戳(服务器用于验证超时)
//sign	签名验证
//date_from	开始日期，格式：yyyy - mm - dd如：2016 - 11 - 15
//date _to	开始日期(形如：2016 - 11 - 15)
//举例
//post提交内容如下：
//uid = 1088201610083578 & time = 1479181567721 & sign = 2BA31823DC72BE2C8223ED28930DA843& date _from = 2016 - 11 - 02 & date _to = 2016 - 11 - 02
CString CTestDemoDlg::do_get_printer_info(CString url, CString uid, CString key, CString time, CString date_from, CString date_to)
{
	//组织sign  apikey=值&time=值&uid=值
	CString sign;
	sign += "apikey=";
	sign += key;
	sign += "&time=";
	sign += time;
	sign += "&uid=";
	sign += uid;

	//将sign以md5方式加密
	MD5 md5;                 //定义MD5的类
	md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

	char*   utf8Str;
	int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

	md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

	CString sign2;
	sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

	//组织POST
	CString postStr;
	postStr += "uid=";
	postStr += uid;
	postStr += "&time=";
	postStr += time;
	postStr += "&sign=";
	postStr += sign2.MakeUpper();//全部转大写
	postStr += "&date_from=";
	postStr += date_from;
	postStr += "&date_to=";
	postStr += date_to;

	string tmp;
	int ret = hc.HttpPost(url, postStr, tmp);

	Json::Reader reader;
	Json::Value root;
	CString response;
	if (reader.parse(tmp.c_str(), root))
	{
		if (root["message"].compare("0x000"))
		{
			response = L"0x000";
			m_Response.SetWindowTextW(response);
		}
		else if (root["message"].compare("0x001"))
		{
			response = L"0x001";
			m_Response.SetWindowTextW(response);
		}
		else
		{
			response = root["printerid"].asCString();
			m_Printerid.SetWindowTextW(response);
			response = root["printerkey"].asCString();
			m_Printerkey.SetWindowTextW(response);

			CString tmp;
			response = root["riqi"].asCString();
			tmp.Append(response);
			response = root["province"].asCString();
			tmp.Append(response);
			response = root["city"].asCString();
			tmp.Append(response);

			response = tmp;
			m_Response.SetWindowTextW(response);
		}
	}
	else
	{
		response = L"Json 解析错误";
		m_Response.SetWindowTextW(response);
	}

	CString filepath;
	CString strFile = L"response.html";
	filepath.Format(L".\\%s", strFile);
	CFile myfile(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	myfile.Write(tmp.c_str(), tmp.length());
	myfile.Close();

	if (NULL != utf8Str)
	{
		free(utf8Str);
		utf8Str = NULL;
	}
	return response;
}


//*****************************************************
//Pos as UTF-8
//试验代码，暂时保留
const int UNICODE_TXT_FLG = 0xFEFF;  //UNICODE文本标示
const int UTF8_TXT_FLG = 0xbfbbef;	 //utf8格式

char* EncodeToUTF8(const char* mbcsStr)
{
	wchar_t*  wideStr;
	char*   utf8Str;
	int   charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);

	utf8Str = (char*)malloc(charLen);

	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	free(wideStr);
	return utf8Str;

}
char* UTF8ToEncode(const char* mbcsStr)
{
	wchar_t*  wideStr;
	char*   unicodeStr;
	int   charLen;

	charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, wideStr, charLen);

	charLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	unicodeStr = (char*)malloc(charLen);
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, unicodeStr, charLen, NULL, NULL);

	free(wideStr);
	return unicodeStr;
}


void CTestDemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CStringW username, password, cname, name, phone;
	//GetDlgItemTextW(IDC_USERNAME, username);
	//GetDlgItemTextW(IDC_PASSWORD, password);
	//GetDlgItemTextW(IDC_CNAME, cname);
	//GetDlgItemTextW(IDC_NAME, name);
	//GetDlgItemTextW(IDC_PHONE, phone);

	BOOL ret = FALSE;
	CInternetSession session;
	CHttpConnection *pServer;
	CHttpFile * pf;
	//m_check = "";
	try
	{
		CString ServerName;
		m_Url.GetWindowTextW(ServerName);
		CString strServer, strObject, strHeader, strRet;
		INTERNET_PORT nPort;
		DWORD dwServiceType;
		if (!AfxParseURL(ServerName, dwServiceType, strServer, strObject, nPort))
		{
			AfxMessageBox(_T("URL is ERROR!"));
			return;
		}


		//**************************************
		CString url, uid, key;
		m_Url.GetWindowTextW(url);
		m_Uid.GetWindowTextW(uid);
		m_Key.GetWindowTextW(key);

		CTime time1 = CTime::GetCurrentTime();
		int nTSeconds = time1.GetTime();
		CTime time2(1970, 1, 2, 0, 0, 0);
		nTSeconds = time1.GetTime();
		CString time;
		time.Format(L"%d", nTSeconds);

		//组织sign
		CString sign;
		sign += "time";
		sign += time;
		sign += "uid";
		sign += uid;
		sign += key;

		//将sign以md5方式加密
		MD5 md5;                 //定义MD5的类
		md5.reset();//注意：每次加密一个字符串，需要调用reset()函数一次。  //用于去除原字符串内容，这样又能继续加密下一个字符串了

		char*   utf8Str;
		int charLen = WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, NULL, 0, NULL, NULL);
		utf8Str = (char*)malloc(charLen);
		WideCharToMultiByte(CP_UTF8, 0, sign.GetBuffer(), -1, utf8Str, charLen, NULL, NULL);

		md5.update(utf8Str);          //因为update函数只接收string类型，所以使用getbuffer()函数转换CString为string

		CString sign2;
		sign2 = md5.toString().c_str();     //toString()函数获得加密字符串，c_str();函数重新转换成CString类型

		//组织POST
		CString postStr;
		postStr += "uid=";
		postStr += uid;
		postStr += "&time=";
		postStr += time;
		postStr += "&sign=";
		postStr += sign2.MakeUpper();//全部转大写

		//**************************************
		CStringW data(postStr);
		//CStringW data = _T("contact_name=") + name + _T("&user_password=") + password + _T("&regemail=") + username + _T("&node_name=") + cname + _T("&contact_phone=") + phone + _T("&province_code=09") + _T("&city_code=021");
		char * pData = EncodeToUTF8(CStringA(data));
		pServer = session.GetHttpConnection(strServer, nPort);
		pf = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
		if (pf == NULL)
		{
			AfxMessageBox(_T("Connot find the web!"));
			return;
		}
		pf->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded"));
		pf->AddRequestHeaders(_T("Accept: */*"));
		//pf->SendRequest(NULL, 0, pData, strlen(pData));
		pf->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)pData, pData == NULL ? 0 : data.GetLength());

		DWORD statusCode = 0;
		if (!pf->QueryInfoStatusCode(statusCode) || statusCode != HTTP_STATUS_OK)
		{
			CStringW estr;
			estr.Format(_T("PC WEB Login failed, Pls Check. status code = %d/n"), statusCode);
			AfxMessageBox(estr);
			return;
		}
		DWORD ptrLen = 100 * 1024;
		LPSTR ptr = new CHAR[ptrLen];
		ZeroMemory(ptr, ptrLen);
		DWORD len = 0, len2 = 0;
		do
		{
			len = pf->Read(ptr + len2, ptrLen);
			len2 += len;
		} while (len != 0);
		CStringA content(ptr);
		char * newContent = UTF8ToEncode(content);
		CFile f;
		f.Open(_T("./user.html"), CFile::modeCreate | CFile::modeWrite);
		f.Write(&UTF8_TXT_FLG, 3);//UTF-8 标识符 写入头部
		f.Write(newContent, strlen(newContent));
		delete pf;
		f.Close();
	}
	catch (CMemoryException* e)
	{

	}
	catch (CFileException* e)
	{
	}
	catch (CException* e)
	{
	}

}



void CTestDemoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Response.SetWindowTextW(L"");
}


void CTestDemoDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_API_Options.GetCurSel())
	{
	case 0://初始化打印机; 
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_init_printer.php");
		m_Printerid.EnableWindow(FALSE);
		m_Oid.EnableWindow(FALSE);
		m_Date_from.EnableWindow(FALSE);
		m_Date_to.EnableWindow(FALSE);
	}
	break;
	case 1://打印订单; 
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_print_data.php");
		m_Printerid.EnableWindow(TRUE);
		m_Oid.EnableWindow(TRUE);
		m_Date_from.EnableWindow(FALSE);
		m_Date_to.EnableWindow(FALSE);
	}
	break;
	case 2://查询订单打印结果; 
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_get_order_print_result.php");
		m_Printerid.EnableWindow(TRUE);
		m_Oid.EnableWindow(TRUE);
		m_Date_from.EnableWindow(FALSE);
		m_Date_to.EnableWindow(FALSE);
	}
	break;
	case 3://查询打印机状态;
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_get_printer_state.php");
		m_Printerid.EnableWindow(TRUE);
		m_Oid.EnableWindow(FALSE);
		m_Date_from.EnableWindow(FALSE);
		m_Date_to.EnableWindow(FALSE);
	}
	break;
	case 4://获取打印机信息;
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/yun/k/api/do_get_printer_info.php");
		m_Printerid.EnableWindow(FALSE);
		m_Oid.EnableWindow(FALSE);
		m_Date_from.EnableWindow(TRUE);
		m_Date_to.EnableWindow(TRUE);

		CTime curTime = CTime::GetCurrentTime();
		CString strTime = curTime.Format("%Y-%m-%d");
		m_Date_from.SetWindowTextW(strTime);
		m_Date_to.SetWindowTextW(strTime);
	}
	break;
	case 5://订单打印完成上报;
	{
		m_Url.SetWindowTextW(L"http://192.168.1.145/空");
	}
	break;

	default:
		break;
	}
}


void CTestDemoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T(".\\response.html"), NULL, NULL, SW_SHOW);
}
