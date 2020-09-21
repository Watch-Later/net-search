#include "mythread.h"
#include "QDebug"
#include "mainwindow.h"
#include "ui_mainwindow.h"
MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    qDebug()<<"start a new thread";
    for(int i=0;i<255;i++)
    {
        QString ip_ready_ping=ip_rec+QString::number(i);
        qDebug()<<ip_ready_ping;
        QString cmd_ping=QString("ping %1 -n 1 -w %2").arg(ip_ready_ping).arg(1000);
        QProcess p_ping;
        p_ping.start(cmd_ping);
        p_ping.waitForReadyRead(1000);
        p_ping.waitForFinished(1000);
        QString response=QString::fromLocal8Bit(p_ping.readAllStandardOutput());
        //qDebug()<<response;
        if(response.contains("TTL"))
            emit isDone(ip_ready_ping);
    }
    qDebug()<<"finish a new thread";
}

void MyThread::deal_ip(QString ip)
{
    ip_rec=ip;
}
