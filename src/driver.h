#ifndef DRIVER_H
#define DRIVER_H
#include <QTableWidget>
#include <vector>
#include <windows.h>
#include "utils.h"

class Driver
{
private:
  int get_data(HKEY hkey, LPCWSTR lpszSubKey, vector<item> &table_data, const QString &keyname);

public:
  Driver();
  int setTableData(QTableWidget *table);
};

#endif // DRIVER_H
