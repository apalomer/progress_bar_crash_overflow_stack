#ifndef FASTThreadedWorker_H
#define FASTThreadedWorker_H

#include <atomic>

#include <QObject>
#include <QProgressDialog>

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
  static void runInThread(int n_iterations, QProgressDialog *progress,
                          QWidget *parent);

  explicit FastThreadedWorker(int n_iterations, QObject *parent = 0);
signals:
  void status(int i);
  void started();
  void finished();
public slots:
  void process();
  void quit();

protected:
  std::atomic_bool isRunning_;
  int n_iterations;
};

#endif // FASTThreadedWorker_H
