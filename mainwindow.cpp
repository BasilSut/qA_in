#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"


#include <QAudioFormat>
#include<QtEndian>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAudioFormat tAudioFormat;
    tAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    tAudioFormat.setChannelCount(1);
    tAudioFormat.setCodec("audio/pcm");
    tAudioFormat.setSampleRate(8000);
    tAudioFormat.setSampleSize(16);
    tAudioFormat.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
        if (!info.isFormatSupported(tAudioFormat)) {
            std::cout<< "Default format not supported, trying to use the nearest.";
            tAudioFormat = info.nearestFormat(tAudioFormat);
        }

    mAudioIn = new QAudioInput(tAudioFormat,this); //создание объекта класса mAudioInput с параметрами формата описанными выше
    //проверка nullptr должна быть выполнена
    mAudioIn->QAudioInput::setBufferSize(8);
    mAudioIn->QAudioInput::setVolume(1.0);
    //char data[1024];
    //mAudioArr = new QByteArray();
    mAudioBuff = new QAudioBuffer();


    mAudioFile = new QFile("test.wav");//динамическое выделение памяти под объект QFile
    //проверка nullptr должна быть выполнена
    mAudioFile->open(QIODevice::WriteOnly);//настройка объекта
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushBtnSrart_clicked()
{
    mInput_dev = mAudioIn->start();
    //char buff[1024];
    char *buff = new char[8]{};
    int bytes_ready;//переменная хранящая количество доступных для записи байтов
    int i = 0;//преременная счетчика while

    //цикл записи данных(ограничен по времени- 300 раз производится проверка буффера)
    while (i < 8) {
        bytes_ready = mAudioIn->bytesReady();//проверка количества доступных для чтения байтов внутри аудиоустройства
        //qDebug() << i << ' ' << mAudioIn->bytesReady() << mAudioIn->QAudioInput::periodSize();//вывод номера обращения к буферу, вывод доступных для считывания байт, вывод минимального необходимого количества байт для чтения
        if (bytes_ready >= (mAudioIn->QAudioInput::periodSize())) {//при наличии доступных для чтения байтов превышающее количество оптимальных для чтения байтов
       //if (bytes_ready ==8){
            mInput_dev->read(buff,bytes_ready);//считываем данные записывая в буфер все доступные байты
            for (int j = 0; j < bytes_ready; j++) {//пока счетчик меньше количества доступных для чтения-записи байт(для всех досупных байт)
                //quint8 value = buffer[j];//запись j-того элемента буфера в переменную x с преобразованием типа в беззнаковый
                //quint8 value = (qFromLittleEndian<qint8>(buff[j]));
                //QString *str_data = new QString(buff) ;
                for(int s=0; s<8;++s)
                    std::cout<<buff[s];
                    ui->plainTextEdit_o->setPlainText("buff");

                ++i;
                if(i==8)
                    i%=8;
            }
        }
    }

    /*mAudioIn->volume();
    mAudioIn->bytesReady();*/
    delete [] buff;
}




void MainWindow::on_pushBtnStop_clicked()
{
    //mInput_dev->close();
    mAudioIn->stop();
    mAudioFile->close();
}
