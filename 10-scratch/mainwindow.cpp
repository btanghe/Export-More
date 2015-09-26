#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.setInterval(500);
    connect(&timer,SIGNAL(timeout()),this,SLOT(connectTCP()));
    connect(&socket,SIGNAL(readyRead()),this,SLOT(readTCP()));
    connect(&socket,SIGNAL(connected()),this,SLOT(connectedTCP()));
    connect(ui->Tempsensor,SIGNAL(valueChanged(int)),this,SLOT(tempChanged(int)));
    connect(ui->LightSensor,SIGNAL(valueChanged(int)),this,SLOT(lightChanged(int)));

    timer.start();

}

void MainWindow::connectTCP()
{
    socket.connectToHost("localhost",42001);
}

void MainWindow::tempChanged(int data)
{
    QByteArray data_send;
    qDebug() << "send sensor update";

        data_send.append((char)0x00);
        data_send.append((char)0x00);
        data_send.append((char)0x00);
        data_send.append((char)0x18);
        data_send.append("sensor-update \"temp\" ");
        data_send.append((char)((data/10)+0x30));
        data_send.append((char)((data%10)+0x30));
        data_send.append(" ");
        socket.write(data_send);


}

void MainWindow::lightChanged(int data)
{

    QByteArray data_send;

        data_send.append((char)0x00);
        data_send.append((char)0x00);
        data_send.append((char)0x00);
        data_send.append((char)0x1c);
        data_send.append("sensor-update \"light\" ");
        data_send.append((char)((data/10000)+0x30));
        data_send.append((char)((data%10000/1000)+0x30));
        data_send.append((char)((data%1000/100)+0x30));
        data_send.append((char)((data%100/10)+0x30));
        data_send.append((char)((data%10)+0x30));
        data_send.append(" ");
        socket.write(data_send);

}

void MainWindow::readTCP()
{
    QString data;
    QByteArray data_byte;
    QByteArray data1;
    int begin,aantal;
    data_byte = socket.readAll();
    begin = data_byte.indexOf("\"") + 1;
    aantal = data_byte.count() - begin - 1;
    data1 = data_byte.mid(begin,aantal);
    qDebug() << data_byte;
    qDebug() << "index of: " << begin << ":" << aantal;
    qDebug() << "data inhoud: " << data_byte.mid(begin,aantal);
    ui->data_label->setText(data_byte.mid(begin,aantal));

    if(data1.contains("led1on") == true )
    {
        ui->led1->setChecked(true);
    }
    if(data1.contains("led1off") == true )
    {
        ui->led1->setChecked(false);
    }

    if(data1.contains("led2on") == true )
    {
        ui->led2->setChecked(true);
    }
    if(data1.contains("led2off") == true )
    {
        ui->led2->setChecked(false);
    }

    if(data1.contains("led3on") == true )
    {
        ui->led3->setChecked(true);
    }
    if(data1.contains("led3off") == true )
    {
        ui->led3->setChecked(false);
    }

    if(data1.contains("led4on") == true )
    {
        ui->led4->setChecked(true);
    }
    if(data1.contains("led4off") == true )
    {
        ui->led4->setChecked(false);
    }

    if(data1.contains("led5on") == true )
    {
        ui->led5->setChecked(true);
    }
    if(data1.contains("led5off") == true )
    {
        ui->led5->setChecked(false);
    }

    if(data1.contains("led6on") == true )
    {
        ui->led6->setChecked(true);
    }
    if(data1.contains("led6off") == true )
    {
        ui->led6->setChecked(false);
    }

    if(data1.contains("led7on") == true )
    {
        ui->led7->setChecked(true);
    }
    if(data1.contains("led7off") == true )
    {
        ui->led7->setChecked(false);
    }

    if(data1.contains("led8on") == true )
    {
        ui->led8->setChecked(true);
    }
    if(data1.contains("led8off") == true )
    {
        ui->led8->setChecked(false);
    }

}

void MainWindow::connectedTCP()
{
    QByteArray data;
    qDebug() << "TCP connected";
    timer.stop();
    emit ui->LightSensor->valueChanged(0);
    emit ui->Tempsensor->valueChanged(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}
