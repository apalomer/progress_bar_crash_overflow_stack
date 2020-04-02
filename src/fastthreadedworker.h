#ifndef FASTTHREADEDWORKER_H
#define FASTTHREADEDWORKER_H

#include <atomic>

#include <QObject>
#include <QMutex>

#include "progressdialog.h"

#ifdef _WIN32
#ifdef THREADWORKER
#define THREADWORKEREXPORT __declspec(dllexport)
#else
#define THREADWORKEREXPORT __declspec(dllimport)
#endif
#else
#define THREADWORKEREXPORT
#endif

class THREADWORKEREXPORT FastThreadedWorker : public QObject {
  Q_OBJECT
public:
  static void runInThread(int n_iterations, ProgressDialog *progress,
                          QWidget *parent);

  explicit FastThreadedWorker(int n_iterations, QObject *parent = 0);
signals:
  void status(int i);
  void started();
  void finished();
public slots:
  void process();
  void quit();
  void blockProgressDialog();
  void unblockProgressDialog();

protected:
  std::atomic_bool isRunning_;
  std::atomic_bool isReady_;
  int n_iterations;
  QMutex mutex_;
};

#endif // FASTTHREADEDWORKER_H
