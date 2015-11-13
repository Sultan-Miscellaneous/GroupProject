#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "binarysearchtree.h"
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setAccessLevel(bool accessLevel,QString);
    QString loginPath;
    Ui::MainWindow *ui;
    void getData(QString);
    void updateTable();
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_LogoutButton_clicked();

private:
    QString accessLevel;
    BST bst;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
