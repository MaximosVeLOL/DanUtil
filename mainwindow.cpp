#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "error.h"

#include "texeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Error::Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mTexEditor_clicked()
{
    TexEditor *t = new TexEditor();
    t->activateWindow();
    t->show();

}

