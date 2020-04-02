#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>

#ifdef _WIN32
#ifdef MAINWINDOW
#define MAINWINDOWEXPORT __declspec(dllexport)
#else
#define MAINWINDOWEXPORT __declspec(dllimport)
#endif
#else
#define MAINWINDOWEXPORT
#endif

namespace Ui {
class MainWindow;
}

class MAINWINDOWEXPORT MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void on_pushButton_nowhait_clicked();

  void on_pushButton_whait_clicked();

private:
  QProgressDialog *createProgressDialog();

  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
