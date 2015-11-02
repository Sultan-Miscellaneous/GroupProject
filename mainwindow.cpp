#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <QFileDialog>
#include <iostream>
#include <stdlib.h>
#include <QFont>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(50,5,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Position")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Room")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Mobile")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Office Phone")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Other")));
    ui->tableView->setModel(model);
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
        ui->tableView->setEditTriggers(QTableView::EditTrigger::NoEditTriggers);
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

void MainWindow::updateTable(){
    bst.inOrder();
    for(int i = 0; i<bst.size(); i++){
//        QStandardItem *key = new QStandardItem(bst[i]->key)
//        model->setItem(i,0,key);
//        QStandardItem *pos = new QStandardItem(bst[i]->position)
//        model->setItem(i,1,pos);
//        QStandardItem *room = new QStandardItem(bst[i]->room)
//        model->setItem(i,2,room);
//        QStandardItem *mobile = new QStandardItem(bst[i]->mobile)
//        model->setItem(i,4,mobile);
//        QStandardItem *pos = new QStandardItem(bst[i]->phone)
//        model->setItem(i,4,phone);
//        QStandardItem *pos = new QStandardItem(bst[i]->phone)
//        model->setItem(i,5,phone);
    }
}

void MainWindow::getData(QString read){
    QFile file(read);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);

    while (!textStream.atEnd()){
        QString k,p,r,m,ph,info;
        textStream >> k >> p >> r >> m >> ph >> info;
        int room = atoi(r.toStdString().c_str());
        bst.insert(k.toStdString(),p.toStdString(),room,m.toStdString(),ph.toStdString(),info.toStdString());
    }

    file.close();
}
