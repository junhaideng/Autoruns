#ifndef BOOTEXECUTE_H
#define BOOTEXECUTE_H
#include <QTableWidget>
#include <vector>
#include "utils.h"
#include <windows.h>

class BootExecute
{
private:
  int get_data(HKEY key, LPCWSTR subKey, vector<item> &table_data);

public:
  BootExecute();
  int setTableData(QTableWidget *table);
};

#endif // BOOTEXECUTE_H
