#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define RPI

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QTcpSocket>
#include <QPixmap>
#include <QSize>


//Expansion board pinout

#define PIN1 RPI_V2_GPIO_P1_07		//4
#define PIN2 RPI_V2_GPIO_P1_08		//14
#define PIN3 RPI_V2_GPIO_P1_18		//24
#define PIN4 RPI_V2_GPIO_P1_16		//23
#define PIN5 RPI_V2_GPIO_P1_15		//22
#define PIN6 RPI_V2_GPIO_P1_13		//27
#define PIN7 RPI_V2_GPIO_P1_12		//18
#define PIN8 RPI_V2_GPIO_P1_11		//17

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap empty;
    QPixmap leds;
    QPixmap led0;
    QPixmap led1;
    QPixmap led2;
    QPixmap led3;
    QPixmap led4;
    QPixmap led5;
    QPixmap led6;
    QPixmap led7;
    QSize size;
    QTimer sensors;


private:
    Ui::MainWindow *ui;

private slots:
    void readSensor();

};

#endif // MAINWINDOW_H
