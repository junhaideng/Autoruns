#include "autoruns.h"
#include "ui_autoruns.h"
#include "about.h"
#include <QMessageBox>

// 所有的标签页
enum Tab
{
  LogonTab = 0,
  ServiceTab,
  DriverTab,
  TasksTab,
  KnowDllsTab,
  BootExecuteTab
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  logon = new Logon();
  service = new Service();
  tasks = new Tasks();
  driver = new Driver();
  dlls = new Dlls();
  bootExecute = new BootExecute();
  // 初始化cache
  for (int i = 0; i < TAB_NUM; i++)
  {
    cache[i] = false;
  }
  // 初始化的时候就对Logon进行设置
  logon->setTableData(ui->LogonTable);
  cache[LogonTab] = true;
}

MainWindow::~MainWindow()
{
  delete ui;
  delete logon;
  delete service;
  delete tasks;
  delete driver;
  delete dlls;
  delete bootExecute;
}

void MainWindow::on_actionAbout_triggered()
{
  About().exec();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

  this->ui->statusBar->showMessage("加载数据中...");

  // 跳转Tab的时候设置数据，有缓存使用缓存
  switch (index)
  {
  case LogonTab:
    if (!cache[LogonTab])
    {
      logon->setTableData(ui->LogonTable);
      cache[LogonTab] = true;
    }
    break;
  case ServiceTab:
    if (!cache[ServiceTab])
    {
      service->setTableData(ui->ServicesTable);
      cache[ServiceTab] = true;
    }

    break;
  case DriverTab:

    if (!cache[DriverTab])
    {

      driver->setTableData(ui->DriversTable);
      cache[DriverTab] = true;
    }

    break;
  case TasksTab:
    if (!cache[TasksTab])
    {
      tasks->setTableData(ui->TasksTable);
      cache[TasksTab] = true;
    }
    break;
  case KnowDllsTab:
    if (!cache[KnowDllsTab])
    {
      dlls->setTableData(ui->DllsTable);
      cache[KnowDllsTab] = true;
    }
    break;
  case BootExecuteTab:
    if (!cache[BootExecuteTab])
    {
      bootExecute->setTableData(ui->BootExecuteTable);
      cache[BootExecuteTab] = true;
    }
    break;
  default:
    QMessageBox::information(NULL, "title", QString("Unsupport tab index: ") + QString::number(index), QMessageBox::Ok, QMessageBox::Yes);
    break;
  }
  this->ui->statusBar->showMessage("数据加载完成", 3000);
}

void MainWindow::on_actionRefresh_triggered()
{
  int index = ui->tabWidget->currentIndex();
  printf("index: %d\n", index);
  // 跳转Tab的时候设置数据，有缓存使用缓存
  switch (index)
  {
  case LogonTab:
    logon->setTableData(ui->LogonTable);
    cache[LogonTab] = true;
    break;
  case ServiceTab:
    service->setTableData(ui->ServicesTable);
    cache[ServiceTab] = true;
    break;
  case DriverTab:
    driver->setTableData(ui->DriversTable);
    cache[DriverTab] = true;
    break;
  case TasksTab:
    tasks->setTableData(ui->TasksTable);
    cache[TasksTab] = true;
    break;
  case KnowDllsTab:
    dlls->setTableData(ui->DllsTable);
    cache[KnowDllsTab] = true;
    break;
  case BootExecuteTab:
    bootExecute->setTableData(ui->BootExecuteTable);
    cache[BootExecuteTab] = true;
    break;
  default:
    QMessageBox::information(NULL, "title", QString("Unsupport tab index: ") + QString::number(index), QMessageBox::Ok, QMessageBox::Yes);
    break;
  }
}
