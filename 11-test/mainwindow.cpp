#include "mainwindow.h"
#include "ui_mainwindow.h"
#ifdef RPI
#include "bcm2835.h"
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#ifdef RPI
	char tmp[2];

    bcm2835_init();

    // Set the pins to be an output
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN6, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN7, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN8, BCM2835_GPIO_FSEL_OUTP);

#endif

    empty = QPixmap(":/pics/empty_scaled.png");
    leds = QPixmap(":/pics/ledsuit_scaled.png");
    led0 = QPixmap(":/pics/led0_scaled.png");
    led1 = QPixmap(":/pics/led1_scaled.png");
    led2 = QPixmap(":/pics/led2_scaled.png");
    led3 = QPixmap(":/pics/led3_scaled.png");
    led4 = QPixmap(":/pics/led4_scaled.png");
    led5 = QPixmap(":/pics/led5_scaled.png");
    led6 = QPixmap(":/pics/led6_scaled.png");
    led7 = QPixmap(":/pics/led7_scaled.png");

    //size = QSize(ui->exportBoard->width(),ui->exportBoard->height());
    //ui->exportBoard->setPixmap(leds.scaled(size));
    ui->exportBoard->setPixmap(leds);

    sensors.setInterval(500);
    connect(&sensors,SIGNAL(timeout()),this,SLOT(readSensor()));
    sensors.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSensor()
{
        //read temperature

        char buffer[4];
        char tmp[2];
        int temp;
        char ad[2];
        int light;
        buffer[0]=buffer[1]=buffer[2]=buffer[3]=0;

#ifdef RPI
        bcm2835_spi_begin();
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);				//SCLK rising edge - clock idle state 1
        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); 	//set clock frequency
        bcm2835_spi_chipSelect(BCM2835_SPI_CS1);                      	//use chip select 1
        bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);      	//chip select 0 to activate

        buffer[0] = 0x50;					//read the temp
        bcm2835_spi_transfern(buffer,3);
        qDebug() << "status: " << buffer[1] << buffer[2];

        temp = buffer[1];
        temp = temp<<8;
        temp = temp + ( buffer[2] & 0xF8);
        temp = temp>>3;
        temp = temp/16;
        ui->Tempsensor->setValue(temp);

        //read light
        bcm2835_i2c_begin();
        bcm2835_i2c_setSlaveAddress(0x29);      // addr pin attached to ground
        bcm2835_i2c_set_baudrate(1000);         // Default

        tmp[0] = 0xa0;                          //select the control register
        bcm2835_i2c_write(tmp,1);
        tmp[0] = 0x03;                          //Power up the device
        bcm2835_i2c_write(tmp,1);
        bcm2835_delay(500);

        bcm2835_i2c_read(tmp,1);
        qDebug() << "if 33 the device is turned on: " << tmp[0];

        tmp[0] = 0xac;				//Channel 0 lower byte
        bcm2835_i2c_write(tmp,1);
        bcm2835_i2c_read(tmp,1);

        ad[1]= (int)tmp[0];

        tmp[0] = 0xad;				//channel 0 upper byte
        bcm2835_i2c_write(tmp,1);
        bcm2835_i2c_read(tmp,1);

        ad[0] = (int)tmp[0];
        light = ad[0]*256+ad[1];
        ui->LightSensor->setValue(light);
#endif

        if(ui->led1->isChecked() == true)
        {
            ui->led1->setChecked(false);
            ui->led2->setChecked(false);
            ui->led3->setChecked(false);
            ui->led4->setChecked(false);
            ui->led5->setChecked(false);
            ui->led6->setChecked(false);
            ui->led7->setChecked(false);
            ui->led8->setChecked(false);
            ui->exportLed0->setPixmap(empty);
            ui->exportLed1->setPixmap(empty);
            ui->exportLed2->setPixmap(empty);
            ui->exportLed3->setPixmap(empty);
            ui->exportLed4->setPixmap(empty);
            ui->exportLed5->setPixmap(empty);
            ui->exportLed6->setPixmap(empty);
            ui->exportLed7->setPixmap(empty);

            #ifdef RPI
            bcm2835_gpio_write(PIN1, LOW);
            bcm2835_gpio_write(PIN2, LOW);
            bcm2835_gpio_write(PIN3, LOW);
            bcm2835_gpio_write(PIN4, LOW);
            bcm2835_gpio_write(PIN5, LOW);
            bcm2835_gpio_write(PIN6, LOW);
            bcm2835_gpio_write(PIN7, LOW);
            bcm2835_gpio_write(PIN8, LOW);
            #endif
        }
        else
        {
            ui->led1->setChecked(true);
            ui->led2->setChecked(true);
            ui->led3->setChecked(true);
            ui->led4->setChecked(true);
            ui->led5->setChecked(true);
            ui->led6->setChecked(true);
            ui->led7->setChecked(true);
            ui->led8->setChecked(true);
            ui->exportLed0->setPixmap(led0);
            ui->exportLed1->setPixmap(led1);
            ui->exportLed2->setPixmap(led2);
            ui->exportLed3->setPixmap(led3);
            ui->exportLed4->setPixmap(led4);
            ui->exportLed5->setPixmap(led5);
            ui->exportLed6->setPixmap(led6);
            ui->exportLed7->setPixmap(led7);

            #ifdef RPI
            bcm2835_gpio_write(PIN1, HIGH);
            bcm2835_gpio_write(PIN2, HIGH);
            bcm2835_gpio_write(PIN3, HIGH);
            bcm2835_gpio_write(PIN4, HIGH);
            bcm2835_gpio_write(PIN5, HIGH);
            bcm2835_gpio_write(PIN6, HIGH);
            bcm2835_gpio_write(PIN7, HIGH);
            bcm2835_gpio_write(PIN8, HIGH);
            #endif
        }

    }


