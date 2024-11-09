#include "mainwindow.h"
#include "ui_mainwindow.h"

Alchemy::Alchemy::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Alchemy::Alchemy::MainWindow::~MainWindow()
{
    delete ui;
}
