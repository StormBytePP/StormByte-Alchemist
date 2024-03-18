#include "mainwindow.h"
#include "ui_mainwindow.h"

Alchemist::Alchemist::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Alchemist::Alchemist::MainWindow::~MainWindow()
{
    delete ui;
}
