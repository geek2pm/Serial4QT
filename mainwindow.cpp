#include "mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_send->setEnabled(false);
    QStringList bauds;
    bauds<<"9600"<<"14400"<<"19200"<<"38400"<<"56000"<<"57600"<<"76800"<<"115200"<<"128000"<<"256000";
    ui->comboBoxBaud->addItems(bauds);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxComs->addItem(info.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_switch_clicked()
{
    if(ui->pushButton_switch->text()=="open"){
        this->serial = new QSerialPort();
        this->serial->setPortName(ui->comboBoxComs->currentText());
        if(this->serial->open(QIODevice::ReadWrite)){
            this->serial->setBaudRate(ui->comboBoxBaud->currentText().toInt());
            this->serial->setDataBits(QSerialPort::Data8);
            this->serial->setParity(QSerialPort::NoParity);
            this->serial->setFlowControl(QSerialPort::NoFlowControl);
            this->serial->setStopBits(QSerialPort::OneStop);
            ui->pushButton_switch->setText("close");
            ui->pushButton_send->setEnabled(true);
            this->timer = new QTimer();
            connect(this->timer, SIGNAL(timeout()), this, SLOT(readComDataSlot()));
            this->timer->start(1000);
        }else{
            QMessageBox::about(NULL, "alert", this->serial->errorString());
            return;
        }
    } else if(ui->pushButton_switch->text()=="close"){
        this->serial->close();
        ui->pushButton_switch->setText("open");
        ui->pushButton_send->setEnabled(false);
    }
}

void MainWindow::readComDataSlot()
{
    QByteArray readComData = serial->readAll();
    if(readComData != NULL)
    {
        ui->textBrowser->append(readComData);
    }
    readComData.clear();
}

void MainWindow::on_pushButton_send_clicked()
{
    QString sendData = ui->textEdit->toPlainText();
    QByteArray sendData_b = sendData.toLatin1();
    serial->write(sendData_b);
    ui->textEdit->clear();
}
