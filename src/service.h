#ifndef SERVICE_H
#define SERVICE_H
#include <QTableWidget>
#include <windows.h>
#include <vector>
#include "utils.h"

using std::vector;

class Service
{
private:
  int get_data(HKEY hkey, LPCWSTR lpszSubKey, vector<item> &table_data, const QString &);

public:
  Service();
  int setTableData(QTableWidget *table);
};

#endif // SERVICE_H
