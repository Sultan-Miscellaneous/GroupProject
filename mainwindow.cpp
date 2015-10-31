#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <unistd.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(incrementStatusBar()));
    statusBarCurrentValue = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::incrementStatusBar(){
    if(ui->progressBar->value()-statusBarCurrentValue>10){
        timer->stop();
        statusBarCurrentValue = ui->progressBar->value();
        cout<<statusBarCurrentValue<<endl;
    }
    ui->progressBar->setValue((float)ui->progressBar->value()+1);
}

void MainWindow::on_actionOpen_triggered()
{
    QUrl filePath = QFileDialog::getOpenFileUrl(this,tr("Select a file"),QDir::homePath());
    cout<<filePath.toString().toStdString()<<endl;
}

void MainWindow::on_pushButton_clicked()
{
    if (statusBarCurrentValue>=100){
        statusBarCurrentValue = 0;
    }timer->start(50);
}
