#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <QFileDialog>
#include <iostream>
#include <QFont>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAccessLevel(bool accessLevel,QString username)
{
    if(accessLevel){
        this->accessLevel = "Administrator";
    }else{
        this->accessLevel = "User";
        ui->AdminControls_2->setVisible(false);
    }
    QFont font;
    font.setBold(true);
    ui->AccountAccessLevel->setText(this->accessLevel);
    ui->AccountAccessLevel->setFont(font);
    ui->UsernameLabel->setText(username);
}
void MainWindow::on_actionOpen_triggered()
{
    QUrl filePath = QFileDialog::getOpenFileUrl(this,tr("Select a file"),QDir::homePath());
    if(filePath.toString()!=""){
//        ui->DirectoryLabel->setText((QString)"Current directory: "
//                                ""+filePath.toString());
        QFont font;
        font.setBold(true);
//        ui->DirectoryLabel->setFont(font);
    }
}

void MainWindow::on_actionQuit_triggered()
{
      qApp->quit();
}


void MainWindow::on_LogoutButton_clicked()
{
    LoginForm* newLogin = new LoginForm;
    this->hide();
    newLogin->show();
}
