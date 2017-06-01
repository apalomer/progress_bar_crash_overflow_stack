#ifndef THREADEDWORKER_H
#define THREADEDWORKER_H

#include <unistd.h>
#include <atomic>

#include <QtCore>
#include <QObject>
#include <QThread>

class ThreadedWorker : public QObject
{
    Q_OBJECT
public:
    explicit ThreadedWorker(int n_iterations, QObject *parent = 0);
signals:
    void status(int i);
    void finished();
    void finished(ThreadedWorker* worker);
public slots:
    void process();
    void quit();
protected:
    std::atomic_bool isRunning_;
    int n_iterations;
};

#endif // THREADEDWORKER_H
