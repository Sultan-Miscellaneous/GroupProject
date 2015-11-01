#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    Ui::MainWindow *ui;
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

private:

};

#endif // MAINWINDOW_H
