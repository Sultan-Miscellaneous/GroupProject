#include "loginform.h"
#include "ui_loginform.h"
#include "qlayout.h"
#include "mainwindow.h"

LoginForm::LoginForm(QWidget *parent) : QWidget(parent), ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    parentFrame = new MainWindow;
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    this->hide();
    parentFrame->show();
}
