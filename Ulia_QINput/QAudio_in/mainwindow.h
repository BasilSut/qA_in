#pragma once

#include <QCoreApplication>
#include <QAudioInput>
#include <QIODevice>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QTextStream> //#
#include <iostream> //#
//using namespace std; //#
#include <QVector>//#
#include <qendian.h>
#include <QtMath>

#include <QMainWindow>

#define QALittleEnd QAudioFormat::LittleEndian
#define QAUnInt QAudioFormat::UnSignedInt
#define QAInt QAudioFormat::SignedInt




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private:
    Ui::MainWindow *ui;

    QAudioInput* audio;
    QAudioFormat format_test;
    QAudioFormat format;
    QAudioDeviceInfo info;
    QIODevice *input;
    QFile *file;
    //QTextStream *text_out;
    //QFile file("out.txt");
    //QTextStream text_out(&file); //#

    QVector<qreal> signal_I_f1;
    QVector<qreal> signal_Q_f1;
    QVector<qreal> signal_I_f2;
    QVector<qreal> signal_Q_f2;
    int sig_f1_cnt = 0;
    int sig_f2_cnt = 0;
    int sig_f1_size;
    int sig_f2_size;

    //const unsigned int audio_buffer_len = 1;
    //char audio_buffer[audio_buffer_len];

    void Audio_Init(int sample_rate,
                    int channel_count,
                    int sample_size,
                    QString codec,
                    QAudioFormat::Endian byte_order,
                    QAudioFormat::SampleType sample_type);
    void Audio_Start_Listen(qreal volume,
                            int cycles_cnt);
    void Audio_Get_Info();
    void Audio_Close();
    QVector<qreal> Create_Signal(QString func, qreal freq, qreal amplitude);
};
