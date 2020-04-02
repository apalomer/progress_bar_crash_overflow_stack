#include "threadedworker.h"

#include <thread>

#include <QDebug>
#include <QThread>

ThreadedWorker::ThreadedWorker(int n_it, QObject *parent)
    : QObject(parent), n_iterations(n_it) {
  isRunning_ = false;
}

void ThreadedWorker::runInThread(int n_iterations, QProgressDialog *progress, QWidget *parent) {
  QThread *th = new QThread(parent);
  ThreadedWorker *work = new ThreadedWorker(n_iterations);
  work->moveToThread(th);
  connect(th, &QThread::started, work, &ThreadedWorker::process);
  connect(work, &ThreadedWorker::status, progress, &QProgressDialog::setValue);
  connect(work, &ThreadedWorker::started, progress, &QProgressDialog::show);
  connect(work, &ThreadedWorker::finished, progress, &QProgressDialog::close);
  connect(work, &ThreadedWorker::finished, th, &QThread::quit);
  connect(work, &ThreadedWorker::finished, work, &ThreadedWorker::deleteLater);
  connect(work, &ThreadedWorker::finished, progress,
          &QProgressDialog::deleteLater);
  connect(th, &QThread::finished, th, &QThread::deleteLater);
  connect(progress, &QProgressDialog::canceled, work, &ThreadedWorker::quit,
          Qt::DirectConnection);
  th->start();
}

void ThreadedWorker::process() {
  if (!isRunning_) {
    emit started();
    isRunning_ = true;
    for (int i = 0; i < n_iterations && isRunning_; i++) {
      emit status(i);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    emit finished();
  }
}

void ThreadedWorker::quit() { isRunning_ = false; }
