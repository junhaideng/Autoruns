#include <QTableWidget>
#include <QMessageBox>
#include <windows.h>
#include <vector>
#include <QDir>
#include "logon.h"
#include "utils.h"

using std::string;
using std::vector;

Logon::Logon()
{
}

int Logon::read_dir(QString path, vector<item> &table_data)
{
  QDir dir(path);
  QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
  vector<info> infos;
  for (int i = 0; i < list.size(); i++)
  {
    std::cout << "file:" << list.at(i).absoluteFilePath().toStdString() << std::endl;
    QFileInfo fileinfo = QFileInfo(list.at(i).absoluteFilePath());
    QString path;
    if (fileinfo.isSymLink())
    {
      path = fileinfo.symLinkTarget();
    }
    else
    {
      path = fileinfo.absoluteFilePath();
    }

    std::cout << "target: " << path.toStdString() << std::endl;
    string desc = GetFileDetailInfoByValue("FileDescription", path.toStdString());
    string company = GetFileDetailInfoByValue("CompanyName", path.toStdString());

    BOOL verified = VerifyEmbeddedSignature(path.toStdWString().data());
    infos.push_back(info{
        .name = fileinfo.baseName(),
        .desc = QString::fromStdString(desc),
        .company = QString::fromStdString(company),
        .image_path = path,
        .isVerified = verified});
  }
  table_data.push_back(item{
      .entry = path,
      .info = infos});
  return 0;
}

int Logon::get_data(HKEY key, LPCWSTR subKey, vector<item> &table_data)
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
    printf("can not get key info\n");
    delete time;
    time = NULL;
    return -1;
  }

  DWORD nameLen = maxValueNameLen + 1;
  DWORD dataLen = maxValueLen + 1;
  DWORD type = 0;
  TCHAR *name = new TCHAR[nameLen];
  BYTE *data = new BYTE[dataLen];

  vector<info> infos;
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
    QString entry = QString::fromStdWString(name);
    QString path = Byte2Qs(data);
    string parsed_path = parse(path.toStdString());

    QString desc = QString::fromStdString(GetFileDetailInfoByValue("FileDescription", parsed_path));
    QString company = QString::fromStdString(GetFileDetailInfoByValue("CompanyName", parsed_path));
    BOOL verified = VerifyEmbeddedSignature(LPCWSTR(QString::fromStdString(parsed_path).toStdWString().data()));
    infos.push_back(info{entry, desc, company, QString::fromStdString(parsed_path), verified});
  }
  table_data.push_back(item{
      .entry = key2Qs(key) + QString::fromStdWString(subKey),
      .info = infos,
      .time = time2Qs(time)});
  delete[] name;
  delete[] data;
  return 0;
}

// 设置数据
int Logon::setTableData(QTableWidget *table)
{
  vector<item> table_data;

  // 注册表内容，这里选取典型的三项注册表
  get_data(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), table_data);
  get_data(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run"), table_data);
  get_data(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), table_data);
  std::cout << parse("%ProgramData%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup") << std::endl;
  // 读取目录内容
  read_dir(QString::fromStdString(parse("%USERPROFILE%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup")), table_data);
  read_dir(QString::fromStdString(parse("%ProgramData%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup")), table_data);
  vector<info> infos;

  for (size_t i = 0; i < table_data.size(); i++)
  {
    item data = table_data[i];
    infos.insert(infos.end(), data.info.begin(), data.info.end());
  }
  // 设置行数
  table->setRowCount(infos.size());
  for (size_t i = 0; i < infos.size(); i++)
  {
    info info = infos[i];
    table->setItem(i, 0, new QTableWidgetItem(info.name));
    table->setItem(i, 1, new QTableWidgetItem(info.desc));
    table->setItem(i, 2, new QTableWidgetItem(info.company));
    table->setItem(i, 3, new QTableWidgetItem(verifyStr(info.isVerified)));
    table->setItem(i, 4, new QTableWidgetItem(info.image_path));
  }
  return 0;
}
