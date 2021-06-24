#include "utils.h"
#include <windows.h>
#include <iostream>
#include <QString>
#include <wintrust.h>
#include <wincrypt.h>
#include <softpub.h>

#pragma comment(lib, "version")
#pragma comment(lib, "wintrust")

using std::string;

const int MAX_SIZE = 512;

QString wchar2Qs(TCHAR *str)
{
  return QString::fromStdWString(str);
}

QString Byte2Qs(BYTE *str)
{
  return QString::fromWCharArray((LPCTSTR)str);
}

// 获取文件属性中的详细信息
// value: 属性键值
// szModuleName: 对应的文件路径
string GetFileDetailInfoByValue(const string &ValueName, const string &szModuleName)
{
  BYTE *m_lpVersionData = NULL;
  DWORD m_dwLangCharset = 0;
  CHAR *tmpstr = NULL;
  DWORD dwHandle;
  // 判断系统能否检索到指定文件的版本信息
  DWORD dwDataSize = GetFileVersionInfoSizeA((LPCSTR)szModuleName.c_str(), &dwHandle);
  if (dwDataSize == 0)
    return "";

  m_lpVersionData = new BYTE[dwDataSize + 1];
  if (NULL == m_lpVersionData)
    return "";

  // 检索信息
  if (!GetFileVersionInfoA((LPCSTR)szModuleName.c_str(), dwHandle, dwDataSize,
                           (void *)m_lpVersionData))
    return "";

  UINT nQuerySize;
  DWORD *pTransTable;
  // 设置语言
  if (!VerQueryValueA(m_lpVersionData, "\\VarFileInfo\\Translation", (void **)&pTransTable, &nQuerySize))
    return "";

  m_dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));
  if (m_lpVersionData == NULL)
    return "";

  tmpstr = new CHAR[128]; // 分配缓冲区
  sprintf_s(tmpstr, 128, "\\StringFileInfo\\%08lx\\%s", m_dwLangCharset, ValueName.c_str());
  LPVOID lpData;

  // 调用此函数查询前需要先依次调用函数GetFileVersionInfoSize和GetFileVersionInfo
  if (!VerQueryValueA((void *)m_lpVersionData, tmpstr, &lpData, &nQuerySize))
  {
    delete[] m_lpVersionData;
    delete[] tmpstr;
    return "";
  }
  delete[] m_lpVersionData;
  delete[] tmpstr;
  return (char *)lpData;
}

string get_env(const string env)
{
  char *name = new char[MAX_SIZE];
  ZeroMemory(name, MAX_SIZE);
  GetEnvironmentVariableA(env.c_str(), name, MAX_SIZE);
  return name;
}

// 解析路径
string parse(const string path)
{

  string image_path = path;
  int n;
  if ((n = image_path.find(" -")) != -1) // 含有命令选项
    image_path = image_path.substr(0, n);
  if ((n = image_path.find(" /")) != -1) // 含有命令选项
    image_path = image_path.substr(0, n);
  if ((n = image_path.find("\"")) != -1)
  { // 被双引号包裹的路径
    if (n == 0)
    {
      image_path = image_path.substr(1);
      if ((n = image_path.find("\"")) != -1)
        image_path = image_path.substr(0, n);
    }
  }
  // 含有环境变量 %
  if ((n = image_path.find("%")) == 0)
  {
    int second = image_path.find("%", n + 1);
    image_path = get_env(image_path.substr(n + 1, second - 1)) + image_path.substr(second + 1);
  }
  // 直接以system32 开始
  if ((n = image_path.find("system32")) != -1) // 包含系统环境变量
    image_path = image_path.substr(n).insert(0, "C:\\Windows\\");
  if ((n = image_path.find("System32")) != -1)
    image_path = image_path.substr(n).insert(0, "C:\\Windows\\");
  if ((n = image_path.find("SysWOW64\\")) != -1)
    image_path = image_path.substr(n).insert(0, "C:\\Windows\\");
  if ((n = image_path.find("\\??\\")) >= 0)
    image_path = image_path.substr(4);

  // 如果只包含文件名
  if ((n = image_path.find("C:")) < 0 && (n = image_path.find("D:")) < 0 && (n = image_path.find("{")) != 0)
  {
    image_path.insert(0, "C:\\Windows\\System32\\");
  }

  return image_path;
}

// 将对应的HKEY转换成字符串
QString key2Qs(HKEY hkey)
{
  if (hkey == HKEY_CLASSES_ROOT)
  {
    return "HKEY_CLASSES_ROOT";
  }
  else if (hkey == HKEY_LOCAL_MACHINE)
  {
    return "HKEY_LOCAL_MACHINE";
  }
  else if (hkey == HKEY_CURRENT_USER)
  {
    return "HKEY_CURRENT_USER";
  }
  else if (hkey == HKEY_CURRENT_CONFIG)
  {
    return "HKEY_CURRENT_CONFIG";
  }
  else if (hkey == HKEY_USERS)
  {
    return "HKEY_USERS";
  }
  return "";
}

QString time2Qs(FILETIME *time)
{
  SYSTEMTIME s;
  FileTimeToSystemTime(time, &s);
  QString t = QString("%1-%2-%3 %4:%5:%6").arg(s.wYear).arg(s.wMonth).arg(s.wDay).arg(s.wHour).arg(s.wMinute).arg(s.wSecond);
  return t;
}

// ref: https://docs.microsoft.com/en-us/windows/win32/seccrypto/example-c-program--verifying-the-signature-of-a-pe-file
BOOL VerifyEmbeddedSignature(LPCWSTR pwszSourceFile)
{
  LONG lStatus;

  // Initialize the WINTRUST_FILE_INFO structure.

  WINTRUST_FILE_INFO FileData;
  memset(&FileData, 0, sizeof(FileData));
  FileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
  FileData.pcwszFilePath = pwszSourceFile;
  FileData.hFile = NULL;
  FileData.pgKnownSubject = NULL;

  GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
  WINTRUST_DATA WinTrustData;

  // Initialize the WinVerifyTrust input data structure.

  // Default all fields to 0.
  memset(&WinTrustData, 0, sizeof(WinTrustData));

  WinTrustData.cbStruct = sizeof(WinTrustData);

  // Use default code signing EKU.
  WinTrustData.pPolicyCallbackData = NULL;

  // No data to pass to SIP.
  WinTrustData.pSIPClientData = NULL;

  // Disable WVT UI.
  WinTrustData.dwUIChoice = WTD_UI_NONE;

  // No revocation checking.
  WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;

  // Verify an embedded signature on a file.
  WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;

  // Verify action.
  WinTrustData.dwStateAction = WTD_STATEACTION_VERIFY;

  // Verification sets this value.
  WinTrustData.hWVTStateData = NULL;

  // Not used.
  WinTrustData.pwszURLReference = NULL;

  // This is not applicable if there is no UI because it changes
  // the UI to accommodate running applications instead of
  // installing applications.
  WinTrustData.dwUIContext = 0;

  // Set pFile.
  WinTrustData.pFile = &FileData;

  // WinVerifyTrust verifies signatures as specified by the GUID
  // and Wintrust_Data.
  lStatus = WinVerifyTrust(
      NULL,
      &WVTPolicyGUID,
      &WinTrustData);

  // Any hWVTStateData must be released by a call with close.
  WinTrustData.dwStateAction = WTD_STATEACTION_CLOSE;

  if (lStatus == ERROR_SUCCESS)
  {
    return true;
  }
  return false;
}

QString verifyStr(BOOL flag)
{
  if (flag)
  {
    return QString("√");
  }
  return QString("×");
}

string bstr2std(BSTR str)
{
  if (str == NULL)
  {
    return "";
  }
  char tmp[MAX_SIZE];
  ZeroMemory(tmp, MAX_SIZE);
  sprintf(tmp, "%S", str);
  return tmp;
}
