#include "fastthreadedworker.h"

#include <thread>

#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

FastThreadedWorker::FastThreadedWorker(int n_it, QObject *parent)
    : QObject(parent), n_iterations(n_it) {
  isRunning_ = false;
}

void FastThreadedWorker::runInThread(int n_iterations, ProgressDialog *progress, QWidget *parent) {
  QThread *th = new QThread(parent);
  FastThreadedWorker *work = new FastThreadedWorker(n_iterations);
  work->moveToThread(th);
  connect(th, &QThread::started, work, &FastThreadedWorker::process);
  connect(work, &FastThreadedWorker::status, progress, &ProgressDialog::setValue);
  connect(work, &FastThreadedWorker::started, progress, &ProgressDialog::show);
  connect(work, &FastThreadedWorker::finished, progress, &ProgressDialog::close);
  connect(work, &FastThreadedWorker::finished, th, &QThread::quit);
  connect(work, &FastThreadedWorker::finished, work, &FastThreadedWorker::deleteLater);
  connect(work, &FastThreadedWorker::finished, progress,
          &ProgressDialog::deleteLater);
  connect(th, &QThread::finished, th, &QThread::deleteLater);
  connect(progress, &ProgressDialog::canceled, work, &FastThreadedWorker::quit,
          Qt::DirectConnection);
  //connect(progress, &ProgressDialog::updatingValue, work, &FastThreadedWorker::blockProgressDialog,
  //  Qt::DirectConnection);
  connect(progress, &ProgressDialog::valueUpdated, work, &FastThreadedWorker::unblockProgressDialog,
    Qt::DirectConnection);
  th->start();
}

void FastThreadedWorker::blockProgressDialog()
{
}

void FastThreadedWorker::unblockProgressDialog()
{
  isReady_ = true;
}

void FastThreadedWorker::process() {
  if (!isRunning_) {
    emit started();
    isRunning_ = true;
    int total_done(0);
    isReady_ = true;
#pragma omp parallel for shared(total_done)
    for (int i = 0; i < n_iterations; i++) {
      if (!isRunning_)
        continue;
#pragma omp critical
      {
        ++total_done;
        if (isReady_)
        {
          isReady_ = false;
          emit status(total_done);
        }
      }
    }
    emit finished();
  }
}

void FastThreadedWorker::quit() { isRunning_ = false; }
