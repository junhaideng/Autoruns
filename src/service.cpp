#include <QTableWidget>
#include <QTableWidgetItem>
#include <windows.h>
#include <iostream>
#include "utils.h"
#include "service.h"
using std::cout;
using std::endl;

Service::Service()
{
}

int Service::get_data(HKEY hkey, LPCWSTR lpszSubKey, vector<item> &table_data, const QString &keyname)
{
  // 首先打开对应的键
  HKEY key = NULL;
  long ret = RegOpenKeyEx(hkey, lpszSubKey, 0, KEY_READ, &key);
  if (ret != ERROR_SUCCESS)
  {
    cout << "open key error" << endl;
    return -1;
  }
  // 子键下的数据数量
  DWORD dwValueCount = 0;
  // 名称的最大长度
  DWORD maxValueNameLen = 0;
  // 名称对应的值的最大长度
  DWORD maxValueDataLen = 0;
  FILETIME *time = new FILETIME();
  // 获取到所有的键值对信息
  ret = RegQueryInfoKey(key, // 打开的句柄。open，或者create
                        NULL,
                        NULL,
                        NULL, // 必须为NULL
                        NULL, // 子键个数
                        NULL, // 子键的最长长度
                        NULL,
                        &dwValueCount,    // // 键值对数量 key-value
                        &maxValueNameLen, // 键的最大长度
                        &maxValueDataLen, // 数据的最大长度
                        NULL,             // 安全描述符
                        time              // 最后写的时间，不关心设为 NULL
  );
  if (ret != ERROR_SUCCESS)
  {
    cout << "query info key error" << endl;
    delete time;
    return -1;
  }

  DWORD dwNameLen = maxValueNameLen + 1;
  TCHAR *pszName = new TCHAR[dwNameLen];
  DWORD dwType = 0;
  DWORD dwValueDataLen = maxValueDataLen + 1;
  BYTE *lpValueData = new BYTE[dwValueDataLen];

  vector<info> infos;

  string path, desc, image_path, company;
  bool flag = false;

  for (DWORD dwIndex = 0; dwIndex < dwValueCount; dwIndex++)
  {
    // 每一次都需要重置，因为会被修改
    dwNameLen = maxValueNameLen + 1;
    dwValueDataLen = maxValueDataLen + 1;
    ZeroMemory(pszName, maxValueNameLen + 1);
    ZeroMemory(lpValueData, maxValueDataLen + 1);

    ret = RegEnumValue(key, dwIndex, pszName, &dwNameLen, NULL, &dwType, lpValueData, &dwValueDataLen);
    if (ret == -1)
    {
      RegCloseKey(key);
      cout << "get enum value error" << endl;
      continue;
    }
    if (lpValueData == NULL)
    {
      return -1;
    }
    QString name = wchar2Qs(pszName);
    QString value = Byte2Qs(lpValueData);

    if (name.compare("Start") == 0)
    {
      if (value.toInt() > 2)
      {
        delete time;
        delete[] pszName;
        delete[] lpValueData;
        return 0;
      }
    }

    if (name.compare("ImagePath", Qt::CaseInsensitive) == 0)
    {
      path = parse(value.toStdString());
//       应该是exe文件
      if(!value.contains("exe")){
          return 0 ;
      }
      flag = true;
      int n = path.find("svchost.exe");
      // 共享进程
      if (n >= 0)
      {
        DWORD dwValueDataLen = maxValueDataLen + 1;
        ZeroMemory(lpValueData, dwValueDataLen);
        ret = RegQueryValueEx(key, TEXT("Description"), NULL, &dwType, lpValueData, &dwValueDataLen);
        string tmp = Byte2Qs(lpValueData).toStdString();
        // 没有对应的描述
        if (tmp.size() == 0)
        {
          delete time;
          delete[] pszName;
          delete[] lpValueData;
          return 0;
        }
        int comma = tmp.find(",");

        // 描述中就是需要的数据
        if (comma < 0)
        {
          desc = tmp;
          company = GetFileDetailInfoByValue("CompanyName", path);
        }
        else
        {
          // 需要到文件中进行查询
          path = parse(tmp.substr(1, comma - 1));
          desc = GetFileDetailInfoByValue("FileDescription", path);
          company = GetFileDetailInfoByValue("CompanyName", path);
        }
      }
      else
      {
        path = parse(path);
        desc = GetFileDetailInfoByValue("FileDescription", path);
        company = GetFileDetailInfoByValue("CompanyName", path);
      }
    }
  }

  if (!flag)
  {
    delete time;
    delete[] pszName;
    delete[] lpValueData;
    RegCloseKey(key);
    return 0;
  }

  BOOL verified = VerifyEmbeddedSignature(LPCWSTR(QString::fromStdString(path).toStdWString().data()));
  infos.push_back(info{
      .name = keyname,
      .desc = QString::fromStdString(desc),
      .company = QString::fromStdString(company),
      .image_path = QString::fromStdString(path),
      .isVerified = verified,
  });
  table_data.push_back(item{
      .entry = key2Qs(hkey) + QString::fromStdWString(lpszSubKey),
      .info = infos,
      .time = time2Qs(time)});
  delete time;
  delete[] pszName;
  delete[] lpValueData;
  RegCloseKey(key);
  return 0;
}

int Service::setTableData(QTableWidget *table)
{
  // 首先打开子键
  HKEY hkey = NULL;
  int ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hkey);
  vector<item> table_data;

  if (ret != ERROR_SUCCESS)
  {
    cout << "open key failed, error code: " << ret << endl;
    return -1;
  }
  cout << "open key success" << endl;

  DWORD subKeys = 0;       // 子键个数
  DWORD maxSubKeysLen = 0; // 子键的最大长度

  // 查询子键信息
  ret = RegQueryInfoKey(hkey, NULL, NULL, NULL, &subKeys, &maxSubKeysLen, NULL, NULL, NULL, NULL, NULL, NULL);
  if (ret != ERROR_SUCCESS)
  {
    cout << "query info key failed" << endl;
    return -1;
  }

  // 子键名称
  TCHAR *keyName = new TCHAR[maxSubKeysLen + 1];
  // 子键的长度
  DWORD keyLen = 0;
  TCHAR *tmp = new TCHAR[512];

  for (DWORD index = 0; index < subKeys; index++)
  {
    // 初始化内存空间
    ZeroMemory(keyName, maxSubKeysLen + 1);
    ZeroMemory(tmp, 512);

    keyLen = maxSubKeysLen + 1;
    ret = RegEnumKeyEx(hkey, index, keyName, &keyLen, NULL, NULL, NULL, NULL);
    if (ret != ERROR_SUCCESS)
    {
      cout << "enum key failed with code: " << ret << endl;
      continue;
    }
    // 访问子键中的值名称和对应的值
    lstrcat(tmp, TEXT("SYSTEM\\CurrentControlSet\\Services\\"));
    lstrcat(tmp, keyName);

    get_data(HKEY_LOCAL_MACHINE, tmp, table_data, wchar2Qs(keyName));
  }

  vector<info> infos;
  for (size_t i = 0; i < table_data.size(); i++)
  {
    infos.insert(infos.end(), table_data[i].info.begin(), table_data[i].info.end());
  }

  table->setRowCount(infos.size());

  for (size_t i = 0; i < infos.size(); i++)
  {
    table->setItem(i, 0, new QTableWidgetItem(infos[i].name));
    table->setItem(i, 1, new QTableWidgetItem(infos[i].desc));
    table->setItem(i, 2, new QTableWidgetItem(infos[i].company));
    table->setItem(i, 3, new QTableWidgetItem(verifyStr(infos[i].isVerified)));
    table->setItem(i, 4, new QTableWidgetItem(infos[i].image_path));
  }
  delete[] keyName;
  delete[] tmp;
  cout << "query info key success" << endl;
  RegCloseKey(hkey);
  return 0;
}
