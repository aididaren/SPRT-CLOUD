
// TestDemoDlg.h: 头文件
//

#pragma once
#include "HttpClient.h"


// CTestDemoDlg 对话框
class CTestDemoDlg : public CDialogEx
{
// 构造
public:
	CTestDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTDEMO_DIALOG };
#endif

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	CHttpClient hc;
	afx_msg void OnBnClickedButton3();

	CEdit m_Url;
	CEdit m_Response;
	afx_msg void OnBnClickedButton4();

	CEdit m_Uid;
	CEdit m_Key;
	afx_msg void OnCbnSelchangeCombo1();

	CComboBox m_API_Options;

	CEdit m_Printerid;
	CEdit m_Oid;
	CEdit m_Date_from;
	CEdit m_Date_to;
	CEdit m_Printerkey;

	CString do_init_printer(CString url, CString uid, CString key, CString time);
	CString do_print_data(CString url, CString uid, CString key, CString time, CString printerid, CString printerkey, CString oid);
	CString do_get_order_print_result(CString url, CString uid, CString key, CString time, CString printerid, CString taskid);
	CString do_get_printer_state(CString url, CString uid, CString key, CString time, CString printerid, CString printerkey);
	CString do_get_printer_info(CString url, CString uid, CString key, CString time, CString date_from, CString date_to);

	CString taskid;

	afx_msg void OnBnClickedButton5();
};
