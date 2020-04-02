#include "FastThreadedWorker.h"

#include <thread>

#include <QDebug>
#include <QThread>

FastThreadedWorker::FastThreadedWorker(int n_it, QObject *parent)
    : QObject(parent), n_iterations(n_it) {
  isRunning_ = false;
}

void FastThreadedWorker::runInThread(int n_iterations, QProgressDialog *progress, QWidget *parent) {
  QThread *th = new QThread(parent);
  FastThreadedWorker *work = new FastThreadedWorker(n_iterations);
  work->moveToThread(th);
  connect(th, &QThread::started, work, &FastThreadedWorker::process);
  connect(work, &FastThreadedWorker::status, progress, &QProgressDialog::setValue);
  connect(work, &FastThreadedWorker::started, progress, &QProgressDialog::show);
  connect(work, &FastThreadedWorker::finished, progress, &QProgressDialog::close);
  connect(work, &FastThreadedWorker::finished, th, &QThread::quit);
  connect(work, &FastThreadedWorker::finished, work, &FastThreadedWorker::deleteLater);
  connect(work, &FastThreadedWorker::finished, progress,
          &QProgressDialog::deleteLater);
  connect(th, &QThread::finished, th, &QThread::deleteLater);
  connect(progress, &QProgressDialog::canceled, work, &FastThreadedWorker::quit,
          Qt::DirectConnection);
  th->start();
}

void FastThreadedWorker::process() {
  if (!isRunning_) {
    emit started();
    isRunning_ = true;
#pragma omp parallel for
    for (int i = 0; i < n_iterations; i++) {
      if (!isRunning_)
        continue;
#pragma omp critical
      {
        emit status(i);
      }
    }
    emit finished();
  }
}

void FastThreadedWorker::quit() { isRunning_ = false; }
