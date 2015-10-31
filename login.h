#ifndef LOGIN_H
#define LOGIN_H

#include <qmainwindow.h>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    Ui::Login *ui;
};

#endif // LOGIN_H
