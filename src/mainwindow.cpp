#include "mainwindow.h"
#include "threadedworker.h"
#include "fastthreadedworker.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

ProgressDialog *MainWindow::createProgressDialog(int max_value) {
  ProgressDialog*progress = new ProgressDialog("Iterating...", "Cancell", 0,
                                                  max_value, this);
  progress->setWindowFlag(Qt::CustomizeWindowHint, true);
  progress->setWindowFlag(Qt::WindowCloseButtonHint, false);
  progress->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
  //progress->setWindowModality(Qt::WindowModal);
  progress->setWindowModality(Qt::ApplicationModal);
  return progress;
}

void MainWindow::on_long_pushButton_clicked() {
  // Run in new thread and create a progress bar
  ThreadedWorker::runInThread(ui->long_spinBox->value(), createProgressDialog(ui->long_spinBox->value()),
                              this);
}

void MainWindow::on_short_pushButton_clicked() {
  // Run in new thread and create a progress bar
  FastThreadedWorker::runInThread(ui->short_spinBox->value(), createProgressDialog(ui->short_spinBox->value()), this);
}
