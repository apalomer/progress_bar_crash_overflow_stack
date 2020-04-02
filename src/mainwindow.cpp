#include "mainwindow.h"
#include "threadedworker.h"
#include "ui_mainwindow.h"

#include <QEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

QProgressDialog *MainWindow::createProgressDialog() {
  QProgressDialog *progress = new QProgressDialog("Iterating...", "Cancell", 0,
                                                  ui->spinBox->value(), this);
  progress->setWindowFlag(Qt::CustomizeWindowHint, true);
  progress->setWindowFlag(Qt::WindowCloseButtonHint, false);
  progress->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
  progress->installEventFilter(this);
  return progress;
}

void MainWindow::on_pushButton_nowhait_clicked() {
  // Run in new thread and create a progress bar
  ThreadedWorker::runInThread(ui->spinBox->value(), createProgressDialog(),
                              this);
}

void MainWindow::on_pushButton_whait_clicked() {
  // Run in new thread and create a progress bar
  QProgressDialog *progress = createProgressDialog();
  progress->setWindowModality(Qt::WindowModal);
  ThreadedWorker::runInThread(ui->spinBox->value(), progress, this);
}
