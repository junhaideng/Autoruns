#include "about.h"
#include "ui_about.h"
#include <windows.h>

About::About(QWidget *parent) : QDialog(parent),
                                ui(new Ui::About)
{
  ui->setupUi(this);
}

About::~About()
{
  delete ui;
}

void About::on_pushButton_clicked()
{
  this->close();
}
