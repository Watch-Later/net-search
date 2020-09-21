#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProcess"
#include "mythread.h"
/***********局域网IP扫描器简易版-Ping**************/
/************mimo431************************/
/************2020-0921-1503****************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->listshow_ip->setVisible(false);
    ui->treeWidget->setHeaderLabels(QStringList()<<"device_name");
    sthread=new MyThread();
    connect(sthread,&MyThread::isDone,this,&MainWindow::dealdone);
    connect(this,SIGNAL(send_ip(QString)),sthread,SLOT(deal_ip(QString)));
    system_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化IP地址
void MainWindow::system_init()
{
    qDebug()<<QThread::idealThreadCount();
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface aInterface,list)
    {
        QTreeWidgetItem *ip_clss=new QTreeWidgetItem(ui->treeWidget);
        ip_clss->setText(0,aInterface.humanReadableName());

        QList<QNetworkAddressEntry> entryList=aInterface.addressEntries();
        for(int i=0;i<entryList.count();i++)
        {
            if(entryList.at(i).ip().protocol()==QAbstractSocket::IPv4Protocol)
            {
                QTreeWidgetItem *ipv=new QTreeWidgetItem(ip_clss);
                ipv->setText(0,entryList.at(i).ip().toString());
            }
        }
    }
}


void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

    if(!item->text(column).contains("."))
    {
        qDebug()<<"click ip";
        return;
    }
    ui->listWidget->clear();
    //把IP发给子线程
    sthread->start();
    QString ip_scan=item->text(column);
    qDebug()<<"last . location"<<ip_scan.lastIndexOf(".");
    qDebug()<<"send location"<<ip_scan.left(ip_scan.lastIndexOf(".")+1);
    QString ip_sen=ip_scan.left(ip_scan.lastIndexOf(".")+1);
    qDebug()<<ip_sen;
    emit send_ip(ip_sen);
}
void MainWindow::dealdone(QString result)
{
    qDebug()<<"one ip found";
    ui->listWidget->addItem(result);
}
