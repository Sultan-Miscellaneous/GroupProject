#include "loginform.h"
#include "ui_loginform.h"
#include "qlayout.h"
#include "mainwindow.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    parentFrame = new MainWindow;
    database.emptyTable("Empty");
    database.readFile("/Users/Ali/Desktop/CS210/GroupProject/Logins.txt");
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_LoginButton_clicked()
{
    QString username = ui->UsernameEdit->text();
    int userLocationInDatabase = database.search(username);
    if (userLocationInDatabase != -1){
        QString password = ui->PasswordEdit->text();
        if(database.getPassword(userLocationInDatabase) == password){
            this->hide();
            parentFrame->setAccessLevel(database.getAccess(userLocationInDatabase));
            parentFrame->show();
        }else{
            ui->PasswordEdit->setText("Incorrect Password!");
        }
    }else{
        ui->UsernameEdit->setText("Username does not exist.");
    }
}

void LoginForm::on_PasswordEdit_returnPressed()
{
    LoginForm::on_LoginButton_clicked();
}
