#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QProgressDialog>
#include <QObject>
#include <QThread>
#include "threadedworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_nowhait_clicked();

    void on_pushButton_whait_clicked();

private:
    Ui::MainWindow *ui;
    QProgressDialog* progress;
};

#endif // MAINWINDOW_H
