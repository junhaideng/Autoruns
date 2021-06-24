#pragma once
#ifndef LOGON_H
#define LOGON_H

#include <windows.h>
#include <QTableWidget>
#include <vector>
#include "utils.h"
using std::vector;

class Logon
{
private:
  int get_data(HKEY hkey, LPCWSTR subKey, vector<item> &data);
  int read_dir(QString, vector<item> &);

public:
  Logon();
  int setTableData(QTableWidget *);
};

#endif // LOGON_H
