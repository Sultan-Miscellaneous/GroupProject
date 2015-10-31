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
    ~MainWindow();

public slots:
    void on_actionOpen_triggered();
    void on_pushButton_clicked();
    void incrementStatusBar();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    float statusBarCurrentValue;
};

#endif // MAINWINDOW_H
