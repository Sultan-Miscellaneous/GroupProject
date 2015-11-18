#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.h"
#include <QFileDialog>
#include <iostream>
#include <stdlib.h>
#include <QFont>
#include <qmessagebox.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(10,6,this);
    searchModel = new QStandardItemModel(1,6,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Position")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Room")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Mobile")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Office Phone")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Other")));
    ui->tableView->setModel(model);
    ui->gridLayoutWidget->hide();
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
    cout<<loginPath.toStdString()<<endl;
    LoginForm* newLogin = new LoginForm(NULL,loginPath);
    this->hide();
    newLogin->show();
}

void MainWindow::updateTable(){
    bst.inOrder();
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Position")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Room")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Mobile")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Office Phone")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Other")));

    for(int i = 0; i<bst.size(); i++){
        QStandardItem *key = new QStandardItem(bst[i]->data.key);
        model->setItem(i,0,key);
        QStandardItem *pos = new QStandardItem(bst[i]->data.position);
        model->setItem(i,1,pos);
        QStandardItem *room = new QStandardItem(QString::number(bst[i]->data.room));
        model->setItem(i,2,room);
        QStandardItem *mobile = new QStandardItem(bst[i]->data.mobile);
        model->setItem(i,3,mobile);
        QStandardItem *ph = new QStandardItem(bst[i]->data.phone);
        model->setItem(i,4,ph);
        QStandardItem *info = new QStandardItem(bst[i]->data.info);
        model->setItem(i,5,info);
    }
    ui->tableView->setModel(model);
}

void MainWindow::getData(QString read){
    QFile file(read);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);

    while (!textStream.atEnd()){
        QString k,p,r,m,ph,info;
        textStream >> k >> p >> r >> m >> ph >> info;
        clientData data;
        data.key=k;
        data.position=p;
        data.room=atoi(r.toStdString().c_str());;
        data.mobile=m;
        data.phone=ph;
        data.info=info;
        bst.insert(k,data);
    }

    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QUrl filePath = QFileDialog::getOpenFileUrl(this,tr("Select a txt file"),QDir::homePath());
    if(!filePath.toString().isEmpty()){
        pathToDataFile = filePath.toString().remove(0,7);
        MainWindow::getData(pathToDataFile);
        MainWindow::updateTable();
    }
}


void MainWindow::on_AddUserButton_clicked()
{
    ui->tableView->setHidden(true);
    ui->gridLayoutWidget->show();
}

void MainWindow::on_buttonBox_rejected()
{
    ui->tableView->setHidden(false);
    ui->gridLayoutWidget->hide();
}

void MainWindow::on_buttonBox_accepted()
{
    clientData data;
    data.key = ui->nameLine->text();
    data.position = ui->positionLine->text();
    data.room = ui->roomLine->text().toInt();
    data.mobile = QString::number(ui->mobileLine->text().toInt());
    data.phone = QString::number(ui->officePhoneLine->text().toInt());
    data.info = ui->otherInfoLine->text();
    if(bst.insert(data.key,data)==false){
        QMessageBox box;
        box.setText("User already exists");
        box.exec();
    }else{
        QMessageBox box;
        box.setText("User added successfully");
        box.exec();
        updateTable();
        ui->tableView->show();
        ui->gridLayoutWidget->hide();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{

    clientData searchedClient;
    if(bst.retrieve(ui->lineEdit->text(),searchedClient)==true){
        searchModel->clear();
        searchModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        searchModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Position")));
        searchModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Room")));
        searchModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Mobile")));
        searchModel->setHorizontalHeaderItem(4, new QStandardItem(QString("Office Phone")));
        searchModel->setHorizontalHeaderItem(5, new QStandardItem(QString("Other")));

        QStandardItem *key = new QStandardItem(searchedClient.key);
        searchModel->setItem(0,0,key);
        QStandardItem *pos = new QStandardItem(searchedClient.position);
        searchModel->setItem(0,1,pos);
        QStandardItem *room = new QStandardItem(QString::number(searchedClient.room));
        searchModel->setItem(0,2,room);
        QStandardItem *mobile = new QStandardItem(searchedClient.mobile);
        searchModel->setItem(0,3,mobile);
        QStandardItem *ph = new QStandardItem(searchedClient.phone);
        searchModel->setItem(0,4,ph);
        QStandardItem *info = new QStandardItem(searchedClient.info);
        searchModel->setItem(0,5,info);
        ui->tableView->setModel(searchModel);

    }else{
        QMessageBox box;
        box.setText("Can't find User");
        box.exec();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    bst.clear();
    searchModel->clear();
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Position")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Room")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Mobile")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Office Phone")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Other")));
    model->setRowCount(10);
    model->setColumnCount(6);
    ui->tableView->setModel(model);
}

void MainWindow::on_DeleteUserButton_clicked()
{
    QModelIndex index = ui->tableView->model()->index(ui->tableView->currentIndex().row(),0);
    QMessageBox box;
    box.setText("Are you sure you want to delete this record?");
    box.setInformativeText(index.data().toString());
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    switch(box.exec()){
        case QMessageBox::Yes:
        bst.remove(index.data().toString());
        ui->tableView->model()->removeRow(index.row());
        break;
    case QMessageBox::No:
        break;
    }
}

void MainWindow::on_SaveButton_clicked()
{
    QModelIndex index = ui->tableView->model()->index(ui->tableView->currentIndex().row(),0);
    QMessageBox box;
    box.setText("Are you sure you want to overwrite data file?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    switch(box.exec()){
        case QMessageBox::Yes:{
        QFile file(pathToDataFile);
        file.open(QIODevice::WriteOnly);
        QTextStream textStream(&file);
        bst.inOrder();
        for(int i = 0;i<bst.size(); i++){
            textStream << bst[i]->data.key<<" "<< bst[i]->data.position<<" " << bst[i]->data.room<<" " << bst[i]->data.mobile<<" "
                       << bst[i]->data.phone<<" " << bst[i]->data.info;
            if(i!=bst.size()-1){
                textStream<<'\n';
            }
        }
        break;
    }
    case QMessageBox::No:
        break;
    }
}
