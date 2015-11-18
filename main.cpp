#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm l;
    l.show();
    return a.exec();
}
