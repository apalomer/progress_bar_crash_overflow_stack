#include "threadedworker.h"

ThreadedWorker::ThreadedWorker(int n_it, QObject *parent) : QObject(parent),n_iterations(n_it)
{
}

void ThreadedWorker::process()
{
    for (int i=0;i<n_iterations;i++){
        emit this->status(i);
        qDebug()<<QThread::currentThreadId()<<": "<<i;
        usleep(200000);
    }
    emit this->finished(this); // added to inform a controller object that the worker has finished
    emit this->finished();
 }

 void ThreadedWorker::quit(){
     qDebug()<<"How do I make it stop!?";
     thread()->exit();// it does not stop the execution!
 }
