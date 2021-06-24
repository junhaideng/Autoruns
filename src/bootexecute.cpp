#include "bootexecute.h"
#include <windows.h>
#include <QTableWidget>
#include "utils.h"

BootExecute::BootExecute()
{
}

// 从键中获取数据并保存
int BootExecute::get_data(HKEY key, LPCWSTR subKey, vector<item> &table_data)
{
  HKEY hkey;
  // 打开键
  int ret = RegOpenKeyEx(key, subKey, 0, KEY_READ, &hkey);
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
  FILETIME *time = new FILETIME();
  // 获取子键信息
  ret = RegQueryInfoKeyW(hkey, NULL, NULL, NULL, &subKeysCount, &maxSubKeyLen, NULL, &valueCount, &maxValueNameLen, &maxValueLen, NULL, time);
  if (ret != ERROR_SUCCESS)
  {
    delete time;
    printf("can not get key info\n");
    return -1;
  }
  DWORD nameLen = maxValueNameLen + 1;
  DWORD dataLen = maxValueLen + 1;
  DWORD type = 0;
  TCHAR *name = new TCHAR[nameLen];
  BYTE *data = new BYTE[dataLen];

  vector<info> infos;

  // 遍历所有字段，其实也可以使用RegQueryValueEx
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
      delete time;
      delete[] data;
      delete[] name;
      return -1;
    }
    QString value = QString::fromStdWString(name);

    // 找到BootExecute字段
    if (value.compare("BootExecute", Qt::CaseInsensitive) == 0)
    {
      string tmp = value.toStdString();
      if (tmp.find_first_of("autocheck autochk"))
      {
        tmp = "autochk.exe";
      }
      else if (tmp.find_first_of("autocheck autoconv"))
      {
        tmp = "autoconv.exe";
      }
      else if (tmp.find_first_of("autocheck chkntfs"))
      {
        tmp = "chkntfs.exe";
      }

      tmp = parse(tmp);

      // BootExecute默认就是autochk.exe
      QString desc = QString::fromStdString(GetFileDetailInfoByValue("FileDescription", tmp));
      QString company = QString::fromStdString(GetFileDetailInfoByValue("CompanyName", tmp));
      infos.push_back(info{
          .name = Byte2Qs(data),
          .desc = desc,
          .company = company,
          .image_path = QString::fromStdString(tmp),
          .isVerified = VerifyEmbeddedSignature(QString::fromStdString(tmp).toStdWString().data())});
    }
  }
  table_data.push_back(item{
      .entry = key2Qs(key) + QString::fromStdWString(subKey),
      .info = infos,
      .time = time2Qs(time)});
  delete time;
  delete[] name;
  delete[] data;
  return 0;
}

// 设置数据
int BootExecute::setTableData(QTableWidget *table)
{
  vector<item> table_data;

  get_data(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Control\\Session Manager"), table_data);

  vector<info> infos;

  for (size_t i = 0; i < table_data.size(); i++)
  {
    infos.insert(infos.end(), table_data[i].info.begin(), table_data[i].info.end());
  }

  table->setRowCount(infos.size());
  for (size_t i = 0; i < table_data.size(); i++)
  {
    table->setItem(i, 0, new QTableWidgetItem(infos[i].name));
    table->setItem(i, 1, new QTableWidgetItem(infos[i].desc));
    table->setItem(i, 2, new QTableWidgetItem(infos[i].company));
    table->setItem(i, 3, new QTableWidgetItem(verifyStr(infos[i].isVerified)));
  }

  return 0;
}
