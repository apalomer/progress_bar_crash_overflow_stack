#include "threadedworker.h"

ThreadedWorker::ThreadedWorker(int n_it, QObject *parent) : QObject(parent),n_iterations(n_it)
{
    isRunning_ = false;
}

void ThreadedWorker::process()
{
    if(!this->isRunning_)
     {
        isRunning_ = true;
        for (int i=0;i<n_iterations && isRunning_;i++){
            emit this->status(i);
            qDebug()<<QThread::currentThreadId()<<": "<<i;
            usleep(20000);
        }
        emit this->finished(this); // added to inform a controller object that the worker has finished
        emit this->finished();
     }
 }

 void ThreadedWorker::quit(){
     isRunning_ = false;
 }
