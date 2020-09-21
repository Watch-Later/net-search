#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QHostInfo"
#include "QHostAddress"
#include "QNetworkInterface"
#include "QTreeWidget"
#include "QProcess"
#include "mythread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    MyThread *sthread;
    QString hostname;
    QHostInfo ip_local;
    //QList<QHostAddress> ip_list;
    void system_init();
    void dealdone(QString result);
private slots:

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
private:
    Ui::MainWindow *ui;

signals:
    void send_ip(QString ip);
};

#endif // MAINWINDOW_H
