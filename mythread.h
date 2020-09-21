#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "QThread"
#include <QObject>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    QString ip_rec;
protected:
    void run();
signals:
    void isDone(QString ip_result);

public slots:
    void deal_ip(QString);
};

#endif // MYTHREAD_H
