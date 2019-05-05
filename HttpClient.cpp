////////////////////////////////// HttpClient.cpp
#include "StdAfx.h"
#include "HttpClient.h"
//#include "yazuoLog.h"

#define  BUFFER_SIZE       1024

#define  NORMAL_CONNECT             INTERNET_FLAG_KEEP_CONNECTION
#define  SECURE_CONNECT                NORMAL_CONNECT | INTERNET_FLAG_SECURE
#define  NORMAL_REQUEST             INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE 
#define  SECURE_REQUEST             NORMAL_REQUEST | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID

CHttpClient::CHttpClient(LPCTSTR strAgent)
{
	m_pSession = new CInternetSession(strAgent);
	m_pConnection = NULL;
	m_pFile = NULL;
}


CHttpClient::~CHttpClient(void)
{
	Clear();
	if (NULL != m_pSession)
	{
		m_pSession->Close();
		delete m_pSession;
		m_pSession = NULL;
	}
}

void CHttpClient::Clear()
{
	if (NULL != m_pFile)
	{
		m_pFile->Close();
		delete m_pFile;
		m_pFile = NULL;
	}

	if (NULL != m_pConnection)
	{
		m_pConnection->Close();
		delete m_pConnection;
		m_pConnection = NULL;
	}
}

int CHttpClient::ExecuteRequest(LPCTSTR strMethod, LPCTSTR strUrl, LPCTSTR strPostData, string &strResponse)
{
	CString strServer;
	CString strObject;
	DWORD dwServiceType;
	INTERNET_PORT nPort;
	strResponse = "";

	AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort);

	if (AFX_INET_SERVICE_HTTP != dwServiceType && AFX_INET_SERVICE_HTTPS != dwServiceType)
	{
		return FAILURE;
	}

	try
	{
		m_pConnection = m_pSession->GetHttpConnection(strServer,
			dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_CONNECT : SECURE_CONNECT,
			nPort);
		m_pFile = m_pConnection->OpenRequest(strMethod, strObject,
			NULL, 1, NULL, NULL,
			(dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_REQUEST : SECURE_REQUEST));

		//DWORD dwFlags;
		//QueryOption��SetOption�������ûỰ�Ĳ�ѯѡ��糬ʱֵ�����Դ����ȵȡ� 
		//m_pFile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
		//dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
		////set web server option
		//m_pFile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);

		m_pFile->AddRequestHeaders(L"Accept: *,*/*");
		m_pFile->AddRequestHeaders(L"Accept-Language: zh-cn");
		m_pFile->AddRequestHeaders(L"Content-Type: application/x-www-form-urlencoded");
		m_pFile->AddRequestHeaders(L"Accept-Encoding: gzip, deflate");

		char*   utf8Str;
		int charLen = WideCharToMultiByte(CP_UTF8, 0, strPostData, -1, NULL, 0, NULL, NULL);
		utf8Str = (char*)malloc(charLen);
		memset(utf8Str, 0, charLen);
		WideCharToMultiByte(CP_UTF8, 0, strPostData, -1, utf8Str, charLen, NULL, NULL);

		m_pFile->SendRequest(NULL, 0, (LPVOID)utf8Str, charLen-1);

		//m_pFile->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)strPostData, strPostData == NULL ? 0 : _tcslen(strPostData));

		char szChars[BUFFER_SIZE + 1] = { 0 };
		string strRawResponse = "";
		UINT nReaded = 0;
		while ((nReaded = m_pFile->Read((void*)szChars, BUFFER_SIZE)) > 0)
		{
			szChars[nReaded] = '\0';
			strRawResponse += szChars;
			memset(szChars, 0, BUFFER_SIZE + 1);
		}

		//int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, NULL, 0);
		//WCHAR *pUnicode = new WCHAR[unicodeLen + 1];
		//memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));

		//MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, pUnicode, unicodeLen);
		//CString cs(pUnicode);
		//delete[]pUnicode;
		//pUnicode = NULL;

		strResponse = strRawResponse;

		if (NULL != utf8Str)
		{
			free(utf8Str);
			utf8Str = NULL;
		}
		Clear();
	}
	catch (CInternetException* e)
	{
		Clear();
		DWORD dwErrorCode = e->m_dwError;
		e->Delete();

		DWORD dwError = GetLastError();

		//PRINT_LOG("dwError = %d", dwError, 0);

		if (ERROR_INTERNET_TIMEOUT == dwErrorCode)
		{
			return OUTTIME;
		}
		else
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int CHttpClient::HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, string &strResponse)
{
	return ExecuteRequest(L"GET", strUrl, strPostData, strResponse);
}

int CHttpClient::HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, string &strResponse)
{
	return ExecuteRequest(L"POST", strUrl, strPostData, strResponse);
}