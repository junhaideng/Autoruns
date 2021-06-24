#pragma once
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <QString>
#include <windows.h>

using std::string;
using std::vector;

typedef struct
{
  QString name, desc, company, image_path;
  BOOL isVerified;
} info;

typedef struct
{
  // 数据入口
  QString entry;
  // 数据信息
  vector<info> info;
  // 修改时间
  QString time;
} item;

// 将宽字符转换成QString
QString wchar2Qs(TCHAR *str);

// 将BYTE转换成QString
QString Byte2Qs(BYTE *str);

// 获取文件的描述信息
string GetFileDetailInfoByValue(const string &ValueName, const string &szModuleName);

// 获取环境变量值
string get_env(const string env);

// 解析获取文件路径
string parse(const string path);

QString key2Qs(HKEY hkey);

// FILETIME->QString
QString time2Qs(FILETIME *time);

// 检查签名
BOOL VerifyEmbeddedSignature(LPCWSTR pwszSourceFile);

QString verifyStr(BOOL flag);

// BSTR -> string
string bstr2std(BSTR str);

#endif // UTILS_H
