#include "dlls.h"
#include <windows.h>
#include "utils.h"
#include <QTableWidget>

Dlls::Dlls()
{
}

int Dlls::setTableData(QTableWidget *table)
{
  HKEY hkey;
  // 打开键
  int ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("System\\CurrentControlSet\\Control\\Session Manager\\KnownDlls"), 0, KEY_READ, &hkey);
  if (ret != ERROR_SUCCESS)
  {
    printf("can not open key\n");
    return -1;
  }
  DWORD subKeysCount;
  DWORD maxSubKeyLen;
  DWORD valueCount;
  DWORD maxValueNameLen;
  DWORD maxValueLen;
  // 获取子键信息
  ret = RegQueryInfoKeyW(hkey, NULL, NULL, NULL, &subKeysCount, &maxSubKeyLen, NULL, &valueCount, &maxValueNameLen, &maxValueLen, NULL, NULL);
  if (ret != ERROR_SUCCESS)
  {
    printf("can not get key info\n");
    return -1;
  }
  DWORD nameLen = maxValueNameLen + 1;
  DWORD dataLen = maxValueLen + 1;
  DWORD type = 0;
  TCHAR *name = new TCHAR[nameLen];
  BYTE *data = new BYTE[dataLen];

  // 设置表的行数
  table->setRowCount(valueCount);

  for (DWORD i = 0; i < valueCount; i++)
  {
    nameLen = maxValueNameLen + 1;
    dataLen = maxValueLen + 1;
    ZeroMemory(name, nameLen);
    ZeroMemory(data, dataLen);
    ret = RegEnumValueW(hkey, i, name, &nameLen, NULL, &type, data, &dataLen);
    if (ret != ERROR_SUCCESS)
    {
      printf("enum value failed\n");
      delete[] data;
      delete[] name;
      return -1;
    }
    QString qsName = wchar2Qs(name);
    QString qsData = Byte2Qs(data);

    table->setItem(i, 0, new QTableWidgetItem(qsName));
    string parsed_path = parse(qsData.toStdString());
    table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(GetFileDetailInfoByValue("FileDescription", qsData.toStdString()))));
    table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(GetFileDetailInfoByValue("CompanyName", qsData.toStdString()))));
    table->setItem(i, 3, new QTableWidgetItem(verifyStr(VerifyEmbeddedSignature(QString::fromStdString(parsed_path).toStdWString().data()))));
    table->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(parsed_path)));
  }
  delete[] name;
  delete[] data;
  RegCloseKey(hkey);
  return 0;
}
