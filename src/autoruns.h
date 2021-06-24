#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logon.h"
#include "service.h"
#include "tasks.h"
#include "dlls.h"
#include "bootexecute.h"
#include "driver.h"

#define TAB_NUM 6

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionAbout_triggered();

  void on_tabWidget_currentChanged(int index);

  void on_actionRefresh_triggered();

private:
  Ui::MainWindow *ui;

  // 每一个tab
  Logon *logon;
  Service *service;
  Tasks *tasks;
  Dlls *dlls;
  BootExecute *bootExecute;
  Driver *driver;

  // 缓存数据
  bool cache[TAB_NUM];
};
#endif // MAINWINDOW_H
