#include "loginform.h"
#include "ui_loginform.h"
#include "qlayout.h"
#include "mainwindow.h"
#include <QUrl>
#include <QFileDialog>
#include <iostream>

LoginForm::LoginForm(QWidget *parent,QString loginPath) : QWidget(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->PasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);
    if(loginPath.isEmpty()){
        ui->LoginButton->setEnabled(false);
    }else{
        database.emptyTable("Empty");
        database.readFile(loginPath);
        this->loginsPath=loginPath;
    }
    parentFrame = new MainWindow;
<<<<<<< HEAD
=======
    database.emptyTable("Empty");
    database.readFile("/Users/BAlKhamissi/Desktop/GroupProject/Logins.txt");
>>>>>>> Badr's-Branch
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_LoginButton_clicked()
{
<<<<<<< HEAD
    if(database.tableIsEmpty()==false){
=======
    if(ui->PasswordEdit->text()!=""){
>>>>>>> Badr's-Branch
        QString username = ui->UsernameEdit->text();
        int userLocationInDatabase = database.search(username);
        if (userLocationInDatabase != -1){
            QString password = ui->PasswordEdit->text();
            if(database.getPassword(userLocationInDatabase) == password){
                this->hide();
                parentFrame->setAccessLevel(database.getAccess(userLocationInDatabase),username);
                parentFrame->show();
<<<<<<< HEAD
                cout<<loginsPath.toStdString()<<endl;
                parentFrame->loginPath=this->loginsPath;
=======
>>>>>>> Badr's-Branch
            }else{
                ui->PasswordEdit->setEchoMode(QLineEdit::EchoMode::Normal);
                QFont font;
                font.setBold(true);
                ui->PasswordEdit->setFont(font);
                ui->PasswordEdit->setText("Incorrect Password...");
            }
        }else{
            ui->UsernameEdit->setText("Username does not exist.");
        }
<<<<<<< HEAD
    }
    else{
        ui->UsernameEdit->setText("Database Empty");
=======
>>>>>>> Badr's-Branch
    }
}

void LoginForm::on_PasswordEdit_returnPressed()
{
    if(ui->PasswordEdit->text()!="")
        LoginForm::on_LoginButton_clicked();
}


void LoginForm::on_PasswordEdit_textEdited(const QString &arg1)
{
    ui->PasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);
}

void LoginForm::on_pushButton_clicked()
{
    QUrl filePath = QFileDialog::getOpenFileUrl(this,tr("Select a txt file"),QDir::homePath());
     if(filePath.toString()!=""){
         database.emptyTable("Empty");
         database.readFile(filePath.toString().remove(0,7));
         ui->LoginButton->setEnabled(true);
         this->loginsPath=filePath.toString().remove(0,7);
     }
}
