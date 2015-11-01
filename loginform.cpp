#include "loginform.h"
#include "ui_loginform.h"
#include "qlayout.h"
#include "mainwindow.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->PasswordEdit->setEchoMode(QLineEdit::EchoMode::Password);
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
    if(ui->PasswordEdit->text()!=""){
        QString username = ui->UsernameEdit->text();
        int userLocationInDatabase = database.search(username);
        if (userLocationInDatabase != -1){
            QString password = ui->PasswordEdit->text();
            if(database.getPassword(userLocationInDatabase) == password){
                this->hide();
                parentFrame->setAccessLevel(database.getAccess(userLocationInDatabase),username);
                parentFrame->show();
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
