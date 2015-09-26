#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer timer;
    QTcpSocket socket;

private:
    Ui::MainWindow *ui;

private slots:
    void connectTCP();
    void readTCP();
    void connectedTCP();
    void sendData();
    void tempChanged(int data);
    void lightChanged(int data);
};

#endif // MAINWINDOW_H
